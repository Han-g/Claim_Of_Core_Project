// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"

#include "RoomWidget.generated.h"

/**
 * 
 */
UCLASS()
class SERVERTEST_API URoomWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void UpdateMemberList(const TArray<FString>& PlayerList);

protected:
	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* MemberList;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class URoomMemberWidget> MemberWidgetClass;
};
