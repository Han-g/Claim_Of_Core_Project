// Fill out your copyright notice in the Description page of Project Settings.


#include "GameState/LobbyGameMode.h"
#include "GameFramework/PlayerController.h"

ALobbyGameMode::ALobbyGameMode()
{
    DefaultPawnClass = nullptr;
    HUDClass = nullptr;
    PlayerControllerClass = APlayerController::StaticClass();
}

void ALobbyGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    // Lobby map is UI-only, so do not call RestartPlayer().
}
