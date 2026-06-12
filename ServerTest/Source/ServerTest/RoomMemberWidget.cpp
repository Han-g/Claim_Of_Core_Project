// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMemberWidget.h"

void URoomMemberWidget::SetMemberInfo(const FString& PlayerName)
{
	if (NameText) {
		NameText->SetText(FText::FromString(PlayerName));
	}
}