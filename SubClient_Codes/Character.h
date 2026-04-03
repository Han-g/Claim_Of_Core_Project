#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "MyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UTextRenderComponent;
class UAnimInstance;
class UAnimMontage;
class USkeletalMesh;
class UPrimitiveComponent;
class ABaseItem;
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

UENUM(BlueprintType)
enum class ERecStatusEffectType : uint8
{
	Slow      UMETA(DisplayName = "Slow"),
	Stun      UMETA(DisplayName = "Stun"),
	Knockback UMETA(DisplayName = "Knockback"),
};

USTRUCT(BlueprintType)
struct FRoleVisualData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> AnimBPClass = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontage = nullptr;
};

UCLASS(Abstract)
class AMyCharacter : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* HPTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* RoleTextComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* DeathUITextComponent;

protected:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* KnockbackAction;

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Attack();
	void KnockbackTest();

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoMove(float Right, float Forward);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoLook(float Yaw, float Pitch);

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category = "Input")
	virtual void DoJumpEnd();

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

	UFUNCTION(BlueprintPure, Category = "State")
	ERecCharacterState GetCharacterState() const { return CharacterState; }

	UFUNCTION(BlueprintPure, Category = "State")
	bool IsDead() const { return CharacterState == ERecCharacterState::Dead; }

	UFUNCTION(BlueprintPure, Category = "Role")
	ERecRoleType GetRoleType() const { return RoleType; }

	UFUNCTION(BlueprintCallable, Category = "RoleSkill")
	void ActivateRoleSkill();

	UFUNCTION(BlueprintPure, Category = "RoleSkill")
	bool IsRoleSkillActive() const { return bRoleSkillActive; }

	UFUNCTION(BlueprintPure, Category = "RoleSkill")
	bool IsStatusEffectImmune() const;

	UFUNCTION(BlueprintCallable, Category = "Status")
	bool CanReceiveStatusEffect(ERecStatusEffectType InStatusEffect) const;

	UPROPERTY(ReplicatedUsing = OnRep_RoleType, VisibleInstanceOnly, Category = "Role")
	ERecRoleType RoleType = ERecRoleType::Guardian;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterState, VisibleInstanceOnly, Category = "State")
	ERecCharacterState CharacterState = ERecCharacterState::Alive;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Role|Visual")
	FRoleVisualData StrikerVisual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Role|Visual")
	FRoleVisualData GuardianVisual;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Role|Visual")
	FRoleVisualData ManipulatorVisual;

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

	UPROPERTY()
	ABaseItem* OverlappingItem = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Item")
	ABaseItem* CurrentItem = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetOverlappingItem(ABaseItem* Item);

	UFUNCTION(BlueprintCallable, Category = "Item")
	void EquipItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	void DropCurrentItem();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AnimNotify_AttackHit();

private:
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "HP")
	int32 MaxHP = 100;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHP, VisibleInstanceOnly, Category = "HP")
	int32 CurrentHP = 100;

	UPROPERTY(VisibleInstanceOnly, Category = "Role")
	float BaseWalkSpeed = 2000.f;

	UPROPERTY(VisibleInstanceOnly, Category = "Role")
	int32 BaseJumpMaxCount = 1;

	UPROPERTY(ReplicatedUsing = OnRep_RoleSkillActive, VisibleInstanceOnly, Category = "RoleSkill")
	bool bRoleSkillActive = false;

	FTimerHandle RoleSkillTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "RoleSkill|Striker")
	float DashDuration = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "RoleSkill|Striker")
	float DashSpeedMultiplier = 1.45f;

	UPROPERTY(EditDefaultsOnly, Category = "RoleSkill|Striker")
	float DashDamageMultiplier = 1.50f;

	UPROPERTY(EditDefaultsOnly, Category = "RoleSkill|Guardian")
	float HardDuration = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "RoleSkill|Guardian")
	float HardSpeedMultiplier = 0.65f;

	UPROPERTY(EditDefaultsOnly, Category = "RoleSkill|Guardian")
	float HardScaleMultiplier = 1.25f;

	UPROPERTY(EditDefaultsOnly, Category = "RoleSkill|Guardian")
	float HardDamageTakenMultiplier = 0.60f;

	UPROPERTY(EditDefaultsOnly, Category = "RoleSkill|Manipulator")
	float DBJPDuration = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Spectate")
	float SpectateMoveSpeed = 900.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spectate")
	float SpectateVerticalSpeed = 700.f;

	bool bCameraDetached = false;
	bool bSpectateUpHeld = false;
	bool bSpectateDownHeld = false;

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

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPPulseSpeed = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPPulseVignetteAmplitude = 0.20f;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	float LowHPPulseBlendAmplitude = 0.12f;

	UPROPERTY(EditDefaultsOnly, Category = "LowHP")
	FLinearColor LowHPSceneTint = FLinearColor(1.18f, 0.78f, 0.78f, 1.0f);

	UPROPERTY(EditDefaultsOnly, Category = "DeathCamera")
	float DeathCameraTargetArmLength = 650.f;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCamera")
	float DeathCameraInterpSpeed = 0.8f;

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

	FTransform InitialMeshRelativeTransform = FTransform::Identity;
	FTransform InitialCameraBoomRelativeTransform = FTransform::Identity;
	FVector InitialActorScale3D = FVector::OneVector;
	float InitialCameraBoomArmLength = 400.f;
	FVector InitialCameraBoomSocketOffset = FVector::ZeroVector;

private:
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
	void ActivateRoleSkillPressed();

	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(int32 DamageAmount);

	UFUNCTION(Server, Reliable)
	void ServerHeal(int32 HealAmount);

	UFUNCTION(Server, Reliable)
	void ServerResetHP();

	UFUNCTION(Server, Reliable)
	void ServerCycleRole();

	UFUNCTION(Server, Reliable)
	void ServerActivateRoleSkill();

	UFUNCTION()
	void OnRep_CurrentHP();

	UFUNCTION()
	void OnRep_CharacterState();

	UFUNCTION()
	void OnRep_RoleType();

	UFUNCTION()
	void OnRep_RoleSkillActive();

	void SetCurrentHP(int32 NewHP);
	void UpdateHPText();
	void UpdateRoleText();

	static FString RoleTypeToString(ERecRoleType InType);
	static float GetRoleSpeedMultiplier(ERecRoleType InType);

	float GetRoleSkillSpeedMultiplier() const;
	float GetCurrentRoleSkillDuration() const;
	float GetOutgoingDamageMultiplier() const;
	float GetIncomingDamageMultiplier() const;
	FString GetCurrentRoleSkillName() const;

	void ApplyRoleStats();
	void ApplyRoleVisual();
	void ApplyRoleSkillState();
	const FRoleVisualData& GetVisualData(ERecRoleType InRole) const;

	void SetCharacterState(ERecCharacterState NewState);
	void ApplyCharacterState();
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
	void UpdateDeathCameraPullback(float DeltaTime);

	void SetDeathVisualsEnabled(bool bEnabled);
	void SetPlayerControlLocked(bool bLocked);

	void UpdateDeathUI();
	void ShowSpectatingUI();
	void HideDeathUI();

	void EndRoleSkill();
	void RespawnAtPlayerStart();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
