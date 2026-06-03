#pragma once

#include "CoreMinimal.h"
#include "../../BaseItem.h"
#include "BlackHoleGrenadeItem.generated.h"

class ABlackHoleActor;

UCLASS()
class CLAIM_OF_CORE_API ABlackHoleGrenadeItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ABlackHoleGrenadeItem();

protected:
	virtual void OnStartUse() override;

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
	float GrenadePullStrength = 180.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|BlackHole")
	float GrenadePullRadius = 650.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|BlackHole")
	float GrenadeMinDistance = 60.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|BlackHole")
	float GrenadeMaxPullSpeed = 260.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|BlackHole")
	FVector GrenadeBlackHoleScale = FVector(0.35f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "BlackHole Grenade|Debug")
	bool bDrawGrenadeBlackHoleDebug = false;

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
