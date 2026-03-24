#include "MyCharacter.h"

#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SkeletalMeshComponent.h"

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

#include "BaseItem.h"

AMyCharacter::AMyCharacter()
{
	// Replication / Tick
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	// Collision
	GetCapsuleComponent()->InitCapsuleSize(200.f, 475.0f);

	// Rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 2000.f;
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

	// State init
	CharacterState = ERecCharacterState::Alive;

	// Role init
	RoleType = ERecRoleType::Guardian;
}

void AMyCharacter::BeginPlay()
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
	ApplyRoleVisual();

	UpdateHPText();
	ApplyCharacterState();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Free-camera vertical move (Q/E) after death + camera detached
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


void AMyCharacter::OnRep_CurrentHP()
{
	UpdateHPText();
}

void AMyCharacter::OnRep_CharacterState()
{
	ApplyCharacterState();
}

void AMyCharacter::OnRep_RoleType()
{
	ApplyRoleStats();
}

void AMyCharacter::UpdateHPText()
{
	if (!HPTextComponent) return;

	const FString Str = FString::Printf(TEXT("HP: %d/%d"), CurrentHP, MaxHP);
	HPTextComponent->SetText(FText::FromString(Str));
}


float AMyCharacter::GetRoleSpeedMultiplier(ERecRoleType InType)
{
	switch (InType)
	{
	case ERecRoleType::Striker:     return 1.2f;
	case ERecRoleType::Guardian:    return 0.8f;
	case ERecRoleType::Manipulator: return 1.0f;
	default:                        return 1.0f;
	}
}

const FRoleVisualData& AMyCharacter::GetVisualData(ERecRoleType InRole) const
{
	switch (InRole)
	{
	case ERecRoleType::Striker:     return StrikerVisual;
	case ERecRoleType::Guardian:    return GuardianVisual;
	case ERecRoleType::Manipulator: return ManipulatorVisual;
	default:                        return StrikerVisual;
	}
}

void AMyCharacter::ApplyRoleStats()
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		// BaseWalkSpeed 기준으로 배율 적용
		const float Mult = GetRoleSpeedMultiplier(RoleType);
		MoveComp->MaxWalkSpeed = BaseWalkSpeed * Mult;
	}
}

void AMyCharacter::ApplyRoleVisual()
{
	const FRoleVisualData& Data = GetVisualData(RoleType);
	if (!Data.Mesh) return;

	USkeletalMeshComponent* SkelComp = GetMesh();
	if (!SkelComp) return;

	// 1) 모델 교체
	SkelComp->SetSkeletalMesh(Data.Mesh);

	// 2) 애님BP 교체
	if (Data.AnimBPClass)
	{
		SkelComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		SkelComp->SetAnimInstanceClass(Data.AnimBPClass);
	}
}


void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, MaxHP);
	DOREPLIFETIME(AMyCharacter, CurrentHP);
	DOREPLIFETIME(AMyCharacter, CharacterState);
	DOREPLIFETIME(AMyCharacter, RoleType);
}

FString AMyCharacter::RoleTypeToString(ERecRoleType InType)
{
	switch (InType)
	{
	case ERecRoleType::Striker:     return TEXT("Striker");
	case ERecRoleType::Guardian:    return TEXT("Guardian");
	case ERecRoleType::Manipulator: return TEXT("Manipulator");
	default:                        return TEXT("Striker");
	}
}

void AMyCharacter::SetCurrentHP(int32 NewHP)
{
	CurrentHP = FMath::Clamp(NewHP, 0, MaxHP);
	UpdateHPText();

	// Server decides death and replicates it
	if (HasAuthority() && !IsDead() && CurrentHP <= 0)
	{
		SetCharacterState(ERecCharacterState::Dead);
	}
}

void AMyCharacter::SetCharacterState(ERecCharacterState NewState)
{
	if (!HasAuthority())
		return;

	if (CharacterState == NewState)
		return;

	CharacterState = NewState;
	ApplyCharacterState();
	ForceNetUpdate();
}

void AMyCharacter::ApplyCharacterState()
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

void AMyCharacter::ApplyDamage(int32 DamageAmount)
{
	if (DamageAmount <= 0) return;

	// 서버 권한이 아니면 RPC로 요청
	if (HasAuthority())
	{
		ServerApplyDamage(DamageAmount);
		return;
	}

	// 서버에서만 실제 적용
	SetCurrentHP(CurrentHP - DamageAmount);
}

void AMyCharacter::Heal(int32 HealAmount)
{
	if (HealAmount <= 0) return;

	if (HasAuthority())
	{
		ServerHeal(HealAmount);
		return;
	}
}

void AMyCharacter::ResetHP()
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

void AMyCharacter::ServerApplyDamage_Implementation(int32 DamageAmount)
{
	ApplyDamage(DamageAmount);
}

void AMyCharacter::ServerHeal_Implementation(int32 HealAmount)
{
	Heal(HealAmount);
}

void AMyCharacter::ServerResetHP_Implementation()
{
	ResetHP();
}

void AMyCharacter::ServerCycleRole_Implementation()
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
	ApplyRoleVisual();
	ForceNetUpdate();
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

	PlayerInputComponent->BindKey(EKeys::F, IE_Pressed, this, &AMyCharacter::EquipItem);
	PlayerInputComponent->BindKey(EKeys::G, IE_Pressed, this, &AMyCharacter::DropCurrentItem);

	// Q/E hold for vertical movement while spectating
	PlayerInputComponent->BindKey(EKeys::Q, IE_Pressed, this, &AMyCharacter::SpectateUpPressed);
	PlayerInputComponent->BindKey(EKeys::Q, IE_Released, this, &AMyCharacter::SpectateUpReleased);

	PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &AMyCharacter::SpectateDownPressed);
	PlayerInputComponent->BindKey(EKeys::E, IE_Released, this, &AMyCharacter::SpectateDownReleased);

	// R키 부활
	PlayerInputComponent->BindKey(EKeys::R, IE_Pressed, this, &AMyCharacter::ResurrectPressed);
	
	// P키 역할군 변경
	PlayerInputComponent->BindKey(EKeys::P, IE_Pressed, this, &AMyCharacter::CycleRolePressed);

	PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &AMyCharacter::SpectateConfirmPressed);
	PlayerInputComponent->BindKey(EKeys::T, IE_Pressed, this, &AMyCharacter::SelfDamagePressed);
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
	if (IsDead()) return;
	Jump();
}

void AMyCharacter::DoJumpEnd()
{
	StopJumping();
}

void AMyCharacter::Jump()
{
	if (IsDead()) return;

	Super::Jump();

}


void AMyCharacter::SelfDamagePressed()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	if (IsDead() || bDeathSequenceLocked)
	{
		return;
	}

	ApplyDamage(10);
}

void AMyCharacter::UpdateLocalPostProcessEffects()
{
	if (!IsLocallyControlled() || !FollowCamera)
	{
		return;
	}

	FollowCamera->PostProcessSettings.bOverride_ColorSaturation = false;
	FollowCamera->PostProcessSettings.bOverride_VignetteIntensity = false;
	FollowCamera->PostProcessSettings.bOverride_SceneColorTint = false;
	FollowCamera->PostProcessBlendWeight = 0.0f;

	if (bDeathSequenceLocked)
	{
		FollowCamera->PostProcessSettings.bOverride_ColorSaturation = true;
		FollowCamera->PostProcessBlendWeight = 1.0f;
		FollowCamera->PostProcessSettings.ColorSaturation = FVector4(0.f, 0.f, 0.f, 1.f);
		FollowCamera->PostProcessSettings.SceneColorTint = FLinearColor::White;
		return;
	}

	if (bLowHPEffectActive)
	{
		FollowCamera->PostProcessSettings.bOverride_ColorSaturation = true;
		FollowCamera->PostProcessSettings.bOverride_VignetteIntensity = true;
		FollowCamera->PostProcessSettings.bOverride_SceneColorTint = true;

		FollowCamera->PostProcessBlendWeight = LowHPPostProcessBlendWeight;
		FollowCamera->PostProcessSettings.ColorSaturation =
			FVector4(LowHPSaturation, LowHPSaturation, LowHPSaturation, 1.f);

		FollowCamera->PostProcessSettings.VignetteIntensity = LowHPVignetteIntensity;
		FollowCamera->PostProcessSettings.SceneColorTint = LowHPSceneTint;
		return;
	}

	FollowCamera->PostProcessSettings.ColorSaturation = FVector4(1.f, 1.f, 1.f, 1.f);
	FollowCamera->PostProcessSettings.VignetteIntensity = 0.4f;
	FollowCamera->PostProcessSettings.SceneColorTint = FLinearColor::White;
}

void AMyCharacter::UpdateLowHPEffectState()
{
	const bool bShouldBeLowHP =
		(CharacterState == ERecCharacterState::Alive) &&
		(CurrentHP > 0) &&
		(CurrentHP <= LowHPThreshold);

	bLowHPEffectActive = bShouldBeLowHP;
	UpdateLocalPostProcessEffects();
}

void AMyCharacter::UpdateLowHPPulseEffect(float DeltaTime)
{
	if (!IsLocallyControlled() || !FollowCamera)
	{
		return;
	}

	if (bDeathSequenceLocked)
	{
		return;
	}

	if (!bLowHPEffectActive)
	{
		return;
	}

	const float Time = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
	const float Pulse01 = 0.5f + 0.5f * FMath::Sin(Time * LowHPPulseSpeed * 2.0f * PI);

	const float DynamicBlend =
		LowHPPostProcessBlendWeight + (Pulse01 * LowHPPulseBlendAmplitude);

	const float DynamicVignette =
		LowHPVignetteIntensity + (Pulse01 * LowHPPulseVignetteAmplitude);

	FollowCamera->PostProcessSettings.bOverride_ColorSaturation = true;
	FollowCamera->PostProcessSettings.bOverride_VignetteIntensity = true;
	FollowCamera->PostProcessSettings.bOverride_SceneColorTint = true;

	FollowCamera->PostProcessBlendWeight = DynamicBlend;
	FollowCamera->PostProcessSettings.ColorSaturation =
		FVector4(LowHPSaturation, LowHPSaturation, LowHPSaturation, 1.f);

	FollowCamera->PostProcessSettings.VignetteIntensity = DynamicVignette;
	FollowCamera->PostProcessSettings.SceneColorTint = LowHPSceneTint;
}

void AMyCharacter::StartDeathCameraShake()
{
	if (!IsLocallyControlled() || !CameraBoom)
	{
		return;
	}

	bDeathCameraShaking = true;
	DeathShakeElapsed = 0.0f;
}

void AMyCharacter::UpdateDeathCameraShake(float DeltaTime)
{
	if (!CameraBoom)
	{
		return;
	}

	if (!bDeathCameraShaking)
	{
		return;
	}

	DeathShakeElapsed += DeltaTime;

	const float Alpha = DeathShakeElapsed / FMath::Max(DeathShakeDuration, KINDA_SMALL_NUMBER);
	if (Alpha >= 1.0f)
	{
		StopDeathCameraShake();
		return;
	}

	const float Damping = 1.0f - Alpha;
	const float Time = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;

	const float OffsetY = FMath::Sin(Time * DeathShakeFrequency) * DeathShakeAmplitude * Damping;
	const float OffsetZ = FMath::Cos(Time * DeathShakeFrequency * 1.3f) * (DeathShakeAmplitude * 0.6f) * Damping;

	CameraBoom->SocketOffset = InitialCameraBoomSocketOffset + FVector(0.f, OffsetY, OffsetZ);
}

void AMyCharacter::StopDeathCameraShake()
{
	bDeathCameraShaking = false;
	DeathShakeElapsed = 0.0f;

	if (CameraBoom)
	{
		CameraBoom->SocketOffset = InitialCameraBoomSocketOffset;
	}
}

void AMyCharacter::SetDeathVisualsEnabled(bool bEnabled)
{
	bDeathSequenceLocked = bEnabled;
	UpdateLocalPostProcessEffects();
}

void AMyCharacter::SetPlayerControlLocked(bool bLocked)
{
	if (!IsLocallyControlled())
	{
		return;
	}

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		PC->SetIgnoreMoveInput(bLocked);
		PC->SetIgnoreLookInput(bLocked);
	}
}

void AMyCharacter::UpdateDeathUI()
{
	if (!IsLocallyControlled() || !DeathUITextComponent)
	{
		return;
	}

	DeathUITextComponent->SetHiddenInGame(false);
	DeathUITextComponent->SetVisibility(true);

	if (bAwaitingSpectateInput)
	{
		if (bSpectateInputUnlocked)
		{
			DeathUITextComponent->SetText(FText::FromString(TEXT("YOU DIED\nPress Space")));
		}
		else
		{
			DeathUITextComponent->SetText(FText::FromString(TEXT("YOU DIED")));
		}
	}
	else if (bCanSpectate)
	{
		DeathUITextComponent->SetText(FText::FromString(TEXT("SPECTATING")));
	}
	else
	{
		DeathUITextComponent->SetText(FText::FromString(TEXT("YOU DIED")));
	}
}

void AMyCharacter::ShowSpectatingUI()
{
	UpdateDeathUI();

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpectatingUIHideTimerHandle);
		GetWorldTimerManager().SetTimer(
			SpectatingUIHideTimerHandle,
			this,
			&AMyCharacter::HideDeathUI,
			SpectatingUITextDuration,
			false
		);
	}
}

void AMyCharacter::HideDeathUI()
{
	if (!DeathUITextComponent)
	{
		return;
	}

	DeathUITextComponent->SetText(FText::GetEmpty());
	DeathUITextComponent->SetVisibility(false);
	DeathUITextComponent->SetHiddenInGame(true);
}

void AMyCharacter::ShowCorpse()
{
	bCorpseHidden = false;

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetVisibility(true, true);
		MeshComp->SetHiddenInGame(false, true);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	if (HPTextComponent)
	{
		HPTextComponent->SetVisibility(true);
		HPTextComponent->SetHiddenInGame(false);
	}
}

void AMyCharacter::HideCorpse()
{
	if (!IsDead() || bCorpseHidden)
	{
		return;
	}

	bCorpseHidden = true;

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetAllBodiesSimulatePhysics(false);
		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComp->SetVisibility(false, true);
		MeshComp->SetHiddenInGame(true, true);
	}

	if (HPTextComponent)
	{
		HPTextComponent->SetVisibility(false);
		HPTextComponent->SetHiddenInGame(true);
	}

}

void AMyCharacter::EnterDeathWaitingState()
{
	bCanSpectate = false;
	bAwaitingSpectateInput = true;
	bSpectateInputUnlocked = false;

	SetDeathVisualsEnabled(true);
	SetPlayerControlLocked(true);
	UpdateDeathUI();

	if (CameraBoom && !bCameraDetached)
	{
		CameraBoom->TargetArmLength = InitialCameraBoomArmLength;
	}

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpectateInputUnlockTimerHandle);
		GetWorldTimerManager().SetTimer(
			SpectateInputUnlockTimerHandle,
			this,
			&AMyCharacter::UnlockSpectateInput,
			SpectateInputUnlockDelay,
			false
		);
	}
}

void AMyCharacter::UnlockSpectateInput()
{
	if (!IsDead() || !bAwaitingSpectateInput)
	{
		return;
	}

	bSpectateInputUnlocked = true;
	UpdateDeathUI();
}

void AMyCharacter::EnterSpectateMode()
{
	if (!IsDead() || !bAwaitingSpectateInput || !bSpectateInputUnlocked)
	{
		return;
	}

	bCanSpectate = true;
	bAwaitingSpectateInput = false;

	HideCorpse();

	if (IsLocallyControlled())
	{
		SetDeathVisualsEnabled(false);
		SetPlayerControlLocked(false);

		if (CameraBoom && !bCameraDetached)
		{
			CameraBoom->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			bCameraDetached = true;
		}

		ShowSpectatingUI();
	}
}

void AMyCharacter::ApplyDeadState()
{
	if (!IsDead()) return;

	ShowCorpse();

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

	StartDeathCameraShake();
	EnterDeathWaitingState();
}

void AMyCharacter::ApplyAliveState()
{
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpectatingUIHideTimerHandle);
		GetWorldTimerManager().ClearTimer(SpectateInputUnlockTimerHandle);
	}

	bSpectateUpHeld = false;
	bSpectateDownHeld = false;
	bCanSpectate = false;
	bAwaitingSpectateInput = false;
	bSpectateInputUnlocked = false;
	bDeathSequenceLocked = false;

	ShowCorpse();

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetAllBodiesSimulatePhysics(false);
		MeshComp->SetSimulatePhysics(false);
		MeshComp->bBlendPhysics = false;
		MeshComp->SetAllBodiesPhysicsBlendWeight(0.f);
		MeshComp->SetRelativeTransform(InitialMeshRelativeTransform);
		MeshComp->SetCollisionProfileName(TEXT("CharacterMesh"));
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
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
	UpdateHPText();

	StopDeathCameraShake();

	if (CameraBoom)
	{
		CameraBoom->TargetArmLength = InitialCameraBoomArmLength;
		CameraBoom->SocketOffset = InitialCameraBoomSocketOffset;
	}

	if (IsLocallyControlled())
	{
		SetPlayerControlLocked(false);
		HideDeathUI();

		if (CameraBoom && bCameraDetached)
		{
			CameraBoom->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
			CameraBoom->SetRelativeTransform(InitialCameraBoomRelativeTransform);
			CameraBoom->TargetArmLength = InitialCameraBoomArmLength;
			CameraBoom->SocketOffset = InitialCameraBoomSocketOffset;
			bCameraDetached = false;
		}

		UpdateLowHPEffectState();
	}
}

void AMyCharacter::RespawnAtPlayerStart()
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

void AMyCharacter::ResurrectPressed()
{
	// 로컬 입력에서만 호출
	if (!IsLocallyControlled())
		return;

	ResetHP();
}

void AMyCharacter::CycleRolePressed()
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

void AMyCharacter::SpectateConfirmPressed()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	if (!IsDead())
	{
		return;
	}

	if (!bAwaitingSpectateInput)
	{
		return;
	}

	if (!bSpectateInputUnlocked)
	{
		return;
	}

	EnterSpectateMode();
}



////////
////////
////////
////////
////////
// Attack function

void AMyCharacter::Attack()
{
	// 무기 들고 있으면 무기 쪽 StartUse로 처리(무기 몽타주 + 노티파이 + DoHit)
	if (CurrentItem)
	{
		CurrentItem->StartUse();
		return;
	}
	// 무기 없을 때만 기존 맨손 몽타주(원하면 유지)
	if (!IsValid(Controller)) return;

	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	const FRoleVisualData& Data = GetVisualData(RoleType);
	if (!AnimInstance)	return;
	if (!Data.AttackMontage)	return;
	if (AnimInstance->Montage_IsPlaying(Data.AttackMontage)) return;

	AnimInstance->Montage_Play(Data.AttackMontage);

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

// Item API

void AMyCharacter::SetOverlappingItem(ABaseItem* Item)
{
	OverlappingItem = Item;

}

void AMyCharacter::EquipItem()
{
	if (!OverlappingItem) return;
	if (CurrentItem) return; // 이미 무기 들고 있으면 무시

	CurrentItem = OverlappingItem;

	// 무기 쪽에 오너 세팅(네 BaseItem에 있음)
	CurrentItem->SetOwnerCharacter(this);

	// 충돌/물리 끄기(손에 붙이면 보통 필요없음)
	CurrentItem->SetActorEnableCollision(false);

	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(CurrentItem->GetRootComponent()))
	{
		Prim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Prim->SetSimulatePhysics(false);
	}

	// 손 소켓에 부착
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		CurrentItem->AttachToComponent(
			MeshComp,
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("RightHandSocket")
		);
	}
}

void AMyCharacter::DropCurrentItem()
{
	if (!CurrentItem) return;

	CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentItem->SetOwnerCharacter(nullptr);

	// 바닥에 떨어뜨릴거면 충돌/물리 다시 켜기
	CurrentItem->SetActorEnableCollision(true);

	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(CurrentItem->GetRootComponent()))
	{
		Prim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Prim->SetSimulatePhysics(true);
	}

	CurrentItem = nullptr;
}

void AMyCharacter::AnimNotify_AttackHit()
{
	if (CurrentItem)
	{
		CurrentItem->DoHit(); // 여기서 SphereTraceMulti로 피격 판정
	}
}
