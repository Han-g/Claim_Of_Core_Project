// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ClientNetworking.h"

#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "RobbyWidget.generated.h"

/**
 *
 */
UCLASS()
class CLAIM_OF_CORE_API URobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ReloadRoomList(const TArray<FRoomInfoData>& RoomList);

protected:
	virtual void NativeConstruct() override;

private:
	int RoomID;

	UPROPERTY(meta = (BindWidget))
	UButton* CreateButton;
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* RoomScrollBox;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class URoomEnterWidget> RoomEntryClass;

	UFUNCTION()
	void OnCreateButtonClicked();

	UFUNCTION()
	void OnStartButtonClicked();
};
