// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMemberWidget.h"
#include "NetworkInstance.h"


void URoomMemberWidget::NativeConstruct()
{
    Super::NativeConstruct();

    UpdateRoleButtonColors();

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

FReply URoomMemberWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && SlotIndex >= 0)
    {
        OnSlotClicked.Broadcast(SlotIndex);
        return FReply::Handled();
    }

    return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void URoomMemberWidget::SetEmptyMember()
{
    SelectedRoleType = -1;
    UpdateRoleButtonColors();
    SetRoleButtonsEnabled(false);

	if (PlayerName) {
		PlayerName->SetText(FText::FromString(TEXT("Empty Player")));
	}
	if (PlayerState) {
		PlayerState->SetText(FText::FromString(TEXT("EMPTY")));
	}
}

void URoomMemberWidget::SetMemberInfo(const FString& playerName, bool bIsReady, int32 RoleType, bool bCanSelect)
{
    SelectedRoleType = RoleType;

	if (PlayerName) {
		PlayerName->SetText(FText::FromString(playerName));
	}

	if (PlayerState) {
		PlayerState->SetText(FText::FromString(bIsReady ? TEXT("READY") : TEXT("WAITING")));
	}

    SetRoleButtonsEnabled(bCanSelect);
    UpdateRoleButtonColors();
}

void URoomMemberWidget::SetSlotIndex(int32 InSlotIndex)
{
    SlotIndex = InSlotIndex;
}

void URoomMemberWidget::SetRoleButtonsEnabled(bool bEnabled)
{
    bCanSelectRole = bEnabled;

    if (StrikerButton) { StrikerButton->SetIsEnabled(bEnabled); }
    if (GuardianButton) { GuardianButton->SetIsEnabled(bEnabled); }
    if (ManipulatorButton) { ManipulatorButton->SetIsEnabled(bEnabled); }
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
    if (!bCanSelectRole)
    {
        return;
    }

    SelectedRoleType = InRoleType;
    UpdateRoleButtonColors();

    UE_LOG(LogTemp, Display, TEXT("[RoomMemberWidget] Role button clicked: %d"), SelectedRoleType);

    if (UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance()))
    {
        GI->SelectCharacterAndReady(InRoleType);
    }
}

void URoomMemberWidget::UpdateRoleButtonColors()
{
    const FLinearColor NormalColor = FLinearColor(0.08f, 0.08f, 0.08f, 1.0f);
    const FLinearColor SelectedColor = FLinearColor(0.1f, 0.45f, 1.0f, 1.0f);

    if (StrikerButton)
    {
        StrikerButton->SetBackgroundColor(SelectedRoleType == 0 ? SelectedColor : NormalColor);
    }

    if (GuardianButton)
    {
        GuardianButton->SetBackgroundColor(SelectedRoleType == 1 ? SelectedColor : NormalColor);
    }

    if (ManipulatorButton)
    {
        ManipulatorButton->SetBackgroundColor(SelectedRoleType == 2 ? SelectedColor : NormalColor);
    }
}
