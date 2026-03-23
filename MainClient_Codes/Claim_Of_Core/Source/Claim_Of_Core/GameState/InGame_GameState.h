#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "InGame_GameState.generated.h"

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

UCLASS()
class CLAIM_OF_CORE_API AInGame_GameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AInGame_GameState();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Round")
	ERoundState RoundState;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Round")
	int32 ReadyTime;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Round")
	int32 GameTime;

	UPROPERTY(BlueprintReadOnly, Replicated, Category = "Phase")
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

	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
