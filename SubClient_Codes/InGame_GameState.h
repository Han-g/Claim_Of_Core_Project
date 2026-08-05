#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InGame_GameState.generated.h"

class UCameraShakeBase;
class USoundBase;

UENUM(BlueprintType)
enum class ERoundState : uint8
{
	Waiting   UMETA(DisplayName = "Waiting"),
	Playing   UMETA(DisplayName = "Playing"),
	Finished  UMETA(DisplayName = "Finished")
};

UENUM(BlueprintType)
enum class EMapPhase : uint8
{
	None   UMETA(DisplayName = "None"),
	Phase1 UMETA(DisplayName = "Phase 1"),
	Phase2 UMETA(DisplayName = "Phase 2"),
	Phase3 UMETA(DisplayName = "Phase 3"),
	End    UMETA(DisplayName = "End")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnPhaseChangedSignature,
	EMapPhase, OldPhase,
	EMapPhase, NewPhase
);

UCLASS()
class CLAIM_OF_CORE_API AInGame_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AInGame_GameState();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_RoundState, Category = "Round")
	ERoundState RoundState;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Round")
	int32 ReadyTime;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Round")
	int32 GameTime;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentPhase, Category = "Phase")
	EMapPhase CurrentPhase;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Phase")
	int32 Phase1Time;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Phase")
	int32 Phase2Time;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Phase")
	int32 Phase3Time;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Round")
	int32 CurrentReadyTime;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Round")
	int32 CurrentGameTime;

	UPROPERTY(BlueprintAssignable, Category = "Phase")
	FOnPhaseChangedSignature OnPhaseChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Phase|Feedback")
	TSubclassOf<UCameraShakeBase> PhaseChangeShakeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Phase|Feedback")
	TObjectPtr<USoundBase> PhaseChangeSound;

	UFUNCTION(BlueprintCallable, Category = "Phase")
	void UpdatePhase();

	UFUNCTION(BlueprintPure, Category = "Phase")
	int32 GetElapsedPlayTime() const;

	void StartReady();
	void StartRound();
	void EndRound();

protected:
	FTimerHandle TimerHandle_Countdown;

	void CountdownTick();
	void SetPlayersMovementEnabled(bool bEnableMovement);
	void ApplyMovementByRoundState();
	void HandlePhaseChanged(EMapPhase OldPhase, EMapPhase NewPhase);
	FString GetPhaseMessage(EMapPhase NewPhase) const;

	UFUNCTION()
	void OnRep_RoundState(ERoundState OldRoundState);

	UFUNCTION()
	void OnRep_CurrentPhase(EMapPhase OldPhase);

	UFUNCTION(BlueprintImplementableEvent, Category = "Phase")
	void BP_OnPhaseChanged(EMapPhase OldPhase, EMapPhase NewPhase);

	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};