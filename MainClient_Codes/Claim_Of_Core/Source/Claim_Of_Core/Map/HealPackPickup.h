#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealPackPickup.generated.h"

class AMyCharacter;
class UPrimitiveComponent;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class CLAIM_OF_CORE_API AHealPackPickup : public AActor
{
	GENERATED_BODY()

public:
	AHealPackPickup();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealPack")
	TObjectPtr<USphereComponent> PickupCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "HealPack")
	TObjectPtr<UStaticMeshComponent> PickupMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealPack")
	int32 HealAmount = 30;

private:
	bool bConsumed = false;

	UFUNCTION()
	void OnPickupBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	bool Consume(AMyCharacter* Character);
};
