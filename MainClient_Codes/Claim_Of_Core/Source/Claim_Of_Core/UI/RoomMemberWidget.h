// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "RoomMemberWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API URoomMemberWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetEmptyMember();
	void SetMemberInfo(const FString& playerName, bool bIsReady);

protected:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerState;

	UPROPERTY(meta = (BindWidget))
	class UButton* Striker;

	UPROPERTY(meta = (BindWidget))
	class UButton* Guardian;

	UPROPERTY(meta = (BindWidget))
	class UButton* Manipulator;
};
