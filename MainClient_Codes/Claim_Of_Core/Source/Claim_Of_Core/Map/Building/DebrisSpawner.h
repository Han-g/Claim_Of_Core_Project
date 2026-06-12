#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameState/InGame_GameState.h"
#include "DebrisSpawner.generated.h"

class ASmallDebrisActor;
class UBoxComponent;

UCLASS()
class CLAIM_OF_CORE_API ADebrisSpawner : public AActor
{
	GENERATED_BODY()

public:
	ADebrisSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> SpawnArea;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	TSubclassOf<ASmallDebrisActor> DebrisClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float SpawnHeightOffset = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float RandomHeightOffset = 100.f;

	// Phase 1
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase1")
	float Phase1MinSpawnInterval = 6.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase1")
	float Phase1MaxSpawnInterval = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase1")
	int32 Phase1MinSpawnCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase1")
	int32 Phase1MaxSpawnCount = 1;

	// Phase 2
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase2")
	float Phase2MinSpawnInterval = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase2")
	float Phase2MaxSpawnInterval = 6.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase2")
	int32 Phase2MinSpawnCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase2")
	int32 Phase2MaxSpawnCount = 2;

	// Phase 3
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase3")
	float Phase3MinSpawnInterval = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase3")
	float Phase3MaxSpawnInterval = 4.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase3")
	int32 Phase3MinSpawnCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase3")
	int32 Phase3MaxSpawnCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	bool bDrawDebugBox = false;

protected:
	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState = nullptr;

	float SpawnAccumulator = 0.f;
	float NextSpawnTime = 0.f;

protected:
	void InitializeGameState();
	void UpdateSpawner(float DeltaTime);
	void SpawnDebrisByCurrentPhase();

	float GetRandomSpawnInterval() const;
	int32 GetRandomSpawnCount() const;
	FVector GetRandomSpawnLocation() const;
	bool CanSpawn() const;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};