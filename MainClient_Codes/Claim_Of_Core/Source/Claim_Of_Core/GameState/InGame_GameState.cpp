#include "InGame_GameState.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

AInGame_GameState::AInGame_GameState()
{
	RoundState = ERoundState::Waiting;
	ReadyTime = 3;

	CurrentPhase = EMapPhase::None;
	Phase1Time = 40;
	Phase2Time = 60;
	Phase3Time = 20;
	GameTime = Phase1Time + Phase2Time + Phase3Time;

	CurrentReadyTime = ReadyTime;
	CurrentGameTime = GameTime;
}

void AInGame_GameState::BeginPlay()
{
	Super::BeginPlay();

	RoundState = ERoundState::Waiting;
	CurrentPhase = EMapPhase::None;
	CurrentReadyTime = ReadyTime;
	CurrentGameTime = GameTime;
}

void AInGame_GameState::StartReady()
{
	if (!HasAuthority() || !GetWorld())
	{
		return;
	}

	RoundState = ERoundState::Waiting;
	CurrentReadyTime = ReadyTime;
	CurrentGameTime = GameTime;
	UpdatePhase();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Countdown);

	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle_Countdown,
		this,
		&AInGame_GameState::CountdownTick,
		1.0f,
		true
	);

	ForceNetUpdate();
}

void AInGame_GameState::StartRound()
{
	if (!HasAuthority())
	{
		return;
	}

	RoundState = ERoundState::Playing;
	CurrentGameTime = GameTime;
	UpdatePhase();
	ForceNetUpdate();
}

void AInGame_GameState::EndRound()
{
	if (!HasAuthority())
	{
		return;
	}

	RoundState = ERoundState::Finished;
	CurrentPhase = EMapPhase::End;
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Countdown);
	}
	ForceNetUpdate();
}

void AInGame_GameState::CountdownTick()
{
	if (!HasAuthority())
	{
		return;
	}

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
		UpdatePhase();

		if (CurrentGameTime <= 0)
		{
			EndRound();
		}
	}

	ForceNetUpdate();
}

void AInGame_GameState::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AInGame_GameState, RoundState);
	DOREPLIFETIME(AInGame_GameState, ReadyTime);
	DOREPLIFETIME(AInGame_GameState, GameTime);

	DOREPLIFETIME(AInGame_GameState, CurrentPhase);
	DOREPLIFETIME(AInGame_GameState, Phase1Time);
	DOREPLIFETIME(AInGame_GameState, Phase2Time);
	DOREPLIFETIME(AInGame_GameState, Phase3Time);
	DOREPLIFETIME(AInGame_GameState, CurrentReadyTime);
	DOREPLIFETIME(AInGame_GameState, CurrentGameTime);
}

int32 AInGame_GameState::GetElapsedPlayTime() const
{
	return GameTime - CurrentGameTime;
}

void AInGame_GameState::ActivateGameplayFromServerStart()
{
	if (bGameplayActivated)
	{
		return;
	}

	bGameplayActivated = true;
	OnGameplayActivated.Broadcast();

	// 현재 구조를 유지하려면 여기서부터 시작
	StartReady();
}

void AInGame_GameState::UpdatePhase()
{
	if (!HasAuthority())
	{
		return;
	}

	if (RoundState != ERoundState::Playing)
	{
		CurrentPhase = EMapPhase::None;
		return;
	}

	const int32 Elapsed = GetElapsedPlayTime();

	if (Elapsed < Phase1Time)
	{
		CurrentPhase = EMapPhase::Phase1;
	}
	else if (Elapsed < Phase1Time + Phase2Time)
	{
		CurrentPhase = EMapPhase::Phase2;
	}
	else if (Elapsed < Phase1Time + Phase2Time + Phase3Time)
	{
		CurrentPhase = EMapPhase::Phase3;
	}
	else
	{
		CurrentPhase = EMapPhase::End;
	}
}
