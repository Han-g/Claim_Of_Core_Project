#include "BGMManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

ABGMManager::ABGMManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABGMManager::BeginPlay()
{
	Super::BeginPlay();

	if (BGM)
	{
		BGMComponent = UGameplayStatics::SpawnSound2D(
			this,
			BGM,
			Volume,
			1.0f,
			0.0f
		);

		if (BGMComponent && bLoop)
		{
			BGMComponent->bAutoDestroy = false;
		}
	}
}
