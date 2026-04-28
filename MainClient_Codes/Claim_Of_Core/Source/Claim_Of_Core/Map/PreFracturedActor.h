#pragma once

#include "CoreMinimal.h"
#include "BreakableActor.h"
#include "PreFracturedActor.generated.h"

class UStaticMeshComponent;
class AInGame_GameState;

USTRUCT(BlueprintType)
struct FPreFracturedChunkData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunk")
	int32 ChunkIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunk")
	TArray<int32> Neighbors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunk")
	float CurrentDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunk")
	float BreakThreshold = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunk")
	bool bBroken = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Chunk")
	bool bAnchored = false;
};

UCLASS(Abstract)
class CLAIM_OF_CORE_API APreFracturedActor : public ABreakableActor
{
	GENERATED_BODY()

public:
	APreFracturedActor();

protected:
	virtual void BeginPlay() override;

	void InitializeGameState();
	void HandleGameplayActivated();
	void ActivateFractureRuntime();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fracture")
	TArray<TObjectPtr<UStaticMeshComponent>> ChunkMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture")
	TArray<FPreFracturedChunkData> ChunkData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture")
	float ChainScatterImpulse = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture")
	bool bFreezeAfterChainReaction = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture")
	float FreezeDelay = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture")
	float NeighborDamageRatio = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture")
	FName ChunkTag = "Chunk";

public:
	UFUNCTION(BlueprintCallable, Category = "Fracture")
	virtual void PrepareFracture();

	UFUNCTION(BlueprintCallable, Category = "Fracture")
	virtual void ApplyDamageToChunk(int32 ChunkIndex, float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Fracture")
	virtual void BreakChunk(int32 ChunkIndex, bool bFromImpact = false);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture|AutoGraph")
	bool bAutoBuildGraph = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture|AutoGraph")
	float NeighborDistanceThreshold = 55.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture|AutoGraph")
	bool bAutoSetAnchored = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fracture|AutoGraph")
	float AnchorBottomTolerance = 20.f;

protected:
	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Fracture")
	bool bFractureRuntimeActivated = false;

protected:
	void CollectChunkMeshes();
	void InitializeChunkData();
	bool IsValidChunkIndex(int32 ChunkIndex) const;
	int32 FindChunkIndexByComponent(const UPrimitiveComponent* HitComp) const;

	virtual void OnChunkBrokenInternal(int32 BrokenChunkIndex, bool bFromImpact);
	virtual void DropUnsupportedChunks();
	virtual void FreezeRemainingChunks();

	void AutoBuildNeighborGraph();
	void AutoSetAnchoredChunks();
protected:
	virtual void OnBrokenInternal() override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Fracture")
	void BP_OnChunkBroken(int32 BrokenChunkIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Fracture")
	void BP_OnChainReactionFinished();
};