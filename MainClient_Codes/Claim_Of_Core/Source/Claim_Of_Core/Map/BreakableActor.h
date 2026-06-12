#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakableActor.generated.h"

UENUM(BlueprintType)
enum class EBreakableActorState : uint8
{
	Idle,
	Active,
	Breaking,
	Broken
};

UCLASS(Abstract)
class CLAIM_OF_CORE_API ABreakableActor : public AActor
{
	GENERATED_BODY()

public:
	ABreakableActor();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breakable")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Breakable")
	EBreakableActorState BreakableState = EBreakableActorState::Idle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breakable")
	bool bActivated = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breakable")
	bool bBroken = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Breakable")
	float MaxDurability = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Breakable")
	float CurrentDurability = 100.f;

public:
	UFUNCTION(BlueprintCallable, Category = "Breakable")
	virtual void ActivateBreakable();

	UFUNCTION(BlueprintCallable, Category = "Breakable")
	virtual void ResetBreakable();

	UFUNCTION(BlueprintCallable, Category = "Breakable")
	virtual void ApplyBreakableDamage(float DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "Breakable")
	virtual void BreakActor();

	UFUNCTION(BlueprintPure, Category = "Breakable")
	bool IsBroken() const { return bBroken; }

	UFUNCTION(BlueprintPure, Category = "Breakable")
	bool IsActivated() const { return bActivated; }

protected:
	virtual void OnActivatedInternal();
	virtual void OnBrokenInternal();

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Breakable")
	void BP_OnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "Breakable")
	void BP_OnBroken();
};