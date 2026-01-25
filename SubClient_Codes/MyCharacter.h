#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UHPComponent;

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Alive UMETA(DisplayName = "Alive"),
	Dead  UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class EInputState : uint8
{
	Enabled  UMETA(DisplayName = "Enabled"),
	Disabled UMETA(DisplayName = "Disabled")
};

UCLASS()
class CLAIM_OF_CORE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHPComponent* HPComponent;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CharacterState, Category = "State")
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_InputState, Category = "State")
	EInputState InputState;

public:
	UFUNCTION(BlueprintCallable, Category = "State")
	void EnterDead(); 

	UFUNCTION(BlueprintPure, Category = "State")
	bool IsDead() const { return CharacterState == ECharacterState::Dead; }

	UFUNCTION(BlueprintPure, Category = "State")
	bool CanProcessInput() const { return CharacterState == ECharacterState::Alive && InputState == EInputState::Enabled; }

protected:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void StartJump();
	void StopJump();

protected:
	UFUNCTION()
	void HandleHPZero();

protected:
	UFUNCTION()
	void OnRep_CharacterState();

	UFUNCTION()
	void OnRep_InputState();

	void ApplyCharacterState();
	void ApplyInputState();

	void SetLocalInputIgnored(bool bIgnore);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
