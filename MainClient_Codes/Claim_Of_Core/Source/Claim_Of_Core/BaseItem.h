#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseItem.generated.h"

class AMyCharacter;
class UAnimMontage;

UCLASS()
class CLAIM_OF_CORE_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	ABaseItem();

protected:
	virtual void BeginPlay() override;

public:

	/* ===== 기본 스탯 ===== */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float KnockbackPower = 800.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Range = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Radius = 80.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	UAnimMontage* AttackMontage;

	UPROPERTY()
	AMyCharacter* OwnerCharacter;

	void SetOwnerCharacter(AMyCharacter* NewOwner);

	/* ===== 사용 ===== */

	virtual void StartUse();   // 버튼 눌렀을 때
	virtual void DoHit();      // 애님 노티파이에서 호출

protected:

	virtual void OnStartUse();         // 상속용
	virtual void OnHitTarget(AActor* Target); // 상속용

	void ApplyDamage(AActor* Target);
	void ApplyKnockback(ACharacter* Target);
};
