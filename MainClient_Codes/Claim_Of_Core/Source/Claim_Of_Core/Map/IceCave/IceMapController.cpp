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

}
