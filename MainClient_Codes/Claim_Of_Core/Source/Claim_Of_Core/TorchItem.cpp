#include "TorchItem.h"

#include "CollisionQueryParams.h"
#include "Engine/OverlapResult.h"
#include "Kismet/GameplayStatics.h"
#include "Sub/MyCharacter.h"

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
		TryStartThaw(Target);
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

void ATorchItem::TryStartThaw(AMyCharacter* Target)
{
	if (!IsValidThawTarget(Target))
	{
		return;
	}

	if (CurrentThawTarget != Target)
	{
		CurrentThawTarget = Target;
		ThawProgress = 0.f;
	}
}

void ATorchItem::UpdateThaw(float DeltaTime)
{
	if (!CurrentThawTarget)
	{
		return;
	}

	if (DeltaTime <= 0.f || !IsValidThawTarget(CurrentThawTarget))
	{
		CancelThaw();
		return;
	}

	ThawProgress += DeltaTime;
	if (ThawProgress >= ThawRequiredTime)
	{
		AMyCharacter* ThawedTarget = CurrentThawTarget;
		ThawedTarget->EndFreeze();
		BP_OnUnfreezeTarget(ThawedTarget);
		CancelThaw();
	}
}

void ATorchItem::CancelThaw()
{
	CurrentThawTarget = nullptr;
	ThawProgress = 0.f;
}

bool ATorchItem::IsValidThawTarget(AMyCharacter* Target) const
{
	return OwnerCharacter &&
		!OwnerCharacter->IsDead() &&
		Target &&
		!Target->IsDead() &&
		Target->IsFrozen() &&
		IsTargetInTorchRange(Target);
}

bool ATorchItem::IsTargetInTorchRange(AMyCharacter* Target) const
{
	if (!OwnerCharacter || !Target)
	{
		return false;
	}

	const FVector Center = OwnerCharacter->GetActorLocation() + OwnerCharacter->GetActorForwardVector() * Range;
	const float AllowedRange = Radius + ThawRangeBuffer;
	return FVector::DistSquared(Target->GetActorLocation(), Center) <= FMath::Square(AllowedRange);
}
