// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "LoginWidget.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnLoginResult);

UCLASS()
class CLAIM_OF_CORE_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void ShowPopup(const FText& PopupMessage);
	UFUNCTION()
	void HidePopup();

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

private:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ID_BOX;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* PW_BOX;

	UPROPERTY(meta = (BindWidget))
	UButton* RegisterButton;

	UPROPERTY(meta = (BindWidget))
	UButton* LoginButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* FailLoginPopUp;

	//FOnLoginResult OnLoginResult;

	FTimerHandle FailPopupTimerHandle;

	UFUNCTION()
	void OnLoginClicked();

	UFUNCTION()
	void OnRegisterCliecked();
};
