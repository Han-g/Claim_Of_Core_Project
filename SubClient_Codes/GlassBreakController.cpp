#include "GlassBreakController.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AGlassBreakController::AGlassBreakController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGlassBreakController::BeginPlay()
{
	Super::BeginPlay();

	FindGlassActorsByTag();
	FreezeGlassActors();

	GetWorldTimerManager().SetTimer(
		BreakTimerHandle,
		this,
		&AGlassBreakController::BreakGlassActors,
		BreakStartTime,
		false
	);

	UE_LOG(LogTemp, Warning, TEXT("[GlassBreakController] Found Glass Count: %d"), FoundGlassActors.Num());
	UE_LOG(LogTemp, Warning, TEXT("[GlassBreakController] Glass will break after %.1f seconds."), BreakStartTime);
}

void AGlassBreakController::FindGlassActorsByTag()
{
	FoundGlassActors.Empty();

	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), GlassTag, TaggedActors);

	for (AActor* Actor : TaggedActors)
	{
		if (IsValid(Actor))
		{
			FoundGlassActors.Add(Actor);
		}
	}
}

void AGlassBreakController::FreezeGlassActors()
{
	for (AActor* Actor : FoundGlassActors)
	{
		if (!IsValid(Actor))
		{
			continue;
		}

		UStaticMeshComponent* Mesh = GetStaticMeshComponentFromActor(Actor);

		if (!IsValid(Mesh))
		{
			continue;
		}

		Mesh->SetMobility(EComponentMobility::Movable);

		Mesh->SetSimulatePhysics(false);
		Mesh->SetEnableGravity(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->SetCollisionObjectType(ECC_WorldDynamic);

		Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Mesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

		UE_LOG(LogTemp, Warning, TEXT("[GlassBreakController] Frozen: %s"), *Actor->GetName());
	}
}

void AGlassBreakController::BreakGlassActors()
{
	UE_LOG(LogTemp, Warning, TEXT("[GlassBreakController] BreakGlassActors called."));

	for (AActor* Actor : FoundGlassActors)
	{
		if (!IsValid(Actor))
		{
			continue;
		}

		UStaticMeshComponent* Mesh = GetStaticMeshComponentFromActor(Actor);

		if (!IsValid(Mesh))
		{
			continue;
		}

		Mesh->SetMobility(EComponentMobility::Movable);

		Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Mesh->SetSimulatePhysics(true);
		Mesh->SetEnableGravity(bUseGravityAfterBreak);
		Mesh->WakeAllRigidBodies();

		const FVector RandomDirection = FVector(
			FMath::RandRange(-1.0f, 1.0f),
			FMath::RandRange(-1.0f, 1.0f),
			0.0f
		).GetSafeNormal();

		const FVector FinalImpulse =
			(RandomDirection * BreakImpulseStrength) +
			(FVector::UpVector * UpImpulseStrength);

		Mesh->AddImpulse(FinalImpulse, NAME_None, true);

		UE_LOG(LogTemp, Warning, TEXT("[GlassBreakController] Broken: %s"), *Actor->GetName());
	}
}

UStaticMeshComponent* AGlassBreakController::GetStaticMeshComponentFromActor(AActor* Actor) const
{
	if (!IsValid(Actor))
	{
		return nullptr;
	}

	return Actor->FindComponentByClass<UStaticMeshComponent>();
}
