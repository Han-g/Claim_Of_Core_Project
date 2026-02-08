#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyCharacter.generated.h"

class UHPComponent;

class UInputMappingContext;
class UInputAction;

class USpringArmComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Alive,
	Dead
};

UENUM(BlueprintType)
enum class EInputState : uint8
{
	Enabled,
	Disabled
};

UCLASS()
class CLAIM_OF_CORE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHPComponent* HPComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;

	UPROPERTY(ReplicatedUsing = OnRep_CharacterState)
	ECharacterState CharacterState;

	UPROPERTY(ReplicatedUsing = OnRep_InputState)
	EInputState InputState;

public:
	void EnterDead();

	bool IsDead() const { return CharacterState == ECharacterState::Dead; }
	bool CanProcessInput() const { return CharacterState == ECharacterState::Alive && InputState == EInputState::Enabled; }

protected:
	// ✅ Enhanced Input 콜백
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpPressed(const FInputActionValue& Value);
	void JumpReleased(const FInputActionValue& Value);

protected:
	UFUNCTION()
	void HandleHPZero();

	UFUNCTION()
	void OnRep_CharacterState();

	UFUNCTION()
	void OnRep_InputState();

	void ApplyCharacterState();
	void ApplyInputState();

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// ✅ Enhanced Input 에셋
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

private:
	// Spectate (죽은 뒤 카메라)
	UPROPERTY(EditDefaultsOnly, Category = "Spectate")
	float SpectateVerticalSpeed = 700.f;

	bool bCameraDetached = false;
	bool bSpectateUpHeld = false;
	bool bSpectateDownHeld = false;

	void SpectateUpPressed();
	void SpectateUpReleased();
	void SpectateDownPressed();
	void SpectateDownReleased();
	void SpectateMoveVertical(float Axis, float DeltaTime);
};
