// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMemberWidget.h"

void URoomMemberWidget::SetEmptyMember()
{
	if (PlayerName) {
		PlayerName->SetText(FText::FromString(TEXT("Empty Player")));
	}
	if (PlayerState) {
		PlayerState->SetText(FText::FromString(TEXT("EMPTY")));
	}
}

void URoomMemberWidget::SetMemberInfo(const FString& playerName, bool bIsReady)
{
	if (PlayerName) {
		PlayerName->SetText(FText::FromString(playerName));
	}
	if (PlayerState) {
		PlayerState->SetText(FText::FromString(bIsReady ? TEXT("READY") : TEXT("WAITING")));
	}
}