// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameSettingInterface.h"

#include "Base/Claim_Of_CorePlayerController.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/NetworkInstance.h"

void UGameSettingInterface::NativeConstruct()
{
	Super::NativeConstruct();

	SetIsFocusable(true);

	if (BackToGameButton)
	{
		BackToGameButton->OnClicked.AddDynamic(this, &UGameSettingInterface::OnBackToGameClicked);
	}

	if (SurrenderButton)
	{
		SurrenderButton->OnClicked.AddDynamic(this, &UGameSettingInterface::OnSurrenderClicked);
	}

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UGameSettingInterface::OnExitGameClicked);
	}
}

FReply UGameSettingInterface::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	const FKey Key = InKeyEvent.GetKey();

	if (Key == EKeys::Escape || Key == EKeys::P)
	{
		OnBackToGameClicked();
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UGameSettingInterface::OnBackToGameClicked()
{
	if (AClaim_Of_CorePlayerController* PC = Cast<AClaim_Of_CorePlayerController>(GetOwningPlayer()))
	{
		PC->CloseGameSettingMenu();
		return;
	}

	RemoveFromParent();
}

void UGameSettingInterface::OnSurrenderClicked()
{
	if (UNetworkInstance* GI = GetGameInstance<UNetworkInstance>())
	{
		GI->SurrenderAndReturnToLobby();
	}
}

void UGameSettingInterface::OnExitGameClicked()
{
	APlayerController* PC = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
}