#pragma once

#include "CoreMinimal.h"
#include "../../BaseItem.h"
#include "JungleOneShotGunItem.generated.h"

UCLASS()
class CLAIM_OF_CORE_API AJungleOneShotGunItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AJungleOneShotGunItem();

protected:
	virtual void OnStartUse() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jungle Gun")
	float GunDamage = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jungle Gun")
	float TraceDistance = 10000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jungle Gun")
	float HitSweepRadius = 45.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jungle Gun|Debug")
	bool bDrawDebugTrace = true;

private:
	bool bHasFired = false;

	void FireHitscan();
};
