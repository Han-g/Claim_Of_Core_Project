#include "UmbrellaItem.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Sub/MyCharacter.h"

AUmbrellaItem::AUmbrellaItem()
{
	PrimaryActorTick.bCanEverTick = false;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MaxDurability = 3;
	CurrentDurability = 3;
	OpenedMoveSpeedMultiplier = 0.85f;
	ClosedDamage = 12.f;
	ClosedKnockbackPower = 400.f;
	GuardedDamageMultiplier = 0.3f;
}

void AUmbrellaItem::BeginPlay()
{
	Super::BeginPlay();

	CurrentDurability = MaxDurability;
	CurrentMode = EUmbrellaMode::Closed;
	UpdateAttackStat();
}

void AUmbrellaItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUmbrellaItem::StartUse()
{
	if (!OwnerCharacter || IsBroken())
	{
		return;
	}

	ToggleUmbrella();
}

void AUmbrellaItem::OnStartUse()
{
	// 사용 안 함
}

void AUmbrellaItem::DoHit()
{
	if (!OwnerCharacter || IsBroken())
	{
		return;
	}

	if (CurrentMode == EUmbrellaMode::Opened)
	{
		return;
	}

	Super::DoHit();
}

void AUmbrellaItem::OnHitTarget(AActor* Target)
{
	UE_LOG(LogTemp, Log, TEXT("[Umbrella] Hit Target: %s"), *GetNameSafe(Target));
}

void AUmbrellaItem::OpenUmbrella()
{
	if (!OwnerCharacter || IsBroken() || CurrentMode == EUmbrellaMode::Opened)
	{
		return;
	}

	CurrentMode = EUmbrellaMode::Opened;
	UpdateAttackStat();

	if (UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement())
	{
		if (!bSpeedModified)
		{
			CachedOriginalWalkSpeed = MoveComp->MaxWalkSpeed;
			MoveComp->MaxWalkSpeed = CachedOriginalWalkSpeed * OpenedMoveSpeedMultiplier;
			bSpeedModified = true;
		}
	}

	OwnerCharacter->SetUmbrellaGuardActive(true);

	UE_LOG(LogTemp, Warning, TEXT("[Umbrella] Opened"));
}

void AUmbrellaItem::CloseUmbrella()
{
	if (!OwnerCharacter || IsBroken() || CurrentMode == EUmbrellaMode::Closed)
	{
		return;
	}

	CurrentMode = EUmbrellaMode::Closed;
	UpdateAttackStat();

	if (UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement())
	{
		if (bSpeedModified)
		{
			MoveComp->MaxWalkSpeed = CachedOriginalWalkSpeed;
			bSpeedModified = false;
		}
	}

	OwnerCharacter->SetUmbrellaGuardActive(false);

	UE_LOG(LogTemp, Warning, TEXT("[Umbrella] Closed"));
}

void AUmbrellaItem::ToggleUmbrella()
{
	if (CurrentMode == EUmbrellaMode::Closed)
	{
		OpenUmbrella();
	}
	else if (CurrentMode == EUmbrellaMode::Opened)
	{
		CloseUmbrella();
	}
}

bool AUmbrellaItem::CanGuard() const
{
	return OwnerCharacter
		&& CurrentMode == EUmbrellaMode::Opened
		&& CurrentDurability > 0
		&& !OwnerCharacter->IsDead();
}

void AUmbrellaItem::HandleGuardHit(AActor* DamageCauser, float IncomingDamage)
{
	if (!CanGuard())
	{
		return;
	}

	CurrentDurability = FMath::Max(0, CurrentDurability - 1);

	const float ReducedDamage = IncomingDamage * GuardedDamageMultiplier;
	OwnerCharacter->ApplyDamage(FMath::RoundToInt(ReducedDamage));

	UE_LOG(LogTemp, Warning,
		TEXT("[Umbrella] Guard Success / Durability: %d / Damage: %.1f"),
		CurrentDurability,
		ReducedDamage);

	if (CurrentDurability <= 0)
	{
		BreakUmbrella();
	}
}

void AUmbrellaItem::BreakUmbrella()
{
	if (IsBroken())
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("[Umbrella] Broken"));

	if (OwnerCharacter)
	{
		OwnerCharacter->SetUmbrellaGuardActive(false);

		if (UCharacterMovementComponent* MoveComp = OwnerCharacter->GetCharacterMovement())
		{
			if (bSpeedModified)
			{
				MoveComp->MaxWalkSpeed = CachedOriginalWalkSpeed;
				bSpeedModified = false;
			}
		}
	}

	CurrentMode = EUmbrellaMode::Broken;

	AMyCharacter* CachedOwnerCharacter = OwnerCharacter;

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SetActorEnableCollision(false);

	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(GetRootComponent()))
	{
		Prim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Prim->SetSimulatePhysics(false);
	}

	SetOwnerCharacter(nullptr);

	if (CachedOwnerCharacter)
	{
		CachedOwnerCharacter->ClearCurrentItemReference(this);
	}

	Destroy();
}
void AUmbrellaItem::OnGuardBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!CanGuard() || !OtherActor)
	{
		return;
	}

	if (!IsFallingDebrisActor(OtherActor))
	{
		return;
	}

	HandleGuardHit(OtherActor, 30.f);
}

void AUmbrellaItem::UpdateAttackStat()
{
	if (CurrentMode == EUmbrellaMode::Closed)
	{
		Damage = ClosedDamage;
		KnockbackPower = ClosedKnockbackPower;
	}
	else
	{
		Damage = 0.f;
		KnockbackPower = 0.f;
	}
}

bool AUmbrellaItem::IsFallingDebrisActor(AActor* OtherActor) const
{
	return OtherActor && OtherActor->ActorHasTag(TEXT("FallingDebris"));
}