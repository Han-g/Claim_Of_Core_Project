#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LargeDebrisActor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class CLAIM_OF_CORE_API ALargeDebrisActor : public AActor
{
	GENERATED_BODY()

public:
	ALargeDebrisActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bFreezeAfterLanding = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris")
	float MinImpactSpeedToLand = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bActivated = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bLanded = false;

protected:
	UFUNCTION()
	void OnDebrisHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

public:
	UFUNCTION(BlueprintCallable, Category = "Debris")
	void PrepareDebris();

	UFUNCTION(BlueprintCallable, Category = "Debris")
	void ActivateDebris(float InitialImpulseStrength = 0.f);

	UFUNCTION(BlueprintPure, Category = "Debris")
	bool IsActivated() const { return bActivated; }

	UFUNCTION(BlueprintPure, Category = "Debris")
	bool IsLanded() const { return bLanded; }

protected:
	void FreezeDebris();

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Debris")
	void BP_OnDebrisActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "Debris")
	void BP_OnDebrisLanded();
};