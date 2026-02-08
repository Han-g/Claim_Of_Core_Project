#include "MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputCoreTypes.h"

#include "Net/UnrealNetwork.h"

AMyCharacter::AMyCharacter()
{
	// Replication / Tick
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	// Collision
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// HP Text (3D)
	HPTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HPText"));
	HPTextComponent->SetupAttachment(GetMesh());
	HPTextComponent->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
	HPTextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	HPTextComponent->SetHorizontalAlignment(EHTA_Center);
	HPTextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	HPTextComponent->SetWorldSize(20.f);
	HPTextComponent->SetText(FText::FromString(TEXT("HP: 100/100")));
	HPTextComponent->SetVisibility(true);

	// HP init
	MaxHP = 100;
	CurrentHP = MaxHP;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	UpdateHPText();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Free-camera vertical move (Q/E) after death + camera detached
	if (!bIsDead || !bCameraDetached)
		return;

	float Axis = 0.f;
	if (bSpectateUpHeld)    Axis += 1.f;
	if (bSpectateDownHeld)  Axis -= 1.f;

	if (Axis != 0.f)
	{
		SpectateMoveVertical(Axis, DeltaTime);
	}
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, MaxHP);
	DOREPLIFETIME(AMyCharacter, CurrentHP);
	DOREPLIFETIME(AMyCharacter, bIsDead);
}

void AMyCharacter::OnRep_CurrentHP()
{
	UpdateHPText();
}

void AMyCharacter::OnRep_IsDead()
{
	ApplyDeadState();
}

void AMyCharacter::UpdateHPText()
{
	if (!HPTextComponent) return;

	const FString Str = FString::Printf(TEXT("HP: %d/%d"), CurrentHP, MaxHP);
	HPTextComponent->SetText(FText::FromString(Str));
}

void AMyCharacter::SetCurrentHP(int32 NewHP)
{
	CurrentHP = FMath::Clamp(NewHP, 0, MaxHP);
	UpdateHPText();

	// Server decides death and replicates it
	if (HasAuthority() && !bIsDead && CurrentHP <= 0)
	{
		bIsDead = true;
		ApplyDeadState();
		ForceNetUpdate();
	}
}

void AMyCharacter::ApplyDamage(int32 DamageAmount)
{
	if (DamageAmount <= 0) return;

	// HP changes are server-authoritative
	if (HasAuthority())
	{
		SetCurrentHP(CurrentHP - DamageAmount);
	}
}

void AMyCharacter::Heal(int32 HealAmount)
{
	if (HealAmount <= 0) return;

	if (HasAuthority())
	{
		SetCurrentHP(CurrentHP + HealAmount);
	}
}

void AMyCharacter::ResetHP()
{
	if (HasAuthority())
	{
		SetCurrentHP(MaxHP);
	}
}

float AMyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HasAuthority() && ActualDamage > 0.f)
	{
		ApplyDamage(FMath::RoundToInt(ActualDamage));
	}

	return ActualDamage;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enhanced Input bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);

		// Attacking
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::Attack);
		EnhancedInputComponent->BindAction(KnockbackAction, ETriggerEvent::Started, this, &AMyCharacter::KnockbackTest);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}

	// Q/E hold for vertical movement while spectating
	PlayerInputComponent->BindKey(EKeys::Q, IE_Pressed, this, &AMyCharacter::SpectateUpPressed);
	PlayerInputComponent->BindKey(EKeys::Q, IE_Released, this, &AMyCharacter::SpectateUpReleased);

	PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &AMyCharacter::SpectateDownPressed);
	PlayerInputComponent->BindKey(EKeys::E, IE_Released, this, &AMyCharacter::SpectateDownReleased);
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AMyCharacter::DoMove(float Right, float Forward)
{
	// Dead: move detached camera instead of character
	if (bIsDead)
	{
		SpectateMove(Right, Forward);
		return;
	}

	if (GetController() != nullptr)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AMyCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMyCharacter::DoJumpStart()
{
	if (bIsDead) return;
	Jump();
}

void AMyCharacter::DoJumpEnd()
{
	StopJumping();
}

void AMyCharacter::Jump()
{
	if (bIsDead) return;

	Super::Jump();

	// Apply jump damage only when jump is considered "pressed" (server-authoritative)
	if (bPressedJump)
	{
		if (HasAuthority())
		{
			ApplyDamage(10);
		}
	}
}

void AMyCharacter::ApplyDeadState()
{
	if (!bIsDead) return;

	// Stop character movement
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
		MoveComp->DisableMovement();
	}

	StopJumping();

	// Ragdoll (requires Physics Asset)
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
		MeshComp->SetSimulatePhysics(true);
		MeshComp->WakeAllRigidBodies();
		MeshComp->bBlendPhysics = true;
	}

	// Disable capsule collision (optional but kept as-is)
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	// Local: detach camera boom for free movement
	if (IsLocallyControlled())
	{
		if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			PC->SetIgnoreMoveInput(false);
			PC->SetIgnoreLookInput(false);
		}

		if (CameraBoom && !bCameraDetached)
		{
			CameraBoom->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			bCameraDetached = true;
		}
	}
}

void AMyCharacter::SpectateMove(float Right, float Forward)
{
	if (!CameraBoom) return;

	const float Dt = GetWorld() ? GetWorld()->GetDeltaSeconds() : 0.f;

	FRotator ControlRot = GetActorRotation();
	if (GetController())
	{
		ControlRot = GetController()->GetControlRotation();
	}
	const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

	const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	const FVector Delta = (ForwardDir * Forward + RightDir * Right) * SpectateMoveSpeed * Dt;
	CameraBoom->AddWorldOffset(Delta, false);
}

void AMyCharacter::SpectateUpPressed() { bSpectateUpHeld = true; }
void AMyCharacter::SpectateUpReleased() { bSpectateUpHeld = false; }

void AMyCharacter::SpectateDownPressed() { bSpectateDownHeld = true; }
void AMyCharacter::SpectateDownReleased() { bSpectateDownHeld = false; }

void AMyCharacter::SpectateMoveVertical(float Axis, float DeltaTime)
{
	if (!CameraBoom) return;

	const FVector Delta = FVector::UpVector * Axis * SpectateVerticalSpeed * DeltaTime;
	CameraBoom->AddWorldOffset(Delta, false);
}

// Attack function

void AMyCharacter::Attack()
{
	if (!IsValid(Controller))
	{
		UE_LOG(LogTemp, Error, TEXT("[Attack] Controller INVALID"));
		return;
	}

	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	if (!AnimInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("[Attack] AnimInstance NULL"));
		return;
	}

	if (!AttackMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("[Attack] AttackMontage NULL"));
		return;
	}

	if (AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Attack] Montage already playing"));
		return;
	}

	float PlayRate = AnimInstance->Montage_Play(AttackMontage);


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