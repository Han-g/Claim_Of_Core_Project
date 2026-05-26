#include "IceChillSpawner.h"

#include "IceChillZone.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

AIceChillSpawner::AIceChillSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(Root);
	SpawnArea->SetBoxExtent(FVector(5000.f, 5000.f, 100.f));
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnArea->SetHiddenInGame(false);
}

void AIceChillSpawner::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameState();
	SpawnAccumulator = 0.f;
	NextSpawnTime = GetRandomSpawnInterval();
}

void AIceChillSpawner::Tick(float DeltaTime)
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
			FColor::Cyan,
			false,
			0.f,
			0,
			2.f
		);
	}
}

void AIceChillSpawner::InitializeGameState()
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

void AIceChillSpawner::UpdateSpawner(float DeltaTime)
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
		SpawnChillZones();
		NextSpawnTime = GetRandomSpawnInterval();
	}
}

void AIceChillSpawner::SpawnChillZones()
{
	if (!ChillZoneClass || !GetWorld())
	{
		return;
	}

	const int32 SpawnCount = GetRandomSpawnCount();
	for (int32 i = 0; i < SpawnCount; ++i)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorld()->SpawnActor<AIceChillZone>(
			ChillZoneClass,
			GetRandomSpawnLocation(),
			FRotator::ZeroRotator,
			SpawnParams
		);
	}
}

float AIceChillSpawner::GetRandomSpawnInterval() const
{
	if (!CachedGameState)
	{
		return Phase2MaxSpawnInterval;
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase3)
	{
		return FMath::FRandRange(Phase3MinSpawnInterval, Phase3MaxSpawnInterval);
	}

	return FMath::FRandRange(Phase2MinSpawnInterval, Phase2MaxSpawnInterval);
}

int32 AIceChillSpawner::GetRandomSpawnCount() const
{
	if (!CachedGameState)
	{
		return 0;
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase3)
	{
		return FMath::RandRange(Phase3MinSpawnCount, Phase3MaxSpawnCount);
	}

	return Phase2SpawnCount;
}

FVector AIceChillSpawner::GetRandomSpawnLocation() const
{
	if (!SpawnArea)
	{
		return GetActorLocation();
	}

	const FVector Center = SpawnArea->GetComponentLocation();
	const FVector Extent = SpawnArea->GetScaledBoxExtent();

	FVector SpawnLocation = Center;
	SpawnLocation.X += FMath::FRandRange(-Extent.X, Extent.X);
	SpawnLocation.Y += FMath::FRandRange(-Extent.Y, Extent.Y);
	SpawnLocation.Z = SpawnZ;

	return SpawnLocation;
}

bool AIceChillSpawner::CanSpawn() const
{
	if (!CachedGameState || !ChillZoneClass)
	{
		return false;
	}

	if (CachedGameState->RoundState != ERoundState::Playing)
	{
		return false;
	}

	return CachedGameState->CurrentPhase == EMapPhase::Phase2 ||
		CachedGameState->CurrentPhase == EMapPhase::Phase3;
}
