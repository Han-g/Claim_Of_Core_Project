// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomWidget.h"
#include "RoomMemberWidget.h"
#include "NetworkInstance.h"


void URoomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton) {
		StartButton->OnClicked.AddDynamic(this, &URoomWidget::OnStartButtonClicked);
	}
}


void URoomWidget::UpdateMemberList(const TArray<FRoomMemberInfo>& PlayerList)
{
	if (!MemberList || !MemberWidgetClass) { return; }

	MemberList->ClearChildren();

	for (int32 i = 0; i < 6; ++i)
	{
		URoomMemberWidget* NewMember = CreateWidget<URoomMemberWidget>(GetWorld(), MemberWidgetClass);
		if (NewMember)
		{
			if (i < PlayerList.Num()) { NewMember->SetMemberInfo(PlayerList[i].PlayerName, PlayerList[i].bIsReady); }
			else { NewMember->SetEmptyMember(); }

			UUniformGridSlot* GridSlot = MemberList->AddChildToUniformGrid(NewMember);

			if (GridSlot)
			{
				GridSlot->SetRow(0);
				GridSlot->SetColumn(i);

				GridSlot->SetHorizontalAlignment(HAlign_Fill);
				GridSlot->SetVerticalAlignment(VAlign_Fill);
			}
		}
	}

	if (MemberCount) {
		FString CountStr = FString::Printf(TEXT("%d / 6"), FMath::Min(PlayerList.Num(), 6));
		MemberCount->SetText(FText::FromString(CountStr));
	}
}

void URoomWidget::OnStartButtonClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Game Start Button Clicked!"));

	UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
	if (GI) { 
		// Start Condition Check
		GI->RequestGameStart(); 

		// Immediate Start For Test
		
		//GI->HandleGameStart();
	}
}
