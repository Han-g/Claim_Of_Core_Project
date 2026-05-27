#include "IceChillZone.h"

#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "TimerManager.h"
#include "../../Sub/MyCharacter.h"

AIceChillZone::AIceChillZone()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ChillCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ChillCollision"));
	ChillCollision->SetupAttachment(Root);
	ChillCollision->SetSphereRadius(Radius);
	ChillCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ChillCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	ChillCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ChillCollision->SetGenerateOverlapEvents(true);
	ChillCollision->OnComponentBeginOverlap.AddDynamic(this, &AIceChillZone::OnChillBeginOverlap);
	ChillCollision->OnComponentEndOverlap.AddDynamic(this, &AIceChillZone::OnChillEndOverlap);

	ChillMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChillMesh"));
	ChillMeshComponent->SetupAttachment(Root);
	ChillMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ChillMeshComponent->SetGenerateOverlapEvents(false);

	ChillDecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("ChillDecal"));
	ChillDecalComponent->SetupAttachment(Root);
	ChillDecalComponent->DecalSize = FVector(128.f, Radius, Radius);

	ChillEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ChillEffect"));
	ChillEffectComponent->SetupAttachment(Root);
	ChillEffectComponent->SetAutoActivate(true);
}

void AIceChillZone::BeginPlay()
{
	Super::BeginPlay();

	ApplyVisualSettings();

	if (ZoneLifeTime > 0.f)
	{
		SetLifeSpan(ZoneLifeTime);
	}
}

void AIceChillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bApplyFreezeLocally || DeltaTime <= 0.f)
	{
		return;
	}

	for (auto It = CharacterStayTimes.CreateIterator(); It; ++It)
	{
		AMyCharacter* Character = It.Key().Get();
		if (!IsValid(Character) || Character->IsDead())
		{
			It.RemoveCurrent();
			continue;
		}

		It.Value() += DeltaTime;
		if (It.Value() >= FreezeBuildUpTime)
		{
			ApplyFreezeToCharacter(Character);
			It.RemoveCurrent();
		}
	}
}

void AIceChillZone::OnChillBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (!IsValid(Character) || Character->IsDead())
	{
		return;
	}

	CharacterStayTimes.FindOrAdd(Character) = 0.f;
}

void AIceChillZone::OnChillEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
	{
		CharacterStayTimes.Remove(Character);
	}
}

void AIceChillZone::ApplyVisualSettings()
{
	if (ChillCollision)
	{
		ChillCollision->SetSphereRadius(Radius);
	}

	if (ChillMeshComponent)
	{
		if (ChillMesh)
		{
			ChillMeshComponent->SetStaticMesh(ChillMesh);
		}

		if (ChillMeshMaterial)
		{
			ChillMeshComponent->SetMaterial(0, ChillMeshMaterial);
		}
	}

	if (ChillDecalComponent)
	{
		ChillDecalComponent->DecalSize = FVector(128.f, Radius, Radius);
		if (ChillDecalMaterial)
		{
			ChillDecalComponent->SetDecalMaterial(ChillDecalMaterial);
		}
	}

	if (ChillEffectComponent && ChillVisualEffect)
	{
		ChillEffectComponent->SetAsset(ChillVisualEffect);
	}
}

void AIceChillZone::ApplyFreezeToCharacter(AMyCharacter* Character)
{
	if (!IsValid(Character) || Character->IsDead())
	{
		return;
	}

	if (!Character->CanReceiveStatusEffect(ERecStatusEffectType::Freeze))
	{
		return;
	}

	Character->ApplyFreeze();

	/*UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
	if (!MoveComp)
	{
		return;
	}

	const float SavedMaxWalkSpeed = MoveComp->MaxWalkSpeed;
	const EMovementMode SavedMovementMode = MoveComp->MovementMode;
	const TWeakObjectPtr<AMyCharacter> WeakCharacter(Character);

	MoveComp->StopMovementImmediately();
	MoveComp->DisableMovement();

	if (UWorld* World = GetWorld())
	{
		FTimerHandle RestoreHandle;
		World->GetTimerManager().SetTimer(
			RestoreHandle,
			FTimerDelegate::CreateLambda(
				[WeakCharacter, SavedMovementMode, SavedMaxWalkSpeed]()
				{
					AMyCharacter* RestoredCharacter = WeakCharacter.Get();
					if (!IsValid(RestoredCharacter) || RestoredCharacter->IsDead())
					{
						return;
					}

					if (UCharacterMovementComponent* RestoredMoveComp = RestoredCharacter->GetCharacterMovement())
					{
						const EMovementMode RestoreMode =
							SavedMovementMode == MOVE_None ? MOVE_Walking : SavedMovementMode;

						RestoredMoveComp->SetMovementMode(RestoreMode);
						RestoredMoveComp->MaxWalkSpeed = SavedMaxWalkSpeed;
					}
				}),
			FMath::Max(0.01f, FreezeDuration),
			false
		);
	}*/
}
