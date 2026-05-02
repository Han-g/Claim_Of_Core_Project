#include "MapPhaseManager.h"
#include "Kismet/GameplayStatics.h"

AMapPhaseManager::AMapPhaseManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMapPhaseManager::BeginPlay()
{
	Super::BeginPlay();

	InitializeFromGameState();

	if (!CachedGameState) { return; }

	CachedGameState->OnNativeRoundStateChanged.AddUObject(
		this, &AMapPhaseManager::HandleRoundStateChangedFromGameState);

	CachedGameState->OnNativePhaseChanged.AddUObject(
		this, &AMapPhaseManager::HandlePhaseChangedFromGameState);

	HandleRoundStateChanged(CachedGameState->RoundState);
	HandlePhaseChanged(CachedGameState->CurrentPhase);

	SetActorTickEnabled(false);
	//UpdateFromGameState();
}

void AMapPhaseManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateFromGameState();
}

void AMapPhaseManager::InitializeFromGameState()
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

void AMapPhaseManager::UpdateFromGameState()
{
	if (!CachedGameState)
	{
		InitializeFromGameState();
	}

	if (!CachedGameState)
	{
		return;
	}

	if (CachedRoundState != CachedGameState->RoundState)
	{
		HandleRoundStateChanged(CachedGameState->RoundState);
	}

	if (CachedPhase != CachedGameState->CurrentPhase)
	{
		HandlePhaseChanged(CachedGameState->CurrentPhase);
	}
}

void AMapPhaseManager::HandlePhaseChanged(EMapPhase NewPhase)
{
	CachedPhase = NewPhase;

	UE_LOG(LogTemp, Warning, TEXT("[MapPhaseManager] Map Phase Changed: %s"),
		*UEnum::GetValueAsString(CachedPhase));

	OnMapPhaseChanged.Broadcast(CachedPhase);
	BP_OnMapPhaseChanged(CachedPhase);
}

void AMapPhaseManager::HandleRoundStateChanged(ERoundState NewRoundState)
{
	CachedRoundState = NewRoundState;

	UE_LOG(LogTemp, Warning, TEXT("[MapPhaseManager] Round State Changed: %s"),
		*UEnum::GetValueAsString(CachedRoundState));

	OnRoundStateChanged.Broadcast(CachedRoundState);
	BP_OnRoundStateChanged(CachedRoundState);
}

void AMapPhaseManager::HandleRoundStateChangedFromGameState(ERoundState OldState, ERoundState NewState)
{
	HandleRoundStateChanged(NewState);
}

void AMapPhaseManager::HandlePhaseChangedFromGameState(EMapPhase OldPhase, EMapPhase NewPhase)
{
	HandlePhaseChanged(NewPhase);
}
