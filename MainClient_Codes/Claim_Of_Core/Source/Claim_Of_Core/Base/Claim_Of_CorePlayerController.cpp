// Copyright Epic Games, Inc. All Rights Reserved.


#include "Claim_Of_CorePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "Blueprint/UserWidget.h"
#include "Claim_Of_Core.h"

#include "Widgets/Input/SVirtualJoystick.h"
#include "UI/GameSettingInterface.h"

void AClaim_Of_CorePlayerController::StartClientOnlyTestPressed()
{
	if (UNetworkInstance* GI = GetGameInstance<UNetworkInstance>())
	{
		UE_LOG(LogTemp, Display, TEXT("Test key Pressed!!!"));
		GI->StartClientOnlyTestFlow();
	}
}

void AClaim_Of_CorePlayerController::ToggleGameSettingMenu()
{
	if (GameSettingWidgetInstance)
	{
		CloseGameSettingMenu();
	}
	else
	{
		OpenGameSettingMenu();
	}
}

void AClaim_Of_CorePlayerController::OpenGameSettingMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("[GameSetting] Open requested. Local=%d Class=%s"),
		IsLocalPlayerController() ? 1 : 0,
		*GetNameSafe(GameSettingWidgetClass));

	if (!IsLocalPlayerController() || !GameSettingWidgetClass)
	{
		return;
	}

	GameSettingWidgetInstance = CreateWidget<UGameSettingInterface>(this, GameSettingWidgetClass);
	if (!GameSettingWidgetInstance)
	{
		return;
	}

	GameSettingWidgetInstance->AddToViewport(100);

	SetShowMouseCursor(true);

	FInputModeGameAndUI InputMode;
	InputMode.SetWidgetToFocus(GameSettingWidgetInstance->TakeWidget());
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);

	GameSettingWidgetInstance->SetKeyboardFocus();
}

void AClaim_Of_CorePlayerController::CloseGameSettingMenu()
{
	if (GameSettingWidgetInstance)
	{
		GameSettingWidgetInstance->RemoveFromParent();
		GameSettingWidgetInstance = nullptr;
	}

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameOnly());
}

void AClaim_Of_CorePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// only spawn touch controls on local player controllers
	if (ShouldUseTouchControls() && IsLocalPlayerController())
	{
		// spawn the mobile controls widget
		MobileControlsWidget = CreateWidget<UUserWidget>(this, MobileControlsWidgetClass);

		if (MobileControlsWidget)
		{
			// add the controls to the player screen
			MobileControlsWidget->AddToPlayerScreen(0);

		} else {

			UE_LOG(LogClaim_Of_Core, Error, TEXT("Could not spawn mobile controls widget."));

		}

	}
}

void AClaim_Of_CorePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// only add IMCs for local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Contexts
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
			{
				Subsystem->AddMappingContext(CurrentContext, 0);
			}

			// only add these IMCs if we're not using mobile touch input
			if (!ShouldUseTouchControls())
			{
				for (UInputMappingContext* CurrentContext : MobileExcludedMappingContexts)
				{
					Subsystem->AddMappingContext(CurrentContext, 0);
				}
			}

			InputComponent->BindKey(EKeys::Subtract, IE_Pressed, this,
				&AClaim_Of_CorePlayerController::StartClientOnlyTestPressed);
			InputComponent->BindKey(EKeys::Escape, IE_Pressed, this, &AClaim_Of_CorePlayerController::ToggleGameSettingMenu);
			InputComponent->BindKey(EKeys::P, IE_Pressed, this, &AClaim_Of_CorePlayerController::ToggleGameSettingMenu);
		}
	}
}

bool AClaim_Of_CorePlayerController::ShouldUseTouchControls() const
{
	// are we on a mobile platform? Should we force touch?
	return SVirtualJoystick::ShouldDisplayTouchInterface() || bForceTouchControls;
}
