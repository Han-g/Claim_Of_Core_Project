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

			// 3. 그리드 패널에 자식으로 추가하고 '그리드 슬롯' 정보를 받아옵니다.
			UUniformGridSlot* GridSlot = MemberList->AddChildToUniformGrid(NewMember);

			if (GridSlot)
			{
				// 4. 행(Row)과 열(Column) 설정
				// 1x6 배열이므로 Row는 무조건 0, Column은 i(0~5)가 됩니다.
				GridSlot->SetRow(0);
				GridSlot->SetColumn(i);

				// 5. 정렬 설정 (패널 안에 위젯이 꽉 차게)
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
	if (GI) { GI->RequestGameStart(); }
}