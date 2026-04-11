// Fill out your copyright notice in the Description page of Project Settings.


#include "RobbyWidget.h"
#include "NetworkInstance.h"
#include "../Networking/ClientNetworking.h"
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

    // 1. 기존에 떠 있던 방 목록을 싹 지웁니다.
    RoomScrollBox->ClearChildren();

    // 2. 서버가 준 리스트만큼 새 위젯을 만들어서 붙입니다.
    for (const FRoomInfoData& Room : RoomList)
    {
        URoomEnterWidget* RoomWidget = CreateWidget<URoomEnterWidget>(GetWorld(), RoomEntryClass);
        if (RoomWidget)
        {
            // 방 정보 초기화 (기존에 만드셨던 함수 활용)
            RoomWidget->InitRoomInfo(Room.RoomID, Room.RoomName);
            RoomWidget->UpdatePlayerCount(Room.CurrentPlayers); // 인원수 업데이트

            // 스크롤 박스에 자식으로 추가
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