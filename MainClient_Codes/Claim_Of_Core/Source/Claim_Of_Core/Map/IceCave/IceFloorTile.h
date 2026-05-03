#pragma once

#include "CoreMinimal.h"
#include "../BreakableActor.h"
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
	// 이 액터 안에 붙어있는 StaticMeshComponent들을 자동 수집해서 사용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IceFloor")
	TArray<TObjectPtr<UStaticMeshComponent>> IcePieces;

	// 바깥부터 깨질 순서
	UPROPERTY()
	TArray<int32> SortedPieceIndices;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	bool bAutoStart = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float BreakInterval = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float CrackDelay = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float DownImpulse = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	float BrokenLifeSpan = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IceFloor")
	TObjectPtr<UMaterialInterface> CrackedMaterial = nullptr;

	int32 CurrentPieceIndex = 0;

	float Timer = 0.f;

	bool bStartedBreaking = false;
	bool bCurrentPieceCracked = false;

	FTimerHandle TimerHandle;
protected:
	virtual void OnActivatedInternal() override;
	virtual void OnBrokenInternal() override;

	void CollectIcePieces();
	void BuildBreakOrder();

	void ProcessBreaking(float DeltaTime);

	void CrackPiece(int32 PieceIndex);
	void BreakPiece(int32 PieceIndex);

public:
	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	void StartIceBreaking();

	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	void StopIceBreaking();

	UFUNCTION(BlueprintCallable, Category = "IceFloor")
	void SetBreakInterval(float NewInterval);
};