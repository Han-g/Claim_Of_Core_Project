#include "IceFloorTile.h"
#include "../../Sub/MyCharacter.h"

#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

AIceFloorTile::AIceFloorTile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIceFloorTile::ApplyNetworkPieceState(int32 PieceIndex, int32 EventState)
{
	if (!IcePieces.IsValidIndex(PieceIndex))
	{
		return;
	}

	if (EventState == 1)       // Cracked
	{
		CrackPiece(PieceIndex);
	}
	else if (EventState == 2)  // Breaking
	{
		CrackPiece(PieceIndex);
	}
	else if (EventState == 3)  // Broken
	{
		BreakPiece(PieceIndex);
	}
}

void AIceFloorTile::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		CachedGameState = World->GetGameState<AInGame_GameState>();
	}

	CollectIcePieces();
	BuildBreakOrder();
}

void AIceFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CheckPhaseAndStart();

	if (bStartedBreaking && !IsBroken())
	{
		ProcessBreaking(DeltaTime);
	}

	ProcessStandingDamage(DeltaTime);
}

void AIceFloorTile::StartBreaking()
{
	if (bStartedBreaking || IsBroken())
	{
		return;
	}

	if (IcePieces.Num() <= 0)
	{
		CollectIcePieces();
		BuildBreakOrder();
	}

	ActivateBreakable();

	bStartedBreaking = true;
	bCurrentPieceCracked = false;
	CurrentPieceIndex = 0;
	Timer = 0.f;
}

void AIceFloorTile::CollectIcePieces()
{
	IcePieces.Reset();

	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);

	for (UStaticMeshComponent* Component : Components)
	{
		if (!IsValid(Component))
		{
			continue;
		}

		const bool bTaggedPiece = Component->ComponentHasTag(IcePieceTag);
		const bool bNamedPiece = Component->GetName().StartsWith(TEXT("Floor_cell_"));

		if (!bTaggedPiece && !bNamedPiece)
		{
			continue;
		}

		Component->SetMobility(EComponentMobility::Movable);
		Component->SetSimulatePhysics(false);
		Component->SetEnableGravity(false);
		Component->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		IcePieces.Add(Component);
	}

	IcePieces.Sort([](
		const TObjectPtr<UStaticMeshComponent>& A,
		const TObjectPtr<UStaticMeshComponent>& B)
		{
			if (!IsValid(A)) { return false; }
			if (!IsValid(B)) { return true; }

			return A->GetName().Compare(B->GetName(), ESearchCase::IgnoreCase) < 0;
		});

	PieceDamageProgress.Init(0.f, IcePieces.Num());
	PieceCrackedByStandingFlags.Init(0, IcePieces.Num());
	PieceBrokenFlags.Init(0, IcePieces.Num());
	StandingCharactersByPiece.SetNum(IcePieces.Num());
}

void AIceFloorTile::BuildBreakOrder()
{
	SortedPieceIndices.Reset();

	for (int32 i = 0; i < IcePieces.Num(); ++i)
	{
		if (!IsValid(IcePieces[i]))
		{
			continue;
		}

		const float Dist = FVector::Dist2D(IcePieces[i]->Bounds.Origin, GetActorLocation());

		if (Dist < InnerSafeRadius)
		{
			continue;
		}

		SortedPieceIndices.Add(i);
	}

	SortedPieceIndices.Sort([this](int32 A, int32 B)
		{
			const float DistA = FVector::Dist2D(IcePieces[A]->GetComponentLocation(), GetActorLocation());
			const float DistB = FVector::Dist2D(IcePieces[B]->GetComponentLocation(), GetActorLocation());

			return DistA > DistB;
		});
}

void AIceFloorTile::CheckPhaseAndStart()
{
	if (!bUsePhaseEdgeBreaking || bStartedBreaking || IsBroken())
	{
		return;
	}

	if (!CachedGameState && GetWorld())
	{
		CachedGameState = GetWorld()->GetGameState<AInGame_GameState>();
	}

	if (!CachedGameState)
	{
		return;
	}

	if (CachedGameState->CurrentPhase == EMapPhase::Phase2 ||
		CachedGameState->CurrentPhase == EMapPhase::Phase3)
	{
		StartBreaking();
	}
}

void AIceFloorTile::ProcessBreaking(float DeltaTime)
{
	if (CurrentPieceIndex >= SortedPieceIndices.Num())
	{
		BreakActor();
		return;
	}

	const int32 PieceIndex = SortedPieceIndices[CurrentPieceIndex];

	if (!IcePieces.IsValidIndex(PieceIndex) || !IsValid(IcePieces[PieceIndex]) || PieceBrokenFlags[PieceIndex])
	{
		++CurrentPieceIndex;
		Timer = 0.f;
		bCurrentPieceCracked = false;
		return;
	}

	Timer += DeltaTime;

	if (!bCurrentPieceCracked)
	{
		if (Timer >= GetCurrentBreakInterval())
		{
			CrackPiece(PieceIndex);
			bCurrentPieceCracked = true;
			Timer = 0.f;
		}

		return;
	}

	if (Timer >= CrackDelay)
	{
		BreakPiece(PieceIndex);
		++CurrentPieceIndex;
		bCurrentPieceCracked = false;
		Timer = 0.f;
	}
}

void AIceFloorTile::CrackPiece(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex) || !IsValid(IcePieces[PieceIndex]))
	{
		return;
	}

	if (PieceBrokenFlags.IsValidIndex(PieceIndex) && PieceBrokenFlags[PieceIndex])
	{
		return;
	}

	if (m_CrackedMaterial)
	{
		IcePieces[PieceIndex]->SetMaterial(0, m_CrackedMaterial);
	}

	if (PieceCrackedByStandingFlags.IsValidIndex(PieceIndex))
	{
		PieceCrackedByStandingFlags[PieceIndex] = 1;
	}
}

void AIceFloorTile::BreakPiece(int32 PieceIndex)
{
	if (!IcePieces.IsValidIndex(PieceIndex) || !IsValid(IcePieces[PieceIndex]))
	{
		return;
	}

	if (PieceBrokenFlags.IsValidIndex(PieceIndex) && PieceBrokenFlags[PieceIndex])
	{
		return;
	}

	UStaticMeshComponent* Piece = IcePieces[PieceIndex];

	PieceBrokenFlags[PieceIndex] = 1;

	Piece->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	Piece->SetMobility(EComponentMobility::Movable);
	Piece->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Piece->SetCollisionObjectType(ECC_WorldDynamic);
	Piece->SetCollisionResponseToAllChannels(ECR_Block);
	Piece->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore); // 조각이 플레이어를 밀지 않게 하려면

	Piece->SetSimulatePhysics(true);
	Piece->SetEnableGravity(true);
	Piece->AddImpulse(FVector::DownVector * DownImpulse, NAME_None, true);

	DestroyPieceLater(Piece);

	if (AreAllBreakablePiecesBroken())
	{
		BreakActor();
	}
}

void AIceFloorTile::NotifyPlayerStandingOnPiece(AMyCharacter* StandingCharacter, UPrimitiveComponent* StandingComponent)
{
	if (!IsValid(StandingCharacter) || !IsValid(StandingComponent)|| StandingCharacter->IsDead())
	{
		return;
	}

	const int32 PieceIndex = FindPieceIndex(StandingComponent);

	if (!StandingCharactersByPiece.IsValidIndex(PieceIndex) ||
		!PieceBrokenFlags.IsValidIndex(PieceIndex) ||
		PieceBrokenFlags[PieceIndex])
	{
		return;
	}

	StandingCharactersByPiece[PieceIndex].Add(StandingCharacter);
}

void AIceFloorTile::ProcessStandingDamage(float DeltaTime)
{
	const float StandingBreakTime = GetCurrentStandingBreakTime();

	for (int32 i = 0; i < StandingCharactersByPiece.Num(); ++i)
	{
		if (!IcePieces.IsValidIndex(i) || !IsValid(IcePieces[i]))
		{
			StandingCharactersByPiece[i].Reset();
			continue;
		}

		if (PieceBrokenFlags.IsValidIndex(i) && PieceBrokenFlags[i])
		{
			StandingCharactersByPiece[i].Reset();
			continue;
		}

		if (StandingBreakTime <= 0.f || StandingCharactersByPiece[i].Num() <= 0)
		{
			StandingCharactersByPiece[i].Reset();
			continue;
		}

		PieceDamageProgress[i] += DeltaTime / StandingBreakTime;

		if (PieceDamageProgress[i] >= CrackProgressThreshold && !PieceCrackedByStandingFlags[i])
		{
			CrackPiece(i);
		}

		if (PieceDamageProgress[i] >= 1.f)
		{
			BreakPiece(i);
		}

		StandingCharactersByPiece[i].Reset();
	}
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

float AIceFloorTile::GetCurrentBreakInterval() const
{
	if (CachedGameState && CachedGameState->CurrentPhase == EMapPhase::Phase3)
	{
		return Phase3BreakInterval;
	}

	return Phase2BreakInterval;
}

bool AIceFloorTile::AreAllBreakablePiecesBroken() const
{
	if (SortedPieceIndices.Num() <= 0)
	{
		return false;
	}

	for (const int32 PieceIndex : SortedPieceIndices)
	{
		if (PieceBrokenFlags.IsValidIndex(PieceIndex) && !PieceBrokenFlags[PieceIndex])
		{
			return false;
		}
	}

	return true;
}

int32 AIceFloorTile::FindPieceIndex(UPrimitiveComponent* PieceComponent) const
{
	UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(PieceComponent);

	if (!MeshComponent)
	{
		return INDEX_NONE;
	}

	for (int32 i = 0; i < IcePieces.Num(); ++i)
	{
		if (IcePieces[i] == MeshComponent)
		{
			return i;
		}
	}

	return INDEX_NONE;
}

void AIceFloorTile::DestroyPieceLater(UStaticMeshComponent* Piece)
{
	if (!IsValid(Piece) || !GetWorld())
	{
		return;
	}

	FTimerHandle DestroyTimerHandle;

	GetWorldTimerManager().SetTimer(
		DestroyTimerHandle,
		FTimerDelegate::CreateWeakLambda(this, [Piece]()
			{
				if (IsValid(Piece))
				{
					Piece->DestroyComponent();
				}
			}),
		BrokenDestroyDelay,
		false
	);
}