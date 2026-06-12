#include "BaseItem.h"

#include "Components/SphereComponent.h"

#include "Engine/EngineTypes.h"
#include "Engine/OverlapResult.h"
#include "Engine/World.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"

#include "Sub/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = false;

	PickupCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollision"));
	RootComponent = PickupCollision;

	PickupCollision->SetSphereRadius(150.f);
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnBeginOverlap);
	PickupCollision->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnEndOverlap);

}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItem::SetOwnerCharacter(AMyCharacter* NewOwner)
{
	OwnerCharacter = NewOwner;
}

void ABaseItem::OnBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OwnerCharacter) return; // 이미 소유자가 있으면 무시

	UE_LOG(LogTemp, Warning, TEXT("[Item] BeginOverlap with %s"), *GetNameSafe(OtherActor));

	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character)
	{
		Character->SetOverlappingItem(this);
	}

}

void ABaseItem::OnEndOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (OwnerCharacter) return; // 이미 소유자가 있으면 무시

	UE_LOG(LogTemp, Warning, TEXT("[Item] BeginOverlap with %s"), *GetNameSafe(OtherActor));

	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (Character)
	{
		Character->SetOverlappingItem(nullptr);
	}
}

UAnimMontage* ABaseItem::GetAttackMontageByRole(ERecRoleType InRole) const
{
	switch (InRole)
	{
	case ERecRoleType::Striker:     return StrikerMontage;
	case ERecRoleType::Guardian:    return GuardianMontage;
	case ERecRoleType::Manipulator: return ManipulatorMontage;
	default:                        return nullptr;
	}
}

FTransform ABaseItem::GetAttachOffsetByRole(ERecRoleType InRole) const
{
	switch (InRole)
	{
	case ERecRoleType::Striker:     return StrikerAttachOffset;
	case ERecRoleType::Guardian:    return GuardianAttachOffset;
	case ERecRoleType::Manipulator: return ManipulatorAttachOffset;
	default:                        return FTransform::Identity;
	}
}

void ABaseItem::StartUse()
{
	if (!OwnerCharacter) return;

	// 아이템 고유 동작 (상속 클래스에서 구현)
	OnStartUse();
}

void ABaseItem::DoHit()
{
	if (!OwnerCharacter) return;


	FVector Start = OwnerCharacter->GetActorLocation();
	Start.Z += 80.0f;

	const FVector Forward = OwnerCharacter->GetActorForwardVector();
	const FVector Center = Start + Forward * (Range * 0.5f);
	const FVector End = Start + Forward * Range;

	TArray<FHitResult> Hits;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(WeaponHitSweep), false);
	Params.AddIgnoredActor(OwnerCharacter);
	Params.AddIgnoredActor(this);

	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

	const FCollisionShape Shape = FCollisionShape::MakeSphere(Radius);

	const bool bHit = GetWorld()->SweepMultiByObjectType(
		Hits,
		Start,
		End,
		FQuat::Identity,
		ObjectParams,
		Shape,
		Params
	);

	/*TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);
	Params.AddIgnoredActor(this);

	FCollisionShape Shape = FCollisionShape::MakeSphere(Radius * 0.5f);


	bool bHit = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		Center,
		FQuat::Identity,
		ECC_Pawn,
		Shape,
		Params
	);*/

	/*DrawDebugSphere(
		GetWorld(),
		Center,
		Radius,
		24,
		bHit ? FColor::Green : FColor::Red,
		false,
		1.0f,
		0,
		2.0f
	);*/

	if (!bHit) { return; }

	for (const FHitResult& Hit : Hits)
	{
		AActor* Target = Hit.GetActor();
		if (!Target)
		{
			continue;
		}

		UE_LOG(LogTemp, Warning,
			TEXT("[ITEM_SWEEP_RAW] Target=%s Class=%s"),
			*GetNameSafe(Target),
			*GetNameSafe(Target->GetClass()));

		AMyCharacter* Victim = Cast<AMyCharacter>(Target);
		if (!Victim || Victim->IsDead())
		{
			UE_LOG(LogTemp, Warning,
				TEXT("[ITEM_SWEEP_SKIP] Target=%s Victim=%s IsDead=%d"),
				*GetNameSafe(Target),
				*GetNameSafe(Victim),
				Victim ? Victim->IsDead() : -1);
			continue;
		}

		OwnerCharacter->ReportAttackHitToServer(Victim);
		OnHitTarget(Target);

		/*DrawDebugPoint(
			GetWorld(),
			Hit.ImpactPoint,
			16.0f,
			FColor::Yellow,
			false,
			1.0f
		);*/
	}
}

void ABaseItem::ApplyDamage(AActor* Target)
{
	if (!Target) return;

	UGameplayStatics::ApplyDamage(
		Target,
		Damage,
		OwnerCharacter->GetController(),
		this,
		nullptr
	);
}

void ABaseItem::ApplyKnockback(ACharacter* Target)
{
	if (!Target) return;

	FVector Dir = Target->GetActorLocation() - OwnerCharacter->GetActorLocation();
	Dir.Z = 0.f;
	Dir.Normalize();

	FVector LaunchVel = Dir * KnockbackPower;
	LaunchVel.Z = 200.f;

	Target->LaunchCharacter(LaunchVel, true, true);
}

void ABaseItem::OnStartUse()
{
	if (!OwnerCharacter) return;

	const ERecRoleType CurrentRole = OwnerCharacter->GetRoleType();
	UAnimMontage* AttackMontage = GetAttackMontageByRole(CurrentRole);

	UAnimInstance* AnimInstance = OwnerCharacter->GetMesh() ? OwnerCharacter->GetMesh()->GetAnimInstance() : nullptr;
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("[Item] AnimInstance NULL"));
		return;
	}

	if (!AttackMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("[Item] Role montage NULL (Role=%d)"), (int32)CurrentRole);
		return;
	}

	if (AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Item] Montage already playing"));
		return;
	}

	AnimInstance->Montage_Play(AttackMontage);

}

void ABaseItem::OnHitTarget(AActor* Target)
{
	// 기본은 아무것도 안 함
}
