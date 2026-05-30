// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMode.h"

APawn* AInGameMode::SpawnDefaultPawnAtTransform_Implementation(
	AController* NewPlayer,
	const FTransform& SpawnTransform)
{
	FTransform FinalTransform = SpawnTransform;

	const UWorld* World = GetWorld();
	const bool bIsSpaceMap =
		World && World->GetMapName().Contains(TEXT("SpaceStationStage"));

	if (bIsSpaceMap && SpawnTransform.GetLocation().IsNearlyZero())
	{
		FinalTransform.SetLocation(FVector(600.f, -3000.f, 2000.f));

		UE_LOG(LogTemp, Warning,
			TEXT("[InGameModeCpp] Space fallback spawn applied. Old=%s New=%s"),
			*SpawnTransform.GetLocation().ToString(),
			*FinalTransform.GetLocation().ToString());
	}

	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, FinalTransform);
}