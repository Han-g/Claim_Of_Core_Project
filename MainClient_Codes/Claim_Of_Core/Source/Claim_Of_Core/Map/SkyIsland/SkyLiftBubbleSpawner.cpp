#include "SkyLiftBubbleSpawner.h"

#include "Components/BoxComponent.h"
#include "SkyLiftBubble.h"

ASkyLiftBubbleSpawner::ASkyLiftBubbleSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	SpawnArea->SetupAttachment(Root);
	SpawnArea->SetBoxExtent(FVector(1200.f, 1200.f, 80.f));
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SpawnArea->SetHiddenInGame(false);
}

void ASkyLiftBubbleSpawner::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add(TEXT("SkyLiftBubbleSpawner"));
	ResetNextSpawnTime();
}

void ASkyLiftBubbleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HasAuthority() || DeltaTime <= 0.f)
	{
		return;
	}

	CleanupInactiveBubbles();

	if (ActiveBubbles.Num() >= MaxActiveBubbles)
	{
		SpawnAccumulator = 0.f;
		return;
	}

	SpawnAccumulator += DeltaTime;
	if (SpawnAccumulator < NextSpawnTime)
	{
		return;
	}

	SpawnAccumulator = 0.f;
	SpawnBubble();
	ResetNextSpawnTime();
}

void ASkyLiftBubbleSpawner::SpawnBubble()
{
	if (!GetWorld())
	{
		return;
	}

	UClass* ClassToSpawn = BubbleClass ? BubbleClass.Get() : ASkyLiftBubble::StaticClass();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	ASkyLiftBubble* Bubble = GetWorld()->SpawnActor<ASkyLiftBubble>(
		ClassToSpawn,
		GetRandomSpawnLocation(),
		FRotator::ZeroRotator,
		SpawnParams);

	if (Bubble)
	{
		ActiveBubbles.Add(Bubble);
	}
}

void ASkyLiftBubbleSpawner::CleanupInactiveBubbles()
{
	for (int32 i = ActiveBubbles.Num() - 1; i >= 0; --i)
	{
		if (!ActiveBubbles[i].IsValid())
		{
			ActiveBubbles.RemoveAtSwap(i);
		}
	}
}

void ASkyLiftBubbleSpawner::ResetNextSpawnTime()
{
	NextSpawnTime = FMath::FRandRange(MinSpawnInterval, FMath::Max(MinSpawnInterval, MaxSpawnInterval));
}

FVector ASkyLiftBubbleSpawner::GetRandomSpawnLocation() const
{
	if (!SpawnArea)
	{
		return GetActorLocation() + FVector(0.f, 0.f, SpawnZOffset);
	}

	const FVector Extent = SpawnArea->GetScaledBoxExtent();
	const FVector LocalOffset(
		FMath::FRandRange(-Extent.X, Extent.X),
		FMath::FRandRange(-Extent.Y, Extent.Y),
		FMath::FRandRange(-Extent.Z, Extent.Z) + SpawnZOffset);

	return SpawnArea->GetComponentTransform().TransformPosition(LocalOffset);
}
