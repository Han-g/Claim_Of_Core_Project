#pragma once

#include "CoreMinimal.h"
#include "../../BaseItem.h"
#include "CloudGrenadeItem.generated.h"

class ASkyCloudPlatform;

UCLASS()
class CLAIM_OF_CORE_API ACloudGrenadeItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ACloudGrenadeItem();

protected:
	virtual void OnStartUse() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade")
	TSubclassOf<ASkyCloudPlatform> CloudPlatformClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Throw")
	float ThrowSpeed = 1800.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Throw")
	float ThrowUpwardSpeed = 350.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Throw")
	float ThrowSpawnForwardOffset = 120.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Throw")
	float ThrowSpawnUpOffset = 80.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Fuse")
	float FuseTimeMin = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Fuse")
	float FuseTimeMax = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Cloud")
	FVector CloudPlatformScale = FVector(1.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Cloud")
	float CloudSpawnUpOffset = 12.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cloud Grenade|Cloud")
	float CloudLifeSpan = 8.f;

private:
	bool bHasBeenThrown = false;
	bool bHasExploded = false;

	FTimerHandle FuseTimerHandle;

	void Explode();
	void SpawnCloudPlatform(const FVector& SpawnLocation);
};
