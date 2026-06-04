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

	if (ExitButton) {
		ExitButton->OnClicked.AddDynamic(this, &URoomWidget::OnExitButtonClicked);
	}
}


void URoomWidget::UpdateMemberList(const TArray<FRoomMemberInfo>& PlayerList)
{
	if (!MemberList || !MemberWidgetClass) { return; }

	UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
	const int32 LocalUID = GI ? GI->GetPlayerUID() : -1;

	MemberList->ClearChildren();

	for (int32 i = 0; i < 6; ++i)
	{
		URoomMemberWidget* NewMember = CreateWidget<URoomMemberWidget>(GetWorld(), MemberWidgetClass);
		if (NewMember)
		{
			NewMember->SetSlotIndex(i);
			NewMember->OnSlotClicked.AddDynamic(this, &URoomWidget::OnMemberSlotClicked);

			const FRoomMemberInfo* SlotMember = PlayerList.FindByPredicate(
				[i](const FRoomMemberInfo& Info)
				{
					return Info.roomSlot == i;
				}
			);

			if (SlotMember)
			{
				const bool bCanSelect = SlotMember->userUID == LocalUID;

				NewMember->SetMemberInfo(
					SlotMember->playerName,
					SlotMember->bIsReady,
					SlotMember->roleType,
					bCanSelect
				);
			}
			else
			{
				NewMember->SetEmptyMember();
			}

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

	bool bLocalIsHost = false;

	for (const FRoomMemberInfo& Member : PlayerList) {
		if (Member.userUID == LocalUID) {
			bLocalIsHost = Member.bIsHost;
			break;
		}
	}

	if (StartButton) { StartButton->SetIsEnabled(bLocalIsHost); }

	if (MemberCount) {
		FString CountStr = FString::Printf(TEXT("%d / 6"), FMath::Min(PlayerList.Num(), 6));
		MemberCount->SetText(FText::FromString(CountStr));
	}
}

void URoomWidget::SetRoomActionsEnabled(bool bEnabled)
{
	if (StartButton)
	{
		StartButton->SetIsEnabled(bEnabled);
	}

	if (ExitButton)
	{
		ExitButton->SetIsEnabled(bEnabled);
	}
}

void URoomWidget::OnExitButtonClicked()
{
	UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
	if (GI)
	{
		GI->RequestLeaveRoom();
	}
}

void URoomWidget::OnStartButtonClicked()
{
	UE_LOG(LogTemp, Display, TEXT("Game Start Button Clicked!"));

	UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
	if (GI) { 
		// Start Condition Check
		GI->RequestGameStart();
	}
}

void URoomWidget::OnMemberSlotClicked(int32 SlotIndex)
{
	UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance());
	if (!GI)
	{
		return;
	}

	GI->RequestRoomSlotSelect(SlotIndex);
}
