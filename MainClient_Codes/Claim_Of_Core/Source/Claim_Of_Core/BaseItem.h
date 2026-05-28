#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sub/MyCharacter.h"
#include "Net/UnrealNetwork.h"
#include "BaseItem.generated.h"

class AMyCharacter;
class UAnimMontage;
class USphereComponent;


UENUM(BlueprintType)
enum class EItemAnimPoseType : uint8
{
	None   UMETA(DisplayName = "None"),
	Sword  UMETA(DisplayName = "Sword"),
	Spear  UMETA(DisplayName = "Spear"),
	Hammer UMETA(DisplayName = "Hammer")
};

UCLASS()
class CLAIM_OF_CORE_API ABaseItem : public AActor
{
	GENERATED_BODY()

public:
	ABaseItem();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	EItemAnimPoseType ItemAnimPoseType = EItemAnimPoseType::None;

	// 아이템이 겹쳐질 때 콜리전 (픽업 범위)

	UPROPERTY(VisibleAnywhere)
	USphereComponent* PickupCollision;

	UFUNCTION()
	void OnBeginOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);


	/* ===== 기본 스탯 ===== */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Point;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float KnockbackPower = 800.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Range = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	float Radius = 80.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mongtage")
	UAnimMontage* GuardianMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mongtage")
	UAnimMontage* ManipulatorMontage;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mongtage")
	UAnimMontage* StrikerMontage;
	UAnimMontage* GetAttackMontageByRole(ERecRoleType InRole) const;

	UPROPERTY()
	AMyCharacter* OwnerCharacter;

	// Role

	UFUNCTION(BlueprintPure, Category = "Role")
	ERecRoleType GetRoleType() const { return OwnerCharacter->GetRoleType(); }

	int32 GetItemID() const { return ItemID; }
	void SetItemID(int32 InItemID) { ItemID = InItemID; }

	AMyCharacter* GetOwnerCharacter() const { return OwnerCharacter; }
	void SetOwnerCharacter(AMyCharacter* NewOwner);

	/* ===== 사용 ===== */

	virtual void StartUse();   // 버튼 눌렀을 때
	virtual void DoHit();      // 애님 노티파이에서 호출

protected:

	virtual void OnStartUse();         // 상속용
	virtual void OnHitTarget(AActor* Target); // 상속용

	void ApplyDamage(AActor* Target);
	void ApplyKnockback(ACharacter* Target);

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item", meta = (AllowPrivateAccess = "true"))
	int32 ItemID = -1;
};
