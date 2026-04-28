// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMemberWidget.h"
#include "NetworkInstance.h"


void URoomMemberWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StrikerButton)
    {
        StrikerButton->OnClicked.RemoveDynamic(this, &URoomMemberWidget::OnStrikerClicked);
        StrikerButton->OnClicked.AddDynamic(this, &URoomMemberWidget::OnStrikerClicked);
    }

    if (GuardianButton)
    {
        GuardianButton->OnClicked.RemoveDynamic(this, &URoomMemberWidget::OnGuardianClicked);
        GuardianButton->OnClicked.AddDynamic(this, &URoomMemberWidget::OnGuardianClicked);
    }

    if (ManipulatorButton)
    {
        ManipulatorButton->OnClicked.RemoveDynamic(this, &URoomMemberWidget::OnManipulatorClicked);
        ManipulatorButton->OnClicked.AddDynamic(this, &URoomMemberWidget::OnManipulatorClicked);
    }
}

void URoomMemberWidget::NativeDestruct()
{
    if (StrikerButton)
    {
        StrikerButton->OnClicked.RemoveDynamic(this, &URoomMemberWidget::OnStrikerClicked);
    }

    if (GuardianButton)
    {
        GuardianButton->OnClicked.RemoveDynamic(this, &URoomMemberWidget::OnGuardianClicked);
    }

    if (ManipulatorButton)
    {
        ManipulatorButton->OnClicked.RemoveDynamic(this, &URoomMemberWidget::OnManipulatorClicked);
    }

    Super::NativeDestruct();
}

void URoomMemberWidget::SetEmptyMember()
{
	if (PlayerName) {
		PlayerName->SetText(FText::FromString(TEXT("Empty Player")));
	}
	if (PlayerState) {
		PlayerState->SetText(FText::FromString(TEXT("EMPTY")));
	}
}

void URoomMemberWidget::SetMemberInfo(const FString& playerName, bool bIsReady)
{
	if (PlayerName) {
		PlayerName->SetText(FText::FromString(playerName));
	}
	if (PlayerState) {
		PlayerState->SetText(FText::FromString(bIsReady ? TEXT("READY") : TEXT("WAITING")));
	}
}

void URoomMemberWidget::OnStrikerClicked()
{
    HandleRoleSelected(0);
}

void URoomMemberWidget::OnGuardianClicked()
{
    HandleRoleSelected(1);
}

void URoomMemberWidget::OnManipulatorClicked()
{
    HandleRoleSelected(2);
}

void URoomMemberWidget::HandleRoleSelected(int32 InRoleType)
{
    SelectedRoleType = InRoleType;

    UE_LOG(LogTemp, Display, TEXT("[RoomMemberWidget] Role button clicked: %d"), SelectedRoleType);

    if (UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance()))
    {
        GI->SelectCharacterAndReady(InRoleType);
    }
}