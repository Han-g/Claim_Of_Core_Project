// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManager.generated.h"

class USoundBase;
class UAudioComponent;

UCLASS()
class CLAIM_OF_CORE_API ASoundManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	TObjectPtr<USoundBase> BGM;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	float Volume = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sound")
	bool bLoop = true;

private:
	UPROPERTY()
	TObjectPtr<UAudioComponent> BGMComponent;

	bool bManualStop = false;

	UFUNCTION()
	void HandleBGMFinished();

	void PlayBGM();
	void StopBGM();
};
