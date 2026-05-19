#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "TorchItem.generated.h"

class AMyCharacter;

struct FTorchBurnState
{
	float RemainingTime = 0.f;
	float TimeUntilNextTick = 0.f;
};

UCLASS()
class CLAIM_OF_CORE_API ATorchItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ATorchItem();

	virtual void Tick(float DeltaTime) override;
	virtual void DoHit() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Torch|Burn")
	int32 BurnDamagePerTick = 3;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Torch|Burn")
	float BurnTickInterval = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Torch|Burn")
	float BurnDuration = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Torch|Thaw")
	float ThawRequiredTime = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Torch|Thaw")
	float ThawRangeBuffer = 0.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Torch|Thaw")
	TObjectPtr<AMyCharacter> CurrentThawTarget = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Torch|Thaw")
	float ThawProgress = 0.f;

	TMap<AMyCharacter*, FTorchBurnState> ActiveBurns;

	void ApplyBurn(AMyCharacter* Target);
	void UpdateBurns(float DeltaTime);
	void TryStartThaw(AMyCharacter* Target);
	void UpdateThaw(float DeltaTime);
	void CancelThaw();
	bool IsValidThawTarget(AMyCharacter* Target) const;
	bool IsTargetInTorchRange(AMyCharacter* Target) const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Torch")
	void BP_OnTorchHitTarget(AActor* Target);

	UFUNCTION(BlueprintImplementableEvent, Category = "Torch")
	void BP_OnUnfreezeTarget(AMyCharacter* Target);
};
