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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceMap")
	EIceMapPhase CurrentPhase = EIceMapPhase::Phase1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceMap")
	float Phase2StartTime = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceMap")
	float Phase3StartTime = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceMap")
	float IcicleSpawnIntervalPhase2 = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceMap")
	float IcicleSpawnIntervalPhase3 = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceMap")
	float FloorBreakIntervalPhase3 = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceMap")
	TArray<TObjectPtr<AIcicleActor>> IcicleActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceMap")
	TArray<TObjectPtr<AIceFloorTile>> FloorTiles;

	FTimerHandle Phase2TimerHandle;
	FTimerHandle Phase3TimerHandle;
	FTimerHandle IcicleSpawnTimerHandle;
	FTimerHandle FloorBreakTimerHandle;

	void EnterPhase2();
	void EnterPhase3();

	void TriggerRandomIcicle();
	void TriggerRandomFloorTile();

public:
	UFUNCTION(BlueprintCallable)
	void StartIceMap();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnPhaseChanged(EIceMapPhase NewPhase);
};