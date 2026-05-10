#pragma once

#include "CoreMinimal.h"
#include "../BreakableActor.h"
#include "../../GameState/InGame_GameState.h"
#include "IceFloorTile.generated.h"

UCLASS()
class CLAIM_OF_CORE_API AIceFloorTile : public ABreakableActor
{
	GENERATED_BODY()

public:
	AIceFloorTile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IceFloor")
	TArray<TObjectPtr<UStaticMeshComponent>> IcePieces;

	UPROPERTY()
	TArray<int32> SortedPieceIndices;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float Phase2BreakInterval = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float Phase3BreakInterval = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float CrackDelay = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float DownImpulse = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float BrokenDestroyDelay = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	TObjectPtr<UMaterialInterface> CrackedMaterial = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|Donut")
	float InnerSafeRadius = 4000.f;

	int32 CurrentPieceIndex = 0;
	float Timer = 0.f;

	bool bStartedBreaking = false;
	bool bCurrentPieceCracked = false;

	void CollectIcePieces();
	void BuildBreakOrder();
	void CheckPhaseAndStart();
	void ProcessBreaking(float DeltaTime);

	void CrackPiece(int32 PieceIndex);
	void BreakPiece(int32 PieceIndex);

	void DestroyPieceLater(UStaticMeshComponent* Piece);
};