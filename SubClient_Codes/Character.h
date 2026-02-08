#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RecCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;
class UTextRenderComponent;

UCLASS(abstract)
class ARecCharacter : public ACharacter
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

public:
	ARecCharacter();

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
