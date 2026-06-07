// Fill out your copyright notice in the Description page of Project Settings.


#include "RoundWinWidget.h"

void URoundWinWidget::SetRoundResultInfo(int32 WinnerTeamID, int32 Team1Score, int32 Team2Score)
{
    if (!RoundResult)
    {
        return;
    }

    const FString ResultText =
        WinnerTeamID >= 0
        ? FString::Printf(TEXT("Team %d WIN"), WinnerTeamID)
        : TEXT("DRAW");

    RoundResult->SetText(FText::FromString(ResultText));
}
