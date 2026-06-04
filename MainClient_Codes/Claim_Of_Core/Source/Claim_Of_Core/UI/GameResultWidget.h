// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameResultWidget.generated.h"

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API UGameResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetGameResultInfo(int32 WinnerTeamID, int32 Team1Score, int32 Team2Score);

private:

};
