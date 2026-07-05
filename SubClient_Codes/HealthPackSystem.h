#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameFramework/Actor.h"
#include "HealthPackSystem.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class UParticleSystem;
class USoundBase;
class AHealthPackActor;

UINTERFACE(MinimalAPI, Blueprintable)
class UHealableInterface : public UInterface
{
	GENERATED_BODY()
};

class YOURPROJECT_API IHealableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
	bool TryHeal(float HealAmount);
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnHealthPackPicked,
	AHealthPackActor*, PickedPack
);

UCLASS()
class YOURPROJECT_API AHealthPackActor : public AActor
{
	GENERATED_BODY()

public:
	AHealthPackActor();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* VerticalBar;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* HorizontalBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthPack")
	float HealAmount = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthPack")
	float RotationSpeed = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* PickupEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects")
	USoundBase* PickupSound;

	UPROPERTY(BlueprintReadOnly, Category = "HealthPack")
	bool bWasPickedUp = false;

	UFUNCTION()
	void OnOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void Pickup();

public:
	UPROPERTY(BlueprintAssignable, Category = "HealthPack")
	FOnHealthPackPicked OnPicked;
};

UCLASS()
class YOURPROJECT_API AHealthPackSpawner : public AActor
{
	GENERATED_BODY()

public:
	AHealthPackSpawner();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TSubclassOf<AHealthPackActor> HealthPackClass;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<AActor*> SpawnPoints;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float InitialSpawnDelay = 1.0f;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	float RespawnDelay = 15.0f;

	UPROPERTY()
	AHealthPackActor* CurrentHealthPack;

	FTimerHandle SpawnTimerHandle;

	void SpawnHealthPack();

	UFUNCTION()
	void OnHealthPackPicked(AHealthPackActor* PickedPack);
};
