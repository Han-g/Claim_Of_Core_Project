// Fill out your copyright notice in the Description page of Project Settings.


#include "RobbyWidget.h"
#include "NetworkInstance.h"
#include "ClientNetworking.h"
#include "RoomEnterWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "InputCoreTypes.h"

void URobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

    SetIsFocusable(true);
    SetKeyboardFocus();

	if (CreateButton) { CreateButton->OnClicked.AddDynamic(this, &URobbyWidget::OnCreateButtonClicked); }

	if (StartButton) { StartButton->OnClicked.AddDynamic(this, &URobbyWidget::OnStartButtonClicked); }
}

FReply URobbyWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Subtract)
	{
		APlayerController* PC = GetOwningPlayer();

		if (!PC && GetWorld())
		{
			PC = GetWorld()->GetFirstPlayerController();
		}

		UKismetSystemLibrary::QuitGame(this, PC, EQuitPreference::Quit, true);
		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void URobbyWidget::ReloadRoomList(const TArray<FRoomInfoData>& RoomList)
{
    if (!RoomScrollBox || !RoomEntryClass) {
        UE_LOG(LogTemp, Error, TEXT("ScrollBox or WidgetClass is missing!"));
        return;
    }

    RoomScrollBox->ClearChildren();

    for (const FRoomInfoData& Room : RoomList)
    {
        URoomEnterWidget* RoomWidget = CreateWidget<URoomEnterWidget>(GetWorld(), RoomEntryClass);
        if (RoomWidget)
        {
            RoomWidget->InitRoomInfo(Room.RoomID, Room.RoomName, Room.CurrentPlayers);

            RoomScrollBox->AddChild(RoomWidget);
        }
    }
}


void URobbyWidget::OnCreateButtonClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Create Room Button Clicked!"));

	UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
	if (GI)
	{
		GI->CreateRoom();
	}
}

void URobbyWidget::OnStartButtonClicked()
{

}
