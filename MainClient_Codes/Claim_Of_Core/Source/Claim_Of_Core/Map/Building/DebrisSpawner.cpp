#include "DebrisSpawner.h"

#include "SmallDebrisActor.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

ADebrisSpawner::ADebrisSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(Root);
	SpawnArea->SetBoxExtent(FVector(500.f, 500.f, 100.f));
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnArea->SetHiddenInGame(false);
}

void ADebrisSpawner::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameState();
	SpawnAccumulator = 0.f;
	NextSpawnTime = GetRandomSpawnInterval();
}

void ADebrisSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InitializeGameState();
	UpdateSpawner(DeltaTime);

	if (bDrawDebugBox && SpawnArea)
	{
		DrawDebugBox(
			GetWorld(),
			SpawnArea->GetComponentLocation(),
			SpawnArea->GetScaledBoxExtent(),
			SpawnArea->GetComponentQuat(),
			FColor::Red,
			false,
			0.f,
			0,
			2.f
		);
	}
}

void ADebrisSpawner::InitializeGameState()
{
	if (CachedGameState)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		CachedGameState = World->GetGameState<AInGame_GameState>();
	}
}

void ADebrisSpawner::UpdateSpawner(float DeltaTime)
{
	if (!CanSpawn())
	{
		SpawnAccumulator = 0.f;
		return;
	}

	SpawnAccumulator += DeltaTime;

	if (SpawnAccumulator >= NextSpawnTime)
	{
		SpawnAccumulator = 0.f;
		SpawnDebrisByCurrentPhase();
		NextSpawnTime = GetRandomSpawnInterval();

		UE_LOG(LogTemp, Warning, TEXT("[DebrisSpawner] Next Spawn Time: %.2f"), NextSpawnTime);
	}
}

void ADebrisSpawner::SpawnDebrisByCurrentPhase()
{
	if (!DebrisClass || !GetWorld())
	{
		return;
	}

	const int32 SpawnCount = GetRandomSpawnCount();

	for (int32 i = 0; i < SpawnCount; ++i)
	{
		const FVector SpawnLocation = GetRandomSpawnLocation();
		const FRotator SpawnRotation = FRotator::ZeroRotator;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ASmallDebrisActor* SpawnedDebris = GetWorld()->SpawnActor<ASmallDebrisActor>(
			DebrisClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);

		if (SpawnedDebris)
		{
			UE_LOG(LogTemp, Warning, TEXT("[DebrisSpawner] Spawned SmallDebris: %s"), *SpawnedDebris->GetName());
		}
	}
}

float ADebrisSpawner::GetRandomSpawnInterval() const
{
	if (!CachedGameState)
	{
		return 5.f;
	}

	switch (CachedGameState->CurrentPhase)
	{
	case EMapPhase::Phase1:
		return FMath::FRandRange(Phase1MinSpawnInterval, Phase1MaxSpawnInterval);

	case EMapPhase::Phase2:
		return FMath::FRandRange(Phase2MinSpawnInterval, Phase2MaxSpawnInterval);

	case EMapPhase::Phase3:
		return FMath::FRandRange(Phase3MinSpawnInterval, Phase3MaxSpawnInterval);

	default:
		return 5.f;
	}
}

int32 ADebrisSpawner::GetRandomSpawnCount() const
{
	if (!CachedGameState)
	{
		return 0;
	}

	switch (CachedGameState->CurrentPhase)
	{
	case EMapPhase::Phase1:
		return FMath::RandRange(Phase1MinSpawnCount, Phase1MaxSpawnCount);

	case EMapPhase::Phase2:
		return FMath::RandRange(Phase2MinSpawnCount, Phase2MaxSpawnCount);

	case EMapPhase::Phase3:
		return FMath::RandRange(Phase3MinSpawnCount, Phase3MaxSpawnCount);

	default:
		return 0;
	}
}

FVector ADebrisSpawner::GetRandomSpawnLocation() const
{
	if (!SpawnArea)
	{
		return GetActorLocation();
	}

	const FVector Center = SpawnArea->GetComponentLocation();
	const FVector Extent = SpawnArea->GetScaledBoxExtent();

	const float RandomX = FMath::FRandRange(-Extent.X, Extent.X);
	const float RandomY = FMath::FRandRange(-Extent.Y, Extent.Y);
	const float RandomZ = FMath::FRandRange(0.f, RandomHeightOffset);

	FVector SpawnLocation = Center;
	SpawnLocation.X += RandomX;
	SpawnLocation.Y += RandomY;
	SpawnLocation.Z += Extent.Z + SpawnHeightOffset + RandomZ;

	return SpawnLocation;
}

bool ADebrisSpawner::CanSpawn() const
{
	if (!CachedGameState || !DebrisClass)
	{
		return false;
	}

	if (CachedGameState->RoundState != ERoundState::Playing)
	{
		return false;
	}

	switch (CachedGameState->CurrentPhase)
	{
	case EMapPhase::Phase1:
	case EMapPhase::Phase2:
	case EMapPhase::Phase3:
		return true;

	default:
		return false;
	}
}

#if WITH_EDITOR
void ADebrisSpawner::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
#endif