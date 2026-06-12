// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/URoundPrepareWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

void URoundPrepareWidget::SetRoundPrepareInfo(
	int32 CurrentRound,
	int32 MaxRound,
	int32 Team1Score,
	int32 Team2Score,
	float MapSelectTime
)
{
	if (RoundText)
	{
		RoundText->SetText(FText::FromString(
			FString::Printf(TEXT("%d / %d"), CurrentRound, MaxRound)
		));
	}

	if (ScoreBoardText)
	{
		ScoreBoardText->SetText(FText::FromString(
			FString::Printf(TEXT("%d : %d"), Team1Score, Team2Score)
		));
	}

	RemainingTime = MapSelectTime;
	bCountingDown = true;
	UpdateCounterText();
}

void URoundPrepareWidget::SetSelectedMap(int32 MapType)
{
	if (SelectedMapImage)
	{
		if (UTexture2D* MapTexture = GetMapTexture(MapType))
		{
			SelectedMapImage->SetBrushFromTexture(MapTexture, true);
		}
	}

	RemainingTime = 5.0f;
	bCountingDown = true;
	UpdateCounterText();
}

void URoundPrepareWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bCountingDown)
	{
		return;
	}

	RemainingTime -= InDeltaTime;
	if (RemainingTime <= 0.0f)
	{
		RemainingTime = 0.0f;
		bCountingDown = false;
	}

	UpdateCounterText();
}

void URoundPrepareWidget::UpdateCounterText()
{
	if (!CounterText)
	{
		return;
	}

	const int32 DisplayTime = FMath::CeilToInt(RemainingTime);
	CounterText->SetText(FText::FromString(FString::Printf(TEXT("%d"), DisplayTime)));
}

UTexture2D* URoundPrepareWidget::GetMapTexture(int32 MapType) const
{
	switch (MapType)
	{
	case 1:
		return BuildingMapImage;
	case 2:
		return IceCaveMapImage;
	case 3:
		return SpaceStationMapImage;
	case 4:
		return JungleMapImage;
	case 5:
		return SkyIslandMapImage;
	default:
		return nullptr;
	}
}