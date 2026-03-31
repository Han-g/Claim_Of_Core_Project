// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"

#include "RoomMemberWidget.generated.h"

/**
 * 
 */
UCLASS()
class SERVERTEST_API URoomMemberWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMemberInfo(const FString& PlayerName);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* NameText;
};
