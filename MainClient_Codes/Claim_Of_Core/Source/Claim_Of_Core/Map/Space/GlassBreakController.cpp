// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Space/GlassBreakController.h"

#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGlassBreakController::AGlassBreakController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGlassBreakController::BeginPlay()
{
	Super::BeginPlay();

	FindGlassActorsByTag();

	for (AActor* Actor : FoundGlassActors)
	{
		UStaticMeshComponent* Mesh = GetStaticMeshComponentFromActor(Actor);
		if (!IsValid(Mesh))
		{
			continue;
		}

		Mesh->SetSimulatePhysics(false);
		Mesh->SetEnableGravity(false);
		Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UE_LOG(LogTemp, Warning,
		TEXT("[GlassBreakController] Temporarily disabled glass actors. Count=%d"),
		FoundGlassActors.Num());

	return;

	//PrepareGlassActors();
}


void AGlassBreakController::PrepareGlassActors()
{
	FindGlassActorsByTag();
	BrokenGlassTags.Empty();

	for (AActor* Actor : FoundGlassActors)
	{
		FreezeGlassActor(Actor);
	}

	UE_LOG(LogTemp, Warning,
		TEXT("[GlassBreakController] Prepared Glass Count: %d"),
		FoundGlassActors.Num());
}

void AGlassBreakController::ResetGlassActors()
{
	if (FoundGlassActors.Num() == 0 || InitialGlassTransforms.Num() == 0)
	{
		PrepareGlassActors();
		return;
	}

	BrokenGlassTags.Empty();

	for (AActor* Actor : FoundGlassActors)
	{
		if (!IsValid(Actor))
		{
			continue;
		}

		if (const FTransform* InitialTransform = InitialGlassTransforms.Find(TObjectKey<AActor>(Actor)))
		{
			Actor->SetActorTransform(*InitialTransform, false, nullptr, ETeleportType::TeleportPhysics);
		}

		FreezeGlassActor(Actor);
	}
}

void AGlassBreakController::BreakPhase2GlassActors()
{
	BreakGlassActorsByTag(Phase2GlassTag);
}

void AGlassBreakController::BreakPhase3GlassActors()
{
	BreakGlassActorsByTag(Phase3GlassTagA);
	BreakGlassActorsByTag(Phase3GlassTagB);
}

void AGlassBreakController::BreakGlassActorsByTag(FName TargetGlassTag)
{
	if (TargetGlassTag.IsNone() || BrokenGlassTags.Contains(TargetGlassTag))
	{
		return;
	}

	TArray<TWeakObjectPtr<AActor>>* GlassActors = GlassActorsByTag.Find(TargetGlassTag);

	if (!GlassActors)
	{
		FindGlassActorsByTag();
		GlassActors = GlassActorsByTag.Find(TargetGlassTag);
	}

	if (!GlassActors || GlassActors->Num() == 0)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[GlassBreakController] No glass actors found. Tag=%s"),
			*TargetGlassTag.ToString());
		return;
	}

	BrokenGlassTags.Add(TargetGlassTag);

	for (const TWeakObjectPtr<AActor>& ActorPtr : *GlassActors)
	{
		if (AActor* Actor = ActorPtr.Get())
		{
			BreakGlassActor(Actor);
		}
	}

	UE_LOG(LogTemp, Warning,
		TEXT("[GlassBreakController] Broken Glass Tag=%s Count=%d"),
		*TargetGlassTag.ToString(),
		GlassActors->Num());
}

void AGlassBreakController::FindGlassActorsByTag()
{
	FoundGlassActors.Empty();
	GlassActorsByTag.Empty();
	InitialGlassTransforms.Empty();

	TArray<FName> GlassTagList;
	GlassTagList.AddUnique(Phase2GlassTag);
	GlassTagList.AddUnique(Phase3GlassTagA);
	GlassTagList.AddUnique(Phase3GlassTagB);

	for (const FName& Tag : GlassTagList)
	{
		if (Tag.IsNone())
		{
			continue;
		}

		TArray<AActor*> TaggedActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), Tag, TaggedActors);

		TArray<TWeakObjectPtr<AActor>>& Group = GlassActorsByTag.FindOrAdd(Tag);

		for (AActor* Actor : TaggedActors)
		{
			if (!IsValid(Actor))
			{
				continue;
			}

			Group.Add(Actor);
			FoundGlassActors.AddUnique(Actor);
			InitialGlassTransforms.FindOrAdd(TObjectKey<AActor>(Actor), Actor->GetActorTransform());
		}
	}
}

void AGlassBreakController::FreezeGlassActor(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return;
	}

	UStaticMeshComponent* Mesh = GetStaticMeshComponentFromActor(Actor);
	if (!IsValid(Mesh))
	{
		return;
	}

	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetSimulatePhysics(false);
	Mesh->SetEnableGravity(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);

	Mesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	Mesh->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
}

void AGlassBreakController::BreakGlassActor(AActor* Actor)
{
	if (!IsValid(Actor))
	{
		return;
	}

	UStaticMeshComponent* Mesh = GetStaticMeshComponentFromActor(Actor);
	if (!IsValid(Mesh))
	{
		return;
	}

	Mesh->SetMobility(EComponentMobility::Movable);
	Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);

	if (bIgnorePawnCollisionAfterBreak)
	{
		Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	}

	Mesh->SetSimulatePhysics(true);
	Mesh->SetEnableGravity(bUseGravityAfterBreak);
	Mesh->WakeAllRigidBodies();

	const FVector BreakOrigin = bUseControllerLocationAsBreakOrigin
		? GetActorLocation()
		: BreakOriginLocation;

	FVector OutwardDirection = Mesh->GetComponentLocation() - BreakOrigin;
	OutwardDirection.Z = 0.f;
	OutwardDirection = OutwardDirection.GetSafeNormal();

	if (OutwardDirection.IsNearlyZero())
	{
		OutwardDirection = Actor->GetActorForwardVector();
	}

	const FVector RandomSpread(
		FMath::RandRange(-1.0f, 1.0f),
		FMath::RandRange(-1.0f, 1.0f),
		FMath::RandRange(-0.2f, 0.5f)
	);

	const FVector FinalDirection =
		(OutwardDirection + RandomSpread * BreakRandomSpreadStrength).GetSafeNormal();

	const FVector FinalImpulse =
		(FinalDirection * BreakImpulseStrength) +
		(FVector::UpVector * UpImpulseStrength);

	Mesh->AddImpulse(FinalImpulse, NAME_None, true);
}

UStaticMeshComponent* AGlassBreakController::GetStaticMeshComponentFromActor(AActor* Actor) const
{
	if (!IsValid(Actor))
	{
		return nullptr;
	}

	return Actor->FindComponentByClass<UStaticMeshComponent>();
}