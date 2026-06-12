#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../BreakableActor.h"
#include "../../GameState/InGame_GameState.h"
#include "IceFloorTile.generated.h"

class UPrimitiveComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UMaterialInterface;
class AMyCharacter;

//UENUM(BlueprintType)
//enum class EIceFloorState : uint8
//{
//	Normal,
//	Cracked,
//	Breaking,
//	Broken
//};
//
//USTRUCT(BlueprintType)
//struct FIceFloorPieceData
//{
//	GENERATED_BODY()
//
//	UPROPERTY()
//	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;
//
//	UPROPERTY()
//	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial = nullptr;
//
//	UPROPERTY()
//	float DistanceToCenter = 0.f;
//
//	UPROPERTY()
//	EIceFloorState State = EIceFloorState::Normal;
//};

UCLASS()
class CLAIM_OF_CORE_API AIceFloorTile : public ABreakableActor
{
	GENERATED_BODY()

public:
	AIceFloorTile();

	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	void StartBreaking();

	// Local Ice floor Distruction Process -> Need to delete
	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	void NotifyPlayerStandingOnPiece(AMyCharacter* StandingCharacter, UPrimitiveComponent* StandingComponent);

	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	int32 GetPieceIndexFromComponent(UPrimitiveComponent* PieceComponent) const { return FindPieceIndex(PieceComponent); };

	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	void ApplyNetworkPieceState(int32 PieceIndex, int32 EventState);

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

	UPROPERTY()
	TArray<float> PieceDamageProgress;

	UPROPERTY()
	TArray<uint8> PieceCrackedByStandingFlags;

	UPROPERTY()
	TArray<uint8> PieceBrokenFlags;

	TArray<TSet<TWeakObjectPtr<AMyCharacter>>> StandingCharactersByPiece;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	FName IcePieceTag = TEXT("IcePiece");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|StandingBreak")
	bool bUsePhaseEdgeBreaking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|StandingBreak")
	float Phase2StandingBreakTime = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|StandingBreak")
	float Phase3StandingBreakTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|StandingBreak")
	float CrackProgressThreshold = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float Phase2BreakInterval = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float Phase3BreakInterval = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float CrackDelay = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float DownImpulse = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float BrokenDestroyDelay = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	TObjectPtr<UMaterialInterface> m_CrackedMaterial = nullptr;

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
	void ProcessStandingDamage(float DeltaTime);

	void CrackPiece(int32 PieceIndex);
	void BreakPiece(int32 PieceIndex);

	float GetCurrentStandingBreakTime() const;
	float GetCurrentBreakInterval() const;
	bool AreAllBreakablePiecesBroken() const;

	int32 FindPieceIndex(UPrimitiveComponent* PieceComponent) const;
	void DestroyPieceLater(UStaticMeshComponent* Piece);
};