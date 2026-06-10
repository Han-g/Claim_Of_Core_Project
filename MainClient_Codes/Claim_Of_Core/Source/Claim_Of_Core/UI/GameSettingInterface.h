// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameSettingInterface.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API UGameSettingInterface : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UPROPERTY(meta = (BindWidget))
	UButton* BackToGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SurrenderButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

private:
	UFUNCTION()
	void OnBackToGameClicked();

	UFUNCTION()
	void OnSurrenderClicked();

	UFUNCTION()
	void OnExitGameClicked();
};
