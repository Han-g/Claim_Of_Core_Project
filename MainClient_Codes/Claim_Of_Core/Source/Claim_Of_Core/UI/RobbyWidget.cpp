// Fill out your copyright notice in the Description page of Project Settings.


#include "RobbyWidget.h"
#include "NetworkInstance.h"
#include "ClientNetworking.h"
#include "RoomEnterWidget.h"

void URobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CreateButton) { CreateButton->OnClicked.AddDynamic(this, &URobbyWidget::OnCreateButtonClicked); }

	if (StartButton) { StartButton->OnClicked.AddDynamic(this, &URobbyWidget::OnStartButtonClicked); }
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
            RoomWidget->InitRoomInfo(Room.RoomID, Room.RoomName, Room.CurrentPlayers, Room.MaxPlayers);

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
