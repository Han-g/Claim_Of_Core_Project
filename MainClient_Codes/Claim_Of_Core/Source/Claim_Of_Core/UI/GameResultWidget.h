// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ClientNetworkTypes.h"
#include "GameResultWidget.generated.h"

class UTextBlock;
class UButton;
class UImage;
class UTexture2D;
class UWidget;

struct FRoundChangePacket;

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API UGameResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetGameResultInfo(int32 WinnerTeamID, int32 Team1Score, int32 Team2Score,
		const TArray<FRoundChangePacket>& RoundResults);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* ResultTag = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GameResult = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton = nullptr;

	UPROPERTY(meta = (BindWidgetOptional))
	UWidget* Round1From = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	UWidget* Round2From = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	UWidget* Round3From = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	UWidget* Round4From = nullptr;
	UPROPERTY(meta = (BindWidgetOptional))
	UWidget* Round5From = nullptr;

	UPROPERTY(meta = (BindWidget))
	UImage* Map1Image = nullptr;
	UPROPERTY(meta = (BindWidget))
	UImage* Map2Image = nullptr;
	UPROPERTY(meta = (BindWidget))
	UImage* Map3Image = nullptr;
	UPROPERTY(meta = (BindWidget))
	UImage* Map4Image = nullptr;
	UPROPERTY(meta = (BindWidget))
	UImage* Map5Image = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Round1Result = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Round2Result = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Round3Result = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Round4Result = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Round5Result = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Result|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* BuildingMapImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Result|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* IceCaveMapImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Result|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* SpaceStationMapImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Result|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* JungleMapImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Result|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* SkyIslandMapImage = nullptr;

	UFUNCTION()
	void OnExitClicked();

	void ClearRoundRows();
	void SetRoundRow(int32 RowIndex, const FRoundChangePacket& Packet);

	UTexture2D* GetMapTexture(int32 MapType) const;
	FString GetWinnerText(int32 WinnerTeamID) const;
};
