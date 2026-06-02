// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "URoundPrepareWidget.generated.h"

class UImage;
class UTextBlock;
class UTexture2D;

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API URoundPrepareWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Round")
	void SetRoundPrepareInfo(
		int32 CurrentRound,
		int32 MaxRound,
		int32 Team1Score,
		int32 Team2Score,
		float MapSelectTime
	);

	UFUNCTION(BlueprintCallable, Category = "Round")
	void SetSelectedMap(int32 MapType);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	UImage* SelectedMapImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoundText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreBoardText = nullptr;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CounterText = nullptr;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Round|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* BuildingMapImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Round|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* IceCaveMapImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Round|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* SpaceStationMapImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Round|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* JungleMapImage = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Round|Map", meta = (AllowPrivateAccess = "true"))
	UTexture2D* SkyIslandMapImage = nullptr;

	float RemainingTime = 0.0f;
	bool bCountingDown = false;

	void UpdateCounterText();
	UTexture2D* GetMapTexture(int32 MapType) const;
};