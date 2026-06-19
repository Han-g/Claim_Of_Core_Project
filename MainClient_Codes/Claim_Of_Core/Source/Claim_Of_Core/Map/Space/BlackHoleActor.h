#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHoleActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class CLAIM_OF_CORE_API ABlackHoleActor : public AActor
{
	GENERATED_BODY()

public:
	ABlackHoleActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlackHole")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlackHole")
	TObjectPtr<UStaticMeshComponent> BlackHoleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlackHole")
	TObjectPtr<USphereComponent> PullRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlackHole|Effect")
	TObjectPtr<UNiagaraComponent> BlackHoleEffectComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole|Effect")
	TObjectPtr<UNiagaraSystem> BlackHoleEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlackHole")
	bool bActive = false;

	// 기존보다 약하게 조정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlackHole")
	float PullStrength = 900.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlackHole")
	float PullRadius = 2500.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlackHole")
	float MinDistance = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlackHole")
	float MaxPullSpeed = 800.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BlackHole|Debug")
	bool bDrawDebug = true;

protected:
	void ApplyVisibleState(bool bVisible);
	void ApplyActiveState();

public:
	UFUNCTION(BlueprintCallable, Category = "BlackHole")
	void ShowBlackHole();

	UFUNCTION(BlueprintCallable, Category = "BlackHole")
	void HideBlackHole();

	UFUNCTION(BlueprintCallable, Category = "BlackHole")
	void ActivateBlackHole();

	UFUNCTION(BlueprintCallable, Category = "BlackHole")
	void DeactivateBlackHole();
};
