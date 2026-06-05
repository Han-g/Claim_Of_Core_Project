#include "CloudGrenadeItem.h"

#include "SkyCloudPlatform.h"
#include "Components/PrimitiveComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "../../Sub/MyCharacter.h"

ACloudGrenadeItem::ACloudGrenadeItem()
{
	CloudPlatformClass = ASkyCloudPlatform::StaticClass();

	Damage = 0.f;
	KnockbackPower = 0.f;
	Range = 0.f;
	Radius = 0.f;
}

void ACloudGrenadeItem::OnStartUse()
{
	if (!OwnerCharacter || !GetWorld() || bHasBeenThrown)
	{
		return;
	}

	AMyCharacter* Thrower = OwnerCharacter;
	const FVector Forward = Thrower->GetActorForwardVector().GetSafeNormal();
	const FVector ThrowLocation = Thrower->GetActorLocation() + Forward * ThrowSpawnForwardOffset + FVector::UpVector * ThrowSpawnUpOffset;

	Thrower->DropCurrentItem();

	bHasBeenThrown = true;
	SetActorLocation(ThrowLocation, false, nullptr, ETeleportType::TeleportPhysics);
	SetActorRotation(Forward.Rotation());

	UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(GetRootComponent());
	if (!Prim)
	{
		Destroy();
		return;
	}

	Prim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Prim->SetCollisionResponseToAllChannels(ECR_Block);
	Prim->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	Prim->SetSimulatePhysics(true);
	Prim->SetNotifyRigidBodyCollision(true);
	Prim->SetPhysicsLinearVelocity(Forward * ThrowSpeed + FVector::UpVector * ThrowUpwardSpeed);

	const float FuseTime = FMath::FRandRange(FuseTimeMin, FMath::Max(FuseTimeMin, FuseTimeMax));
	GetWorld()->GetTimerManager().SetTimer(FuseTimerHandle, this, &ACloudGrenadeItem::Explode, FuseTime, false);
}

void ACloudGrenadeItem::Explode()
{
	if (!bHasBeenThrown || bHasExploded)
	{
		return;
	}

	bHasExploded = true;
	SpawnCloudPlatform(GetActorLocation() + FVector::UpVector * CloudSpawnUpOffset);
	Destroy();
}

void ACloudGrenadeItem::SpawnCloudPlatform(const FVector& SpawnLocation)
{
	if (!GetWorld() || !CloudPlatformClass)
	{
		return;
	}

	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ASkyCloudPlatform* CloudPlatform = GetWorld()->SpawnActor<ASkyCloudPlatform>(
		CloudPlatformClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (!CloudPlatform)
	{
		return;
	}

	CloudPlatform->SetActorScale3D(CloudPlatformScale);

	if (CloudLifeSpan > 0.f)
	{
		CloudPlatform->SetLifeSpan(CloudLifeSpan);
	}
}
