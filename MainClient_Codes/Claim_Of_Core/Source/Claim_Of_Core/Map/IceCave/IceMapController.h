#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceMapController.generated.h"

class AIcicleActor;
class AIceFloorTile;

UENUM(BlueprintType)
enum class EIceMapPhase : uint8
{
	Phase1,
	Phase2,
	Phase3
};

UCLASS()
class CLAIM_OF_CORE_API AIceMapController : public AActor
{
	GENERATED_BODY()

public:
	AIceMapController();

protected:
	virtual void BeginPlay() override;

};