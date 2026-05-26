#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../GameState/InGame_GameState.h"
#include "IceChillSpawner.generated.h"

class AIceChillZone;
class UBoxComponent;

UCLASS()
class CLAIM_OF_CORE_API AIceChillSpawner : public AActor
{
	GENERATED_BODY()

public:
	AIceChillSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	TSubclassOf<AIceChillZone> ChillZoneClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float SpawnZ = 130.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase2")
	float Phase2MinSpawnInterval = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase2")
	float Phase2MaxSpawnInterval = 16.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase2")
	int32 Phase2SpawnCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase3")
	float Phase3MinSpawnInterval = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase3")
	float Phase3MaxSpawnInterval = 9.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase3")
	int32 Phase3MinSpawnCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner|Phase3")
	int32 Phase3MaxSpawnCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	bool bDrawDebugBox = false;

	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState = nullptr;

	float SpawnAccumulator = 0.f;
	float NextSpawnTime = 0.f;

	void InitializeGameState();
	void UpdateSpawner(float DeltaTime);
	void SpawnChillZones();

	float GetRandomSpawnInterval() const;
	int32 GetRandomSpawnCount() const;
	FVector GetRandomSpawnLocation() const;
	bool CanSpawn() const;
};
