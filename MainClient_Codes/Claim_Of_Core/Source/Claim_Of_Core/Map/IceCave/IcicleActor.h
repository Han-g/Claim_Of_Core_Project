#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IcicleActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EIcicleState : uint8
{
	Idle,
	Warning,
	Falling,
	Broken
};

UCLASS()
class CLAIM_OF_CORE_API AIcicleActor : public AActor
{
	GENERATED_BODY()

public:
	AIcicleActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> IcicleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> WarningRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> DamageCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Icicle")
	EIcicleState CurrentState = EIcicleState::Idle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Icicle")
	float WarningTime = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Icicle")
	float Damage = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Icicle")
	float DestroyDelay = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Icicle")
	bool bDestroyAfterHitGround = true;

	FTimerHandle WarningTimerHandle;
	FTimerHandle DestroyTimerHandle;

	UFUNCTION()
	void OnIcicleHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit
	);

	void BreakIcicle();

public:
	UFUNCTION(BlueprintCallable)
	void StartWarning();

	UFUNCTION(BlueprintCallable)
	void StartFalling();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnWarningStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnFallingStarted();

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnBroken();
};