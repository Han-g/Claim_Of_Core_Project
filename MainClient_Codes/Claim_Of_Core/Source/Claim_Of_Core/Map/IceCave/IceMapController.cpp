#include "IceMapController.h"
#include "IcicleActor.h"
#include "IceFloorTile.h"
#include "TimerManager.h"

AIceMapController::AIceMapController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AIceMapController::BeginPlay()
{
	Super::BeginPlay();

	StartIceMap();
}

void AIceMapController::StartIceMap()
{
	CurrentPhase = EIceMapPhase::Phase1;
	BP_OnPhaseChanged(CurrentPhase);

	GetWorldTimerManager().SetTimer(
		Phase2TimerHandle,
		this,
		&AIceMapController::EnterPhase2,
		Phase2StartTime,
		false
	);

	GetWorldTimerManager().SetTimer(
		Phase3TimerHandle,
		this,
		&AIceMapController::EnterPhase3,
		Phase3StartTime,
		false
	);
}

void AIceMapController::EnterPhase2()
{
	CurrentPhase = EIceMapPhase::Phase2;
	BP_OnPhaseChanged(CurrentPhase);

	GetWorldTimerManager().SetTimer(
		IcicleSpawnTimerHandle,
		this,
		&AIceMapController::TriggerRandomIcicle,
		IcicleSpawnIntervalPhase2,
		true
	);
}

void AIceMapController::EnterPhase3()
{
	CurrentPhase = EIceMapPhase::Phase3;
	BP_OnPhaseChanged(CurrentPhase);

	GetWorldTimerManager().ClearTimer(IcicleSpawnTimerHandle);

	GetWorldTimerManager().SetTimer(
		IcicleSpawnTimerHandle,
		this,
		&AIceMapController::TriggerRandomIcicle,
		IcicleSpawnIntervalPhase3,
		true
	);

	GetWorldTimerManager().SetTimer(
		FloorBreakTimerHandle,
		this,
		&AIceMapController::TriggerRandomFloorTile,
		FloorBreakIntervalPhase3,
		true
	);
}

void AIceMapController::TriggerRandomIcicle()
{
	TArray<AIcicleActor*> AvailableIcicles;

	for (AIcicleActor* Icicle : IcicleActors)
	{
		if (!IsValid(Icicle))
		{
			continue;
		}

		AvailableIcicles.Add(Icicle);
	}

	if (AvailableIcicles.Num() <= 0)
	{
		return;
	}

	const int32 Index = FMath::RandRange(0, AvailableIcicles.Num() - 1);
	AvailableIcicles[Index]->StartWarning();
}

void AIceMapController::TriggerRandomFloorTile()
{
	TArray<AIceFloorTile*> AvailableTiles;

	for (AIceFloorTile* Tile : FloorTiles)
	{
		if (!IsValid(Tile))
		{
			continue;
		}

		if (!Tile->IsBroken())
		{
			AvailableTiles.Add(Tile);
		}
	}

	if (AvailableTiles.Num() <= 0)
	{
		return;
	}

	const int32 Index = FMath::RandRange(0, AvailableTiles.Num() - 1);
	AvailableTiles[Index]->StartBreaking();
}