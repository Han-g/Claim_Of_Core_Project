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
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HPTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HPText"));
	HPTextComponent->SetupAttachment(GetMesh());
	HPTextComponent->SetRelativeLocation(FVector(0.f, 0.f, 220.f));
	HPTextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	HPTextComponent->SetHorizontalAlignment(EHTA_Center);
	HPTextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	HPTextComponent->SetWorldSize(20.f);
	HPTextComponent->SetText(FText::FromString(TEXT("HP: 100/100")));
	HPTextComponent->SetVisibility(true);

	RoleTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("RoleText"));
	RoleTextComponent->SetupAttachment(GetMesh());
	RoleTextComponent->SetRelativeLocation(FVector(0.f, 0.f, 245.f));
	RoleTextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RoleTextComponent->SetHorizontalAlignment(EHTA_Center);
	RoleTextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	RoleTextComponent->SetWorldSize(18.f);
	RoleTextComponent->SetText(FText::FromString(TEXT("Striker")));
	RoleTextComponent->SetVisibility(true);

	DeathUITextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DeathUIText"));
	DeathUITextComponent->SetupAttachment(FollowCamera);
	DeathUITextComponent->SetRelativeLocation(FVector(135.f, 0.f, -15.f));
	DeathUITextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	DeathUITextComponent->SetHorizontalAlignment(EHTA_Center);
	DeathUITextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	DeathUITextComponent->SetWorldSize(8.f);
	DeathUITextComponent->SetText(FText::GetEmpty());
	DeathUITextComponent->SetVisibility(false);
	DeathUITextComponent->SetHiddenInGame(true);
	DeathUITextComponent->SetOnlyOwnerSee(true);
	DeathUITextComponent->SetCastShadow(false);

	MaxHP = 100;
	CurrentHP = MaxHP;
	CharacterState = ERecCharacterState::Alive;
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
		InitialCameraBoomArmLength = CameraBoom->TargetArmLength;
		InitialCameraBoomSocketOffset = CameraBoom->SocketOffset;
	}

	ApplyRoleStats();
	UpdateHPText();
	UpdateRoleText();
	UpdateLowHPEffectState();
	ApplyCharacterState();
}

void ARecCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLowHPPulseEffect(DeltaTime);
	UpdateDeathCameraShake(DeltaTime);

	if (IsDead() && bDeathSequenceLocked && CameraBoom && !bCameraDetached)
	{
		CameraBoom->TargetArmLength = FMath::FInterpTo(
			CameraBoom->TargetArmLength,
			DeathCameraTargetArmLength,
			DeltaTime,
			DeathCameraInterpSpeed
		);
	}

	if (!IsDead() || !bCameraDetached || !bCanSpectate)
	{
		return;
	}

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
	UpdateLowHPEffectState();
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
		const float Mult = GetRoleSpeedMultiplier(RoleType);
		MoveComp->MaxWalkSpeed = BaseWalkSpeed * Mult;
	}
}

void ARecCharacter::SetCurrentHP(int32 NewHP)
{
	CurrentHP = FMath::Clamp(NewHP, 0, MaxHP);
	UpdateHPText();
	UpdateLowHPEffectState();

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
	if (IsDead()) return;

	if (!HasAuthority())
	{
		ServerApplyDamage(DamageAmount);
		return;
	}

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
	if (!HasAuthority())
	{
		ServerResetHP();
		return;
	}

	if (CharacterState == ERecCharacterState::Dead)
	{
		CurrentHP = MaxHP;
		UpdateHPText();
		UpdateLowHPEffectState();

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

	if (HasAuthority() && ActualDamage > 0.f && !IsDead())
	{
		ApplyDamage(FMath::RoundToInt(ActualDamage));
	}

	return ActualDamage;
}

void ARecCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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

	PlayerInputComponent->BindKey(EKeys::SpaceBar, IE_Pressed, this, &ARecCharacter::SpectateConfirmPressed);
	PlayerInputComponent->BindKey(EKeys::T, IE_Pressed, this, &ARecCharacter::SelfDamagePressed);
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
		if (bCanSpectate)
		{
			SpectateMove(Right, Forward);
		}
		return;
	}

	if (bDeathSequenceLocked)
	{
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
	if (bDeathSequenceLocked)
	{
		return;
	}

	if (IsDead() && !bCanSpectate)
	{
		return;
	}

	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ARecCharacter::DoJumpStart()
{
	if (IsDead()) return;
	if (bDeathSequenceLocked) return;
	Jump();
}

void ARecCharacter::DoJumpEnd()
{
	StopJumping();
}

void ARecCharacter::Jump()
{
	if (IsDead()) return;
	if (bDeathSequenceLocked) return;

	Super::Jump();
}

void ARecCharacter::SelfDamagePressed()
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

void ARecCharacter::UpdateLocalPostProcessEffects()
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

void ARecCharacter::UpdateLowHPEffectState()
{
	const bool bShouldBeLowHP =
		(CharacterState == ERecCharacterState::Alive) &&
		(CurrentHP > 0) &&
		(CurrentHP <= LowHPThreshold);

	bLowHPEffectActive = bShouldBeLowHP;
	UpdateLocalPostProcessEffects();
}

void ARecCharacter::UpdateLowHPPulseEffect(float DeltaTime)
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

void ARecCharacter::StartDeathCameraShake()
{
	if (!IsLocallyControlled() || !CameraBoom)
	{
		return;
	}

	bDeathCameraShaking = true;
	DeathShakeElapsed = 0.0f;
}

void ARecCharacter::UpdateDeathCameraShake(float DeltaTime)
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

void ARecCharacter::StopDeathCameraShake()
{
	bDeathCameraShaking = false;
	DeathShakeElapsed = 0.0f;

	if (CameraBoom)
	{
		CameraBoom->SocketOffset = InitialCameraBoomSocketOffset;
	}
}

void ARecCharacter::SetDeathVisualsEnabled(bool bEnabled)
{
	bDeathSequenceLocked = bEnabled;
	UpdateLocalPostProcessEffects();
}

void ARecCharacter::SetPlayerControlLocked(bool bLocked)
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

void ARecCharacter::UpdateDeathUI()
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

void ARecCharacter::ShowSpectatingUI()
{
	UpdateDeathUI();

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(SpectatingUIHideTimerHandle);
		GetWorldTimerManager().SetTimer(
			SpectatingUIHideTimerHandle,
			this,
			&ARecCharacter::HideDeathUI,
			SpectatingUITextDuration,
			false
		);
	}
}

void ARecCharacter::HideDeathUI()
{
	if (!DeathUITextComponent)
	{
		return;
	}

	DeathUITextComponent->SetText(FText::GetEmpty());
	DeathUITextComponent->SetVisibility(false);
	DeathUITextComponent->SetHiddenInGame(true);
}

void ARecCharacter::ShowCorpse()
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

	if (RoleTextComponent)
	{
		RoleTextComponent->SetVisibility(true);
		RoleTextComponent->SetHiddenInGame(false);
	}
}

void ARecCharacter::HideCorpse()
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

	if (RoleTextComponent)
	{
		RoleTextComponent->SetVisibility(false);
		RoleTextComponent->SetHiddenInGame(true);
	}
}

void ARecCharacter::EnterDeathWaitingState()
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
			&ARecCharacter::UnlockSpectateInput,
			SpectateInputUnlockDelay,
			false
		);
	}
}

void ARecCharacter::UnlockSpectateInput()
{
	if (!IsDead() || !bAwaitingSpectateInput)
	{
		return;
	}

	bSpectateInputUnlocked = true;
	UpdateDeathUI();
}

void ARecCharacter::EnterSpectateMode()
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

void ARecCharacter::ApplyDeadState()
{
	if (!IsDead()) return;

	ShowCorpse();

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
		MoveComp->DisableMovement();
	}

	StopJumping();

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComp->SetCollisionProfileName(TEXT("Ragdoll"));
		MeshComp->SetSimulatePhysics(true);
		MeshComp->WakeAllRigidBodies();
		MeshComp->bBlendPhysics = true;
	}

	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	StartDeathCameraShake();
	EnterDeathWaitingState();
}

void ARecCharacter::ApplyAliveState()
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
	UpdateRoleText();

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
	if (!CameraBoom || !bCanSpectate)
		return;

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

void ARecCharacter::SpectateUpPressed()
{
	if (!bCanSpectate) return;
	bSpectateUpHeld = true;
}

void ARecCharacter::SpectateUpReleased()
{
	bSpectateUpHeld = false;
}

void ARecCharacter::SpectateDownPressed()
{
	if (!bCanSpectate) return;
	bSpectateDownHeld = true;
}

void ARecCharacter::SpectateDownReleased()
{
	bSpectateDownHeld = false;
}

void ARecCharacter::SpectateMoveVertical(float Axis, float DeltaTime)
{
	if (!CameraBoom || !bCanSpectate)
		return;

	const FVector Delta = FVector::UpVector * Axis * SpectateVerticalSpeed * DeltaTime;
	CameraBoom->AddWorldOffset(Delta, false);
}

void ARecCharacter::ResurrectPressed()
{
	if (!IsLocallyControlled())
		return;

	ResetHP();
}

void ARecCharacter::CycleRolePressed()
{
	if (!IsLocallyControlled())
		return;

	if (IsDead() || bDeathSequenceLocked)
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

void ARecCharacter::SpectateConfirmPressed()
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