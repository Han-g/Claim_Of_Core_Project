#include "IceFloorTile.h"
#include "Components/PrimitiveComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../../Sub/MyCharacter.h"
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

	ProcessStandingDamage(DeltaTime);

	if (bUsePhaseEdgeBreaking)
	{
		CheckPhaseAndStart();
		ProcessBreaking(DeltaTime);
	}
}

void AIceFloorTile::NotifyPlayerStandingOnPiece(AMyCharacter* StandingCharacter, UPrimitiveComponent* StandingComponent)
{
	if (!StandingCharacter || StandingCharacter->IsDead() || !StandingComponent)
	{
		return;
	}

	const int32 PieceIndex = FindPieceIndex(StandingComponent);
	if (!IcePieces.IsValidIndex(PieceIndex) ||
		!StandingCharactersByPiece.IsValidIndex(PieceIndex) ||
		!PieceBrokenFlags.IsValidIndex(PieceIndex) ||
		PieceBrokenFlags[PieceIndex])
	{
		return;
	}

	StandingCharactersByPiece[PieceIndex].Add(StandingCharacter);
}

void AIceFloorTile::CollectIcePieces()
{
	IcePieces.Empty();
	PieceDamageProgress.Empty();
	PieceCrackedByStandingFlags.Empty();
	PieceBrokenFlags.Empty();
	StandingCharactersByPiece.Empty();

	TArray<UStaticMeshComponent*> MeshComponents;
	GetComponents<UStaticMeshComponent>(MeshComponents);

	for (UStaticMeshComponent* MeshComp : MeshComponents)
	{
		if (!MeshComp)
		{
			continue;
		}

		IcePieces.Add(MeshComp);
		PieceDamageProgress.Add(0.f);
		PieceCrackedByStandingFlags.Add(false);
		PieceBrokenFlags.Add(false);
		StandingCharactersByPiece.AddDefaulted();

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

	if (PieceBrokenFlags.IsValidIndex(PieceIndex) && PieceBrokenFlags[PieceIndex])
	{
		Timer = 0.f;
		CurrentPieceIndex++;
		bCurrentPieceCracked = false;
		return;
	}

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

void AIceFloorTile::ProcessStandingDamage(float DeltaTime)
{
	if (DeltaTime <= 0.f)
	{
		return;
	}

	if (!CachedGameState)
	{
		CachedGameState = GetWorld() ? GetWorld()->GetGameState<AInGame_GameState>() : nullptr;
	}

	const float CurrentBreakTime = GetCurrentStandingBreakTime();

	for (int32 PieceIndex = 0; PieceIndex < StandingCharactersByPiece.Num(); ++PieceIndex)
	{
		TSet<TWeakObjectPtr<AMyCharacter>>& StandingCharacters = StandingCharactersByPiece[PieceIndex];

		if (CurrentBreakTime <= 0.f ||
			!IcePieces.IsValidIndex(PieceIndex) ||
			!PieceDamageProgress.IsValidIndex(PieceIndex) ||
			!PieceCrackedByStandingFlags.IsValidIndex(PieceIndex) ||
			!PieceBrokenFlags.IsValidIndex(PieceIndex) ||
			PieceBrokenFlags[PieceIndex])
		{
			StandingCharacters.Empty();
			continue;
		}

		int32 StandingPlayerCount = 0;
		for (const TWeakObjectPtr<AMyCharacter>& StandingCharacter : StandingCharacters)
		{
			AMyCharacter* Character = StandingCharacter.Get();
			if (Character && !Character->IsDead())
			{
				StandingPlayerCount++;
			}
		}

		if (StandingPlayerCount > 0)
		{
			PieceDamageProgress[PieceIndex] = FMath::Clamp(
				PieceDamageProgress[PieceIndex] + (DeltaTime / CurrentBreakTime) * StandingPlayerCount,
				0.f,
				1.f
			);

			if (!PieceCrackedByStandingFlags[PieceIndex] && PieceDamageProgress[PieceIndex] >= CrackProgressThreshold)
			{
				CrackPiece(PieceIndex);
				PieceCrackedByStandingFlags[PieceIndex] = true;
			}

			if (PieceDamageProgress[PieceIndex] >= 1.f)
			{
				BreakPiece(PieceIndex);
			}
		}

		StandingCharacters.Empty();
	}
}

void AIceFloorTile::CrackPiece(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex))
	{
		return;
	}

	if (PieceBrokenFlags.IsValidIndex(PieceIndex) && PieceBrokenFlags[PieceIndex])
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

	if (PieceBrokenFlags.IsValidIndex(PieceIndex) && PieceBrokenFlags[PieceIndex])
	{
		return;
	}

	UStaticMeshComponent* Piece = IcePieces[PieceIndex];
	if (!Piece)
	{
		UE_LOG(LogTemp, Error, TEXT("[IceFloor] Piece Null"));
		return;
	}

	if (PieceBrokenFlags.IsValidIndex(PieceIndex))
	{
		PieceBrokenFlags[PieceIndex] = true;
	}

	Piece->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	Piece->SetMobility(EComponentMobility::Movable);
	Piece->SetSimulatePhysics(true);
	Piece->SetEnableGravity(true);
	Piece->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Piece->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	Piece->AddImpulse(FVector(0.f, 0.f, -DownImpulse), NAME_None, true);

	UE_LOG(LogTemp, Warning, TEXT("[IceFloor] Physics: %d / Gravity: %d / Collision: %d"),
		Piece->IsSimulatingPhysics(),
		Piece->IsGravityEnabled(),
		(int32)Piece->GetCollisionEnabled()
	);

	DestroyPieceLater(Piece);
}

float AIceFloorTile::GetCurrentStandingBreakTime() const
{
	if (!CachedGameState || CachedGameState->RoundState != ERoundState::Playing)
	{
		return 0.f;
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase2)
	{
		return Phase2StandingBreakTime;
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase3)
	{
		return Phase3StandingBreakTime;
	}

	return 0.f;
}

int32 AIceFloorTile::FindPieceIndex(UPrimitiveComponent* PieceComponent) const
{
	for (int32 i = 0; i < IcePieces.Num(); ++i)
	{
		if (IcePieces[i] == PieceComponent)
		{
			return i;
		}
	}

	return INDEX_NONE;
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
