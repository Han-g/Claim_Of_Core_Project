// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/SkyIsland/SkyLiftBubbleSpawner.h"

// Sets default values
ASkyLiftBubbleSpawner::ASkyLiftBubbleSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkyLiftBubbleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASkyLiftBubbleSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

