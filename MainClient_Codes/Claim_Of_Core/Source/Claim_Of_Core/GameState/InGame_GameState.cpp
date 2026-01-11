#include "InGame_GameState.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

AInGame_GameState::AInGame_GameState()
{
	RoundState = ERoundState::Waiting;
	ReadyTime = 3;
	GameTime = 10;

	CurrentReadyTime = ReadyTime;
	CurrentGameTime = GameTime;
}

void AInGame_GameState::BeginPlay()
{
	Super::BeginPlay();
	StartReady();
}

void AInGame_GameState::StartReady()
{
	RoundState = ERoundState::Waiting;
	CurrentReadyTime = ReadyTime;

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Countdown,
		this,
		&AInGame_GameState::CountdownTick,
		1.0f,
		true
	);
}

void AInGame_GameState::StartRound()
{
	RoundState = ERoundState::Playing;
	CurrentGameTime = GameTime;
}

void AInGame_GameState::EndRound()
{
	RoundState = ERoundState::Finished;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Countdown);
}

void AInGame_GameState::CountdownTick()
{
	if (RoundState == ERoundState::Waiting)
	{
		CurrentReadyTime--;
		if (CurrentReadyTime <= 0)
		{
			StartRound();
		}
	}
	else if (RoundState == ERoundState::Playing)
	{
		CurrentGameTime--;
		if (CurrentGameTime <= 0)
		{
			EndRound();
		}
	}
}

void AInGame_GameState::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGame_GameState, RoundState);
	DOREPLIFETIME(AInGame_GameState, ReadyTime);
	DOREPLIFETIME(AInGame_GameState, GameTime);
}
