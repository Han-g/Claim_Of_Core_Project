#include "SkyLiftBubble.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "NiagaraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "../../Sub/MyCharacter.h"

ASkyLiftBubble::ASkyLiftBubble()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	LiftCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LiftCollision"));
	SetRootComponent(LiftCollision);
	LiftCollision->SetSphereRadius(220.f);
	LiftCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LiftCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	LiftCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	LiftCollision->SetGenerateOverlapEvents(true);
	LiftCollision->OnComponentBeginOverlap.AddDynamic(this, &ASkyLiftBubble::OnBubbleBeginOverlap);
	LiftCollision->OnComponentEndOverlap.AddDynamic(this, &ASkyLiftBubble::OnBubbleEndOverlap);

	BubbleMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BubbleMesh"));
	BubbleMeshComponent->SetupAttachment(LiftCollision);
	BubbleMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BubbleMeshComponent->SetGenerateOverlapEvents(false);

	UpdraftCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("UpdraftCollision"));
	UpdraftCollision->SetupAttachment(LiftCollision);
	UpdraftCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UpdraftCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	UpdraftCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	UpdraftCollision->SetGenerateOverlapEvents(false);
	UpdraftCollision->OnComponentBeginOverlap.AddDynamic(this, &ASkyLiftBubble::OnBubbleBeginOverlap);
	UpdraftCollision->OnComponentEndOverlap.AddDynamic(this, &ASkyLiftBubble::OnBubbleEndOverlap);

	UpdraftEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("UpdraftEffect"));
	UpdraftEffectComponent->SetupAttachment(LiftCollision);
	UpdraftEffectComponent->SetAutoActivate(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (DefaultMesh.Succeeded())
	{
		BubbleMeshComponent->SetStaticMesh(DefaultMesh.Object);
		BubbleMeshComponent->SetRelativeScale3D(FVector(2.2f, 2.2f, 4.0f));
	}
}

void ASkyLiftBubble::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(TEXT("SkyLiftBubble"));
	ApplyVisualSettings();
	ApplyUpdraftCollisionSettings();
}

void ASkyLiftBubble::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bUpdraftActive || DeltaTime <= 0.f)
	{
		return;
	}

	ActiveElapsed += DeltaTime;
	ApplyUpdraft();

	if (ActiveElapsed >= ActiveDuration)
	{
		Destroy();
	}
}

void ASkyLiftBubble::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASkyLiftBubble, bConsumed);
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

	if (bUpdraftActive)
	{
		OverlappingCharacters.Add(Character);
		return;
	}

	if (!bConsumed && HasAuthority())
	{
		ConsumeBubble(Character);
	}
}

void ASkyLiftBubble::OnBubbleEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
	{
		OverlappingCharacters.Remove(Character);
	}
}

void ASkyLiftBubble::ConsumeBubble(AMyCharacter* Character)
{
	if (bConsumed || !Character || Character->IsDead())
	{
		return;
	}

	bConsumed = true;
	bUpdraftActive = true;
	ActiveElapsed = 0.f;
	OverlappingCharacters.Add(Character);

	ApplyConsumedVisual();
}

void ASkyLiftBubble::ApplyConsumedVisual()
{
	if (BubbleMeshComponent)
	{
		BubbleMeshComponent->SetHiddenInGame(true);
		BubbleMeshComponent->SetVisibility(false, true);
	}

	if (LiftCollision)
	{
		LiftCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LiftCollision->SetGenerateOverlapEvents(false);
	}

	if (UpdraftCollision)
	{
		UpdraftCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		UpdraftCollision->SetGenerateOverlapEvents(true);
	}

	if (UpdraftEffectComponent)
	{
		UpdraftEffectComponent->Activate(true);
	}
}

void ASkyLiftBubble::OnRep_Consumed()
{
	if (bConsumed)
	{
		ApplyConsumedVisual();
	}
}

void ASkyLiftBubble::ApplyUpdraft()
{
	for (auto It = OverlappingCharacters.CreateIterator(); It; ++It)
	{
		AMyCharacter* Character = It->Get();
		if (!Character || Character->IsDead())
		{
			It.RemoveCurrent();
			continue;
		}

		UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
		if (!MoveComp)
		{
			continue;
		}

		FVector Velocity = MoveComp->Velocity;
		Velocity.Z = FMath::Max(Velocity.Z, UpdraftSpeed);
		MoveComp->Velocity = Velocity;
	}
}

void ASkyLiftBubble::ApplyVisualSettings()
{
	if (BubbleMesh)
	{
		BubbleMeshComponent->SetStaticMesh(BubbleMesh);
	}

	if (BubbleMaterial)
	{
		BubbleMeshComponent->SetMaterial(0, BubbleMaterial);
	}

	if (UpdraftEffect && UpdraftEffectComponent)
	{
		UpdraftEffectComponent->SetAsset(UpdraftEffect);
	}

	if (UpdraftEffectComponent)
	{
		UpdraftEffectComponent->SetRelativeLocation(FVector::ZeroVector);
		UpdraftEffectComponent->Deactivate();
	}
}

void ASkyLiftBubble::ApplyUpdraftCollisionSettings()
{
	if (!UpdraftCollision)
	{
		return;
	}

	UpdraftCollision->SetCapsuleSize(UpdraftRadius, UpdraftHeight * 0.5f);
	UpdraftCollision->SetRelativeLocation(FVector(0.f, 0.f, UpdraftHeight * 0.5f));
}
