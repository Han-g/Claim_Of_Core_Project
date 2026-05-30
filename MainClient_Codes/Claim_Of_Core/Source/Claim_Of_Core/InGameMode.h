// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API AInGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(
		AController* NewPlayer,
		const FTransform& SpawnTransform) override;
};
