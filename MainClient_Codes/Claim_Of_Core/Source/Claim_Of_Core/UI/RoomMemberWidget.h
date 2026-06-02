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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoomMemberSlotClicked, int32, SlotIndex);

UCLASS()
class CLAIM_OF_CORE_API URoomMemberWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetEmptyMember();
	void SetMemberInfo(const FString& playerName, bool bIsReady, int32 RoleType, bool bCanSelect);

	void SetSlotIndex(int32 InSlotIndex);

	UPROPERTY(BlueprintAssignable, Category = "Room")
	FOnRoomMemberSlotClicked OnSlotClicked;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* PlayerState;

	UPROPERTY(meta = (BindWidget))
	class UButton* StrikerButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* GuardianButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* ManipulatorButton;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Character")
	int32 SelectedRoleType = -1;

private:
	int32 SlotIndex = -1;
	bool bCanSelectRole = false;

	void SetRoleButtonsEnabled(bool bEnabled);

	UFUNCTION()
	void OnStrikerClicked();

	UFUNCTION()
	void OnGuardianClicked();

	UFUNCTION()
	void OnManipulatorClicked();

	void HandleRoleSelected(int32 InRoleType);

	void UpdateRoleButtonColors();
};
