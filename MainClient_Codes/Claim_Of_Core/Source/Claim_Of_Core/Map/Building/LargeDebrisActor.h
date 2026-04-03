#pragma once

#include "CoreMinimal.h"
#include "../PreFracturedActor.h"
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
	float SpeedToDamageScale = 0.08f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	int32 MaxInitialBreakCount = 2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float BottomChunkTolerance = 30.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bDebrisActivated = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bLanded = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris|Fall")
	float CurrentFallSpeed = 0.f;

protected:
	void UpdateActorFall(float DeltaTime);
	void LandAndFracture();
	void GetBottomChunks(TArray<int32>& OutChunkIndices) const;
	void BreakInitialBottomChunks(float ImpactSpeed);

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

protected:
	virtual void DropUnsupportedChunks() override;
	virtual void OnChunkBrokenInternal(int32 BrokenChunkIndex, bool bFromImpact) override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Debris")
	void BP_OnDebrisActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "Debris")
	void BP_OnDebrisLanded();
};