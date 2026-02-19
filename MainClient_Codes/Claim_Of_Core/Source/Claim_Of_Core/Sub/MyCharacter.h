#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UTextRenderComponent;
class BaseItem;

UCLASS(abstract)
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// HP Text (3D)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* HPTextComponent;

protected:
	// Enhanced Input Actions
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	/** Attack Input Action */
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	// TESTING Knockback
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* KnockbackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* AttackMontage = nullptr;
public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	// Damage entry-point (engine)
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	// Replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Enhanced Input callbacks
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	void Attack();
	void KnockbackTest();

public:
	// UI / virtual joystick compatible wrappers
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();


public:
	// HP API
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

	UFUNCTION(BlueprintPure, Category = "State")
	bool IsDead() const { return bIsDead; }

	// Attack API

	UFUNCTION()
	void ApplyKnockback(AActor* Attacker, float KnockbackStrength);

	UFUNCTION()
	void OnAttackOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	// Item API
	// 겹쳐있는 무기 (픽업 가능한 아이템)
	UPROPERTY()
	ABaseItem* OverlappingItem;

	// 현재 들고있는 무기
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item")
	ABaseItem* CurrentItem = nullptr;
	
	// 겹쳐있는 아이템 설정 (픽업 범위에 들어갔을 때) -> 아이템이 이 함수를 호출하도록
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetOverlappingItem(ABaseItem* Item);

	// 픽업했을 때 호출(손 소켓에 장착)
	UFUNCTION(BlueprintCallable, Category = "Item")
	void EquipItem();

	// 무기 버리기(필요하면)
	UFUNCTION(BlueprintCallable, Category = "Item")
	void DropCurrentItem();

	// AnimNotify에서 호출할 함수 (HitCheck 같은 노티파이에서)
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AnimNotify_AttackHit();
	

private:
	// Replicated HP state
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "HP")
	int32 MaxHP = 100;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHP, VisibleInstanceOnly, Category = "HP")
	int32 CurrentHP = 100;

	UPROPERTY(ReplicatedUsing = OnRep_IsDead, VisibleInstanceOnly, Category = "State")
	bool bIsDead = false;

	// Spectate (when dead)
	UPROPERTY(EditDefaultsOnly, Category = "Spectate")
	float SpectateMoveSpeed = 900.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spectate")
	float SpectateVerticalSpeed = 700.f;

	bool bCameraDetached = false;

	bool bSpectateUpHeld = false;    // Q
	bool bSpectateDownHeld = false;  // E

	void SpectateUpPressed();
	void SpectateUpReleased();
	void SpectateDownPressed();
	void SpectateDownReleased();

	void SpectateMove(float Right, float Forward);
	void SpectateMoveVertical(float Axis, float DeltaTime);

	// Rep callbacks
	UFUNCTION()
	void OnRep_IsDead();

	UFUNCTION()
	void OnRep_CurrentHP();

	// Internal helpers
	void ApplyDeadState();
	void SetCurrentHP(int32 NewHP);
	void UpdateHPText();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};