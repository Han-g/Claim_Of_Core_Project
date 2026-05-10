#include "IceFloorTile.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AIceFloorTile::AIceFloorTile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIceFloorTile::BeginPlay()
{
	Super::BeginPlay();

	CachedGameState = GetWorld() ? GetWorld()->GetGameState<AInGame_GameState>() : nullptr;

	CollectIcePieces();
	BuildBreakOrder();

	UE_LOG(LogTemp, Warning, TEXT("[IceFloor] BeginPlay / Pieces: %d / Sorted: %d / GameState: %s"),
		IcePieces.Num(),
		SortedPieceIndices.Num(),
		CachedGameState ? TEXT("Valid") : TEXT("Null")
	);

	Tags.Add(TEXT("IceFloor"));
}

void AIceFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckPhaseAndStart();
	ProcessBreaking(DeltaTime);
}

void AIceFloorTile::CollectIcePieces()
{
	IcePieces.Empty();

	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>(MeshComponents);

	for (UStaticMeshComponent* MeshComp : MeshComponents)
	{
		if (!MeshComp)
		{
			continue;
		}

		IcePieces.Add(MeshComp);

		MeshComp->SetMobility(EComponentMobility::Movable);
		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetEnableGravity(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshComp->SetCollisionObjectType(ECC_WorldStatic);
		MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
		
		
	}

	UE_LOG(LogTemp, Warning, TEXT("[IceFloor] CollectIcePieces Count: %d"), IcePieces.Num());
}

void AIceFloorTile::BuildBreakOrder()
{
	SortedPieceIndices.Empty();

	const FVector Center = GetActorLocation();

	TArray<TPair<int32, float>> DistanceList;

	for (int32 i = 0; i < IcePieces.Num(); i++)
	{
		if (!IcePieces[i])
		{
			continue;
		}

		const FVector PieceCenter = IcePieces[i]->Bounds.Origin;

		const float Distance = FVector::Dist2D(
			PieceCenter,
			Center
		);

		UE_LOG(LogTemp, Warning, TEXT("[IceFloor] Piece: %s / Distance: %.1f / Inner: %.1f"),
			*IcePieces[i]->GetName(),
			Distance,
			InnerSafeRadius
		);

		if (Distance < InnerSafeRadius)
		{
			continue;
		}

		DistanceList.Add({ i, Distance });
	}

	DistanceList.Sort([](const auto& A, const auto& B)
		{
			return A.Value > B.Value;
		});

	for (auto& Pair : DistanceList)
	{
		SortedPieceIndices.Add(Pair.Key);
	}

	UE_LOG(LogTemp, Warning, TEXT("[IceFloor] Break Count: %d"), SortedPieceIndices.Num());
}

void AIceFloorTile::CheckPhaseAndStart()
{
	if (!CachedGameState)
	{
		CachedGameState = GetWorld() ? GetWorld()->GetGameState<AInGame_GameState>() : nullptr;
		return;
	}

	if (CachedGameState->RoundState != ERoundState::Playing)
	{
		return;
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase2 ||
		CachedGameState->CurrentPhase == EMapPhase::Phase3)
	{
		if (!bStartedBreaking)
		{
			bStartedBreaking = true;
			Timer = 0.f;

			UE_LOG(LogTemp, Warning, TEXT("[IceFloor] Start Breaking From Phase: %d"),
				(int32)CachedGameState->CurrentPhase
			);
		}
	}
}

void AIceFloorTile::ProcessBreaking(float DeltaTime)
{
	if (!bStartedBreaking)
	{
		return;
	}

	if (SortedPieceIndices.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("[IceFloor] SortedPieceIndices EMPTY"));
		return;
	}

	if (CurrentPieceIndex >= SortedPieceIndices.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("[IceFloor] All Pieces Broken"));
		BreakActor();
		bStartedBreaking = false;
		return;
	}

	float CurrentInterval = Phase2BreakInterval;

	if (CachedGameState && CachedGameState->CurrentPhase == EMapPhase::Phase3)
	{
		CurrentInterval = Phase3BreakInterval;
	}

	Timer += DeltaTime;

	const int32 PieceIndex = SortedPieceIndices[CurrentPieceIndex];

	if (!bCurrentPieceCracked)
	{
		if (Timer >= CurrentInterval)
		{
			Timer = 0.f;
			CrackPiece(PieceIndex);
			bCurrentPieceCracked = true;

			UE_LOG(LogTemp, Warning, TEXT("[IceFloor] Crack Piece: %d"), PieceIndex);
		}

		return;
	}

	if (Timer >= CrackDelay)
	{
		Timer = 0.f;

		BreakPiece(PieceIndex);

		UE_LOG(LogTemp, Warning, TEXT("[IceFloor] Break Piece: %d"), PieceIndex);

		CurrentPieceIndex++;
		bCurrentPieceCracked = false;
	}
}

void AIceFloorTile::CrackPiece(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex))
	{
		return;
	}

	UStaticMeshComponent* Piece = IcePieces[PieceIndex];
	if (!Piece)
	{
		return;
	}

	if (CrackedMaterial)
	{
		Piece->SetMaterial(0, CrackedMaterial);
	}
}

void AIceFloorTile::BreakPiece(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex))
	{
		UE_LOG(LogTemp, Error, TEXT("[IceFloor] Invalid PieceIndex: %d"), PieceIndex);
		return;
	}

	UStaticMeshComponent* Piece = IcePieces[PieceIndex];
	if (!Piece)
	{
		UE_LOG(LogTemp, Error, TEXT("[IceFloor] Piece Null"));
		return;
	}

	Piece->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	Piece->SetMobility(EComponentMobility::Movable);
	Piece->SetSimulatePhysics(true);
	Piece->SetEnableGravity(true);
	Piece->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	UE_LOG(LogTemp, Warning, TEXT("[IceFloor] Physics: %d / Gravity: %d / Collision: %d"),
		Piece->IsSimulatingPhysics(),
		Piece->IsGravityEnabled(),
		(int32)Piece->GetCollisionEnabled()
	);

	DestroyPieceLater(Piece);
}

void AIceFloorTile::DestroyPieceLater(UStaticMeshComponent* Piece)
{
	if (!Piece || BrokenDestroyDelay <= 0.f)
	{
		return;
	}

	FTimerHandle DestroyTimerHandle;

	GetWorld()->GetTimerManager().SetTimer(
		DestroyTimerHandle,
		[Piece]()
		{
			if (IsValid(Piece))
			{
				Piece->DestroyComponent();
			}
		},
		BrokenDestroyDelay,
		false
	);
}