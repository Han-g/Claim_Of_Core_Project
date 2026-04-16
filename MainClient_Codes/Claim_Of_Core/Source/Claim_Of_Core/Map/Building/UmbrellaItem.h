#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "UmbrellaItem.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class EUmbrellaMode : uint8
{
	Closed,
	Opened,
	Broken
};

UCLASS()
class CLAIM_OF_CORE_API AUmbrellaItem : public ABaseItem
{
	GENERATED_BODY()

public:
	AUmbrellaItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime);

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Umbrella")
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Umbrella")
	EUmbrellaMode CurrentMode = EUmbrellaMode::Closed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Umbrella")
	int32 MaxDurability = 3;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Umbrella")
	int32 CurrentDurability = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Umbrella")
	float OpenedMoveSpeedMultiplier = 0.85f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Umbrella|Attack")
	float ClosedDamage = 12.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Umbrella|Attack")
	float ClosedKnockbackPower = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Umbrella|Guard")
	float GuardedDamageMultiplier = 0.3f;

	UFUNCTION(BlueprintCallable, Category = "Umbrella")
	void OpenUmbrella();

	UFUNCTION(BlueprintCallable, Category = "Umbrella")
	void CloseUmbrella();

	UFUNCTION(BlueprintCallable, Category = "Umbrella")
	void ToggleUmbrella();

	UFUNCTION(BlueprintCallable, Category = "Umbrella")
	void HandleGuardHit(AActor* DamageCauser, float IncomingDamage = 30.f);

	UFUNCTION(BlueprintCallable, Category = "Umbrella")
	void BreakUmbrella();

	UFUNCTION(BlueprintPure, Category = "Umbrella")
	bool IsOpened() const { return CurrentMode == EUmbrellaMode::Opened; }

	UFUNCTION(BlueprintPure, Category = "Umbrella")
	bool IsBroken() const { return CurrentMode == EUmbrellaMode::Broken; }

	UFUNCTION(BlueprintPure, Category = "Umbrella")
	bool CanGuard() const;

	UFUNCTION()
	void OnGuardBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	virtual void StartUse() override;
	virtual void DoHit() override;

protected:
	virtual void OnStartUse() override;
	virtual void OnHitTarget(AActor* Target) override;

	void UpdateAttackStat();
	bool IsFallingDebrisActor(AActor* OtherActor) const;

	float CachedOriginalWalkSpeed = 0.f;
	bool bSpeedModified = false;
};