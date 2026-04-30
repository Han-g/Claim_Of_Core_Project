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
	FVector Forward = OwnerCharacter->GetActorForwardVector();
	FVector Center = Start + Forward * Range;

	TArray<FOverlapResult> Overlaps;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(OwnerCharacter);
	Params.AddIgnoredActor(this);

	FCollisionShape Shape = FCollisionShape::MakeSphere(Radius);

	bool bHit = GetWorld()->OverlapMultiByChannel(
		Overlaps,
		Center,
		FQuat::Identity,
		ECC_Pawn,
		Shape,
		Params
	);

	if (!bHit) return;

	for (auto& Result : Overlaps)
	{
		AActor* Target = Result.GetActor();
		if (!Target) continue;

		ApplyDamage(Target);

		if (ACharacter* HitCharacter = Cast<ACharacter>(Target))
		{
			ApplyKnockback(HitCharacter);
		}

		OnHitTarget(Target);
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
