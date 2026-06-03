#include "BlackHoleGrenadeItem.h"

#include "BlackHoleActor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "../../Sub/MyCharacter.h"

ABlackHoleGrenadeItem::ABlackHoleGrenadeItem()
{
	BlackHoleClass = ABlackHoleActor::StaticClass();

	Damage = 0.f;
	KnockbackPower = 0.f;
	Range = 0.f;
	Radius = 0.f;
}

void ABlackHoleGrenadeItem::OnStartUse()
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
	Prim->OnComponentHit.AddDynamic(this, &ABlackHoleGrenadeItem::OnGrenadeHit);
}

void ABlackHoleGrenadeItem::OnGrenadeHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	if (!bHasBeenThrown || bHasExploded || Hit.ImpactNormal.Z < GroundNormalThreshold)
	{
		return;
	}

	bHasExploded = true;
	SpawnGrenadeBlackHole(Hit);
	Destroy();
}

void ABlackHoleGrenadeItem::SpawnGrenadeBlackHole(const FHitResult& Hit)
{
	if (!GetWorld() || !BlackHoleClass)
	{
		return;
	}

	const FVector SpawnLocation = Hit.ImpactPoint + FVector::UpVector * 8.f;
	const FRotator SpawnRotation = FRotator::ZeroRotator;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ABlackHoleActor* BlackHole = GetWorld()->SpawnActor<ABlackHoleActor>(
		BlackHoleClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (!BlackHole)
	{
		return;
	}

	BlackHole->ConfigureBlackHole(
		GrenadePullStrength,
		GrenadePullRadius,
		GrenadeMinDistance,
		GrenadeMaxPullSpeed,
		bDrawGrenadeBlackHoleDebug,
		GrenadeBlackHoleScale
	);
	BlackHole->ShowBlackHole();
	BlackHole->ActivateBlackHole();
}
