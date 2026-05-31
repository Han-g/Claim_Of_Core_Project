#include "TorchItem.h"

#include "CollisionQueryParams.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"
#include "../../Sub/MyCharacter.h"

ATorchItem::ATorchItem()
{
	PrimaryActorTick.bCanEverTick = true;

	Damage = 0.f;
	KnockbackPower = 200.f;
	Range = 220.f;
	Radius = 110.f;
}

void ATorchItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateBurns(DeltaTime);
	UpdateThaw(DeltaTime);
}

void ATorchItem::DoHit()
{
	if (!OwnerCharacter || OwnerCharacter->IsDead() || !GetWorld())
	{
		CancelThaw();
		return;
	}

	const FVector Center = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * Range;

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);
	Params.AddIgnoredActor(this);

	const FCollisionShape Shape = FCollisionShape::MakeSphere(Radius);
	const bool bHit = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		Center,
		FQuat::Identity,
		ECC_Pawn,
		Shape,
		Params
	);

	// COC_DEBUG_HITBOX Torch draw call
	DrawDebugHitBox(Center, Radius, bHit);

	if (!bHit)
	{
		return;
	}

	for (const FOverlapResult& Result : Overlaps)
	{
		AMyCharacter* Target = Cast<AMyCharacter>(Result.GetActor());
		if (!Target || Target->IsDead())
		{
			continue;
		}

		ApplyBurn(Target);
		BP_OnTorchHitTarget(Target);
	}
}

void ATorchItem::ApplyBurn(AMyCharacter* Target)
{
	if (!Target || Target->IsDead())
	{
		return;
	}

	FTorchBurnState& BurnState = ActiveBurns.FindOrAdd(Target);
	BurnState.RemainingTime = BurnDuration;
	if (BurnState.TimeUntilNextTick <= 0.f)
	{
		BurnState.TimeUntilNextTick = BurnTickInterval;
	}
}

void ATorchItem::UpdateBurns(float DeltaTime)
{
	if (DeltaTime <= 0.f || ActiveBurns.Num() == 0)
	{
		return;
	}

	for (auto It = ActiveBurns.CreateIterator(); It; ++It)
	{
		AMyCharacter* Target = It.Key();
		FTorchBurnState& BurnState = It.Value();

		if (!OwnerCharacter || OwnerCharacter->IsDead() || !Target || Target->IsDead())
		{
			It.RemoveCurrent();
			continue;
		}

		BurnState.TimeUntilNextTick -= DeltaTime;

		while (BurnState.RemainingTime > 0.f && BurnState.TimeUntilNextTick <= 0.f)
		{
			UGameplayStatics::ApplyDamage(
				Target,
				static_cast<float>(BurnDamagePerTick),
				OwnerCharacter->GetController(),
				this,
				nullptr
			);

			BurnState.TimeUntilNextTick += BurnTickInterval;
		}

		BurnState.RemainingTime -= DeltaTime;
		if (BurnState.RemainingTime <= 0.f)
		{
			It.RemoveCurrent();
		}
	}
}

void ATorchItem::UpdateThaw(float DeltaTime)
{
	if (DeltaTime <= 0.f)
	{
		return;
	}

	if (!OwnerCharacter || OwnerCharacter->IsDead())
	{
		CancelThaw();
		return;
	}

	TArray<AMyCharacter*> ThawTargets;
	CollectThawTargetsInRange(ThawTargets);

	TSet<AMyCharacter*> ThawTargetSet;
	for (AMyCharacter* Target : ThawTargets)
	{
		ThawTargetSet.Add(Target);
	}

	for (auto It = ActiveThawProgresses.CreateIterator(); It; ++It)
	{
		AMyCharacter* Target = It.Key();
		if (!ThawTargetSet.Contains(Target) || !IsValidThawTarget(Target))
		{
			It.RemoveCurrent();
		}
	}

	for (AMyCharacter* Target : ThawTargets)
	{
		if (!IsValidThawTarget(Target))
		{
			continue;
		}

		float& ThawProgress = ActiveThawProgresses.FindOrAdd(Target);
		ThawProgress += DeltaTime;

		if (ThawProgress >= ThawRequiredTime)
		{
			Target->EndFreeze();
			BP_OnUnfreezeTarget(Target);
			ActiveThawProgresses.Remove(Target);
		}
	}
}

void ATorchItem::CancelThaw()
{
	ActiveThawProgresses.Empty();
}

bool ATorchItem::IsValidThawTarget(AMyCharacter* Target) const
{
	return OwnerCharacter &&
		!OwnerCharacter->IsDead() &&
		Target &&
		!Target->IsDead() &&
		Target->IsFrozen();
}

void ATorchItem::CollectThawTargetsInRange(TArray<AMyCharacter*>& OutTargets) const
{
	OutTargets.Reset();

	if (!GetWorld())
	{
		return;
	}

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (OwnerCharacter)
	{
		Params.AddIgnoredActor(OwnerCharacter);
	}

	const bool bHit = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		GetActorLocation(),
		FQuat::Identity,
		ECC_Pawn,
		FCollisionShape::MakeSphere(ThawRadius),
		Params
	);

	if (!bHit)
	{
		return;
	}

	TSet<AMyCharacter*> UniqueTargets;

	for (const FOverlapResult& Result : Overlaps)
	{
		AMyCharacter* Target = Cast<AMyCharacter>(Result.GetActor());
		if (!IsValidThawTarget(Target))
		{
			continue;
		}

		if (!UniqueTargets.Contains(Target))
		{
			UniqueTargets.Add(Target);
			OutTargets.Add(Target);
		}
	}
}
