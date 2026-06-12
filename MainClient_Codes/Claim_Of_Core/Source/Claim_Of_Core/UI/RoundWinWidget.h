// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "RoundWinWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API URoundWinWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = "Round")
	void SetRoundResultInfo(int32 WinnerTeamID, int32 Team1Score, int32 Team2Score);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoundResult = nullptr;
};
