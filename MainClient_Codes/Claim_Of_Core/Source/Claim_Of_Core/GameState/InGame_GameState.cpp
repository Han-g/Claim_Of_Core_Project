#include "InGame_GameState.h"

#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraShakeBase.h"
#include "Sound/SoundBase.h"

AInGame_GameState::AInGame_GameState()
{
	RoundState = ERoundState::Waiting;
	ReadyTime = 3;

	CurrentPhase = EMapPhase::None;
	Phase1Time = 2;
	Phase2Time = 60;
	Phase3Time = 20;
	GameTime = Phase1Time + Phase2Time + Phase3Time;

	CurrentReadyTime = ReadyTime;
	CurrentGameTime = GameTime;

	PhaseChangeShakeClass = nullptr;
	PhaseChangeSound = nullptr;
}

void AInGame_GameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		StartReady();
	}
}

void AInGame_GameState::StartReady()
{
	RoundState = ERoundState::Waiting;
	CurrentPhase = EMapPhase::None;
	CurrentReadyTime = ReadyTime;
	CurrentGameTime = GameTime;

	ApplyMovementByRoundState();

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Countdown);
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

	UpdatePhase();
	ApplyMovementByRoundState();
}

void AInGame_GameState::EndRound()
{
	const EMapPhase OldPhase = CurrentPhase;

	RoundState = ERoundState::Finished;
	CurrentPhase = EMapPhase::End;

	ApplyMovementByRoundState();

	if (OldPhase != CurrentPhase)
	{
		HandlePhaseChanged(OldPhase, CurrentPhase);
	}

	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_Countdown);
}

void AInGame_GameState::CountdownTick()
{
	if (RoundState == ERoundState::Waiting)
	{
		CurrentReadyTime--;

		if (CurrentReadyTime <= 0)
		{
			CurrentReadyTime = 0;
			StartRound();
		}
	}
	else if (RoundState == ERoundState::Playing)
	{
		CurrentGameTime--;
		if (CurrentGameTime < 0)
		{
			CurrentGameTime = 0;
		}

		UpdatePhase();

		if (CurrentGameTime <= 0)
		{
			EndRound();
		}
	}
}

void AInGame_GameState::SetPlayersMovementEnabled(bool bEnableMovement)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (!PC)
		{
			continue;
		}

		PC->SetIgnoreMoveInput(!bEnableMovement);

		ACharacter* Character = Cast<ACharacter>(PC->GetPawn());
		if (!Character)
		{
			continue;
		}

		UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();
		if (!MoveComp)
		{
			continue;
		}

		if (bEnableMovement)
		{
			if (MoveComp->MovementMode == MOVE_None)
			{
				MoveComp->SetMovementMode(MOVE_Walking);
			}
		}
		else
		{
			Character->StopJumping();
			MoveComp->StopMovementImmediately();
			MoveComp->DisableMovement();
		}
	}
}

void AInGame_GameState::ApplyMovementByRoundState()
{
	const bool bCanMove = (RoundState == ERoundState::Playing && CurrentPhase != EMapPhase::None);
	SetPlayersMovementEnabled(bCanMove);
}

void AInGame_GameState::OnRep_RoundState(ERoundState OldRoundState)
{
	ApplyMovementByRoundState();
}

void AInGame_GameState::OnRep_CurrentPhase(EMapPhase OldPhase)
{
	ApplyMovementByRoundState();
	HandlePhaseChanged(OldPhase, CurrentPhase);
}

int32 AInGame_GameState::GetElapsedPlayTime() const
{
	return GameTime - CurrentGameTime;
}

void AInGame_GameState::UpdatePhase()
{
	const EMapPhase OldPhase = CurrentPhase;

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

	if (OldPhase != CurrentPhase)
	{
		HandlePhaseChanged(OldPhase, CurrentPhase);
	}
}

FString AInGame_GameState::GetPhaseMessage(EMapPhase NewPhase) const
{
	switch (NewPhase)
	{
	case EMapPhase::Phase1:
		return TEXT("Phase 1");
	case EMapPhase::Phase2:
		return TEXT("Phase 2");
	case EMapPhase::Phase3:
		return TEXT("Phase 3");
	case EMapPhase::End:
		return TEXT("End");
	default:
		return TEXT("");
	}
}

void AInGame_GameState::HandlePhaseChanged(EMapPhase OldPhase, EMapPhase NewPhase)
{
	OnPhaseChanged.Broadcast(OldPhase, NewPhase);
	BP_OnPhaseChanged(OldPhase, NewPhase);

	if (GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	const FString PhaseMessage = GetPhaseMessage(NewPhase);

	if (!PhaseMessage.IsEmpty() && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			2.0f,
			FColor::Yellow,
			PhaseMessage
		);
	}

	if (PhaseChangeSound)
	{
		UGameplayStatics::PlaySound2D(this, PhaseChangeSound);
	}

	if (PhaseChangeShakeClass)
	{
		APlayerController* PC = GetWorld() ? GetWorld()->GetFirstPlayerController() : nullptr;
		if (PC)
		{
			PC->ClientStartCameraShake(PhaseChangeShakeClass);
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

	DOREPLIFETIME(AInGame_GameState, CurrentPhase);
	DOREPLIFETIME(AInGame_GameState, Phase1Time);
	DOREPLIFETIME(AInGame_GameState, Phase2Time);
	DOREPLIFETIME(AInGame_GameState, Phase3Time);

	DOREPLIFETIME(AInGame_GameState, CurrentReadyTime);
	DOREPLIFETIME(AInGame_GameState, CurrentGameTime);
}