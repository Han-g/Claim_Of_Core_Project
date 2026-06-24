#include "LargeDebrisController.h"

#include "LargeDebrisActor.h"
#include "Engine/World.h"

ALargeDebrisController::ALargeDebrisController()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void ALargeDebrisController::HandleGameplayActivated()
{
	ActivateGameplayRuntime();
}

void ALargeDebrisController::ActivateGameplayRuntime()
{
	if (bRuntimeActivated) { return; }

	bRuntimeActivated = true;

	PrepareDebrisActors(Phase2DebrisActors, 2000);
	PrepareDebrisActors(Phase3DebrisActors, 3000);

	SetActorTickEnabled(true);
}

void ALargeDebrisController::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameState();
	SetActorTickEnabled(false);

	if (CachedGameState)
	{
		if (CachedGameState->IsGameplayActivated())
		{
			ActivateGameplayRuntime();
		}
		else
		{
			CachedGameState->OnGameplayActivated.AddUObject(
				this, &ALargeDebrisController::HandleGameplayActivated);
		}
	}
}

void ALargeDebrisController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bRuntimeActivated) { return; }

	InitializeGameState();
	//HandlePhaseLogic();
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
	if (!CachedGameState) { return; }

	if (CachedGameState->RoundState != ERoundState::Playing) { return; }

	if (CachedGameState->CurrentPhase == EMapPhase::Phase2 && !bPhase2Triggered) {
		TriggerPhase2Debris();
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase3 && !bPhase3Triggered) {
		TriggerPhase3Debris();
	}
}

void ALargeDebrisController::TriggerPhase2Debris()
{
	bPhase2Triggered = true;
	
	UE_LOG(LogTemp, Warning, TEXT("[LargeDebrisController] Trigger Phase2 Debris"));

	for (int32 i = 0; i < Phase2DebrisActors.Num(); ++i)
	{
		ALargeDebrisActor* DebrisActor = Phase2DebrisActors[i];
		if (!DebrisActor) continue;

		const float FixedDelay = 0.2f + i * 1.0f;

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
			FixedDelay,
			false
		);
	}
}

void ALargeDebrisController::TriggerPhase3Debris()
{
	bPhase3Triggered = true;

	UE_LOG(LogTemp, Warning, TEXT("[LargeDebrisController] Trigger Phase3 Debris"));
	
	for (int32 i = 0; i < Phase3DebrisActors.Num(); ++i)
	{
		ALargeDebrisActor* DebrisActor = Phase3DebrisActors[i];
		if (!DebrisActor) continue;

		const float FixedDelay = 0.2f + i * 1.0f;

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
			FixedDelay,
			false
		);
	}

}

bool ALargeDebrisController::ApplyServerChunkBreak(int32 DebrisID, int32 ChunkIndex, bool bFromImpact)
{
	auto ApplyToDebrisArray = [DebrisID, ChunkIndex, bFromImpact](const TArray<TObjectPtr<ALargeDebrisActor>>& DebrisActors)
	{
		for (ALargeDebrisActor* DebrisActor : DebrisActors)
		{
			if (!DebrisActor || DebrisActor->GetLargeDebrisID() != DebrisID)
			{
				continue;
			}

			DebrisActor->ApplyServerChunkBreak(ChunkIndex, bFromImpact);
			return true;
		}

		return false;
	};

	return ApplyToDebrisArray(Phase2DebrisActors) || ApplyToDebrisArray(Phase3DebrisActors);
}

void ALargeDebrisController::PrepareDebrisActors(const TArray<TObjectPtr<ALargeDebrisActor>>& DebrisActors, int32 BaseID)
{
	for (int32 i = 0; i < DebrisActors.Num(); ++i)
	{
		ALargeDebrisActor* DebrisActor = DebrisActors[i];
		if (!DebrisActor) { continue; }

		DebrisActor->SetLargeDebrisID(BaseID + i);
		DebrisActor->PrepareDebris();
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
