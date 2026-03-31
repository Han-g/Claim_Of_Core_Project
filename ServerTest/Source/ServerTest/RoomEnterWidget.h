// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "RoomEnterWidget.generated.h"

#define MAXPLAYER 6

/**
 * 
 */
UCLASS()
class SERVERTEST_API URoomEnterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitRoomInfo(int32 s_RoomID, const FString& s_RoomName);
	void UpdatePlayerCount(int32 CurrentPlayers);

	int32 GetRoomID() const { return RoomID; }

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoomName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerCounter;

	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton;

	int32 RoomID;

	UFUNCTION()
	void OnJoinButtonClicked();
};
