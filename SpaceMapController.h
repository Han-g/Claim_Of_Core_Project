#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceMapController.generated.h"

class ABlackHoleActor;

UENUM(BlueprintType)
enum class ESpaceMapPhase : uint8
{
	Phase1 UMETA(DisplayName = "Phase 1"),
	Phase2 UMETA(DisplayName = "Phase 2"),
	Phase3 UMETA(DisplayName = "Phase 3")
};

UCLASS()
class CLAIM_OF_CORE_API ASpaceMapController : public AActor
{
	GENERATED_BODY()

public:
	ASpaceMapController();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap")
	ESpaceMapPhase CurrentPhase = ESpaceMapPhase::Phase1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap")
	float Phase2StartTime = 40.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap")
	float Phase3StartTime = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|LowGravity")
	float LowGravityScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|LowGravity")
	float LowGravityJumpZVelocity = 700.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|LowGravity")
	float LowGravityAirControl = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|SpaceMovement")
	float SpaceFallingLateralFriction = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|SpaceMovement")
	float SpaceBrakingDecelerationFalling = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|JumpAnimation")
	float GroundAnimRateScale = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|JumpAnimation")
	float JumpAnimRateScale = 0.45f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|JumpAnimation")
	float JumpAnimCheckInterval = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|Phase2")
	TObjectPtr<ABlackHoleActor> BlackHoleActor = nullptr;

	FTimerHandle Phase2TimerHandle;
	FTimerHandle Phase3TimerHandle;
	FTimerHandle LowGravityApplyTimerHandle;
	FTimerHandle JumpAnimApplyTimerHandle;

protected:
	void EnterPhase1();
	void EnterPhase2();
	void EnterPhase3();

	void ApplyLowGravityToAllCharacters();
	void ApplyJumpAnimRateToAllCharacters();
	void ResetAnimRateToAllCharacters();

public:
	UFUNCTION(BlueprintCallable, Category = "SpaceMap")
	void StartSpaceMap();

	UFUNCTION(BlueprintCallable, Category = "SpaceMap")
	void StopSpaceMap();

	UFUNCTION(BlueprintPure, Category = "SpaceMap")
	ESpaceMapPhase GetCurrentPhase() const { return CurrentPhase; }

	UFUNCTION(BlueprintImplementableEvent, Category = "SpaceMap")
	void BP_OnPhaseChanged(ESpaceMapPhase NewPhase);
};
