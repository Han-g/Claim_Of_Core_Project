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

void URoomEnterWidget::InitRoomInfo(int32 s_RoomID, const FString& s_RoomName, int32 CurrentPlayers, int32 MaxPlayers)
{
	RoomID = s_RoomID;

	if (RoomName) { RoomName->SetText(FText::FromString(s_RoomName)); }
	UpdatePlayerCount(CurrentPlayers, MaxPlayers);
}

void URoomEnterWidget::UpdatePlayerCount(int32 CurrentPlayers, int32 MaxPlayers)
{
	if (PlayerCounter) {
		const int32 SafeMaxPlayers = FMath::Max(MaxPlayers, 1);
		FString CountStr = FString::Printf(TEXT("%d / %d"), CurrentPlayers, SafeMaxPlayers);
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
