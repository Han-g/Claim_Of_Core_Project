#include "LargeDebrisController.h"

#include "LargeDebrisActor.h"
#include "Engine/World.h"

ALargeDebrisController::ALargeDebrisController()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void ALargeDebrisController::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameState();

	PrepareDebrisActors(Phase2DebrisActors);
	PrepareDebrisActors(Phase3DebrisActors);
}

void ALargeDebrisController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InitializeGameState();
	HandlePhaseLogic();
}

void ALargeDebrisController::InitializeGameState()
{
	if (CachedGameState)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		CachedGameState = World->GetGameState<AInGame_GameState>();
	}
}

void ALargeDebrisController::HandlePhaseLogic()
{
	if (!CachedGameState)
	{
		return;
	}

	if (CachedGameState->RoundState != ERoundState::Playing)
	{
		return;
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase2 && !bPhase2Triggered)
	{
		TriggerPhase2Debris();
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase3 && !bPhase3Triggered)
	{
		TriggerPhase3Debris();
	}
}

void ALargeDebrisController::TriggerPhase2Debris()
{
	bPhase2Triggered = true;
	
	UE_LOG(LogTemp, Warning, TEXT("[LargeDebrisController] Trigger Phase2 Debris"));

	for (ALargeDebrisActor* DebrisActor : Phase2DebrisActors)
	{
		if (!DebrisActor) continue;

		const float RandomDelay = FMath::FRandRange(0.2f, 2.5f);

		FTimerHandle TempHandle;
		FTimerDelegate TimerDel;
		TimerDel.BindLambda([this, DebrisActor]()
			{
				if (DebrisActor)
				{
					DebrisActor->ActivateDebris(InitialImpulseStrength);
					DebrisActor->SetActorHiddenInGame(false);
				}
			});

		GetWorld()->GetTimerManager().SetTimer(
			TempHandle,
			TimerDel,
			RandomDelay,
			false
		);
	}
}

void ALargeDebrisController::TriggerPhase3Debris()
{
	bPhase3Triggered = true;

	UE_LOG(LogTemp, Warning, TEXT("[LargeDebrisController] Trigger Phase3 Debris"));
	
	for (ALargeDebrisActor* DebrisActor : Phase3DebrisActors)
	{
		if (!DebrisActor) continue;

		const float RandomDelay = FMath::FRandRange(0.2f, 2.5f);

		FTimerHandle TempHandle;
		FTimerDelegate TimerDel;
		TimerDel.BindLambda([this, DebrisActor]()
			{
				if (DebrisActor)
				{
					DebrisActor->ActivateDebris(InitialImpulseStrength);
				}
			});

		GetWorld()->GetTimerManager().SetTimer(
			TempHandle,
			TimerDel,
			RandomDelay,
			false
		);
	}

}

void ALargeDebrisController::PrepareDebrisActors(const TArray<TObjectPtr<ALargeDebrisActor>>& DebrisActors)
{
	for (ALargeDebrisActor* DebrisActor : DebrisActors)
	{
		if (DebrisActor)
		{
			DebrisActor->PrepareDebris();
		}
	}
}

void ALargeDebrisController::ActivateDebrisActors(const TArray<TObjectPtr<ALargeDebrisActor>>& DebrisActors)
{
	for (ALargeDebrisActor* DebrisActor : DebrisActors)
	{
		if (DebrisActor)
		{
			DebrisActor->ActivateDebris(InitialImpulseStrength);
		}
	}
}