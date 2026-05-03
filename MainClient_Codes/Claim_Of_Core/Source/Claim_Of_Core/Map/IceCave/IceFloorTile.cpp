#include "IceFloorTile.h"
#include "Components/StaticMeshComponent.h"

AIceFloorTile::AIceFloorTile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AIceFloorTile::BeginPlay()
{
	Super::BeginPlay();

	CollectIcePieces();
	BuildBreakOrder();

	if (bAutoStart)
	{
		StartIceBreaking();
	}
}

void AIceFloorTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ProcessBreaking(DeltaTime);
}

void AIceFloorTile::OnActivatedInternal()
{
	StartIceBreaking();
}

void AIceFloorTile::OnBrokenInternal()
{
	StartIceBreaking();
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

		// 시작할 때는 바닥으로 고정
		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetEnableGravity(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
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

		const float Distance = FVector::Dist2D(
			IcePieces[i]->GetComponentLocation(),
			Center
		);

		DistanceList.Add(TPair<int32, float>(i, Distance));
	}

	// 거리 먼 순서 = 바깥쪽부터
	DistanceList.Sort([](const TPair<int32, float>& A, const TPair<int32, float>& B)
		{
			return A.Value > B.Value;
		});

	for (const TPair<int32, float>& Pair : DistanceList)
	{
		SortedPieceIndices.Add(Pair.Key);
	}
}

void AIceFloorTile::StartIceBreaking()
{
	if (bStartedBreaking)
	{
		return;
	}

	bStartedBreaking = true;
	Timer = 0.f;
	CurrentPieceIndex = 0;
	bCurrentPieceCracked = false;
}

void AIceFloorTile::StopIceBreaking()
{
	bStartedBreaking = false;
	Timer = 0.f;
}

void AIceFloorTile::SetBreakInterval(float NewInterval)
{
	BreakInterval = FMath::Max(0.01f, NewInterval);
}

void AIceFloorTile::ProcessBreaking(float DeltaTime)
{
	if (!bStartedBreaking)
	{
		return;
	}

	if (CurrentPieceIndex >= SortedPieceIndices.Num())
	{
		BreakActor();
		bStartedBreaking = false;
		return;
	}

	Timer += DeltaTime;

	const int32 PieceIndex = SortedPieceIndices[CurrentPieceIndex];

	if (!bCurrentPieceCracked)
	{
		if (Timer >= BreakInterval)
		{
			Timer = 0.f;
			CrackPiece(PieceIndex);
			bCurrentPieceCracked = true;
		}

		return;
	}

	if (Timer >= CrackDelay)
	{
		Timer = 0.f;
		BreakPiece(PieceIndex);

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
		return;
	}

	UStaticMeshComponent* Piece = IcePieces[PieceIndex];
	if (!Piece)
	{
		return;
	}

	Piece->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	Piece->SetSimulatePhysics(true);
	Piece->SetEnableGravity(true);
	Piece->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	Piece->AddImpulse(FVector(0.f, 0.f, -DownImpulse), NAME_None, true);

	if (BrokenLifeSpan > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle,
			[Piece]()
			{
				if (Piece)
				{
					Piece->DestroyComponent();
				}
			},
			BrokenLifeSpan,
			false
		);
	}
}