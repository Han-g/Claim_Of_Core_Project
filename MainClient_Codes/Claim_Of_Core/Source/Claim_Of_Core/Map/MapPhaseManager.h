#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameState/InGame_GameState.h"
#include "MapPhaseManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMapPhaseChangedSignature, EMapPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRoundStateChangedSignature, ERoundState, NewRoundState);

UCLASS()
class CLAIM_OF_CORE_API AMapPhaseManager : public AActor
{
	GENERATED_BODY()

public:
	AMapPhaseManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phase")
	EMapPhase CachedPhase = EMapPhase::None;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phase")
	ERoundState CachedRoundState = ERoundState::Waiting;

public:
	UPROPERTY(BlueprintAssignable, Category = "Phase")
	FOnMapPhaseChangedSignature OnMapPhaseChanged;

	UPROPERTY(BlueprintAssignable, Category = "Phase")
	FOnRoundStateChangedSignature OnRoundStateChanged;

public:
	UFUNCTION(BlueprintCallable, Category = "Phase")
	void InitializeFromGameState();

	UFUNCTION(BlueprintPure, Category = "Phase")
	AInGame_GameState* GetInGameGameState() const { return CachedGameState; }

	UFUNCTION(BlueprintPure, Category = "Phase")
	EMapPhase GetCurrentMapPhase() const { return CachedPhase; }

	UFUNCTION(BlueprintPure, Category = "Phase")
	ERoundState GetCurrentRoundState() const { return CachedRoundState; }

	UFUNCTION(BlueprintPure, Category = "Phase")
	bool IsRoundPlaying() const { return CachedRoundState == ERoundState::Playing; }

protected:
	void UpdateFromGameState();
	void HandlePhaseChanged(EMapPhase NewPhase);
	void HandleRoundStateChanged(ERoundState NewRoundState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Phase")
	void BP_OnMapPhaseChanged(EMapPhase NewPhase);

	UFUNCTION(BlueprintImplementableEvent, Category = "Phase")
	void BP_OnRoundStateChanged(ERoundState NewRoundState);
};