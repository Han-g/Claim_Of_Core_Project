// Fill out your copyright notice in the Description page of Project Settings.


#include "Sound/SoundManager.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"


// Sets default values
ASoundManager::ASoundManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASoundManager::BeginPlay()
{
	Super::BeginPlay();

	PlayBGM();
}

void ASoundManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	StopBGM();
	Super::EndPlay(EndPlayReason);
}

void ASoundManager::PlayBGM()
{
	if (!BGM || BGMComponent)
	{
		return;
	}

	bManualStop = false;

	BGMComponent = UGameplayStatics::SpawnSound2D(this, BGM, Volume);
	if (BGMComponent)
	{
		BGMComponent->bAutoDestroy = false;
		BGMComponent->OnAudioFinished.AddUniqueDynamic(this, &ASoundManager::HandleBGMFinished);
	}
}

void ASoundManager::StopBGM()
{
	bManualStop = true;

	if (BGMComponent)
	{
		BGMComponent->Stop();
		BGMComponent = nullptr;
	}
}

void ASoundManager::HandleBGMFinished()
{
	BGMComponent = nullptr;

	if (bLoop && !bManualStop)
	{
		PlayBGM();
	}
}