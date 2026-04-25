#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceFloorTile.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class UMaterialInstanceDynamic;
class AInGame_GameState;

UENUM(BlueprintType)
enum class EIcePieceState : uint8
{
	Normal,
	Cracked,
	Breaking,
	Broken
};

USTRUCT(BlueprintType)
struct FIceFloorPieceData
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> DynamicMaterial = nullptr;

	UPROPERTY()
	float DistanceToCenter = 0.f;

	UPROPERTY()
	EIcePieceState State = EIcePieceState::Normal;
};

UCLASS()
class CLAIM_OF_CORE_API AIceFloorTile : public AActor
{
	GENERATED_BODY()

public:
	AIceFloorTile();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IceFloor")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(BlueprintReadOnly, Category = "IceFloor")
	TArray<FIceFloorPieceData> IcePieces;

	UPROPERTY(BlueprintReadOnly, Category = "IceFloor")
	FVector FloorCenter = FVector::ZeroVector;

	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|Material")
	FName CrackAmountParamName = TEXT("CrackAmount");

	// true면 태그가 붙은 조각만 수집
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|Collect")
	bool bUsePieceTag = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|Collect")
	FName IcePieceTag = TEXT("IcePiece");

	// 이 거리보다 중심에 가까운 조각은 안 깨짐
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|RandomBreak")
	float MinSafeDistance = 300.f;

	// Phase2에서 랜덤으로 금 가는 간격
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|RandomBreak")
	float Phase2RandomInterval = 0.6f;

	// Phase3에서 더 빠르게 금 가는 간격
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|RandomBreak")
	float Phase3RandomInterval = 0.25f;

	// 금 간 뒤 깨지기까지 랜덤 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|RandomBreak")
	float BreakAfterCrackMinDelay = 0.7f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|RandomBreak")
	float BreakAfterCrackMaxDelay = 1.8f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|Break")
	bool bFallWhenBroken = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|Break")
	float PhysicsLinearDamping = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|Break")
	float PhysicsAngularDamping = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor|Break")
	float BrokenPieceHideDelay = 5.f;

	UPROPERTY(BlueprintReadOnly, Category = "IceFloor|Phase")
	bool bPhase2Triggered = false;

	UPROPERTY(BlueprintReadOnly, Category = "IceFloor|Phase")
	bool bPhase3Triggered = false;

	FTimerHandle RandomBreakTimerHandle;

protected:
	void CacheGameState();
	void HandlePhaseLogic();

	void CollectIcePieces();
	void BuildPieceData();

	void TriggerPhase2IceFloor();
	void TriggerPhase3IceFloor();

	void CrackRandomOuterPiece();

	void SetPieceCracked(int32 PieceIndex);
	void StartPieceBreaking(int32 PieceIndex);
	void BreakPiece(int32 PieceIndex);

	void HidePiece(int32 PieceIndex);

	bool HasBreakableOuterPiece() const;

public:
	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	void InitializeIceFloor();

	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	void ResetIceFloor();

	UFUNCTION(BlueprintImplementableEvent, Category = "IceFloor")
	void BP_OnPieceCracked(UStaticMeshComponent* PieceMesh);

	UFUNCTION(BlueprintImplementableEvent, Category = "IceFloor")
	void BP_OnPieceBreaking(UStaticMeshComponent* PieceMesh);

	UFUNCTION(BlueprintImplementableEvent, Category = "IceFloor")
	void BP_OnPieceBroken(UStaticMeshComponent* PieceMesh);
};