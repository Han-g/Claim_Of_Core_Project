#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Claim_Of_Core_GameState.generated.h"

// 라운드 상태
UENUM(BlueprintType)
enum class ERoundState : uint8
{
	Waiting UMETA(DisplayName = "Waiting"),
	Playing UMETA(DisplayName = "Playing"),
	Finished UMETA(DisplayName = "Finished")
};

UCLASS()
class CLAIM_OF_CORE_API AClaim_Of_Core_GameState : public AGameState
{
	GENERATED_BODY()

public:
	AClaim_Of_Core_GameState();

protected:
	virtual void BeginPlay() override;

public:
	/* ====== 라운드 상태 ====== */
	UPROPERTY(BlueprintReadOnly, Category = "Round")
	ERoundState RoundState;

	/* ====== 준비 시간 (초) ====== */
	UPROPERTY(BlueprintReadOnly, Category = "Round")
	int32 ReadyTime;

	/* ====== 남은 시간 (초) ====== */
	UPROPERTY(BlueprintReadOnly, Category = "Round")
	int32 GameTime;

	/* ====== 타이머 핸들 ====== */
	FTimerHandle TimerHandle_Countdown;

	/* ====== 게임 준비 ====== */
	void StartReady();

	/* ====== 라운드 시작 ====== */
	void StartRound();

	/* ====== 라운드 종료 ====== */
	void EndRound();

private:
	/* ====== 1초마다 호출되는 카운트 함수 ====== */
	void CountdownTick();
	
	int32 CurrentReadyTime;   // 실제 카운트용
	int32 CurrentGameTime; // 실제 카운트용
};
