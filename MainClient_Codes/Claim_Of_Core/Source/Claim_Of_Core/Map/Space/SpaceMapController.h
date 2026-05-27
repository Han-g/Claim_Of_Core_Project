#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameState/InGame_GameState.h"

#include "SpaceMapController.generated.h"

class ABlackHoleActor;

UCLASS()
class CLAIM_OF_CORE_API ASpaceMapController : public AActor
{
	GENERATED_BODY()

public:
	ASpaceMapController();

	void InitializeGameState();
	void SyncFromGameState();

	void HandleRoundStateChanged(ERoundState OldState, ERoundState NewState);
	void HandlePhaseChanged(EMapPhase OldPhase, EMapPhase NewPhase);
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap")
	EMapPhase  CurrentPhase = EMapPhase::Phase1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|LowGravity")
	float LowGravityScale = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpaceMap|LowGravity")
	float LowGravityJumpZVelocity = 1500.f;

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

	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState = nullptr;

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
	EMapPhase GetCurrentPhase() const { return CurrentPhase; }

	UFUNCTION(BlueprintImplementableEvent, Category = "SpaceMap")
	void BP_OnPhaseChanged(EMapPhase NewPhase);
};
