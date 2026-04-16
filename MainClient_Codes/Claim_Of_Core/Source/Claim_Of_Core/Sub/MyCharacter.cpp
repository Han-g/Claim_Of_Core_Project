#include "MyCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/GameModeBase.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "InputCoreTypes.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

#include "../Map/Building/UmbrellaItem.h"

#include "BaseItem.h"

AMyCharacter::AMyCharacter()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(200.f, 475.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 2000.f;
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
	RoleTextComponent->SetRelativeLocation(FVector(0.f, 0.f, 255.f));
	RoleTextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	RoleTextComponent->SetHorizontalAlignment(EHTA_Center);
	RoleTextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	RoleTextComponent->SetWorldSize(18.f);
	RoleTextComponent->SetText(FText::FromString(TEXT("Role: Guardian")));
	RoleTextComponent->SetVisibility(true);

	DeathUITextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("DeathUIText"));
	DeathUITextComponent->SetupAttachment(FollowCamera);
	DeathUITextComponent->SetRelativeLocation(FVector(160.f, 0.f, -25.f));
	DeathUITextComponent->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));
	DeathUITextComponent->SetHorizontalAlignment(EHTA_Center);
	DeathUITextComponent->SetVerticalAlignment(EVRTA_TextCenter);
	DeathUITextComponent->SetWorldSize(24.f);
	DeathUITextComponent->SetText(FText::GetEmpty());
	DeathUITextComponent->SetVisibility(false);
	DeathUITextComponent->SetHiddenInGame(true);
	DeathUITextComponent->SetOnlyOwnerSee(true);
	DeathUITextComponent->SetCastShadow(false);

	UmbrellaGuardBox = CreateDefaultSubobject<UBoxComponent>(TEXT("UmbrellaGuardBox"));
	UmbrellaGuardBox->SetupAttachment(RootComponent);
	UmbrellaGuardBox->SetBoxExtent(FVector(60.f, 60.f, 20.f));
	UmbrellaGuardBox->SetRelativeLocation(FVector(0.f, 0.f, 260.f));
	UmbrellaGuardBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UmbrellaGuardBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	UmbrellaGuardBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	UmbrellaGuardBox->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnUmbrellaGuardBoxBeginOverlap);

	MaxHP = 100;
	CurrentHP = MaxHP;
	CharacterState = ERecCharacterState::Alive;
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
		InitialCameraBoomArmLength = CameraBoom->TargetArmLength;
		InitialCameraBoomSocketOffset = CameraBoom->SocketOffset;
	}

	InitialActorScale3D = GetActorScale3D();
	BaseJumpMaxCount = JumpMaxCount;

	ApplyRoleStats();
	ApplyRoleVisual();
	ApplyRoleSkillState();

	UpdateHPText();
	UpdateRoleText();
	UpdateLowHPEffectState();
	ApplyCharacterState();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLowHPPulseEffect(DeltaTime);
	UpdateDeathCameraShake(DeltaTime);
	UpdateDeathCameraPullback(DeltaTime);

	if (!IsDead() || !bCameraDetached || !bCanSpectate)
	{
		return;
	}

	float Axis = 0.f;
	if (bSpectateUpHeld)   Axis += 1.f;
	if (bSpectateDownHeld) Axis -= 1.f;

	if (Axis != 0.f)
	{
		SpectateMoveVertical(Axis, DeltaTime);
	}
}

void AMyCharacter::OnRep_CurrentHP()
{
	UpdateHPText();
	UpdateLowHPEffectState();
}

void AMyCharacter::OnRep_CharacterState()
{
	ApplyCharacterState();
}

void AMyCharacter::OnRep_RoleType()
{
	ApplyRoleStats();
	ApplyRoleVisual();
	ApplyRoleSkillState();
	UpdateRoleText();
}

void AMyCharacter::OnRep_RoleSkillActive()
{
	ApplyRoleStats();
	ApplyRoleSkillState();
	UpdateRoleText();
}

void AMyCharacter::UpdateHPText()
{
	if (!HPTextComponent)
	{
		return;
	}

	const FString Str = FString::Printf(TEXT("HP: %d/%d"), CurrentHP, MaxHP);
	HPTextComponent->SetText(FText::FromString(Str));
}

void AMyCharacter::UpdateRoleText()
{
	if (!RoleTextComponent)
	{
		return;
	}

	FString Str = FString::Printf(TEXT("Role: %s"), *RoleTypeToString(RoleType));

	if (bRoleSkillActive)
	{
		Str += FString::Printf(TEXT("\nSkill: %s"), *GetCurrentRoleSkillName());
	}

	RoleTextComponent->SetText(FText::FromString(Str));
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

float AMyCharacter::GetRoleSkillSpeedMultiplier() const
{
	if (!bRoleSkillActive)
	{
		return 1.0f;
	}

	switch (RoleType)
	{
	case ERecRoleType::Striker:     return DashSpeedMultiplier;
	case ERecRoleType::Guardian:    return HardSpeedMultiplier;
	case ERecRoleType::Manipulator: return 1.0f;
	default:                        return 1.0f;
	}
}

float AMyCharacter::GetCurrentRoleSkillDuration() const
{
	switch (RoleType)
	{
	case ERecRoleType::Striker:     return DashDuration;
	case ERecRoleType::Guardian:    return HardDuration;
	case ERecRoleType::Manipulator: return DBJPDuration;
	default:                        return 0.f;
	}
}

float AMyCharacter::GetOutgoingDamageMultiplier() const
{
	if (bRoleSkillActive && RoleType == ERecRoleType::Striker)
	{
		return DashDamageMultiplier;
	}
	return 1.0f;
}

float AMyCharacter::GetIncomingDamageMultiplier() const
{
	if (bRoleSkillActive && RoleType == ERecRoleType::Guardian)
	{
		return HardDamageTakenMultiplier;
	}
	return 1.0f;
}

FString AMyCharacter::GetCurrentRoleSkillName() const
{
	switch (RoleType)
	{
	case ERecRoleType::Striker:     return TEXT("Dash");
	case ERecRoleType::Guardian:    return TEXT("Hard");
	case ERecRoleType::Manipulator: return TEXT("DBJP");
	default:                        return TEXT("None");
	}
}

bool AMyCharacter::IsStatusEffectImmune() const
{
	return bRoleSkillActive && RoleType == ERecRoleType::Manipulator;
}

bool AMyCharacter::CanReceiveStatusEffect(ERecStatusEffectType InStatusEffect) const
{
	if (!IsStatusEffectImmune())
	{
		return true;
	}

	switch (InStatusEffect)
	{
	case ERecStatusEffectType::Slow:
	case ERecStatusEffectType::Stun:
	case ERecStatusEffectType::Knockback:
		return false;
	default:
		return true;
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
		const float BaseRoleMult = GetRoleSpeedMultiplier(RoleType);
		const float SkillMult = GetRoleSkillSpeedMultiplier();
		MoveComp->MaxWalkSpeed = BaseWalkSpeed * BaseRoleMult * SkillMult;
	}
}

void AMyCharacter::ApplyRoleVisual()
{
	const FRoleVisualData& Data = GetVisualData(RoleType);

	USkeletalMeshComponent* SkelComp = GetMesh();
	if (!SkelComp)
	{
		return;
	}

	if (Data.Mesh)
	{
		SkelComp->SetSkeletalMesh(Data.Mesh);
	}

	if (Data.AnimBPClass)
	{
		SkelComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		SkelComp->SetAnimInstanceClass(Data.AnimBPClass);
	}
}

void AMyCharacter::ApplyRoleSkillState()
{
	SetActorScale3D(InitialActorScale3D);
	JumpMaxCount = BaseJumpMaxCount;

	if (!bRoleSkillActive)
	{
		return;
	}

	switch (RoleType)
	{
	case ERecRoleType::Striker:
		break;

	case ERecRoleType::Guardian:
		SetActorScale3D(InitialActorScale3D * HardScaleMultiplier);
		break;

	case ERecRoleType::Manipulator:
		JumpMaxCount = FMath::Max(BaseJumpMaxCount, 2);
		break;

	default:
		break;
	}
}

void AMyCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyCharacter, MaxHP);
	DOREPLIFETIME(AMyCharacter, CurrentHP);
	DOREPLIFETIME(AMyCharacter, CharacterState);
	DOREPLIFETIME(AMyCharacter, RoleType);
	DOREPLIFETIME(AMyCharacter, bRoleSkillActive);
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
	UpdateLowHPEffectState();

	if (HasAuthority() && !IsDead() && CurrentHP <= 0)
	{
		SetCharacterState(ERecCharacterState::Dead);
	}
}

void AMyCharacter::SetCharacterState(ERecCharacterState NewState)
{
	if (!HasAuthority())
	{
		return;
	}

	if (CharacterState == NewState)
	{
		return;
	}

	if (NewState == ERecCharacterState::Dead && bRoleSkillActive)
	{
		EndRoleSkill();
	}

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
	if (DamageAmount <= 0 || IsDead())
	{
		return;
	}

	if (!HasAuthority())
	{
		ServerApplyDamage(DamageAmount);
		return;
	}

	SetCurrentHP(CurrentHP - DamageAmount);
}

void AMyCharacter::Heal(int32 HealAmount)
{
	if (HealAmount <= 0)
	{
		return;
	}

	if (!HasAuthority())
	{
		ServerHeal(HealAmount);
		return;
	}

	SetCurrentHP(CurrentHP + HealAmount);
}

void AMyCharacter::ResetHP()
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

void AMyCharacter::ActivateRoleSkill()
{
	if (IsDead() || bDeathSequenceLocked)
	{
		return;
	}

	if (!HasAuthority())
	{
		ServerActivateRoleSkill();
		return;
	}

	if (bRoleSkillActive)
	{
		return;
	}

	bRoleSkillActive = true;

	ApplyRoleStats();
	ApplyRoleSkillState();
	UpdateRoleText();
	ForceNetUpdate();

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(RoleSkillTimerHandle);
		GetWorldTimerManager().SetTimer(
			RoleSkillTimerHandle,
			this,
			&AMyCharacter::EndRoleSkill,
			GetCurrentRoleSkillDuration(),
			false
		);
	}
}

void AMyCharacter::EndRoleSkill()
{
	if (!HasAuthority())
	{
		return;
	}

	if (!bRoleSkillActive)
	{
		return;
	}

	bRoleSkillActive = false;

	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(RoleSkillTimerHandle);
	}

	ApplyRoleStats();
	ApplyRoleSkillState();
	UpdateRoleText();
	ForceNetUpdate();
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
	if (bRoleSkillActive)
	{
		EndRoleSkill();
	}

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
	ApplyRoleSkillState();
	UpdateRoleText();
	ForceNetUpdate();
}

void AMyCharacter::ServerActivateRoleSkill_Implementation()
{
	ActivateRoleSkill();
}

float AMyCharacter::TakeDamage(
	float DamageAmount,
	FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (!HasAuthority() || ActualDamage <= 0.f || IsDead())
	{
		return ActualDamage;
	}

	float FinalDamage = ActualDamage;

	AMyCharacter* AttackerCharacter = nullptr;

	if (EventInstigator && EventInstigator->GetPawn())
	{
		AttackerCharacter = Cast<AMyCharacter>(EventInstigator->GetPawn());
	}

	if (!AttackerCharacter && DamageCauser && DamageCauser->GetOwner())
	{
		AttackerCharacter = Cast<AMyCharacter>(DamageCauser->GetOwner());
	}

	if (AttackerCharacter)
	{
		FinalDamage *= AttackerCharacter->GetOutgoingDamageMultiplier();
	}

	FinalDamage *= GetIncomingDamageMultiplier();

	const int32 FinalDamageInt = FMath::Max(1, FMath::RoundToInt(FinalDamage));
	ApplyDamage(FinalDamageInt);

	return FinalDamage;
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::DoJumpStart);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::DoJumpEnd);
		}

		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		}

		if (MouseLookAction)
		{
			EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		}

		if (LookAction)
		{
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		}

		if (AttackAction)
		{
			EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AMyCharacter::Attack);
		}

		if (KnockbackAction)
		{
			EnhancedInputComponent->BindAction(KnockbackAction, ETriggerEvent::Started, this, &AMyCharacter::KnockbackTest);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component!"), *GetNameSafe(this));
	}

	PlayerInputComponent->BindKey(EKeys::F, IE_Pressed, this, &AMyCharacter::EquipItem);
	PlayerInputComponent->BindKey(EKeys::G, IE_Pressed, this, &AMyCharacter::DropCurrentItem);

	PlayerInputComponent->BindKey(EKeys::Q, IE_Pressed, this, &AMyCharacter::SpectateUpPressed);
	PlayerInputComponent->BindKey(EKeys::Q, IE_Released, this, &AMyCharacter::SpectateUpReleased);

	PlayerInputComponent->BindKey(EKeys::E, IE_Pressed, this, &AMyCharacter::SpectateDownPressed);
	PlayerInputComponent->BindKey(EKeys::E, IE_Released, this, &AMyCharacter::SpectateDownReleased);

	PlayerInputComponent->BindKey(EKeys::R, IE_Pressed, this, &AMyCharacter::ResurrectPressed);
	PlayerInputComponent->BindKey(EKeys::P, IE_Pressed, this, &AMyCharacter::CycleRolePressed);
	PlayerInputComponent->BindKey(EKeys::C, IE_Pressed, this, &AMyCharacter::ActivateRoleSkillPressed);

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

void AMyCharacter::DoLook(float Yaw, float Pitch)
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

void AMyCharacter::DoJumpStart()
{
	if (IsDead() || bDeathSequenceLocked)
	{
		return;
	}

	Jump();
}

void AMyCharacter::DoJumpEnd()
{
	StopJumping();
}

void AMyCharacter::Jump()
{
	if (IsDead() || bDeathSequenceLocked)
	{
		return;
	}

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

void AMyCharacter::ActivateRoleSkillPressed()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	ActivateRoleSkill();
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
	if (!CameraBoom || !bDeathCameraShaking)
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

void AMyCharacter::UpdateDeathCameraPullback(float DeltaTime)
{
	if (!IsLocallyControlled() || !CameraBoom)
	{
		return;
	}

	if (!bDeathSequenceLocked || bCameraDetached)
	{
		return;
	}

	CameraBoom->TargetArmLength = FMath::FInterpTo(
		CameraBoom->TargetArmLength,
		DeathCameraTargetArmLength,
		DeltaTime,
		DeathCameraInterpSpeed
	);
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

	if (RoleTextComponent)
	{
		RoleTextComponent->SetVisibility(true);
		RoleTextComponent->SetHiddenInGame(false);
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

	if (RoleTextComponent)
	{
		RoleTextComponent->SetVisibility(false);
		RoleTextComponent->SetHiddenInGame(true);
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
	if (!IsDead())
	{
		return;
	}

	SetUmbrellaGuardActive(false);

	ShowCorpse();

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
		MoveComp->DisableMovement();
	}

	StopJumping();

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
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
	ApplyRoleSkillState();
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

void AMyCharacter::RespawnAtPlayerStart()
{
	if (!HasAuthority())
	{
		return;
	}

	AController* C = GetController();
	if (!C)
	{
		return;
	}

	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (!GM)
	{
		return;
	}

	AActor* StartSpot = GM->FindPlayerStart(C);
	if (!StartSpot)
	{
		return;
	}

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
	if (!CameraBoom || !bCanSpectate)
	{
		return;
	}

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

void AMyCharacter::SpectateUpPressed()
{
	if (!bCanSpectate)
	{
		return;
	}
	bSpectateUpHeld = true;
}

void AMyCharacter::SpectateUpReleased()
{
	bSpectateUpHeld = false;
}

void AMyCharacter::SpectateDownPressed()
{
	if (!bCanSpectate)
	{
		return;
	}
	bSpectateDownHeld = true;
}

void AMyCharacter::SpectateDownReleased()
{
	bSpectateDownHeld = false;
}

void AMyCharacter::SpectateMoveVertical(float Axis, float DeltaTime)
{
	if (!CameraBoom || !bCanSpectate)
	{
		return;
	}

	const FVector Delta = FVector::UpVector * Axis * SpectateVerticalSpeed * DeltaTime;
	CameraBoom->AddWorldOffset(Delta, false);
}

void AMyCharacter::ResurrectPressed()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	ResetHP();
}

void AMyCharacter::CycleRolePressed()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	if (IsDead() || bDeathSequenceLocked)
	{
		return;
	}

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

void AMyCharacter::Attack()
{
	if (IsDead() || bDeathSequenceLocked)
	{
		return;
	}

	if (CurrentItem)
	{
		CurrentItem->StartUse();
		return;
	}

	if (!IsValid(Controller))
	{
		return;
	}

	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	const FRoleVisualData& Data = GetVisualData(RoleType);

	if (!AnimInstance || !Data.AttackMontage)
	{
		return;
	}

	if (AnimInstance->Montage_IsPlaying(Data.AttackMontage))
	{
		return;
	}

	AnimInstance->Montage_Play(Data.AttackMontage);
}

void AMyCharacter::KnockbackTest()
{
	ApplyKnockback(this, 1200.f);
}

void AMyCharacter::ApplyKnockback(AActor* Attacker, float KnockbackStrength)
{
	if (!Attacker || IsDead())
	{
		return;
	}

	if (!CanReceiveStatusEffect(ERecStatusEffectType::Knockback))
	{
		return;
	}

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
	const FHitResult& SweepResult)
{
	if (AMyCharacter* Victim = Cast<AMyCharacter>(OtherActor))
	{
		Victim->ApplyKnockback(this, 1200.f);
	}
}

void AMyCharacter::SetOverlappingItem(ABaseItem* Item)
{
	OverlappingItem = Item;
}

void AMyCharacter::EquipItem()
{
	if (!OverlappingItem || CurrentItem)
	{
		return;
	}

	CurrentItem = OverlappingItem;
	CurrentItem->SetOwnerCharacter(this);
	CurrentItem->SetActorEnableCollision(false);

	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(CurrentItem->GetRootComponent()))
	{
		Prim->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Prim->SetSimulatePhysics(false);
	}

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
	if (!CurrentItem)
	{
		return;
	}
	SetUmbrellaGuardActive(false);

	CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentItem->SetOwnerCharacter(nullptr);
	CurrentItem->SetActorEnableCollision(true);

	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(CurrentItem->GetRootComponent()))
	{
		Prim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Prim->SetSimulatePhysics(true);
	}

	CurrentItem = nullptr;
}

void AMyCharacter::ClearCurrentItemReference(ABaseItem* Item)
{
	if (CurrentItem == Item)
	{
		CurrentItem = nullptr;
	}
}

void AMyCharacter::SetUmbrellaGuardActive(bool bActive)
{
	if (!UmbrellaGuardBox) return;

	UmbrellaGuardBox->SetCollisionEnabled(
		bActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision
	);
}

void AMyCharacter::OnUmbrellaGuardBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!OtherActor || !CurrentItem)
	{
		return;
	}

	if (!OtherActor->ActorHasTag(TEXT("FallingDebris")))
	{
		return;
	}

	AUmbrellaItem* Umbrella = Cast<AUmbrellaItem>(CurrentItem);
	if (!Umbrella)
	{
		return;
	}

	if (!Umbrella->IsOpened() || Umbrella->IsBroken())
	{
		return;
	}

	Umbrella->HandleGuardHit(OtherActor, 30.f);
}

void AMyCharacter::AnimNotify_AttackHit()
{
	if (CurrentItem)
	{
		CurrentItem->DoHit();
	}
}
