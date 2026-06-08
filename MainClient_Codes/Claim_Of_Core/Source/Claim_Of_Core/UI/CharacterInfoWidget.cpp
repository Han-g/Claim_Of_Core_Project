// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterInfoWidget.h"

void UCharacterInfoWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (StrikerButton)
    {
        StrikerButton->OnClicked.RemoveDynamic(this, &UCharacterInfoWidget::OnStrikerClicked);
        StrikerButton->OnClicked.AddDynamic(this, &UCharacterInfoWidget::OnStrikerClicked);
    }

    if (GuardianButton)
    {
        GuardianButton->OnClicked.RemoveDynamic(this, &UCharacterInfoWidget::OnGuardianClicked);
        GuardianButton->OnClicked.AddDynamic(this, &UCharacterInfoWidget::OnGuardianClicked);
    }

    if (ManipulatorButton)
    {
        ManipulatorButton->OnClicked.RemoveDynamic(this, &UCharacterInfoWidget::OnManipulatorClicked);
        ManipulatorButton->OnClicked.AddDynamic(this, &UCharacterInfoWidget::OnManipulatorClicked);
    }
}

void UCharacterInfoWidget::NativeDestruct()
{
    if (StrikerButton)
    {
        StrikerButton->OnClicked.RemoveDynamic(this, &UCharacterInfoWidget::OnStrikerClicked);
    }

    if (GuardianButton)
    {
        GuardianButton->OnClicked.RemoveDynamic(this, &UCharacterInfoWidget::OnGuardianClicked);
    }

    if (ManipulatorButton)
    {
        ManipulatorButton->OnClicked.RemoveDynamic(this, &UCharacterInfoWidget::OnManipulatorClicked);
    }

    Super::NativeDestruct();
}

void UCharacterInfoWidget::OnStrikerClicked()
{
    HandleRoleSelected(0);
}

void UCharacterInfoWidget::OnGuardianClicked()
{
    HandleRoleSelected(1);
}

void UCharacterInfoWidget::OnManipulatorClicked()
{
    HandleRoleSelected(2);
}

void UCharacterInfoWidget::HandleRoleSelected(int32 InRoleType)
{
    SelectedRoleType = InRoleType;

    UE_LOG(LogTemp, Display, TEXT("[CharacterInfo] Role button clicked: %d"), SelectedRoleType);

    OnCharacterRoleSelected.Broadcast(SelectedRoleType);
}