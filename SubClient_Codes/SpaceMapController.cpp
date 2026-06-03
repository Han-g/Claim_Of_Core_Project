#include "SpaceMapController.h"

#include "BlackHoleActor.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

ASpaceMapController::ASpaceMapController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpaceMapController::BeginPlay()
{
	Super::BeginPlay();

	StartSpaceMap();
}

void ASpaceMapController::StartSpaceMap()
{
	StopSpaceMap();

	// 다시 Phase1부터 시작
	EnterPhase1();

	ApplyLowGravityToAllCharacters();
	ApplyJumpAnimRateToAllCharacters();

	GetWorldTimerManager().SetTimer(
		LowGravityApplyTimerHandle,
		this,
		&ASpaceMapController::ApplyLowGravityToAllCharacters,
		1.0f,
		true
	);

	GetWorldTimerManager().SetTimer(
		JumpAnimApplyTimerHandle,
		this,
		&ASpaceMapController::ApplyJumpAnimRateToAllCharacters,
		JumpAnimCheckInterval,
		true
	);

	GetWorldTimerManager().SetTimer(
		Phase2TimerHandle,
		this,
		&ASpaceMapController::EnterPhase2,
		Phase2StartTime,
		false
	);

	GetWorldTimerManager().SetTimer(
		Phase3TimerHandle,
		this,
		&ASpaceMapController::EnterPhase3,
		Phase3StartTime,
		false
	);
}

void ASpaceMapController::StopSpaceMap()
{
	GetWorldTimerManager().ClearTimer(Phase2TimerHandle);
	GetWorldTimerManager().ClearTimer(Phase3TimerHandle);
	GetWorldTimerManager().ClearTimer(LowGravityApplyTimerHandle);
	GetWorldTimerManager().ClearTimer(JumpAnimApplyTimerHandle);

	ResetAnimRateToAllCharacters();

	if (IsValid(BlackHoleActor))
	{
		BlackHoleActor->HideBlackHole();
	}
}

void ASpaceMapController::EnterPhase1()
{
	CurrentPhase = ESpaceMapPhase::Phase1;

	UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] Enter Phase1"));

	if (IsValid(BlackHoleActor))
	{
		// Phase1부터 블랙홀은 보이게 함
		// 단, 끌어당기는 힘은 아직 꺼둠
		BlackHoleActor->ShowBlackHole();
		BlackHoleActor->DeactivateBlackHole();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] Phase1 - BlackHoleActor is not assigned."));
	}

	BP_OnPhaseChanged(CurrentPhase);
}

void ASpaceMapController::EnterPhase2()
{
	CurrentPhase = ESpaceMapPhase::Phase2;

	UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] Enter Phase2"));

	if (IsValid(BlackHoleActor))
	{
		// Phase2부터 실제로 끌어당김 시작
		BlackHoleActor->ShowBlackHole();
		BlackHoleActor->ActivateBlackHole();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] Phase2 - BlackHoleActor is not assigned."));
	}

	BP_OnPhaseChanged(CurrentPhase);
}

void ASpaceMapController::EnterPhase3()
{
	CurrentPhase = ESpaceMapPhase::Phase3;

	UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] Enter Phase3"));

	if (IsValid(BlackHoleActor))
	{
		// Phase3에서는 끌어당김 종료
		// 원하면 HideBlackHole()로 바꿔서 완전히 사라지게 해도 됨
		BlackHoleActor->DeactivateBlackHole();
	}

	BP_OnPhaseChanged(CurrentPhase);
}

void ASpaceMapController::ApplyLowGravityToAllCharacters()
{
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundCharacters);

	for (AActor* Actor : FoundCharacters)
	{
		ACharacter* Character = Cast<ACharacter>(Actor);

		if (!IsValid(Character))
		{
			continue;
		}

		UCharacterMovementComponent* Movement = Character->GetCharacterMovement();

		if (!IsValid(Movement))
		{
			continue;
		}

		Movement->GravityScale = LowGravityScale;
		Movement->JumpZVelocity = LowGravityJumpZVelocity;
		Movement->AirControl = LowGravityAirControl;

		Movement->FallingLateralFriction = SpaceFallingLateralFriction;
		Movement->BrakingDecelerationFalling = SpaceBrakingDecelerationFalling;
	}
}

void ASpaceMapController::ApplyJumpAnimRateToAllCharacters()
{
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundCharacters);

	for (AActor* Actor : FoundCharacters)
	{
		ACharacter* Character = Cast<ACharacter>(Actor);

		if (!IsValid(Character))
		{
			continue;
		}

		UCharacterMovementComponent* Movement = Character->GetCharacterMovement();

		if (!IsValid(Movement))
		{
			continue;
		}

		USkeletalMeshComponent* Mesh = Character->GetMesh();

		if (!IsValid(Mesh))
		{
			continue;
		}

		if (Movement->IsFalling())
		{
			Mesh->GlobalAnimRateScale = JumpAnimRateScale;
		}
		else
		{
			Mesh->GlobalAnimRateScale = GroundAnimRateScale;
		}
	}
}

void ASpaceMapController::ResetAnimRateToAllCharacters()
{
	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), FoundCharacters);

	for (AActor* Actor : FoundCharacters)
	{
		ACharacter* Character = Cast<ACharacter>(Actor);

		if (!IsValid(Character))
		{
			continue;
		}

		USkeletalMeshComponent* Mesh = Character->GetMesh();

		if (!IsValid(Mesh))
		{
			continue;
		}

		Mesh->GlobalAnimRateScale = 1.0f;
	}
}
