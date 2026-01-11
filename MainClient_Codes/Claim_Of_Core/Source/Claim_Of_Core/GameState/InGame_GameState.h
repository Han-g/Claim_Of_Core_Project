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

	void StartReady();
	void StartRound();
	void EndRound();

protected:
	FTimerHandle TimerHandle_Countdown;

	int32 CurrentReadyTime;
	int32 CurrentGameTime;

	void CountdownTick();

	virtual void GetLifetimeReplicatedProps(
		TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
