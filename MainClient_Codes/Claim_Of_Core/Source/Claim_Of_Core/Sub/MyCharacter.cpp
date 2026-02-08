#include "MyCharacter.h"
#include "HPComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "InputCoreTypes.h"

// ✅ Enhanced Input
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"
#include "Engine/LocalPlayer.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	SetReplicateMovement(true);

	HPComponent = CreateDefaultSubobject<UHPComponent>(TEXT("HPComponent"));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->bOrientRotationToMovement = true;
		MoveComp->RotationRate = FRotator(0.f, 500.f, 0.f);
		MoveComp->JumpZVelocity = 500.f;
		MoveComp->AirControl = 0.35f;
		MoveComp->MaxWalkSpeed = 500.f;
		MoveComp->BrakingDecelerationWalking = 2000.f;
	}

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	CharacterState = ECharacterState::Alive;
	InputState = EInputState::Enabled;

	DefaultMappingContext = nullptr;
	MoveAction = nullptr;
	LookAction = nullptr;
	JumpAction = nullptr;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HPComponent)
	{
		HPComponent->OnHPZero.AddDynamic(this, &AMyCharacter::HandleHPZero);
	}

	// ✅ 로컬 플레이어에 MappingContext 추가
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LP = PC->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* SubSys = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (DefaultMappingContext)
				{
					SubSys->AddMappingContext(DefaultMappingContext, 0);
				}
			}
		}
	}
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead() || !bCameraDetached) return;

	float Axis = 0.f;
	if (bSpectateUpHeld) Axis += 1.f;
	if (bSpectateDownHeld) Axis -= 1.f;

	if (Axis != 0.f)
	{
		SpectateMoveVertical(Axis, DeltaTime);
	}
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ✅ Enhanced Input 바인딩
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		}
		if (LookAction)
		{
			EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		}
		if (JumpAction)
		{
			EIC->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::JumpPressed);
			EIC->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::JumpReleased);
			EIC->BindAction(JumpAction, ETriggerEvent::Canceled, this, &AMyCharacter::JumpReleased);
		}
	}

	// ✅ Q/E는 키 바인딩(원하면 InputAction으로 바꾸면 됨)
	PlayerInputComponent->BindKey(EKeys::Q, IE_Pressed, this, &AMyCharacter::SpectateUpPressed);
	PlayerInputComponent->BindKey(EKeys::Q, IE_Released, this, &AMyCharacter::SpectateUpReleased);
	PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &AMyCharacter::SpectateDownPressed);
	PlayerInputComponent->BindKey(EKeys::E, IE_Released, this, &AMyCharacter::SpectateDownReleased);
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	if (!CanProcessInput()) return;

	const FVector2D Axis = Value.Get<FVector2D>();
	if (Axis.IsNearlyZero()) return;

	const FRotator ControlRot = Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator;
	const FRotator YawRot(0.f, ControlRot.Yaw, 0.f);

	const FVector ForwardDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDir, Axis.Y);
	AddMovementInput(RightDir, Axis.X);
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D Axis = Value.Get<FVector2D>();
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void AMyCharacter::JumpPressed(const FInputActionValue& Value)
{
	if (CanProcessInput())
	{
		Jump();
	}
}

void AMyCharacter::JumpReleased(const FInputActionValue& Value)
{
	StopJumping();
}

void AMyCharacter::HandleHPZero()
{
	EnterDead();
}

void AMyCharacter::EnterDead()
{
	if (HasAuthority())
	{
		CharacterState = ECharacterState::Dead;
		OnRep_CharacterState();
	}
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
			MoveComp->DisableMovement();
		}

		if (IsLocallyControlled() && CameraBoom && !bCameraDetached)
		{
			CameraBoom->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			bCameraDetached = true;
		}
	}
}

void AMyCharacter::ApplyInputState()
{
}

void AMyCharacter::SpectateUpPressed() { bSpectateUpHeld = true; }
void AMyCharacter::SpectateUpReleased() { bSpectateUpHeld = false; }
void AMyCharacter::SpectateDownPressed() { bSpectateDownHeld = true; }
void AMyCharacter::SpectateDownReleased() { bSpectateDownHeld = false; }

void AMyCharacter::SpectateMoveVertical(float Axis, float DeltaTime)
{
	if (!CameraBoom) return;

	CameraBoom->AddWorldOffset(
		FVector::UpVector * Axis * SpectateVerticalSpeed * DeltaTime,
		false
	);
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, CharacterState);
	DOREPLIFETIME(AMyCharacter, InputState);
}
