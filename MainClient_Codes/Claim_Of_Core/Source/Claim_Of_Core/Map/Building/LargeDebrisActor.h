#pragma once

#include "CoreMinimal.h"
#include "../PreFracturedActor.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "LargeDebrisActor.generated.h"

class UPrimitiveComponent;

UCLASS()
class CLAIM_OF_CORE_API ALargeDebrisActor : public APreFracturedActor
{
	GENERATED_BODY()

public:
	ALargeDebrisActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|VFX")
	TObjectPtr<UNiagaraSystem> ChunkBreakEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|VFX")
	TObjectPtr<UNiagaraSystem> LandingDustEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|VFX")
	float DebrisEffectScale = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	bool bUseActorFall = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float GravityAcceleration = 980.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float MaxFallSpeed = 4000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float GroundZ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float GroundOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float MinBreakSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float SpeedToDamageScale = 0.03f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	int32 MaxInitialBreakCount = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float BottomChunkTolerance = 30.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bDebrisActivated = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bLanded = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float CurrentFallSpeed = 0.f;

	// ¼øÂ÷ ºØ±«¿ë
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|SequentialBreak")
	float SequentialBreakInterval = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|SequentialBreak")
	int32 SequentialBreakBatchSize = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris|SequentialBreak")
	TArray<int32> PendingBreakChunks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Damage")
	float BrokenChunkDamageLifeTime = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Damage")
	float BrokenChunkStopSpeedThreshold = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Damage")
	float BrokenChunkStopAngularSpeedThreshold = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Damage")
	float BrokenChunkStopConfirmTime = 0.25f;

	TSet<int32> DamageDisabledBrokenChunks;
	TMap<int32, float> BrokenChunkDamageEndTimes;
	TMap<int32, float> BrokenChunkStillTimes;

	FTimerHandle SequentialBreakTimerHandle;

protected:
	void UpdateActorFall(float DeltaTime);
	void LandAndFracture();
	void GetBottomChunks(TArray<int32>& OutChunkIndices) const;
	void BreakInitialBottomChunks(float ImpactSpeed);

	void StartSequentialUnsupportedBreak();
	void ProcessNextChunkBreak();

	void EnableBrokenChunkDamage(int32 ChunkIndex);
	void DisableBrokenChunkDamage(int32 ChunkIndex);
	void UpdateBrokenChunkDamageState(float DeltaTime);
	bool CanBrokenChunkDealDamage(int32 ChunkIndex) const;

public:
	UFUNCTION(BlueprintCallable, Category = "Debris")
	void PrepareDebris();

	UFUNCTION(BlueprintCallable, Category = "Debris")
	void ActivateDebris(float InitialImpulseStrength = 0.f);

	UFUNCTION(BlueprintPure, Category = "Debris")
	bool IsDebrisActivated() const { return bDebrisActivated; }

	UFUNCTION(BlueprintPure, Category = "Debris")
	bool IsLanded() const { return bLanded; }


public:
	virtual void BreakChunk(int32 ChunkIndex, bool bFromImpact = false) override;

	void SetLargeDebrisID(int32 InID) { LargeDebrisID = InID; }
	int32 GetLargeDebrisID() const { return LargeDebrisID; }
	void ApplyServerChunkBreak(int32 ChunkIndex, bool bFromImpact);

protected:
	virtual void DropUnsupportedChunks() override;
	virtual void OnChunkBrokenInternal(int32 BrokenChunkIndex, bool bFromImpact) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	int32 LargeDebrisID = -1;


	TSet<int32> ReportedHitKeys;

	UFUNCTION()
	void OnLargeDebrisHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Debris")
	void BP_OnDebrisActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "Debris")
	void BP_OnDebrisLanded();
};