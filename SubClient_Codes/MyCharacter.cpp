#include "MyCharacter.h"
#include "HPComponent.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/CapsuleComponent.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;
	SetReplicateMovement(true);

	HPComponent = CreateDefaultSubobject<UHPComponent>(TEXT("HPComponent"));

	CharacterState = ECharacterState::Alive;
	InputState = EInputState::Enabled;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HPComponent)
	{
		HPComponent->OnHPZero.AddDynamic(this, &AMyCharacter::HandleHPZero);
	}

	if (HasAuthority())
	{
		CharacterState = ECharacterState::Alive;
		InputState = EInputState::Enabled;
	}

	ApplyCharacterState();
	ApplyInputState();
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AMyCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AMyCharacter::LookUp);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AMyCharacter::StartJump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &AMyCharacter::StopJump);
}

float AMyCharacter::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	const float Actual = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (Actual <= 0.f) return 0.f;

	if (HPComponent)
	{
		HPComponent->ApplyDamage(FMath::RoundToInt(Actual));
	}

	return Actual;
}

void AMyCharacter::MoveForward(float Value)
{
	if (!CanProcessInput()) return;
	if (Value == 0.f) return;

	AddMovementInput(GetActorForwardVector(), Value);
}

void AMyCharacter::MoveRight(float Value)
{
	if (!CanProcessInput()) return;
	if (Value == 0.f) return;

	AddMovementInput(GetActorRightVector(), Value);
}

void AMyCharacter::Turn(float Value)
{
	if (!CanProcessInput()) return;
	AddControllerYawInput(Value);
}

void AMyCharacter::LookUp(float Value)
{
	if (!CanProcessInput()) return;
	AddControllerPitchInput(Value);
}

void AMyCharacter::StartJump()
{
	if (!CanProcessInput()) return;
	Jump();
}

void AMyCharacter::StopJump()
{
	StopJumping();
}

void AMyCharacter::HandleHPZero()
{
	if (HasAuthority())
	{
		EnterDead();
	}
}

void AMyCharacter::EnterDead()
{
	if (!HasAuthority()) return;
	if (CharacterState == ECharacterState::Dead) return;

	CharacterState = ECharacterState::Dead;
	InputState = EInputState::Disabled;

	ApplyCharacterState();
	ApplyInputState();

	ForceNetUpdate();
}

void AMyCharacter::OnRep_CharacterState()
{
	ApplyCharacterState();
}

void AMyCharacter::OnRep_InputState()
{
	ApplyInputState();
}

void AMyCharacter::ApplyCharacterState()
{
	if (CharacterState == ECharacterState::Dead)
	{
		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		{
			MoveComp->StopMovementImmediately();
			MoveComp->DisableMovement();
		}

		if (UCapsuleComponent* Capsule = GetCapsuleComponent())
		{
			Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

		StopJumping();
	}
	else
	{
	}
}

void AMyCharacter::ApplyInputState()
{
	if (!IsLocallyControlled()) return;

	const bool bIgnore = (InputState == EInputState::Disabled) || (CharacterState == ECharacterState::Dead);
	SetLocalInputIgnored(bIgnore);
}

void AMyCharacter::SetLocalInputIgnored(bool bIgnore)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC) return;

	PC->SetIgnoreMoveInput(bIgnore);
	PC->SetIgnoreLookInput(bIgnore);

	if (bIgnore)
	{
		DisableInput(PC);
	}
	else
	{
		EnableInput(PC);
	}
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, CharacterState);
	DOREPLIFETIME(AMyCharacter, InputState);
}
