// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Jungle/VineClimbActor.h"

#include "Components/BoxComponent.h"
#include "Sub/MyCharacter.h"

// Sets default values
AVineClimbActor::AVineClimbActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	ClimbBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ClimbBox"));
	ClimbBox->SetupAttachment(SceneRoot);

	ClimbBox->SetBoxExtent(FVector(160.f, 160.f, 500.f));
	ClimbBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ClimbBox->SetCollisionObjectType(ECC_WorldDynamic);
	ClimbBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	ClimbBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ClimbBox->SetGenerateOverlapEvents(true);
	ClimbBox->OnComponentBeginOverlap.AddDynamic(this, &AVineClimbActor::OnClimbBoxBeginOverlap);
	ClimbBox->OnComponentEndOverlap.AddDynamic(this, &AVineClimbActor::OnClimbBoxEndOverlap);

	VineStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VineStaticMesh"));
	VineStaticMesh->SetupAttachment(SceneRoot);
	VineStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VineStaticMesh->SetGenerateOverlapEvents(false);

#if WITH_EDITORONLY_DATA
	ClimbBox->ShapeColor = FColor::Green;
#endif
}


// Called when the game starts or when spawned
void AVineClimbActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVineClimbActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!VineStaticMesh || !VineStaticMesh->GetStaticMesh())
	{
		return;
	}

	FVector Min;
	FVector Max;
	VineStaticMesh->GetLocalBounds(Min, Max);

	const FVector MeshExtent = (Max - Min) * 0.5f;
	const FVector MeshCenter = (Min + Max) * 0.5f;
	const FVector MeshScale = VineStaticMesh->GetRelativeScale3D().GetAbs();

	ClimbBox->SetRelativeLocation(
		VineStaticMesh->GetRelativeLocation() + MeshCenter * MeshScale
	);

	ClimbBox->SetBoxExtent(FVector(
		FMath::Max(80.f, MeshExtent.X * MeshScale.X),
		FMath::Max(80.f, MeshExtent.Y * MeshScale.Y),
		MeshExtent.Z * MeshScale.Z
	));
}



void AVineClimbActor::OnClimbBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
	{
		Character->EnterVineClimb(this);
	}
}

void AVineClimbActor::OnClimbBoxEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
	{
		Character->ExitVineClimb(this);
	}
}

