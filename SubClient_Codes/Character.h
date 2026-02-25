#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RecCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UTextRenderComponent;

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

	// Camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	// HP Text
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* HPTextComponent;

	// Role Text
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UTextRenderComponent* RoleTextComponent;

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

public:
	ARecCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;

	// Damage entry-point
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	// Replication
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	// Enhanced Input callbacks
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

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
	// HP API (BP에서 호출해도 서버에서 동작하도록 RPC 포함)
	UFUNCTION(BlueprintCallable, Category = "HP")
	void ApplyDamage(int32 DamageAmount);

	UFUNCTION(BlueprintCallable, Category = "HP")
	void Heal(int32 HealAmount);

	// Dead 상태에서 호출하면 "부활 + PlayerStart 리스폰"
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

private:
	// Replicated HP state
	UPROPERTY(EditDefaultsOnly, Replicated, Category = "HP")
	int32 MaxHP = 100;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHP, VisibleInstanceOnly, Category = "HP")
	int32 CurrentHP = 100;

	// State machine (enum)
	UPROPERTY(ReplicatedUsing = OnRep_CharacterState, VisibleInstanceOnly, Category = "State")
	ERecCharacterState CharacterState = ERecCharacterState::Alive;

	// Role (Striker/Guardian/Manipulator)
	UPROPERTY(ReplicatedUsing = OnRep_RoleType, VisibleInstanceOnly, Category = "Role")
	ERecRoleType RoleType = ERecRoleType::Striker;

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

	// 초기 트랜스폼 캐시(래그돌 복구용)
	FTransform InitialMeshRelativeTransform = FTransform::Identity;
	FTransform InitialCameraBoomRelativeTransform = FTransform::Identity;

	// Input helpers
	void SpectateUpPressed();
	void SpectateUpReleased();
	void SpectateDownPressed();
	void SpectateDownReleased();

	void SpectateMove(float Right, float Forward);
	void SpectateMoveVertical(float Axis, float DeltaTime);

	// R키 부활
	void ResurrectPressed();

	// P키 역할군 변경
	void CycleRolePressed();

	// Rep callbacks
	UFUNCTION()
	void OnRep_CurrentHP();

	UFUNCTION()
	void OnRep_CharacterState();

	UFUNCTION()
	void OnRep_RoleType();

	// Server RPCs
	UFUNCTION(Server, Reliable)
	void ServerApplyDamage(int32 DamageAmount);

	UFUNCTION(Server, Reliable)
	void ServerHeal(int32 HealAmount);

	UFUNCTION(Server, Reliable)
	void ServerResetHP();

	UFUNCTION(Server, Reliable)
	void ServerCycleRole();

	// Internal helpers
	void SetCurrentHP(int32 NewHP);
	void UpdateHPText();
	void UpdateRoleText();

	// Role helpers
	static FString RoleTypeToString(ERecRoleType InType);
	static float GetRoleSpeedMultiplier(ERecRoleType InType);
	void ApplyRoleStats();

	// State helpers
	void SetCharacterState(ERecCharacterState NewState); // server-only setter
	void ApplyCharacterState();                          // apply on both server/clients
	void ApplyDeadState();
	void ApplyAliveState();

	// PlayerStart로 리스폰(서있는 상태)
	void RespawnAtPlayerStart();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
