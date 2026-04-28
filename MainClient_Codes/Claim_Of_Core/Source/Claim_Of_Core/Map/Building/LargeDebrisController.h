#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameState/InGame_GameState.h"
#include "LargeDebrisController.generated.h"

class ALargeDebrisActor;

UCLASS()
class CLAIM_OF_CORE_API ALargeDebrisController : public AActor
{
	GENERATED_BODY()

public:
	bool bRuntimeActivated = false;
	ALargeDebrisController();
	void ActivateGameplayRuntime();
	void HandleGameplayActivated();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris")
	TArray<TObjectPtr<ALargeDebrisActor>> Phase2DebrisActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris")
	TArray<TObjectPtr<ALargeDebrisActor>> Phase3DebrisActors;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris")
	float InitialImpulseStrength = 0.f;

protected:
	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bPhase2Triggered = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bPhase3Triggered = false;

protected:
	void InitializeGameState();
	void HandlePhaseLogic();

	void TriggerPhase2Debris();
	void TriggerPhase3Debris();

	void PrepareDebrisActors(const TArray<TObjectPtr<ALargeDebrisActor>>& DebrisActors);
	void ActivateDebrisActors(const TArray<TObjectPtr<ALargeDebrisActor>>& DebrisActors);
};