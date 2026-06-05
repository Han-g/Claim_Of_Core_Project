#include "JungleOneShotGunItem.h"

#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "../../Sub/MyCharacter.h"

AJungleOneShotGunItem::AJungleOneShotGunItem()
{
	Damage = 0.f;
	KnockbackPower = 0.f;
	Range = 0.f;
	Radius = 0.f;
}

void AJungleOneShotGunItem::OnStartUse()
{
	if (!OwnerCharacter || bHasFired || !OwnerCharacter->IsAiming())
	{
		return;
	}

	bHasFired = true;
	FireHitscan();
	OwnerCharacter->ConsumeCurrentItem(this);
	Destroy();
}

void AJungleOneShotGunItem::FireHitscan()
{
	UCameraComponent* FollowCamera = OwnerCharacter ? OwnerCharacter->GetFollowCamera() : nullptr;
	UWorld* World = GetWorld();
	if (!OwnerCharacter || !FollowCamera || !World)
	{
		return;
	}

	const FVector TraceStart = FollowCamera->GetComponentLocation();
	const FVector TraceEnd = TraceStart + FollowCamera->GetForwardVector() * TraceDistance;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(JungleOneShotGunTrace), true);
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(OwnerCharacter);

	FHitResult BlockerHit;
	const bool bBlockerHit = World->LineTraceSingleByChannel(
		BlockerHit,
		TraceStart,
		TraceEnd,
		ECC_Visibility,
		Params
	);

	TArray<FHitResult> PawnHits;
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);
	World->SweepMultiByObjectType(
		PawnHits,
		TraceStart,
		TraceEnd,
		FQuat::Identity,
		ObjectParams,
		FCollisionShape::MakeSphere(HitSweepRadius),
		Params
	);

	AMyCharacter* TargetCharacter = nullptr;
	FHitResult TargetHit;
	for (const FHitResult& PawnHit : PawnHits)
	{
		AMyCharacter* HitCharacter = Cast<AMyCharacter>(PawnHit.GetActor());
		if (!HitCharacter || HitCharacter->IsDead() || OwnerCharacter->IsSameTeam(HitCharacter))
		{
			continue;
		}

		TargetCharacter = HitCharacter;
		TargetHit = PawnHit;
		break;
	}

	const bool bTargetBlocked = TargetCharacter &&
		bBlockerHit &&
		BlockerHit.Distance < TargetHit.Distance &&
		BlockerHit.GetActor() != TargetCharacter;

	if (bDrawDebugTrace)
	{
		DrawDebugLine(
			World,
			TraceStart,
			bBlockerHit ? BlockerHit.ImpactPoint : TraceEnd,
			bBlockerHit ? FColor::Green : FColor::Red,
			false,
			1.5f,
			0,
			2.f
		);

		if (bBlockerHit)
		{
			DrawDebugSphere(
				World,
				BlockerHit.ImpactPoint,
				18.f,
				12,
				FColor::Yellow,
				false,
				1.5f,
				0,
				2.f
			);
		}

		if (TargetCharacter)
		{
			DrawDebugSphere(
				World,
				TargetHit.ImpactPoint,
				HitSweepRadius,
				16,
				bTargetBlocked ? FColor::Orange : FColor::Cyan,
				false,
				1.5f,
				0,
				2.f
			);
		}
	}

	if (!bBlockerHit && !TargetCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("[JungleOneShotGun] Trace missed"));
		return;
	}

	UE_LOG(
		LogTemp,
		Warning,
		TEXT("[JungleOneShotGun] Blocker=%s Target=%s Blocked=%s"),
		*GetNameSafe(bBlockerHit ? BlockerHit.GetActor() : nullptr),
		*GetNameSafe(TargetCharacter),
		bTargetBlocked ? TEXT("true") : TEXT("false")
	);

	if (!TargetCharacter || bTargetBlocked)
	{
		return;
	}

	TargetCharacter->ApplyDamage(GunDamage);
}
