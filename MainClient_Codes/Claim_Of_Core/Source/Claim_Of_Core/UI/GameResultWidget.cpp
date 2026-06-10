// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameResultWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Widget.h"
#include "Engine/Texture2D.h"
#include "Kismet/GameplayStatics.h"
#include "UI/NetworkInstance.h"

void UGameResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ExitButton)
	{
		ExitButton->OnClicked.RemoveDynamic(this, &UGameResultWidget::OnExitClicked);
		ExitButton->OnClicked.AddDynamic(this, &UGameResultWidget::OnExitClicked);
	}
}

void UGameResultWidget::SetGameResultInfo(
	int32 WinnerTeamID,
	int32 Team1Score,
	int32 Team2Score,
	const TArray<FRoundChangePacket>& RoundResults
)
{
	if (ResultTag)
	{
		ResultTag->SetText(FText::FromString(GetWinnerText(WinnerTeamID)));
	}

	if (GameResult)
	{
		GameResult->SetText(FText::FromString(
			FString::Printf(TEXT("%d : %d"), Team1Score, Team2Score)
		));
	}

	ClearRoundRows();

	TArray<FRoundChangePacket> SortedResults = RoundResults;
	SortedResults.Sort([](const FRoundChangePacket& A, const FRoundChangePacket& B)
		{
			return A.currentRound < B.currentRound;
		});

	for (int32 Index = 0; Index < SortedResults.Num() && Index < 5; ++Index)
	{
		SetRoundRow(Index, SortedResults[Index]);
	}
}

void UGameResultWidget::ClearRoundRows()
{
	const TArray<UWidget*> RowWidgets = {
		Round1From, Round2From, Round3From, Round4From, Round5From
	};

	const TArray<UImage*> MapImages = {
		Map1Image, Map2Image, Map3Image, Map4Image, Map5Image
	};

	const TArray<UTextBlock*> ResultTexts = {
		Round1Result, Round2Result, Round3Result, Round4Result, Round5Result
	};

	for (int32 Index = 0; Index < 5; ++Index)
	{
		if (RowWidgets[Index])
		{
			RowWidgets[Index]->SetVisibility(ESlateVisibility::Collapsed);
		}

		if (MapImages[Index])
		{
			MapImages[Index]->SetVisibility(ESlateVisibility::Hidden);
		}

		if (ResultTexts[Index])
		{
			ResultTexts[Index]->SetText(FText::GetEmpty());
		}
	}
}

void UGameResultWidget::SetRoundRow(int32 RowIndex, const FRoundChangePacket& Packet)
{
	const TArray<UWidget*> RowWidgets = {
		Round1From, Round2From, Round3From, Round4From, Round5From
	};

	const TArray<UImage*> MapImages = {
		Map1Image, Map2Image, Map3Image, Map4Image, Map5Image
	};

	const TArray<UTextBlock*> ResultTexts = {
		Round1Result, Round2Result, Round3Result, Round4Result, Round5Result
	};

	if (!MapImages.IsValidIndex(RowIndex) || !ResultTexts.IsValidIndex(RowIndex))
	{
		return;
	}

	if (RowWidgets.IsValidIndex(RowIndex) && RowWidgets[RowIndex])
	{
		RowWidgets[RowIndex]->SetVisibility(ESlateVisibility::Visible);
	}

	if (UTexture2D* MapTexture = GetMapTexture(Packet.currentMap))
	{
		MapImages[RowIndex]->SetBrushFromTexture(MapTexture, true);
		MapImages[RowIndex]->SetVisibility(ESlateVisibility::Visible);
	}

	ResultTexts[RowIndex]->SetText(
		FText::FromString(GetWinnerText(Packet.result.winnerTeamID))
	);
}

UTexture2D* UGameResultWidget::GetMapTexture(int32 MapType) const
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

FString UGameResultWidget::GetWinnerText(int32 WinnerTeamID) const
{
	switch (WinnerTeamID)
	{
	case 0:
		return TEXT("Team1 WIN");
	case 1:
		return TEXT("Team2 WIN");
	default:
		return TEXT("DRAW");
	}
}

void UGameResultWidget::OnExitClicked()
{
	if (UNetworkInstance* GI = Cast<UNetworkInstance>(GetGameInstance()))
	{
		GI->ReturnToLobbyFromResult();
	}
}