#include "Claim_Of_Core_GameState.h"
#include "Engine/World.h"
#include "TimerManager.h"

AClaim_Of_Core_GameState::AClaim_Of_Core_GameState()
{
	RoundState = ERoundState::Waiting;

	ReadyTime = 3;
	GameTime = 120;

	CurrentReadyTime = ReadyTime;
	CurrentGameTime = GameTime;
}

void AClaim_Of_Core_GameState::BeginPlay()
{
	Super::BeginPlay();
	StartReady();
}

void AClaim_Of_Core_GameState::StartReady()
{
	RoundState = ERoundState::Waiting;
	CurrentReadyTime = ReadyTime;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Countdown,
		this,
		&AClaim_Of_Core_GameState::CountdownTick,
		1.0f,
		true
	);
}

void AClaim_Of_Core_GameState::StartRound()
{
	RoundState = ERoundState::Playing;
	CurrentGameTime = GameTime;
}

void AClaim_Of_Core_GameState::CountdownTick()
{
	if (RoundState == ERoundState::Waiting)
	{
		CurrentReadyTime--;

		if (CurrentReadyTime <= 0)
		{
			StartRound();
		}
		return;
	}

	if (RoundState == ERoundState::Playing)
	{
		CurrentGameTime--;

		if (CurrentGameTime <= 0)
		{
			EndRound();
		}
	}
}

void AClaim_Of_Core_GameState::EndRound()
{
	RoundState = ERoundState::Finished;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Countdown);
}

