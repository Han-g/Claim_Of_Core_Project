#include "LargeDebrisActor.h"

#include "Components/StaticMeshComponent.h"

ALargeDebrisActor::ALargeDebrisActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(Root);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	MeshComp->SetSimulatePhysics(false);
	MeshComp->SetEnableGravity(true);
	MeshComp->SetNotifyRigidBodyCollision(true);

	SetActorHiddenInGame(true);
}

void ALargeDebrisActor::BeginPlay()
{
	Super::BeginPlay();

	if (MeshComp)
	{
		MeshComp->OnComponentHit.AddDynamic(this, &ALargeDebrisActor::OnDebrisHit);
	}
}

void ALargeDebrisActor::PrepareDebris()
{
	bActivated = false;
	bLanded = false;

	if (!MeshComp)
	{
		return;
	}

	MeshComp->SetSimulatePhysics(false);
	MeshComp->SetEnableGravity(true);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
}

void ALargeDebrisActor::ActivateDebris(float InitialImpulseStrength)
{
	if (!MeshComp || bActivated)
	{
		return;
	}

	bActivated = true;

	MeshComp->SetSimulatePhysics(true);
	MeshComp->WakeAllRigidBodies();

	if (InitialImpulseStrength > 0.f)
	{
		const FVector RandomDir = FVector(
			FMath::FRandRange(-1.f, 1.f),
			FMath::FRandRange(-1.f, 1.f),
			-0.2f
		).GetSafeNormal();

		MeshComp->AddImpulse(RandomDir * InitialImpulseStrength, NAME_None, true);
	}

	UE_LOG(LogTemp, Warning, TEXT("[LargeDebrisActor] Activated: %s"), *GetName());

	BP_OnDebrisActivated();
}

void ALargeDebrisActor::OnDebrisHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (!bActivated || bLanded)
	{
		return;
	}

	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	const float CurrentSpeed = MeshComp ? MeshComp->GetComponentVelocity().Size() : 0.f;

	if (CurrentSpeed < MinImpactSpeedToLand)
	{
		return;
	}

	bLanded = true;

	UE_LOG(LogTemp, Warning, TEXT("[LargeDebrisActor] Landed: %s, HitActor: %s"), *GetName(), *OtherActor->GetName());

	if (bFreezeAfterLanding)
	{
		FreezeDebris();
	}

	BP_OnDebrisLanded();
}

void ALargeDebrisActor::FreezeDebris()
{
	if (!MeshComp)
	{
		return;
	}

	MeshComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
	MeshComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
	MeshComp->SetSimulatePhysics(false);
	MeshComp->SetEnableGravity(false);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}