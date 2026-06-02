#include "SkyLiftBubble.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "../../Sub/MyCharacter.h"

ASkyLiftBubble::ASkyLiftBubble()
{
	PrimaryActorTick.bCanEverTick = false;

	LiftCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LiftCollision"));
	SetRootComponent(LiftCollision);
	LiftCollision->SetSphereRadius(90.f);
	LiftCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LiftCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	LiftCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LiftCollision->SetGenerateOverlapEvents(true);
	LiftCollision->OnComponentBeginOverlap.AddDynamic(this, &ASkyLiftBubble::OnBubbleBeginOverlap);

	BubbleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BubbleMesh"));
	BubbleMeshComponent->SetupAttachment(LiftCollision);
	BubbleMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BubbleMeshComponent->SetGenerateOverlapEvents(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (DefaultMesh.Succeeded())
	{
		BubbleMeshComponent->SetStaticMesh(DefaultMesh.Object);
		BubbleMeshComponent->SetRelativeScale3D(FVector(1.8f));
	}
}

void ASkyLiftBubble::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(TEXT("SkyLiftBubble"));
	ApplyVisualSettings();

	if (LifeTime > 0.f)
	{
		SetLifeSpan(LifeTime);
	}
}

void ASkyLiftBubble::OnBubbleBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (!Character || Character->IsDead())
	{
		return;
	}

	Character->LaunchCharacter(FVector(0.f, 0.f, LaunchStrength), false, true);

	if (bDestroyOnUse)
	{
		Destroy();
	}
}

void ASkyLiftBubble::ApplyVisualSettings()
{
	if (!BubbleMeshComponent)
	{
		return;
	}

	if (BubbleMesh)
	{
		BubbleMeshComponent->SetStaticMesh(BubbleMesh);
	}

	if (BubbleMaterial)
	{
		BubbleMeshComponent->SetMaterial(0, BubbleMaterial);
	}
}
