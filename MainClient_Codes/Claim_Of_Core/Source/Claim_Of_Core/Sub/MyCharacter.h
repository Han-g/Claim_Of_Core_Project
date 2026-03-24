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

class FLifetimeProperty;

UENUM(BlueprintType)
enum class ERecCharacterState : uint8
{
	Alive UMETA(DisplayName = "Alive"),
	Dead  UMETA(DisplayName = "Dead"),
};

UENUM(BlueprintType)
enum class ERecRoleType : uint8
{
	Striker     UMETA(DisplayName = "Striker"),
	Guardian    UMETA(DisplayName = "Guardian"),
	Manipulator UMETA(DisplayName = "Manipulator"),
};

USTRUCT(BlueprintType)
struct FRoleVisualData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> Mesh = nullptr;

	// AnimBP(AnimInstance 상속 블루프린트) 클래스
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> AnimBPClass = nullptr;

	// 역할별 기본 몽타주 (예: 공격, 줍기 등)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontage = nullptr;
};

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* RoleTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* DeathUITextComponent;

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
	ERecCharacterState GetCharacterState() const { return CharacterState; }

	UFUNCTION(BlueprintPure, Category = "State")
	bool IsDead() const { return CharacterState == ERecCharacterState::Dead; }

	// Role
	UFUNCTION(BlueprintPure, Category = "Role")
	ERecRoleType GetRoleType() const { return RoleType; }

	UPROPERTY(ReplicatedUsing = OnRep_RoleType, VisibleInstanceOnly, Category = "Role")
	ERecRoleType RoleType = ERecRoleType::Striker;

	// State machine (enum)
	UPROPERTY(ReplicatedUsing = OnRep_CharacterState, VisibleInstanceOnly, Category = "State")
	ERecCharacterState CharacterState = ERecCharacterState::Alive;

	// 역할별 세팅
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Role|Visual")
	FRoleVisualData StrikerVisual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Role|Visual")
	FRoleVisualData GuardianVisual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Role|Visual")
	FRoleVisualData ManipulatorVisual;
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
	// Base movement speed cache (role 배율 적용의 기준)
	UPROPERTY(VisibleInstanceOnly, Category = "Role")
	float BaseWalkSpeed = 500.f;

	// Spectate (when dead)
	UPROPERTY(EditDefaultsOnly, Category = "Spectate")
	float SpectateMoveSpeed = 900.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spectate")
	float SpectateVerticalSpeed = 700.f;

	bool bCameraDetached = false;

	bool bSpectateUpHeld = false;    // Q
	bool bSpectateDownHeld = false;  // E

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float SpectateInputUnlockDelay = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float SpectatingUITextDuration = 2.0f;

	FTimerHandle SpectatingUIHideTimerHandle;
	FTimerHandle SpectateInputUnlockTimerHandle;

	bool bCorpseHidden = false;
	bool bDeathSequenceLocked = false;
	bool bCanSpectate = false;
	bool bAwaitingSpectateInput = false;
	bool bSpectateInputUnlocked = false;

	// Low HP effect
	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	int32 LowHPThreshold = 20;

	UPROPERTY(VisibleInstanceOnly, Category = "LowHP")
	bool bLowHPEffectActive = false;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPPostProcessBlendWeight = 0.45f;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPVignetteIntensity = 0.6f;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPSaturation = 0.55f;

	// Low HP heartbeat pulse
	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPPulseSpeed = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPPulseVignetteAmplitude = 0.20f;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPPulseBlendAmplitude = 0.12f;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	FLinearColor LowHPSceneTint = FLinearColor(1.18f, 0.78f, 0.78f, 1.0f);

	// Death camera pullback during 3 sec lock
	UPROPERTY(EditDefaultsOnly, Category = "DeathCamera")
	float DeathCameraTargetArmLength = 650.f;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCamera")
	float DeathCameraInterpSpeed = 0.8f;

	// Death camera shake
	UPROPERTY(EditDefaultsOnly, Category = "DeathCameraShake")
	float DeathShakeDuration = 0.30f;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCameraShake")
	float DeathShakeAmplitude = 12.0f;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCameraShake")
	float DeathShakeFrequency = 32.0f;

	UPROPERTY(VisibleInstanceOnly, Category = "DeathCameraShake")
	bool bDeathCameraShaking = false;

	UPROPERTY(VisibleInstanceOnly, Category = "DeathCameraShake")
	float DeathShakeElapsed = 0.0f;

	// 초기 트랜스폼 캐시(래그돌 복구용)
	FTransform InitialMeshRelativeTransform = FTransform::Identity;
	FTransform InitialCameraBoomRelativeTransform = FTransform::Identity;
	float InitialCameraBoomArmLength = 4000.f;
	FVector InitialCameraBoomSocketOffset = FVector::ZeroVector;
	
	// Input helpers
	void SpectateUpPressed();
	void SpectateUpReleased();
	void SpectateDownPressed();
	void SpectateDownReleased();

	void SpectateMove(float Right, float Forward);
	void SpectateMoveVertical(float Axis, float DeltaTime);

	void ResurrectPressed();
	void CycleRolePressed();
	void SpectateConfirmPressed();
	void SelfDamagePressed();

	// Server RPCs
	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(int32 DamageAmount);

	UFUNCTION(Server, Reliable)
	void ServerHeal(int32 HealAmount);

	UFUNCTION(Server, Reliable)
	void ServerResetHP();

	UFUNCTION(Server, Reliable)
	void ServerCycleRole();


	// Rep callbacks
	UFUNCTION()
	void OnRep_CurrentHP();

	UFUNCTION()
	void OnRep_CharacterState();

	UFUNCTION()
	void OnRep_RoleType();

	// Internal helpers
	void SetCurrentHP(int32 NewHP);
	void UpdateHPText();

	// Role helpers
	static FString RoleTypeToString(ERecRoleType InType);
	static float GetRoleSpeedMultiplier(ERecRoleType InType);
	void ApplyRoleStats();
	void ApplyRoleVisual();
	const FRoleVisualData& GetVisualData(ERecRoleType InRole) const;

	// State helpers
	void SetCharacterState(ERecCharacterState NewState); // server-only setter
	void ApplyCharacterState();                          // apply on both server/clients
	void ApplyDeadState();
	void ApplyAliveState();

	void EnterDeathWaitingState();
	void EnterSpectateMode();
	void UnlockSpectateInput();

	void HideCorpse();
	void ShowCorpse();

	void UpdateLocalPostProcessEffects();
	void UpdateLowHPEffectState();
	void UpdateLowHPPulseEffect(float DeltaTime);

	void StartDeathCameraShake();
	void UpdateDeathCameraShake(float DeltaTime);
	void StopDeathCameraShake();

	void SetDeathVisualsEnabled(bool bEnabled);
	void SetPlayerControlLocked(bool bLocked);

	void UpdateDeathUI();
	void ShowSpectatingUI();
	void HideDeathUI();

	// PlayerStart로 리스폰(서있는 상태)
	void RespawnAtPlayerStart();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};