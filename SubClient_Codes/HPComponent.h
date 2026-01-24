#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HPComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHPChangedSignature, int32, NewHP, int32, OldHP);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHPZeroSignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CLAIM_OF_CORE_API UHPComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHPComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "HP")
	int32 MaxHP;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CurrentHP, Category = "HP")
	int32 CurrentHP;

	UPROPERTY(BlueprintAssignable, Category = "HP")
	FOnHPChangedSignature OnHPChanged;

	UPROPERTY(BlueprintAssignable, Category = "HP")
	FOnHPZeroSignature OnHPZero;

public:
	UFUNCTION(BlueprintCallable, Category = "HP")
	void ApplyDamage(int32 DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "HP")
	void Heal(int32 HealAmount);

	UFUNCTION(BlueprintCallable, Category = "HP")
	void ResetHP();

	UFUNCTION(BlueprintPure, Category = "HP")
	int32 GetCurrentHP() const { return CurrentHP; }

	UFUNCTION(BlueprintPure, Category = "HP")
	int32 GetMaxHP() const { return MaxHP; }

	UFUNCTION(BlueprintPure, Category = "HP")
	float GetHPPercent() const { return (MaxHP <= 0) ? 0.f : (float)CurrentHP / (float)MaxHP; }

	UFUNCTION(BlueprintPure, Category = "HP")
	bool IsDead() const { return CurrentHP <= 0; }

protected:
	UFUNCTION()
	void OnRep_CurrentHP(int32 OldHP);

	void HandleHPChanged(int32 OldHP);

	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(int32 DamageAmount);

	UFUNCTION(Server, Reliable)
	void ServerHeal(int32 HealAmount);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
