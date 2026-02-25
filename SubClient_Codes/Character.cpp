#include "RecCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameModeBase.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputCoreTypes.h"

#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

#include "Rec.h"

ARecCharacter::ARecCharacter()
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

	// Base speed cache
	BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	// Camera boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// HP Text
	HPTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HPText"));
	HPTextComponent->SetupAttachment(GetMesh());
	HPTextComponent->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
	HPTextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	HPTextComponent->SetHorizontalAlignment(EHTA_Center);
	HPTextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	HPTextComponent->SetWorldSize(20.f);
	HPTextComponent->SetText(FText::FromString(TEXT("HP: 100/100")));
	HPTextComponent->SetVisibility(true);

	// Role Text
	RoleTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RoleText"));
	RoleTextComponent->SetupAttachment(GetMesh());
	RoleTextComponent->SetRelativeLocation(FVector(0.f, 0.f, 245.f)); 
	RoleTextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RoleTextComponent->SetHorizontalAlignment(EHTA_Center);
	RoleTextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	RoleTextComponent->SetWorldSize(18.f);
	RoleTextComponent->SetText(FText::FromString(TEXT("Striker")));
	RoleTextComponent->SetVisibility(true);

	// HP init
	MaxHP = 100;
	CurrentHP = MaxHP;

	// State init
	CharacterState = ERecCharacterState::Alive;

	// Role init (기본 Striker)
	RoleType = ERecRoleType::Striker;
}

void ARecCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GetMesh())
	{
		InitialMeshRelativeTransform = GetMesh()->GetRelativeTransform();
	}
	if (CameraBoom)
	{
		InitialCameraBoomRelativeTransform = CameraBoom->GetRelativeTransform();
	}

	// 스탯 적용(역할군 속도)
	ApplyRoleStats();

	UpdateHPText();
	UpdateRoleText();
	ApplyCharacterState();
}

void ARecCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsDead() || !bCameraDetached)
		return;

	float Axis = 0.f;
	if (bSpectateUpHeld)    Axis += 1.f;
	if (bSpectateDownHeld)  Axis -= 1.f;

	if (Axis != 0.f)
	{
		SpectateMoveVertical(Axis, DeltaTime);
	}
}

void ARecCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARecCharacter, MaxHP);
	DOREPLIFETIME(ARecCharacter, CurrentHP);
	DOREPLIFETIME(ARecCharacter, CharacterState);
	DOREPLIFETIME(ARecCharacter, RoleType);
}

void ARecCharacter::OnRep_CurrentHP()
{
	UpdateHPText();
}

void ARecCharacter::OnRep_CharacterState()
{
	ApplyCharacterState();
}

void ARecCharacter::OnRep_RoleType()
{
	ApplyRoleStats();
	UpdateRoleText();
}

void ARecCharacter::UpdateHPText()
{
	if (!HPTextComponent) return;

	const FString Str = FString::Printf(TEXT("HP: %d/%d"), CurrentHP, MaxHP);
	HPTextComponent->SetText(FText::FromString(Str));
}

void ARecCharacter::UpdateRoleText()
{
	if (!RoleTextComponent) return;

	RoleTextComponent->SetText(FText::FromString(RoleTypeToString(RoleType)));
}

FString ARecCharacter::RoleTypeToString(ERecRoleType InType)
{
	switch (InType)
	{
	case ERecRoleType::Striker:     return TEXT("Striker");
	case ERecRoleType::Guardian:    return TEXT("Guardian");
	case ERecRoleType::Manipulator: return TEXT("Manipulator");
	default:                        return TEXT("Striker");
	}
}

float ARecCharacter::GetRoleSpeedMultiplier(ERecRoleType InType)
{
	switch (InType)
	{
	case ERecRoleType::Striker:     return 1.2f;
	case ERecRoleType::Guardian:    return 0.8f;
	case ERecRoleType::Manipulator: return 1.0f;
	default:                        return 1.0f;
	}
}

void ARecCharacter::ApplyRoleStats()
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		// BaseWalkSpeed 기준으로 배율 적용
		const float Mult = GetRoleSpeedMultiplier(RoleType);
		MoveComp->MaxWalkSpeed = BaseWalkSpeed * Mult;
	}
}

void ARecCharacter::SetCurrentHP(int32 NewHP)
{
	CurrentHP = FMath::Clamp(NewHP, 0, MaxHP);
	UpdateHPText();

	// Server decides death and replicates state
	if (HasAuthority() && CharacterState == ERecCharacterState::Alive && CurrentHP <= 0)
	{
		SetCharacterState(ERecCharacterState::Dead);
	}
}

void ARecCharacter::SetCharacterState(ERecCharacterState NewState)
{
	if (!HasAuthority())
		return;

	if (CharacterState == NewState)
		return;

	CharacterState = NewState;
	ApplyCharacterState();
	ForceNetUpdate();
}

void ARecCharacter::ApplyCharacterState()
{
	if (CharacterState == ERecCharacterState::Dead)
	{
		ApplyDeadState();
	}
	else
	{
		ApplyAliveState();
	}
}

void ARecCharacter::ApplyDamage(int32 DamageAmount)
{
	if (DamageAmount <= 0) return;

	// 서버 권한이 아니면 RPC로 요청
	if (!HasAuthority())
	{
		ServerApplyDamage(DamageAmount);
		return;
	}

	// 서버에서만 실제 적용
	SetCurrentHP(CurrentHP - DamageAmount);
}

void ARecCharacter::Heal(int32 HealAmount)
{
	if (HealAmount <= 0) return;

	if (!HasAuthority())
	{
		ServerHeal(HealAmount);
		return;
	}

	SetCurrentHP(CurrentHP + HealAmount);
}

void ARecCharacter::ResetHP()
{
	// Dead 상태에서 R: "서서 PlayerStart 리스폰"
	if (!HasAuthority())
	{
		ServerResetHP();
		return;
	}

	if (CharacterState == ERecCharacterState::Dead)
	{
		CurrentHP = MaxHP;
		UpdateHPText();

		SetCharacterState(ERecCharacterState::Alive);

		RespawnAtPlayerStart();

		ForceNetUpdate();
	}
	else
	{
		SetCurrentHP(MaxHP);
		ForceNetUpdate();
	}
}

void ARecCharacter::ServerApplyDamage_Implementation(int32 DamageAmount)
{
	ApplyDamage(DamageAmount);
}

void ARecCharacter::ServerHeal_Implementation(int32 HealAmount)
{
	Heal(HealAmount);
}

void ARecCharacter::ServerResetHP_Implementation()
{
	ResetHP();
}

void ARecCharacter::ServerCycleRole_Implementation()
{
	// 서버에서 역할군 순환
	switch (RoleType)
	{
	case ERecRoleType::Striker:
		RoleType = ERecRoleType::Guardian;
		break;
	case ERecRoleType::Guardian:
		RoleType = ERecRoleType::Manipulator;
		break;
	case ERecRoleType::Manipulator:
	default:
		RoleType = ERecRoleType::Striker;
		break;
	}

	ApplyRoleStats();
	UpdateRoleText();
	ForceNetUpdate();
}

float ARecCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HasAuthority() && ActualDamage > 0.f)
	{
		ApplyDamage(FMath::RoundToInt(ActualDamage));
	}

	return ActualDamage;
}

void ARecCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Enhanced Input bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARecCharacter::DoJumpStart);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARecCharacter::DoJumpEnd);
		}

		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARecCharacter::Move);
		}

		if (MouseLookAction)
		{
			EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ARecCharacter::Look);
		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARecCharacter::Look);
		}
	}
	else
	{
		UE_LOG(LogRec, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}

	PlayerInputComponent->BindKey(EKeys::Q, IE_Pressed, this, &ARecCharacter::SpectateUpPressed);
	PlayerInputComponent->BindKey(EKeys::Q, IE_Released, this, &ARecCharacter::SpectateUpReleased);

	PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &ARecCharacter::SpectateDownPressed);
	PlayerInputComponent->BindKey(EKeys::E, IE_Released, this, &ARecCharacter::SpectateDownReleased);

	PlayerInputComponent->BindKey(EKeys::R, IE_Pressed, this, &ARecCharacter::ResurrectPressed);

	PlayerInputComponent->BindKey(EKeys::P, IE_Pressed, this, &ARecCharacter::CycleRolePressed);
}

void ARecCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void ARecCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ARecCharacter::DoMove(float Right, float Forward)
{
	if (IsDead())
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

void ARecCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ARecCharacter::DoJumpStart()
{
	if (IsDead()) return;
	Jump();
}

void ARecCharacter::DoJumpEnd()
{
	StopJumping();
}

void ARecCharacter::Jump()
{
	if (IsDead()) return;

	Super::Jump();

	if (bPressedJump)
	{
		if (HasAuthority())
		{
			ApplyDamage(10);
		}
		else
		{
			ServerApplyDamage(10);
		}
	}
}

void ARecCharacter::ApplyDeadState()
{
	if (!IsDead()) return;

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

	// Disable capsule collision
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

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

void ARecCharacter::ApplyAliveState()
{
	// 관전 키 상태 초기화
	bSpectateUpHeld = false;
	bSpectateDownHeld = false;

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetAllBodiesSimulatePhysics(false);
		MeshComp->SetSimulatePhysics(false);

		MeshComp->bBlendPhysics = false;
		MeshComp->SetAllBodiesPhysicsBlendWeight(0.f);

		MeshComp->SetRelativeTransform(InitialMeshRelativeTransform);

		MeshComp->SetCollisionProfileName(TEXT("CharacterMesh"));
	}

	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Capsule->SetCollisionProfileName(TEXT("Pawn"));
	}

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
		MoveComp->StopMovementImmediately();
	}

	ApplyRoleStats();

	if (IsLocallyControlled())
	{
		if (CameraBoom && bCameraDetached)
		{
			CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			CameraBoom->SetRelativeTransform(InitialCameraBoomRelativeTransform);
			bCameraDetached = false;
		}
	}
}

void ARecCharacter::RespawnAtPlayerStart()
{
	if (!HasAuthority())
		return;

	AController* C = GetController();
	if (!C) return;

	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (!GM) return;

	AActor* StartSpot = GM->FindPlayerStart(C);
	if (!StartSpot) return;

	const FVector SpawnLoc = StartSpot->GetActorLocation();
	const FRotator SpawnRot = StartSpot->GetActorRotation();

	SetActorLocationAndRotation(SpawnLoc, SpawnRot, false, nullptr, ETeleportType::TeleportPhysics);

	C->SetControlRotation(SpawnRot);

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
		MoveComp->Velocity = FVector::ZeroVector;
	}
}

void ARecCharacter::SpectateMove(float Right, float Forward)
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

void ARecCharacter::SpectateUpPressed() { bSpectateUpHeld = true; }
void ARecCharacter::SpectateUpReleased() { bSpectateUpHeld = false; }

void ARecCharacter::SpectateDownPressed() { bSpectateDownHeld = true; }
void ARecCharacter::SpectateDownReleased() { bSpectateDownHeld = false; }

void ARecCharacter::SpectateMoveVertical(float Axis, float DeltaTime)
{
	if (!CameraBoom) return;

	const FVector Delta = FVector::UpVector * Axis * SpectateVerticalSpeed * DeltaTime;
	CameraBoom->AddWorldOffset(Delta, false);
}

void ARecCharacter::ResurrectPressed()
{
	// 로컬 입력에서만 호출
	if (!IsLocallyControlled())
		return;

	ResetHP();
}

void ARecCharacter::CycleRolePressed()
{
	if (!IsLocallyControlled())
		return;

	if (HasAuthority())
	{
		ServerCycleRole_Implementation(); 
	}
	else
	{
		ServerCycleRole();
	}
}
