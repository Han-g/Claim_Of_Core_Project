#include "BaseItem.h"

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
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItem::SetOwnerCharacter(AMyCharacter* NewOwner)
{
	OwnerCharacter = NewOwner;
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
	// 기본은 아무것도 안 함
}

void ABaseItem::OnHitTarget(AActor* Target)
{
	// 기본은 아무것도 안 함
}
