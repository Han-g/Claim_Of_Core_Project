// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "BlackHoleGrenadeItem.generated.h"

class ABlackHoleActor;
class UPrimitiveComponent;

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API ABlackHoleGrenadeItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ABlackHoleGrenadeItem();

	virtual void DoHit() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade")
    TSubclassOf<ABlackHoleActor> BlackHoleClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|Throw")
    float ThrowSpeed = 1800.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|Throw")
    float ThrowUpwardSpeed = 350.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|Throw")
    float ThrowSpawnForwardOffset = 120.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|Throw")
    float ThrowSpawnUpOffset = 80.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|Impact")
    float GroundNormalThreshold = 0.65f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|BlackHole")
    FVector GrenadeBlackHoleScale = FVector(0.35f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|BlackHole")
    float BlackHoleLifeSeconds = 4.0f;

private:
    bool bHasBeenThrown = false;
    bool bHasExploded = false;

    UFUNCTION()
    void OnGrenadeHit(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit
    );

    void SpawnGrenadeBlackHole(const FHitResult& Hit);
};
