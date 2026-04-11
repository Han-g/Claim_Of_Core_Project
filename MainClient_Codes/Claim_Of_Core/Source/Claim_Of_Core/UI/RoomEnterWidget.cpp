// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomEnterWidget.h"
#include "NetworkInstance.h"

void URoomEnterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (JoinButton) {
		JoinButton->OnClicked.AddDynamic(this, &URoomEnterWidget::OnJoinButtonClicked);
	}
}

void URoomEnterWidget::InitRoomInfo(int32 s_RoomID, const FString& s_RoomName)
{
	RoomID = s_RoomID;

	if (RoomName) { RoomName->SetText(FText::FromString(s_RoomName)); }
	UpdatePlayerCount(1);
}

void URoomEnterWidget::UpdatePlayerCount(int32 CurrentPlayers)
{
	if (PlayerCounter) {
		FString CountStr = FString::Printf(TEXT("%d / %d"), CurrentPlayers, MAXPLAYER);
		PlayerCounter->SetText(FText::FromString(CountStr));
	}
}


void URoomEnterWidget::OnJoinButtonClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Join Room Button Clicked!"));

	UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
	if (GI)
	{
		GI->JoinRoom(RoomID);
	}
}