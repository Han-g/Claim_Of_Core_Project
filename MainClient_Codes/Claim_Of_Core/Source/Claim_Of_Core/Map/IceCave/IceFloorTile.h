#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceFloorTile.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EIceFloorState : uint8
{
	Normal,
	Cracked,
	Breaking,
	Broken
};

UCLASS()
class CLAIM_OF_CORE_API AIceFloorTile : public AActor
{
	GENERATED_BODY()

public:
	AIceFloorTile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> FloorMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floor")
	EIceFloorState CurrentState = EIceFloorState::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floor")
	float BreakDelay = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floor")
	bool bFallWhenBroken = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Floor")
	float FallenLifeSpan = 5.0f;

	FTimerHandle BreakTimerHandle;

public:
	UFUNCTION(BlueprintCallable)
	void SetCracked();

	UFUNCTION(BlueprintCallable)
	void StartBreaking();

	UFUNCTION(BlueprintCallable)
	void BreakFloor();

	UFUNCTION(BlueprintPure)
	bool IsBroken() const { return CurrentState == EIceFloorState::Broken; }

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnCracked();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnBreaking();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnBroken();
};