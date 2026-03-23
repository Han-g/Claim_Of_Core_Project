#include "IceFloorTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

AIceFloorTile::AIceFloorTile()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	FloorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorMesh"));
	FloorMesh->SetupAttachment(Root);
	FloorMesh->SetSimulatePhysics(false);
	FloorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	FloorMesh->SetCollisionProfileName(TEXT("BlockAll"));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(Root);
	TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 20.f));

	bFallWhenBroken = false;
}

void AIceFloorTile::BeginPlay()
{
	Super::BeginPlay();
}

void AIceFloorTile::SetCracked()
{
	if (CurrentState != EIceFloorState::Normal)
	{
		return;
	}

	CurrentState = EIceFloorState::Cracked;
	BP_OnCracked();
}

void AIceFloorTile::StartBreaking()
{
	if (CurrentState == EIceFloorState::Broken || CurrentState == EIceFloorState::Breaking)
	{
		return;
	}

	if (CurrentState == EIceFloorState::Normal)
	{
		SetCracked();
	}

	CurrentState = EIceFloorState::Breaking;
	BP_OnBreaking();

	GetWorldTimerManager().SetTimer(
		BreakTimerHandle,
		this,
		&AIceFloorTile::BreakFloor,
		BreakDelay,
		false
	);
}

void AIceFloorTile::BreakFloor()
{
	if (CurrentState == EIceFloorState::Broken)
	{
		return;
	}

	CurrentState = EIceFloorState::Broken;

	FloorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	if (bFallWhenBroken)
	{
		FloorMesh->SetSimulatePhysics(true);
		FloorMesh->SetEnableGravity(true);
	}
	else
	{
		SetActorHiddenInGame(true);
	}

	BP_OnBroken();

	SetLifeSpan(FallenLifeSpan);
}