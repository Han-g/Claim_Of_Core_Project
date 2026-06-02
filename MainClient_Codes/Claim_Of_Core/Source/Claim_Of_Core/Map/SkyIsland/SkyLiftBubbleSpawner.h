#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkyLiftBubbleSpawner.generated.h"

class ASkyLiftBubble;
class UBoxComponent;

UCLASS()
class CLAIM_OF_CORE_API ASkyLiftBubbleSpawner : public AActor
{
	GENERATED_BODY()

public:
	ASkyLiftBubbleSpawner();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UBoxComponent> SpawnArea;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	TSubclassOf<ASkyLiftBubble> BubbleClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float MinSpawnInterval = 7.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float MaxSpawnInterval = 13.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	int32 MaxActiveBubbles = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawner")
	float SpawnZOffset = 120.f;

	TArray<TWeakObjectPtr<ASkyLiftBubble>> ActiveBubbles;
	float SpawnAccumulator = 0.f;
	float NextSpawnTime = 0.f;

	void SpawnBubble();
	void CleanupInactiveBubbles();
	void ResetNextSpawnTime();
	FVector GetRandomSpawnLocation() const;
};
