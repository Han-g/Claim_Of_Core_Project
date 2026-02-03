#include "MyCharacter.h"
#include "HPComponent.h"

#include "Kismet/GameplayStatics.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

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

	DefaultMappingContext = nullptr;
	MoveAction = nullptr;
	LookAction = nullptr;
	JumpAction = nullptr;

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

	// 1) 로컬 플레이어 서브시스템에 IMC 추가 (템플릿 방식)
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{
				if (DefaultMappingContext)
				{
					Subsystem->AddMappingContext(DefaultMappingContext, 0);
				}
			}
		}
	}

	// 2) 바인딩
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		}

		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::StartJump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJump);
		}

		// Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::Attack);
		EnhancedInputComponent->BindAction(KnockbackAction, ETriggerEvent::Started, this, &AMyCharacter::KnockbackTest);
	}
	UE_LOG(LogTemp, Warning, TEXT("MoveAction: %s"), *GetNameSafe(MoveAction));
UE_LOG(LogTemp, Warning, TEXT("LookAction: %s"), *GetNameSafe(LookAction));
UE_LOG(LogTemp, Warning, TEXT("JumpAction: %s"), *GetNameSafe(JumpAction));

}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	if (!CanProcessInput()) return;
	const FVector2D Axis = Value.Get<FVector2D>();


	MoveForward(Axis.Y);
	MoveRight(Axis.X);

}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	if (!CanProcessInput()) return;

	const FVector2D Axis = Value.Get<FVector2D>();

	// 거의 0이면 무시(노이즈 방지)
	if (Axis.IsNearlyZero(0.001f)) return;

	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
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

// Attack function

void AMyCharacter::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("[Attack] Start"));

	if (!IsValid(Controller))
	{
		UE_LOG(LogTemp, Error, TEXT("[Attack] Controller INVALID"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[Attack] Controller OK"));

	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("[Attack] AnimInstance NULL"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[Attack] AnimInstance OK"));

	if (!AttackMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("[Attack] AttackMontage NULL"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[Attack] AttackMontage OK"));

	if (AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Attack] Montage already playing"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[Attack] Montage NOT playing, will play now"));

	float PlayRate = AnimInstance->Montage_Play(AttackMontage);
	UE_LOG(LogTemp, Warning, TEXT("[Attack] Montage_Play called, PlayRate=%f"), PlayRate);


}

// 테스트용 넉백 함수

void AMyCharacter::KnockbackTest() {
	ApplyKnockback(this, 1200.f);
}

// 넉백 적용 함수
void AMyCharacter::ApplyKnockback(AActor* Attacker, float KnockbackStrength)
{
	if (!Attacker) return;

	FVector Dir = -GetActorForwardVector();
	Dir.Z = 0.f;
	Dir = Dir.GetSafeNormal();

	FVector LaunchVel = Dir * KnockbackStrength;
	LaunchVel.Z = 0.f;

	GetCharacterMovement()->SetMovementMode(MOVE_Falling);
	LaunchCharacter(LaunchVel, true, true);
}

void AMyCharacter::OnAttackOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (AMyCharacter* Victim =
		Cast<AMyCharacter>(OtherActor))
	{
		Victim->ApplyKnockback(this, 1200.f);
	}
}
