// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "ClientNetworking.h"

#include "RoomWidget.generated.h"

/**
 *
 */

UCLASS()
class CLAIM_OF_CORE_API URoomWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void UpdateMemberList(const TArray<FRoomMemberInfo>& PlayerList);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UUniformGridPanel* MemberList;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MemberCount;


	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class URoomMemberWidget> MemberWidgetClass;

private:
	UFUNCTION()
	void OnStartButtonClicked();
};
