#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TimerManager.h"
#include "RecCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UTextRenderComponent;
struct FInputActionValue;

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

UCLASS(abstract)
class REC_API ARecCharacter : public ACharacter
{
	GENERATED_BODY()

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

public:
	ARecCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

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

private:
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "HP")
	int32 MaxHP = 100;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHP, VisibleInstanceOnly, Category = "HP")
	int32 CurrentHP = 100;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterState, VisibleInstanceOnly, Category = "State")
	ERecCharacterState CharacterState = ERecCharacterState::Alive;

	UPROPERTY(ReplicatedUsing = OnRep_RoleType, VisibleInstanceOnly, Category = "Role")
	ERecRoleType RoleType = ERecRoleType::Striker;

	UPROPERTY(VisibleInstanceOnly, Category = "Role")
	float BaseWalkSpeed = 500.f;

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

	FTransform InitialMeshRelativeTransform = FTransform::Identity;
	FTransform InitialCameraBoomRelativeTransform = FTransform::Identity;
	float InitialCameraBoomArmLength = 400.f;
	FVector InitialCameraBoomSocketOffset = FVector::ZeroVector;

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

	UFUNCTION()
	void OnRep_CurrentHP();

	UFUNCTION()
	void OnRep_CharacterState();

	UFUNCTION()
	void OnRep_RoleType();

	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(int32 DamageAmount);

	UFUNCTION(Server, Reliable)
	void ServerHeal(int32 HealAmount);

	UFUNCTION(Server, Reliable)
	void ServerResetHP();

	UFUNCTION(Server, Reliable)
	void ServerCycleRole();

	void SetCurrentHP(int32 NewHP);
	void UpdateHPText();
	void UpdateRoleText();

	static FString RoleTypeToString(ERecRoleType InType);
	static float GetRoleSpeedMultiplier(ERecRoleType InType);
	void ApplyRoleStats();

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

	void SetDeathVisualsEnabled(bool bEnabled);
	void SetPlayerControlLocked(bool bLocked);

	void UpdateDeathUI();
	void ShowSpectatingUI();
	void HideDeathUI();

	void RespawnAtPlayerStart();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};