#include "MyCharacter.h"

#include "../Map/IceCave/IceFloorTile.h"

#include "UI/NetworkInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

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

#include "ClientNetworking.h"
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
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->GravityScale = 1.2f;
	GetCharacterMovement()->MaxWalkSpeed = 2000.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	BaseWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = true;
	CameraBoom->ProbeChannel = ECC_Camera;
	CameraBoom->ProbeSize = 8.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HandCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("HandCollision"));
	HandCollision->SetupAttachment(GetMesh(), TEXT("LeftHandSocket"));
	HandCollision->SetBoxExtent(FVector(50.f, 50.f, 50.f));
	HandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HandCollision->SetCollisionObjectType(ECC_WorldDynamic);
	HandCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	HandCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	HandCollision->SetGenerateOverlapEvents(true);
	HandCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacter::OnAttackOverlap);

	FrozenOverlayMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FrozenOverlayMesh"));
	FrozenOverlayMeshComponent->SetupAttachment(GetMesh());
	FrozenOverlayMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FrozenOverlayMeshComponent->SetGenerateOverlapEvents(false);
	FrozenOverlayMeshComponent->SetHiddenInGame(true);
	FrozenOverlayMeshComponent->SetVisibility(false, true);
	FrozenOverlayMeshComponent->SetCastShadow(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> FrozenOverlayMeshFinder(
		TEXT("/Game/Game/Map/Background/IceCave/Mesh/Crystal.Crystal")
	);

	if (FrozenOverlayMeshFinder.Succeeded())
	{
		FrozenOverlayMesh = FrozenOverlayMeshFinder.Object;
	}

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

	MaxHP = 100;
	CurrentHP = MaxHP;
	CharacterState = ERecCharacterState::Alive;
	RoleType = ERecRoleType::Guardian;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>();
	NetworkPlayerUID = NetworkInstance->GetPlayerUID();
	SetNetworkPlayerUID(NetworkPlayerUID);

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

	// Temporary Movement Threat 20fps transform send
	if (IsLocallyControlled() && !IsDead())
	{
		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		{
			CheckIceFloor();

			if (CameraBoom && CameraBoom->bDoCollisionTest)
			{
				static float CameraProbeLogTime = 0.f;
				CameraProbeLogTime += DeltaTime;

				if (CameraProbeLogTime >= 0.2f)
				{
					CameraProbeLogTime = 0.f;

					const FVector Start = CameraBoom->GetComponentLocation();
					const FRotator BoomRot = CameraBoom->GetTargetRotation();
					const FVector End = Start - BoomRot.Vector() * CameraBoom->TargetArmLength;

					FHitResult Hit;
					FCollisionQueryParams Params(SCENE_QUERY_STAT(CameraBoomDebug), false, this);
					Params.AddIgnoredActor(this);

					const bool bHit = GetWorld()->SweepSingleByChannel(
						Hit,
						Start,
						End,
						FQuat::Identity,
						CameraBoom->ProbeChannel,
						FCollisionShape::MakeSphere(CameraBoom->ProbeSize),
						Params
					);

					if (bHit)
					{
						UPrimitiveComponent* HitComp = Hit.GetComponent();

						/*UE_LOG(LogTemp, Warning,
							TEXT("[CameraProbeHit] Actor=%s Comp=%s ChannelResponse=%d Location=%s"),
							*GetNameSafe(Hit.GetActor()),
							*GetNameSafe(HitComp),
							HitComp ? static_cast<int32>(HitComp->GetCollisionResponseToChannel(ECC_Camera)) : -1,
							*Hit.ImpactPoint.ToString()
						);*/
					}
				}
			}

			if (MoveComp->MovementMode != EMovementMode::MOVE_None)
			{
				if (IsLocallyControlled() && bHasLocalCorrectionTarget && !IsDead())
				{
					const FVector CurrentLocation = GetActorLocation();

					FVector NewLocation = CurrentLocation;
					NewLocation.X = FMath::FInterpTo(CurrentLocation.X, LocalCorrectionTargetLocation.X, DeltaTime, LocalCorrectionInterpSpeed);
					NewLocation.Y = FMath::FInterpTo(CurrentLocation.Y, LocalCorrectionTargetLocation.Y, DeltaTime, LocalCorrectionInterpSpeed);

					if (!MoveComp->IsFalling())
					{
						NewLocation.Z = FMath::FInterpTo(CurrentLocation.Z, LocalCorrectionTargetLocation.Z, DeltaTime, 4.f);
					}

					SetActorLocation(NewLocation, false, nullptr, ETeleportType::None);

					const float XYError = FVector::Dist2D(NewLocation, LocalCorrectionTargetLocation);
					const float ZError = FMath::Abs(NewLocation.Z - LocalCorrectionTargetLocation.Z);

					if (XYError <= LocalCorrectionIgnoreDistance && (MoveComp->IsFalling() || ZError <= 30.f))
					{
						bHasLocalCorrectionTarget = false;
					}
				}

				MoveSyncAccumulator += DeltaTime;

				if (MoveSyncAccumulator >= 0.05f)
				{
					MoveSyncAccumulator = 0.f;

					if (UNetworkInstance* NetInst = GetGameInstance<UNetworkInstance>())
					{
						FMovePacket Packet{};

						const FVector Pos = GetActorLocation();
						const float BodyYaw = GetActorRotation().Yaw;

						float CameraDir = BodyYaw;
						if (AController* C = GetController())
						{
							CameraDir = C->GetControlRotation().Yaw;
						}

						Packet.X = Pos.X;
						Packet.Y = Pos.Y;
						Packet.Z = Pos.Z;

						// Character facing direction for remote visual rotation
						Packet.Yaw = BodyYaw;

						// Controller/camera yaw used by server to reconstruct movement
						Packet.cameraDir = CameraDir;

						Packet.VelocityX = CachedMoveRight;
						Packet.VelocityY = CachedMoveForward;

						NetInst->SendMoveInputToServer(Packet);
					}
				}
			}
		}
	}

	if (!IsLocallyControlled() && bHasNetworkTransform && CharacterState == ERecCharacterState::Alive)
	{
		const float RenderTime = GetWorld()->GetTimeSeconds() - RemoteInterpolationDelay;

		while (RemoteSnapshots.Num() >= 2 && RemoteSnapshots[1].Time <= RenderTime)
		{
			RemoteSnapshots.RemoveAt(0);
		}

		if (RemoteSnapshots.Num() >= 2)
		{
			const FRemoteSnapshot& A = RemoteSnapshots[0];
			const FRemoteSnapshot& B = RemoteSnapshots[1];

			const float Alpha = FMath::Clamp(
				(RenderTime - A.Time) / FMath::Max(B.Time - A.Time, KINDA_SMALL_NUMBER),
				0.f,
				1.f
			);

			const FVector NewLocation = FMath::Lerp(A.Location, B.Location, Alpha);
			const FRotator NewRotation = FMath::Lerp(A.Rotation, B.Rotation, Alpha);

			SetActorLocationAndRotation(
				NewLocation,
				NewRotation,
				false,
				nullptr,
				ETeleportType::None
			);
		}

		/*NetworkBlendElapsed += DeltaTime;

		const float Alpha =
			(NetworkBlendDuration > KINDA_SMALL_NUMBER)
			? FMath::Clamp(NetworkBlendElapsed / NetworkBlendDuration, 0.f, 1.f)
			: 1.f;

		const FVector NewLocation = FMath::Lerp(
			NetworkBlendStartLocation,
			NetworkBlendTargetLocation,
			Alpha
		);

		const FRotator NewRotation = FMath::RInterpTo(
			GetActorRotation(),
			NetworkBlendTargetRotation,
			DeltaTime,
			RemoteInterpSpeed
		);*/
	}

	UpdateLowHPPulseEffect(DeltaTime);
	UpdateDeathCameraShake(DeltaTime);
	UpdateDeathCameraPullback(DeltaTime);

	if (!IsDead() || !bCameraDetached || !bCanSpectate)
	{
		return;
	}

	float Axis = 0.f;
	if (bSpectateUpHeld) { Axis += 1.f; }
	if (bSpectateDownHeld) { Axis -= 1.f; }

	if (Axis != 0.f)
	{
		SpectateMoveVertical(Axis, DeltaTime);
	}
}

void AMyCharacter::CheckIceFloor()
{
	if (!GetWorld() || IsDead())
	{
		SetIceMovement(false);
		return;
	}

	FHitResult Hit;

	const FVector Start = GetActorLocation();
	const float TraceDistance =
		GetCapsuleComponent()
		? GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + 150.f
		: 650.f;

	const FVector End = Start - FVector(0.f, 0.f, TraceDistance);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(CheckIceFloor), false, this);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Start,
		End,
		ECC_WorldStatic,
		Params
	);

	if (!bHit)
	{
		SetIceMovement(false);
		return;
	}

	AIceFloorTile* IceFloorTile = Cast<AIceFloorTile>(Hit.GetActor());

	if (!IceFloorTile && Hit.GetComponent())
	{
		IceFloorTile = Cast<AIceFloorTile>(Hit.GetComponent()->GetOwner());
	}

	if (!IceFloorTile)
	{
		SetIceMovement(false);
		return;
	}

	// Ice Floor Local Distruction 
	//IceFloorTile->NotifyPlayerStandingOnPiece(this, Hit.GetComponent());


	// Ice Floor Server Distruction 
	SetIceMovement(true);
	const int32 PieceIndex = IceFloorTile->GetPieceIndexFromComponent(Hit.GetComponent());
	if (PieceIndex >= 0)
{
    if (UNetworkInstance* NetInst = GetGameInstance<UNetworkInstance>())
    {
        NetInst->RequestIceFloorStanding(0, PieceIndex);
    }
}
}

void AMyCharacter::SetIceMovement(bool bNew)
{
	if (bOnIce == bNew)
	{
		return;
	}

	bOnIce = bNew;

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		if (bOnIce)
		{
			MoveComp->GroundFriction = 0.1f;
			MoveComp->BrakingFrictionFactor = 0.2f;
		}
		else
		{
			MoveComp->GroundFriction = 8.f;
			MoveComp->BrakingFrictionFactor = 2.f;
		}
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

float AMyCharacter::GetSkillCoolTime() const
{
	return CurrentCoolTime;
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
	case ERecStatusEffectType::Freeze:
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
		if (bFrozen)
		{
			MoveComp->StopMovementImmediately();
			MoveComp->MaxWalkSpeed = 0.f;
		}
		else
		{
			const float BaseRoleMult = GetRoleSpeedMultiplier(RoleType);
			const float SkillMult = GetRoleSkillSpeedMultiplier();
			MoveComp->MaxWalkSpeed = BaseWalkSpeed * BaseRoleMult * SkillMult;
		}
	}

	switch (RoleType)
	{
	case ERecRoleType::Striker:
		MaxHP = 100;
		AttackDamage = 30;
		KnockbackCoefficient = 1.10f;
		break;

	case ERecRoleType::Guardian:
		MaxHP = 200;
		AttackDamage = 15;
		KnockbackCoefficient = 0.80f;
		break;

	case ERecRoleType::Manipulator:
		MaxHP = 120;
		AttackDamage = 20;
		KnockbackCoefficient = 1.30f;
		break;

	default:
		AttackDamage = 20;
		KnockbackCoefficient = 1.0f;
		break;
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

	switch (RoleType)
	{
	case ERecRoleType::Striker:
		GetMesh()->SetRelativeScale3D(FVector(1.f));
		HandCollision->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("LeftHandSocket")
		);
		break;

	case ERecRoleType::Guardian:
		GetMesh()->SetRelativeScale3D(FVector(1.f));
		HandCollision->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("RightHandSocket")
		);
		break;

	case ERecRoleType::Manipulator:
		GetMesh()->SetRelativeScale3D(FVector(0.6f));
		HandCollision->AttachToComponent(
			GetMesh(),
			FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			TEXT("RightHandSocket")
		);
		break;

	default:
		break;
	}

	RefreshCurrentItemAttachOffset();
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

	if (UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>())
	{
		const int32 LocalUID = NetworkInstance->GetPlayerUID();
		SetNetworkPlayerUID(LocalUID);

		UE_LOG(LogTemp, Display,
			TEXT("[AttackUID] Local character UID set. Character=%s UID=%d"),
			*GetName(),
			LocalUID);
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UE_LOG(LogTemp, Display, TEXT("[InputTrace] Character SetupPlayerInputComponent"));
		if (JumpAction)
		{
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::DoJumpStart);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::DoJumpEnd);
		}

		if (MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMyCharacter::StopMove);
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Canceled, this, &AMyCharacter::StopMove);
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
			UE_LOG(LogTemp, Display, TEXT("[InputTrace] AttackAction is %s"), *GetNameSafe(AttackAction));
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

	// Test Key Bind
	//PlayerInputComponent->BindKey(EKeys::Subtract, IE_Pressed, this, &AMyCharacter::TestFunc);

	// Key Binding
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

void AMyCharacter::TestFunc()
{
	// Prevent Duplicate tansfers Not local player to Other client
	// Prevent Send Test Packet while Dead state or Locked Input
	if (!IsLocallyControlled() || bDeathSequenceLocked) { return; }

	if (UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>()) {
		UE_LOG(LogTemp, Display, TEXT("[ClientTest] TestFunc called. Sending attack test packet."));
		NetworkInstance->StartClientOnlyTestFlow();
	}

	else { UE_LOG(LogTemp, Warning, TEXT("[ClientTest] NetworkInstance is null.")); }
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	if (IsDead() || bDeathSequenceLocked || bFrozen)
	{
		CachedMoveRight = 0.f;
		CachedMoveForward = 0.f;

		if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
		{
			MoveComp->StopMovementImmediately();
			MoveComp->Velocity = FVector::ZeroVector;
		}

		return;
	}

	const FVector2D MovementVector = Value.Get<FVector2D>();
	const float Right = MovementVector.X;
	const float Forward = MovementVector.Y;

	CachedMoveRight = Right;
	CachedMoveForward = Forward;

	DoMove(Right, Forward);

	/*UNetworkInstance* NetInst = GetGameInstance<UNetworkInstance>();
	if (!NetInst) return;

	FMovePacket Packet;
	const FVector Pos = GetActorLocation();

	Packet.X = Pos.X;
	Packet.Y = Pos.Y;
	Packet.Z = Pos.Z;
	Packet.Yaw = GetControlRotation().Yaw;

	Packet.VelocityX = Right;
	Packet.VelocityY = Forward;

	NetInst->SendMoveInputToServer(Packet);*/
}

void AMyCharacter::StopMove(const FInputActionValue& Value)
{
	CachedMoveRight = 0.f;
	CachedMoveForward = 0.f;
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

	if (bDeathSequenceLocked || bFrozen)
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

	if (IsDead() || bCanSpectate)
	{
		return;
	}

	if (GetController() != nullptr)
	{
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void AMyCharacter::UpdateFrozenOverlay()
{
	if (!FrozenOverlayMeshComponent)
	{
		return;
	}

	if (FrozenOverlayMesh)
	{
		FrozenOverlayMeshComponent->SetStaticMesh(FrozenOverlayMesh);
	}

	if (FrozenOverlayMaterial)
	{
		FrozenOverlayMeshComponent->SetMaterial(0, FrozenOverlayMaterial);
	}

	FrozenOverlayMeshComponent->SetRelativeLocation(FrozenOverlayRelativeLocation);
	FrozenOverlayMeshComponent->SetRelativeScale3D(FrozenOverlayRelativeScale);
	FrozenOverlayMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FrozenOverlayMeshComponent->SetHiddenInGame(!bFrozen);
	FrozenOverlayMeshComponent->SetVisibility(bFrozen, true);
}

void AMyCharacter::ApplyFreeze()
{
	if (IsDead() || !CanReceiveStatusEffect(ERecStatusEffectType::Freeze))
	{
		return;
	}

	bFrozen = true;
	CachedMoveRight = 0.f;
	CachedMoveForward = 0.f;

	StopJumping();

	EndAttack();
	GetWorldTimerManager().ClearTimer(AttackTimer);

	if (UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr)
	{
		AnimInstance->Montage_Stop(0.05f);
	}

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
		MoveComp->MaxWalkSpeed = 0.f;
		MoveComp->Velocity = FVector::ZeroVector;
	}

	UpdateFrozenOverlay();
}

void AMyCharacter::EndFreeze()
{
	if (!bFrozen)
	{
		return;
	}

	bFrozen = false;
	UpdateFrozenOverlay();

	ApplyRoleStats();
}

void AMyCharacter::DoJumpStart()
{
	if (IsDead() || bDeathSequenceLocked)
	{
		return;
	}

	if (CanJump())
	{
		if (UNetworkInstance* NetInst = GetGameInstance<UNetworkInstance>())
		{
			NetInst->RequestJumpInput();
		}
	}

	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[JumpCheck][Client] JumpZ=%.1f GravityScale=%.2f AirControl=%.2f MaxWalkSpeed=%.1f"),
			MoveComp->JumpZVelocity,
			MoveComp->GravityScale,
			MoveComp->AirControl,
			MoveComp->MaxWalkSpeed);
	}

	Jump();
}

void AMyCharacter::DoJumpEnd()
{
	if (bFrozen) { return; }
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
	HideCorpse();
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

	/*if (CurrentItem)
	{
		CurrentItem->StartUse();
		return;
	}*/

	if (!IsLocallyControlled())
	{
		return;
	}

	if (UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>())
	{
		//NetworkInstance->SendGameplayTestPacket(PKT_C2S_ATTACK_KEYINPUT);
		const int32 AttackType = CurrentItem ? 1 : 0;
		NetworkInstance->RequestAttackInput(0);
	}
	/*if (!IsValid(Controller))
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

	if (IsLocallyControlled())
	{
		if (UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>())
		{
			NetworkInstance->SendGameplayTestPacket(PKT_C2S_ATTACK_KEYINPUT);
		}
	}

	AnimInstance->Montage_Play(Data.AttackMontage);*/
}

void AMyCharacter::EndAttack()
{
	if (HandCollision)
	{
		HandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	HitActors.Empty();
}

void AMyCharacter::PlayAttackMontageFromServer(int32 AttackType, uint32 AttackSeq)
{
	if (IsDead() || bDeathSequenceLocked) { 
		//UE_LOG(LogTemp, Display, TEXT("Dead State"));
		return; 
	}

	UAnimInstance* AnimInstance = GetMesh() ? GetMesh()->GetAnimInstance() : nullptr;
	const FRoleVisualData& Data = GetVisualData(RoleType);

	UAnimMontage* AttackMontage = Data.AttackMontage;
	if (CurrentItem)
	{
		if (UAnimMontage* ItemMontage = CurrentItem->GetAttackMontageByRole(RoleType))
		{
			AttackMontage = ItemMontage;
		}
	}

	if (!AnimInstance || !AttackMontage)
	{
		//UE_LOG(LogTemp, Display, TEXT("Not Connect with Montage"));
		return;
	}

	if (AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		//UE_LOG(LogTemp, Display, TEXT("Not is playing"));
		return;
	}


	CurrentAttackType = AttackType;
	CurrentAttackSeq = AttackSeq;
	HitActors.Empty();

	//HandCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	const float PlayedLength = AnimInstance->Montage_Play(AttackMontage);
	if (PlayedLength <= 0.f)
	{
		CurrentAttackSeq = 0;
		return;
	}

	GetWorldTimerManager().SetTimer(
		AttackTimer,
		this,
		&AMyCharacter::EndAttack,
		1.8f,
		false
	);
}

void AMyCharacter::SetRoleFromNetwork(int32 InRoleType)
{
	if (InRoleType < 0 || InRoleType > 2) { return; }

	const ERecRoleType NewRoleType = static_cast<ERecRoleType>(InRoleType);
	if (RoleType == NewRoleType) { return; }

	RoleType = static_cast<ERecRoleType>(InRoleType);
	ApplyRoleStats();
	ApplyRoleVisual();
	ApplyRoleSkillState();
	UpdateRoleText();
}

void AMyCharacter::SetHPFromNetwork(int32 InHP)
{
	SetCurrentHP(InHP);
}

void AMyCharacter::SetStateFromNetwork(int32 InState)
{
	if (InState < 0 || InState > 1) { return; }

	const ERecCharacterState NewState = static_cast<ERecCharacterState>(InState);
	if (CharacterState == NewState) {
		return;
	}

	if (NewState == ERecCharacterState::Dead && bRoleSkillActive) {
		EndRoleSkill();
	}

	CharacterState = NewState;
	ApplyCharacterState();
}

void AMyCharacter::ApplyTransformFromNetwork(float X, float Y, float Z, float Yaw)
{
	const FVector NewLocation(X, Y, Z);
	const FRotator NewRotation(0.f, Yaw, 0.f);
	
	if (IsLocallyControlled())
	{
		SetActorLocationAndRotation(
			NewLocation,
			NewRotation,
			false,
			nullptr,
			ETeleportType::TeleportPhysics
		);

		if (AController* C = GetController())
		{
			C->SetControlRotation(NewRotation);
		}
		return;
	}

	if (CharacterState == ERecCharacterState::Dead)
	{
		SetActorLocationAndRotation(
			NewLocation,
			NewRotation,
			false,
			nullptr,
			ETeleportType::TeleportPhysics
		);
		return;
	}

	const float Now = GetWorld()->GetTimeSeconds();

	RemoteSnapshots.Add({ NewLocation, NewRotation, Now });

	while (RemoteSnapshots.Num() > MaxRemoteSnapshotCount)
	{
		RemoteSnapshots.RemoveAt(0);
	}

	bHasNetworkTransform = true;

	/*float MeasuredInterval = 0.033f;
	if (LastNetworkSnapshotTime >= 0.f)
	{
		MeasuredInterval = Now - LastNetworkSnapshotTime;
	}
	LastNetworkSnapshotTime = Now;

	NetworkBlendDuration = FMath::Clamp(
		MeasuredInterval,
		MinNetworkBlendDuration,
		MaxNetworkBlendDuration
	);

	if (!bHasNetworkTransform)
	{
		bHasNetworkTransform = true;

		SetActorLocationAndRotation(NewLocation, NewRotation, false, nullptr, ETeleportType::TeleportPhysics);

		NetworkBlendStartLocation = NewLocation;
		NetworkBlendTargetLocation = NewLocation;
		NetworkBlendStartRotation = NewRotation;
		NetworkBlendTargetRotation = NewRotation;
		NetworkBlendElapsed = NetworkBlendDuration;

		return;
	}

	const float Distance = FVector::Dist(GetActorLocation(), NewLocation);
	if (Distance >= RemoteSnapDistance)
	{
		SetActorLocationAndRotation(NewLocation, NewRotation, false, nullptr, ETeleportType::TeleportPhysics);

		NetworkBlendStartLocation = NewLocation;
		NetworkBlendTargetLocation = NewLocation;
		NetworkBlendStartRotation = NewRotation;
		NetworkBlendTargetRotation = NewRotation;
		NetworkBlendElapsed = NetworkBlendDuration;

		return;
	}

	NetworkBlendStartLocation = GetActorLocation();
	NetworkBlendTargetLocation = NewLocation;
	NetworkBlendStartRotation = GetActorRotation();
	NetworkBlendTargetRotation = NewRotation;
	NetworkBlendElapsed = 0.f;
	//--------------------------------------------------------------
	TargetNetworkLocation = NewLocation;
	TargetNetworkRotation = NewRotation;

	if (!bHasNetworkTransform)
	{
		bHasNetworkTransform = true;

		SetActorLocationAndRotation(
			NewLocation,
			NewRotation,
			false,
			nullptr,
			ETeleportType::TeleportPhysics
		);
		return;
	}

	const float Distance = FVector::Dist(GetActorLocation(), NewLocation);
	if (Distance >= RemoteSnapDistance)
	{
		SetActorLocationAndRotation(
			NewLocation,
			NewRotation,
			false,
			nullptr,
			ETeleportType::TeleportPhysics
		);
	}*/
}

void AMyCharacter::ApplyLocalServerCorrection(float X, float Y, float Z, float Yaw)
{
	if (!IsLocallyControlled()) { return; }

	const FVector Current = GetActorLocation();
	FVector ServerLocation(X, Y, Z);

	ServerLocation.Z = Current.Z;
	const float XYError = FVector::Dist2D(Current, ServerLocation);
	const float ZError = FMath::Abs(Current.Z - ServerLocation.Z);

	UCharacterMovementComponent* MoveComp = GetCharacterMovement();
	const bool bIsFalling = MoveComp && MoveComp->IsFalling();

	if (XYError <= LocalCorrectionIgnoreDistance && ZError <= 30.f)
	{
		bHasLocalCorrectionTarget = false;
		return;
	}

	if (XYError >= LocalCorrectionSnapDistance || ZError >= 400.f || IsDead())
	{
		SetActorLocation(ServerLocation, false, nullptr, ETeleportType::TeleportPhysics);
		bHasLocalCorrectionTarget = false;
		return;
	}

	LocalCorrectionTargetLocation = ServerLocation;


	if (bIsFalling)
	{
		LocalCorrectionTargetLocation.Z = Current.Z;
	}

	bHasLocalCorrectionTarget = true;
}

void AMyCharacter::LockUntilInitialSnapshot()
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->StopMovementImmediately();
		MoveComp->DisableMovement();
		MoveComp->GravityScale = 0.f;
	}

	if (AController* C = GetController())
	{
		if (APlayerController* PC = Cast<APlayerController>(C))
		{
			PC->SetIgnoreMoveInput(true);
			PC->SetIgnoreLookInput(true);
		}
	}
}

void AMyCharacter::UnlockAfterInitialSnapshot()
{
	if (UCharacterMovementComponent* MoveComp = GetCharacterMovement())
	{
		MoveComp->GravityScale = 1.f;
		MoveComp->SetMovementMode(EMovementMode::MOVE_Walking);
		MoveComp->StopMovementImmediately();
	}

	if (AController* C = GetController())
	{
		if (APlayerController* PC = Cast<APlayerController>(C))
		{
			PC->SetIgnoreMoveInput(false);
			PC->SetIgnoreLookInput(false);
		}
	}
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

void AMyCharacter::ApplyHitEvent(AActor* Attacker)
{
	AMyCharacter* Player = Cast<AMyCharacter>(Attacker);
	if (!Player) return;

	if (!Player || IsDead())
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

	FVector LaunchVel;

	if (!Player->CurrentItem)
	{
		LaunchVel = Dir * Player->KnockbackCoefficient * Player->BaseAttackKnockbackPower;
		ApplyDamage(Player->AttackDamage);
	}
	else
	{
		LaunchVel = Dir * Player->KnockbackCoefficient * Player->CurrentItem->KnockbackPower;
		ApplyDamage(Player->CurrentItem->Damage);
	}

	LaunchVel.Z = 0.f;
	LaunchCharacter(LaunchVel, true, true);
	//AMyCharacter* Player = Cast<AMyCharacter>(Attacker);
	//if (!Player) return;

	//if (!Player || IsDead())
	//{
	//	return;
	//}

	//if (!CanReceiveStatusEffect(ERecStatusEffectType::Knockback))
	//{
	//	return;
	//}

	//FVector Dir = GetActorLocation() - Player->GetActorLocation(); //-GetActorForwardVector();
	//Dir.Z = 0.f;
	//Dir = Dir.GetSafeNormal();

	//if (Dir.IsNearlyZero())
	//{
	//	Dir = Player->GetActorForwardVector();
	//	Dir.Z = 0.f;
	//	Dir = Dir.GetSafeNormal();
	//}

	//FVector LaunchVel;
	//int32 DamageAmount = 0;

	//if (!Player->CurrentItem)
	//{
	//	LaunchVel = Dir * Player->KnockbackCoefficient * Player->BaseAttackKnockbackPower;
	//	DamageAmount = FMath::RoundToInt(Player->AttackDamage);
	//}
	//else
	//{
	//	LaunchVel = Dir * KnockbackCoefficient * Player->CurrentItem->KnockbackPower;
	//	DamageAmount = FMath::RoundToInt(Player->CurrentItem->Damage);
	//}

	//UE_LOG(LogTemp, Display,
	//	TEXT("[ATK_TRACE][3_HitEvent] Victim=%s UID=%d Attacker=%s UID=%d Damage=%d VictimHPBefore=%d Launch=(%.1f, %.1f, %.1f)"),
	//	*GetName(),
	//	GetNetworkPlayerUID(),
	//	*Player->GetName(),
	//	Player->GetNetworkPlayerUID(),
	//	DamageAmount,
	//	CurrentHP,
	//	LaunchVel.X, LaunchVel.Y, LaunchVel.Z);

	//ApplyDamage(DamageAmount);
	//LaunchVel.Z = 0.f;

	//LaunchCharacter(LaunchVel, true, true);
}

void AMyCharacter::OnAttackOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AMyCharacter* Victim = Cast<AMyCharacter>(OtherActor);
	ReportAttackHitToServer(Victim);

	/*UE_LOG(LogTemp, Warning, TEXT("[ATK_OVERLAP_ENTRY] Local=%d Seq=%u Other=%s"),
		IsLocallyControlled(),
		CurrentAttackSeq,
		*GetNameSafe(OtherActor));

	AMyCharacter* Victim = Cast<AMyCharacter>(OtherActor);

	if (!Victim)
	{
		return;
	}

	if (Victim == this || Victim->GetNetworkPlayerUID() == GetNetworkPlayerUID())
	{
		UE_LOG(LogTemp, Warning, TEXT("[ATK_SKIP_SELF] UID=%d Actor=%s"),
			GetNetworkPlayerUID(),
			*GetNameSafe(Victim));
		return;
	}

	if (HitActors.Contains(Victim))
	{
		UE_LOG(LogTemp, Error, TEXT("[Attack Trace] Check"));
		return;
	}

	UE_LOG(LogTemp, Display,
		TEXT("[ATK_TRACE][2_Overlap] Attacker=%s UID=%d Victim=%s UID=%d"),
		*GetName(),
		GetNetworkPlayerUID(),
		*Victim->GetName(),
		Victim->GetNetworkPlayerUID());

	HitActors.Add(Victim);
	//Victim->ApplyHitEvent(this);

	if (UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>())
	{
		NetworkInstance->RequestAttackHitReport(
			CurrentAttackSeq,
			Victim->GetNetworkPlayerUID(),
			CurrentAttackType
		);
	}*/
}

void AMyCharacter::SetOverlappingItem(ABaseItem* Item)
{
	OverlappingItem = Item;
}

void AMyCharacter::EquipItem()
{
	if (!OverlappingItem || CurrentItem) { return; }
	if (!IsLocallyControlled()) { return; }

	if (UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>())
	{
		UE_LOG(LogTemp, Warning, TEXT("[PickupTry] Item=%s ItemID=%d"),
			*GetNameSafe(OverlappingItem),
			OverlappingItem ? OverlappingItem->GetItemID() : -999);
		NetworkInstance->RequestItemPickup(OverlappingItem->GetItemID());
	}
	/*CurrentItem = OverlappingItem;
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
			TEXT("LeftHandSocket")
		);
	}*/
}

void AMyCharacter::DropCurrentItem()
{
	if (!CurrentItem) { return; }
	if (!IsLocallyControlled()) { return; }

	if (UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>())
	{
		NetworkInstance->RequestItemDrop(CurrentItem->GetItemID());
	}
	/*CurrentItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	CurrentItem->SetOwnerCharacter(nullptr);
	CurrentItem->SetActorEnableCollision(true);

	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(CurrentItem->GetRootComponent()))
	{
		Prim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Prim->SetSimulatePhysics(true);
	}

	CurrentItem = nullptr;*/
}

void AMyCharacter::RefreshCurrentItemAttachOffset()
{
	if (!CurrentItem)
	{
		return;
	}

	const FTransform AttachOffset = CurrentItem->GetAttachOffsetByRole(RoleType);
	CurrentItem->SetActorRelativeLocation(AttachOffset.GetLocation());
	CurrentItem->SetActorRelativeRotation(AttachOffset.GetRotation());
	CurrentItem->SetActorRelativeScale3D(CurrentItemAttachBaseScale * AttachOffset.GetScale3D());
}

void AMyCharacter::ApplyEquipItemVisual(ABaseItem* Item)
{
	if (!Item) { return; }

	if (CurrentItem == Item)
	{
		RefreshCurrentItemAttachOffset();
		return;
	}
	UE_LOG(LogTemp, Warning,
		TEXT("[EquipVisual] Character=%s UID=%d CurrentItem=%s ItemID=%d PoseType=%d"),
		*GetNameSafe(this),
		GetNetworkPlayerUID(),
		*GetNameSafe(CurrentItem),
		CurrentItem ? CurrentItem->GetItemID() : -1,
		CurrentItem ? static_cast<int32>(CurrentItem->ItemAnimPoseType) : -1);

	if (CurrentItem && CurrentItem != Item) { return; }

	CurrentItem = Item;
	CurrentItemAttachBaseScale = CurrentItem->GetActorScale3D();

	if (OverlappingItem == Item)
	{
		OverlappingItem = nullptr;
	}

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
		RefreshCurrentItemAttachOffset();
	}
}

void AMyCharacter::ApplyDropItemVisual(ABaseItem* Item, const FVector& DropLocation)
{
	if (!Item) { return; }

	const bool bWasCurrentItem = (CurrentItem == Item);
	const FVector DropItemBaseScale = CurrentItemAttachBaseScale;

	if (bWasCurrentItem)
	{
		CurrentItemAttachBaseScale = FVector::OneVector;
		CurrentItem = nullptr;
	}

	if (OverlappingItem == Item) { OverlappingItem = nullptr; }

	Item->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	if (bWasCurrentItem)
	{
		Item->SetActorScale3D(DropItemBaseScale);
	}
	Item->SetOwnerCharacter(nullptr);
	Item->SetActorLocation(DropLocation);
	Item->SetActorEnableCollision(true);

	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Item->GetRootComponent()))
	{
		Prim->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Prim->SetSimulatePhysics(true);
	}
}

void AMyCharacter::AnimNotify_AttackHit()
{
	if (!IsLocallyControlled())
	{
		return;
	}

	if (CurrentItem)
	{
		CurrentItem->DoHit();
		return;
	}

	StartAttackHitWindow(1.2f);
}

void AMyCharacter::StartAttackHitWindow(float Duration)
{
	HitActors.Empty();

	if (HandCollision)
	{
		HandCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}

	GetWorldTimerManager().ClearTimer(AttackTimer);
	GetWorldTimerManager().SetTimer(
		AttackTimer,
		this,
		&AMyCharacter::EndAttack,
		Duration,
		false
	);
}

void AMyCharacter::ReportAttackHitToServer(AMyCharacter* Victim)
{
	if (!IsLocallyControlled()) { UE_LOG(LogTemp, Warning, TEXT("[HIT_REPORT_SKIP] Not local")); return; }
	if (CurrentAttackSeq == 0) { UE_LOG(LogTemp, Warning, TEXT("[HIT_REPORT_SKIP] Seq zero")); return; }
	if (!Victim || Victim->IsDead()) { UE_LOG(LogTemp, Warning, TEXT("[HIT_REPORT_SKIP] Invalid victim")); return; }
	if (Victim == this || Victim->GetNetworkPlayerUID() == GetNetworkPlayerUID())
	{
		UE_LOG(LogTemp, Warning, TEXT("[HIT_REPORT_SKIP] Self or same UID VictimUID=%d OwnerUID=%d"),
			Victim ? Victim->GetNetworkPlayerUID() : -999,
			GetNetworkPlayerUID());
		return;
	}
	if (HitActors.Contains(Victim)) { return; }

	const int32 VictimUID = Victim->GetNetworkPlayerUID();
	if (VictimUID <= 0) { return; }

	if (HitActors.Contains(Victim)) { return; }
	HitActors.Add(Victim);

	if (UNetworkInstance* NetworkInstance = GetGameInstance<UNetworkInstance>())
	{
		NetworkInstance->RequestAttackHitReport(
			CurrentAttackSeq,
			Victim->GetNetworkPlayerUID(),
			CurrentAttackType
		);
	}
}
