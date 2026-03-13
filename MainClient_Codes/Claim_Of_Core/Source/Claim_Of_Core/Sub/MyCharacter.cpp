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

	/*
	// Apply jump damage only when jump is considered "pressed" (server-authoritative)
	if (bPressedJump)
	{
		if (HasAuthority())
		{
			ApplyDamage(10);
		}
	}
	*/
}

void AMyCharacter::ApplyDeadState()
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

void AMyCharacter::ApplyAliveState()
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
