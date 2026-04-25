#include "IceFloorTile.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TimerManager.h"

// 네 프로젝트 실제 경로에 맞게 수정
#include "../GameState/InGame_GameState.h"

AIceFloorTile::AIceFloorTile()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void AIceFloorTile::BeginPlay()
{
	Super::BeginPlay();

	InitializeIceFloor();
}

void AIceFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandlePhaseLogic();
}

void AIceFloorTile::InitializeIceFloor()
{
	CacheGameState();
	CollectIcePieces();
	BuildPieceData();

	UE_LOG(LogTemp, Warning, TEXT("IceFloor Initialized. Piece Count: %d"), IcePieces.Num());
}

void AIceFloorTile::ResetIceFloor()
{
	bPhase2Triggered = false;
	bPhase3Triggered = false;

	GetWorldTimerManager().ClearTimer(RandomBreakTimerHandle);

	for (FIceFloorPieceData& Piece : IcePieces)
	{
		if (!IsValid(Piece.Mesh))
		{
			continue;
		}

		Piece.State = EIcePieceState::Normal;

		Piece.Mesh->SetHiddenInGame(false);
		Piece.Mesh->SetMobility(EComponentMobility::Movable);
		Piece.Mesh->SetSimulatePhysics(false);
		Piece.Mesh->SetEnableGravity(false);
		Piece.Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Piece.Mesh->SetCollisionProfileName(TEXT("BlockAll"));

		if (Piece.DynamicMaterial)
		{
			Piece.DynamicMaterial->SetScalarParameterValue(CrackAmountParamName, 0.f);
		}
	}
}

void AIceFloorTile::CacheGameState()
{
	if (CachedGameState)
	{
		return;
	}

	CachedGameState = GetWorld() ? GetWorld()->GetGameState<AInGame_GameState>() : nullptr;
}

void AIceFloorTile::HandlePhaseLogic()
{
	if (!CachedGameState)
	{
		CacheGameState();
		if (!CachedGameState)
		{
			return;
		}
	}

	if (CachedGameState->RoundState != ERoundState::Playing)
	{
		return;
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase2 && !bPhase2Triggered)
	{
		TriggerPhase2IceFloor();
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase3 && !bPhase3Triggered)
	{
		TriggerPhase3IceFloor();
	}
}

void AIceFloorTile::CollectIcePieces()
{
	IcePieces.Empty();

	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>(MeshComponents);

	for (UStaticMeshComponent* MeshComp : MeshComponents)
	{
		if (!IsValid(MeshComp))
		{
			continue;
		}

		if (bUsePieceTag && !MeshComp->ComponentHasTag(IcePieceTag))
		{
			continue;
		}

		FIceFloorPieceData NewPiece;
		NewPiece.Mesh = MeshComp;
		NewPiece.State = EIcePieceState::Normal;

		MeshComp->SetMobility(EComponentMobility::Movable);
		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetEnableGravity(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComp->SetCollisionProfileName(TEXT("BlockAll"));

		if (MeshComp->GetNumMaterials() > 0)
		{
			NewPiece.DynamicMaterial = MeshComp->CreateDynamicMaterialInstance(0);

			if (NewPiece.DynamicMaterial)
			{
				NewPiece.DynamicMaterial->SetScalarParameterValue(CrackAmountParamName, 0.f);
			}
		}

		IcePieces.Add(NewPiece);
	}
}

void AIceFloorTile::BuildPieceData()
{
	if (IcePieces.Num() == 0)
	{
		return;
	}

	FloorCenter = FVector::ZeroVector;

	int32 ValidCount = 0;

	for (const FIceFloorPieceData& Piece : IcePieces)
	{
		if (!IsValid(Piece.Mesh))
		{
			continue;
		}

		FloorCenter += Piece.Mesh->GetComponentLocation();
		ValidCount++;
	}

	if (ValidCount <= 0)
	{
		return;
	}

	FloorCenter /= ValidCount;

	for (FIceFloorPieceData& Piece : IcePieces)
	{
		if (!IsValid(Piece.Mesh))
		{
			continue;
		}

		Piece.DistanceToCenter = FVector::Dist2D(
			Piece.Mesh->GetComponentLocation(),
			FloorCenter
		);

		UE_LOG(
			LogTemp,
			Warning,
			TEXT("IcePiece: %s / Distance: %.2f"),
			*Piece.Mesh->GetName(),
			Piece.DistanceToCenter
		);
	}
}

void AIceFloorTile::TriggerPhase2IceFloor()
{
	if (IcePieces.Num() == 0)
	{
		return;
	}

	bPhase2Triggered = true;

	UE_LOG(LogTemp, Warning, TEXT("Phase2 IceFloor Random Break Start"));

	GetWorldTimerManager().ClearTimer(RandomBreakTimerHandle);
	GetWorldTimerManager().SetTimer(
		RandomBreakTimerHandle,
		this,
		&AIceFloorTile::CrackRandomOuterPiece,
		Phase2RandomInterval,
		true
	);

	CrackRandomOuterPiece();
}

void AIceFloorTile::TriggerPhase3IceFloor()
{
	if (IcePieces.Num() == 0)
	{
		return;
	}

	bPhase3Triggered = true;

	UE_LOG(LogTemp, Warning, TEXT("Phase3 IceFloor Random Break Faster"));

	GetWorldTimerManager().ClearTimer(RandomBreakTimerHandle);
	GetWorldTimerManager().SetTimer(
		RandomBreakTimerHandle,
		this,
		&AIceFloorTile::CrackRandomOuterPiece,
		Phase3RandomInterval,
		true
	);

	CrackRandomOuterPiece();
}

void AIceFloorTile::CrackRandomOuterPiece()
{
	TArray<int32> Candidates;

	for (int32 i = 0; i < IcePieces.Num(); ++i)
	{
		const FIceFloorPieceData& Piece = IcePieces[i];

		if (!IsValid(Piece.Mesh))
		{
			continue;
		}

		if (Piece.State != EIcePieceState::Normal)
		{
			continue;
		}

		// 중심부는 안전 구역으로 남김
		if (Piece.DistanceToCenter < MinSafeDistance)
		{
			continue;
		}

		Candidates.Add(i);
	}

	if (Candidates.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No More Breakable Outer Ice Pieces"));
		GetWorldTimerManager().ClearTimer(RandomBreakTimerHandle);
		return;
	}

	const int32 RandomCandidateIndex = FMath::RandRange(0, Candidates.Num() - 1);
	const int32 PieceIndex = Candidates[RandomCandidateIndex];

	SetPieceCracked(PieceIndex);

	const float Delay = FMath::FRandRange(
		BreakAfterCrackMinDelay,
		BreakAfterCrackMaxDelay
	);

	FTimerHandle LocalBreakHandle;
	FTimerDelegate BreakDelegate;
	BreakDelegate.BindUObject(this, &AIceFloorTile::StartPieceBreaking, PieceIndex);

	GetWorldTimerManager().SetTimer(
		LocalBreakHandle,
		BreakDelegate,
		Delay,
		false
	);
}

void AIceFloorTile::SetPieceCracked(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex))
	{
		return;
	}

	FIceFloorPieceData& Piece = IcePieces[PieceIndex];

	if (!IsValid(Piece.Mesh))
	{
		return;
	}

	if (Piece.State != EIcePieceState::Normal)
	{
		return;
	}

	Piece.State = EIcePieceState::Cracked;

	if (Piece.DynamicMaterial)
	{
		Piece.DynamicMaterial->SetScalarParameterValue(CrackAmountParamName, 0.45f);
	}

	UE_LOG(LogTemp, Warning, TEXT("Ice Piece Cracked: %s"), *Piece.Mesh->GetName());

	BP_OnPieceCracked(Piece.Mesh);
}

void AIceFloorTile::StartPieceBreaking(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex))
	{
		return;
	}

	FIceFloorPieceData& Piece = IcePieces[PieceIndex];

	if (!IsValid(Piece.Mesh))
	{
		return;
	}

	if (Piece.State == EIcePieceState::Broken || Piece.State == EIcePieceState::Breaking)
	{
		return;
	}

	if (Piece.State == EIcePieceState::Normal)
	{
		SetPieceCracked(PieceIndex);
	}

	Piece.State = EIcePieceState::Breaking;

	if (Piece.DynamicMaterial)
	{
		Piece.DynamicMaterial->SetScalarParameterValue(CrackAmountParamName, 0.9f);
	}

	UE_LOG(LogTemp, Warning, TEXT("Ice Piece Breaking: %s"), *Piece.Mesh->GetName());

	BP_OnPieceBreaking(Piece.Mesh);

	BreakPiece(PieceIndex);
}

void AIceFloorTile::BreakPiece(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex))
	{
		return;
	}

	FIceFloorPieceData& Piece = IcePieces[PieceIndex];

	if (!IsValid(Piece.Mesh))
	{
		return;
	}

	if (Piece.State == EIcePieceState::Broken)
	{
		return;
	}

	Piece.State = EIcePieceState::Broken;

	if (Piece.DynamicMaterial)
	{
		Piece.DynamicMaterial->SetScalarParameterValue(CrackAmountParamName, 1.0f);
	}

	UE_LOG(LogTemp, Warning, TEXT("Ice Piece Broken: %s"), *Piece.Mesh->GetName());

	if (bFallWhenBroken)
	{
		Piece.Mesh->SetMobility(EComponentMobility::Movable);

		Piece.Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Piece.Mesh->SetCollisionResponseToAllChannels(ECR_Block);
		Piece.Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

		Piece.Mesh->SetLinearDamping(PhysicsLinearDamping);
		Piece.Mesh->SetAngularDamping(PhysicsAngularDamping);

		Piece.Mesh->SetEnableGravity(true);
		Piece.Mesh->SetSimulatePhysics(true);
		Piece.Mesh->WakeAllRigidBodies();
	}
	else
	{
		Piece.Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Piece.Mesh->SetHiddenInGame(true);
	}

	BP_OnPieceBroken(Piece.Mesh);

	if (BrokenPieceHideDelay > 0.f)
	{
		FTimerHandle HideHandle;
		FTimerDelegate HideDelegate;
		HideDelegate.BindUObject(this, &AIceFloorTile::HidePiece, PieceIndex);

		GetWorldTimerManager().SetTimer(
			HideHandle,
			HideDelegate,
			BrokenPieceHideDelay,
			false
		);
	}
}

void AIceFloorTile::HidePiece(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex))
	{
		return;
	}

	FIceFloorPieceData& Piece = IcePieces[PieceIndex];

	if (!IsValid(Piece.Mesh))
	{
		return;
	}

	Piece.Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Piece.Mesh->SetSimulatePhysics(false);
	Piece.Mesh->SetHiddenInGame(true);
}

bool AIceFloorTile::HasBreakableOuterPiece() const
{
	for (const FIceFloorPieceData& Piece : IcePieces)
	{
		if (!IsValid(Piece.Mesh))
		{
			continue;
		}

		if (Piece.State == EIcePieceState::Normal &&
			Piece.DistanceToCenter >= MinSafeDistance)
		{
			return true;
		}
	}

	return false;
}