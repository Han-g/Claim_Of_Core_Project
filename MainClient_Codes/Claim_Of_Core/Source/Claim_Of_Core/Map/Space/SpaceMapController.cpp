#include "SpaceMapController.h"

#include "BlackHoleActor.h"
#include "GlassBreakController.h"

#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

ASpaceMapController::ASpaceMapController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpaceMapController::InitializeGameState()
{
	if (CachedGameState)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		CachedGameState = World->GetGameState<AInGame_GameState>();
	}

	if (!CachedGameState)
	{
		UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] InGame_GameState is not valid."));
		return;
	}

	CachedGameState->OnNativeRoundStateChanged.AddUObject(
		this, &ASpaceMapController::HandleRoundStateChanged);

	CachedGameState->OnNativePhaseChanged.AddUObject(
		this, &ASpaceMapController::HandlePhaseChanged);
}

void ASpaceMapController::SyncFromGameState()
{
	if (!CachedGameState)
	{
		return;
	}

	HandleRoundStateChanged(CachedGameState->RoundState, CachedGameState->RoundState);
	HandlePhaseChanged(CachedGameState->CurrentPhase, CachedGameState->CurrentPhase);
}

void ASpaceMapController::HandleRoundStateChanged(ERoundState OldState, ERoundState NewState)
{
	if (NewState != ERoundState::Playing)
	{
		StopSpaceMap();
	}
}

void ASpaceMapController::HandlePhaseChanged(EMapPhase OldPhase, EMapPhase NewPhase)
{
	if (!CachedGameState || CachedGameState->RoundState != ERoundState::Playing)
	{
		return;
	}
	if (IsValid(BlackHoleActor) && CachedGameState)
	{
		BlackHoleActor->SetActorLocation(CachedGameState->SpaceBlackHoleLocation);

		const FVector ActorLocation = BlackHoleActor->GetActorLocation();
		const FVector ServerLocation = CachedGameState->SpaceBlackHoleLocation;

		UE_LOG(LogTemp, Warning,
			TEXT("[SpaceMapController] BlackHole Synced Actor=%s ServerLocation=(X=%.1f, Y=%.1f, Z=%.1f) ActorLocation=(X=%.1f, Y=%.1f, Z=%.1f) Phase=%d"),
			*BlackHoleActor->GetName(),
			ServerLocation.X, ServerLocation.Y, ServerLocation.Z,
			ActorLocation.X, ActorLocation.Y, ActorLocation.Z,
			static_cast<int32>(NewPhase));
	}

	switch (NewPhase)
	{
	case EMapPhase::Phase1:
		StartSpaceMap();
		break;

	case EMapPhase::Phase2:
		EnterPhase2();
		break;

	case EMapPhase::Phase3:
		EnterPhase3();
		break;

	case EMapPhase::None:
	case EMapPhase::End:
	default:
		StopSpaceMap();
		break;
	}
}

void ASpaceMapController::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameState();
	SyncFromGameState();

	UE_LOG(LogTemp, Warning,
		TEXT("[SpaceMapController] BeginPlay. GlassBreakController=%s BlackHoleActor=%s"),
		IsValid(GlassBreakController) ? *GlassBreakController->GetName() : TEXT("NULL"),
		IsValid(BlackHoleActor) ? *BlackHoleActor->GetName() : TEXT("NULL"));
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
}

void ASpaceMapController::StopSpaceMap()
{
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
	CurrentPhase = EMapPhase::Phase1;

	UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] Enter Phase1"));

	if (IsValid(GlassBreakController))
	{
		GlassBreakController->ResetGlassActors();
	}

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
	CurrentPhase = EMapPhase::Phase2;

	UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] Enter Phase2"));

	if (IsValid(GlassBreakController))
	{
		GlassBreakController->BreakPhase2GlassActors();
	}
	else 
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[SpaceMapController] Phase2 GlassBreakController=%s"),
			IsValid(GlassBreakController) ? *GlassBreakController->GetName() : TEXT("NULL"));
	}

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
	CurrentPhase = EMapPhase::Phase3;

	UE_LOG(LogTemp, Warning, TEXT("[SpaceMapController] Enter Phase3"));

	if (IsValid(GlassBreakController))
	{
		GlassBreakController->BreakPhase3GlassActors();
	}
	else
	{
		UE_LOG(LogTemp, Warning,
			TEXT("[SpaceMapController] Phase2 GlassBreakController=%s"),
			IsValid(GlassBreakController) ? *GlassBreakController->GetName() : TEXT("NULL"));
	}

	if (IsValid(BlackHoleActor))
	{
		// Phase3에서는 끌어당김 종료
		// 원하면 HideBlackHole()로 바꿔서 완전히 사라지게 해도 됨
		//BlackHoleActor->DeactivateBlackHole();
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
