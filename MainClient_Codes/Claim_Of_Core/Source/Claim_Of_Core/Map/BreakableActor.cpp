#include "BreakableActor.h"
#include "Components/SceneComponent.h"

ABreakableActor::ABreakableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();

	CurrentDurability = MaxDurability;
}

void ABreakableActor::ActivateBreakable()
{
	if (bActivated)
	{
		return;
	}

	bActivated = true;
	BreakableState = EBreakableActorState::Active;

	OnActivatedInternal();
	BP_OnActivated();
}

void ABreakableActor::ResetBreakable()
{
	bActivated = false;
	bBroken = false;
	BreakableState = EBreakableActorState::Idle;
	CurrentDurability = MaxDurability;
}

void ABreakableActor::ApplyBreakableDamage(float DamageAmount)
{
	if (bBroken)
	{
		return;
	}

	CurrentDurability -= DamageAmount;

	if (CurrentDurability <= 0.f)
	{
		BreakActor();
	}
}

void ABreakableActor::BreakActor()
{
	if (bBroken)
	{
		return;
	}

	bBroken = true;
	BreakableState = EBreakableActorState::Broken;

	OnBrokenInternal();
	BP_OnBroken();
}

void ABreakableActor::OnActivatedInternal()
{
}

void ABreakableActor::OnBrokenInternal()
{
}