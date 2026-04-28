#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SmallDebrisActor.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class CLAIM_OF_CORE_API ASmallDebrisActor : public AActor
{
	GENERATED_BODY()

public:
	ASmallDebrisActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris")
	float DestroyDelayAfterHitGround = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bDestroyOnPlayerHit = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bHasHitSomething = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Debris")
	bool bHasDamagedPlayer = false;

	FTimerHandle TimerHandle_Destroy;

protected:
	UFUNCTION()
	void OnDebrisHit(
		UPrimitiveComponent* HitComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit);

	void StartDestroyTimer();

	UFUNCTION()
	void DestroySelf();
};