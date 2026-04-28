#include "PreFracturedActor.h"
#include "GameState/InGame_GameState.h"

#include "Components/StaticMeshComponent.h"
#include "Containers/Queue.h"
#include "TimerManager.h"

APreFracturedActor::APreFracturedActor()
{
	PrimaryActorTick.bCanEverTick = false;

	NeighborDistanceThreshold = 600.f;
	AnchorBottomTolerance = 300.f;
}

void APreFracturedActor::BeginPlay()
{
	Super::BeginPlay();

	CollectChunkMeshes();
	InitializeChunkData();
	InitializeGameState();

	if (CachedGameState)
	{
		if (CachedGameState->IsGameplayActivated())
		{
			ActivateFractureRuntime();
		}
		else
		{
			CachedGameState->OnGameplayActivated.AddUObject(
				this,
				&APreFracturedActor::HandleGameplayActivated
			);
		}
	}

	/*if (bAutoBuildGraph)
	{
		AutoBuildNeighborGraph();
	}

	if (bAutoSetAnchored)
	{
		AutoSetAnchoredChunks();
	}

	PrepareFracture();*/
}

void APreFracturedActor::InitializeGameState()
{
	if (CachedGameState)
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		CachedGameState = World->GetGameState<AInGame_GameState>();
	}
}

void APreFracturedActor::HandleGameplayActivated()
{
	ActivateFractureRuntime();
}

void APreFracturedActor::ActivateFractureRuntime()
{
	if (bFractureRuntimeActivated)
	{
		return;
	}

	bFractureRuntimeActivated = true;

	if (bAutoBuildGraph)
	{
		AutoBuildNeighborGraph();
	}

	if (bAutoSetAnchored)
	{
		AutoSetAnchoredChunks();
	}

	PrepareFracture();
	ActivateBreakable();
}

void APreFracturedActor::CollectChunkMeshes()
{
	ChunkMeshes.Empty();

	TArray<UStaticMeshComponent*> FoundMeshes;
	GetComponents<UStaticMeshComponent>(FoundMeshes);

	for (UStaticMeshComponent* MeshComp : FoundMeshes)
	{
		if (!MeshComp) continue;

		if (MeshComp->GetName().Contains(ChunkTag.ToString()))
		{
			ChunkMeshes.Add(MeshComp);
		}
	}

	ChunkMeshes.Sort([](const UStaticMeshComponent& A, const UStaticMeshComponent& B)
		{
			return A.GetName() < B.GetName();
		});
}

void APreFracturedActor::InitializeChunkData()
{
	if (ChunkData.Num() < ChunkMeshes.Num())
	{
		const int32 OldNum = ChunkData.Num();
		ChunkData.SetNum(ChunkMeshes.Num());

		for (int32 i = OldNum; i < ChunkData.Num(); ++i)
		{
			ChunkData[i].ChunkIndex = i;
		}
	}

	for (int32 i = 0; i < ChunkData.Num(); ++i)
	{
		ChunkData[i].ChunkIndex = i;
	}
}

bool APreFracturedActor::IsValidChunkIndex(int32 ChunkIndex) const
{
	return ChunkMeshes.IsValidIndex(ChunkIndex) && ChunkData.IsValidIndex(ChunkIndex);
}

int32 APreFracturedActor::FindChunkIndexByComponent(const UPrimitiveComponent* HitComp) const
{
	for (int32 i = 0; i < ChunkMeshes.Num(); ++i)
	{
		if (ChunkMeshes[i] == HitComp)
		{
			return i;
		}
	}
	return INDEX_NONE;
}

void APreFracturedActor::PrepareFracture()
{
	for (int32 i = 0; i < ChunkMeshes.Num(); ++i)
	{
		if (UStaticMeshComponent* MeshComp = ChunkMeshes[i])
		{
			MeshComp->SetSimulatePhysics(false);
			MeshComp->SetEnableGravity(false);
			MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
		}

		if (ChunkData.IsValidIndex(i))
		{
			ChunkData[i].CurrentDamage = 0.f;
			ChunkData[i].bBroken = false;
		}
	}
}

void APreFracturedActor::ApplyDamageToChunk(int32 ChunkIndex, float DamageAmount)
{
	if (!IsValidChunkIndex(ChunkIndex) || ChunkData[ChunkIndex].bBroken || !bFractureRuntimeActivated) {
		return; 
	}

	// 1. 직접 맞은 청크 데미지
	ChunkData[ChunkIndex].CurrentDamage += DamageAmount;

	if (ChunkData[ChunkIndex].CurrentDamage >= ChunkData[ChunkIndex].BreakThreshold)
	{
		BreakChunk(ChunkIndex, true);
	}

	// 2. 이웃 청크에 일부 데미지 전파
	const float NeighborDamage = DamageAmount * NeighborDamageRatio;

	if (NeighborDamage <= 0.f)
	{
		return;
	}

	for (int32 NeighborIndex : ChunkData[ChunkIndex].Neighbors)
	{
		if (!IsValidChunkIndex(NeighborIndex)) continue;
		if (ChunkData[NeighborIndex].bBroken) continue;

		ChunkData[NeighborIndex].CurrentDamage += NeighborDamage;

		if (ChunkData[NeighborIndex].CurrentDamage >= ChunkData[NeighborIndex].BreakThreshold)
		{
			BreakChunk(NeighborIndex, false);
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("ApplyDamageToChunk: Index=%d Damage=%f"), ChunkIndex, DamageAmount);

}
void APreFracturedActor::BreakChunk(int32 ChunkIndex, bool bFromImpact)
{
	if (!IsValidChunkIndex(ChunkIndex) || ChunkData[ChunkIndex].bBroken || !bFractureRuntimeActivated) {
		return; 
	}

	ChunkData[ChunkIndex].bBroken = true;

	if (UStaticMeshComponent* MeshComp = ChunkMeshes[ChunkIndex])
	{
		MeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetEnableGravity(true);
		MeshComp->WakeAllRigidBodies();

		if (bFromImpact)
		{
			const FVector ScatterDir = FVector(
				FMath::FRandRange(-1.f, 1.f),
				FMath::FRandRange(-1.f, 1.f),
				FMath::FRandRange(0.1f, 0.5f)
			).GetSafeNormal();

			//MeshComp->AddImpulse(ScatterDir * ChainScatterImpulse, NAME_None, true);
		}
	}

	BP_OnChunkBroken(ChunkIndex);
	OnChunkBrokenInternal(ChunkIndex, bFromImpact);
	UE_LOG(LogTemp, Warning, TEXT("BreakChunk called: %d"), ChunkIndex);
}

void APreFracturedActor::OnChunkBrokenInternal(int32 BrokenChunkIndex, bool bFromImpact)
{
	DropUnsupportedChunks();

	if (bFreezeAfterChainReaction)
	{
		FTimerHandle TempHandle;
		GetWorldTimerManager().SetTimer(
			TempHandle,
			this,
			&APreFracturedActor::FreezeRemainingChunks,
			FreezeDelay,
			false
		);
	}
}

void APreFracturedActor::DropUnsupportedChunks()
{
	TSet<int32> SupportedSet;
	TQueue<int32> Queue;

	for (int32 i = 0; i < ChunkData.Num(); ++i)
	{
		if (ChunkData[i].bBroken) continue;

		if (ChunkData[i].bAnchored)
		{
			SupportedSet.Add(i);
			Queue.Enqueue(i);
		}
	}

	while (!Queue.IsEmpty())
	{
		int32 CurrentIndex;
		Queue.Dequeue(CurrentIndex);

		for (int32 NeighborIndex : ChunkData[CurrentIndex].Neighbors)
		{
			if (!ChunkData.IsValidIndex(NeighborIndex)) continue;
			if (ChunkData[NeighborIndex].bBroken) continue;
			if (SupportedSet.Contains(NeighborIndex)) continue;

			SupportedSet.Add(NeighborIndex);
			Queue.Enqueue(NeighborIndex);
		}
	}

	for (int32 i = 0; i < ChunkData.Num(); ++i)
	{
		if (ChunkData[i].bBroken) continue;
		if (ChunkData[i].bAnchored) continue;

		if (!SupportedSet.Contains(i))
		{
			ChunkData[i].bBroken = true;

			if (UStaticMeshComponent* MeshComp = ChunkMeshes[i])
			{
				MeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

				MeshComp->SetSimulatePhysics(true);
				MeshComp->SetEnableGravity(true);
				MeshComp->WakeAllRigidBodies();

				const FVector ScatterDir = FVector(
					FMath::FRandRange(-1.f, 1.f),
					FMath::FRandRange(-1.f, 1.f),
					FMath::FRandRange(0.1f, 0.5f)
				).GetSafeNormal();

				MeshComp->AddImpulse(ScatterDir * ChainScatterImpulse, NAME_None, true);
			}

			BP_OnChunkBroken(i);
		}
	}
}

void APreFracturedActor::FreezeRemainingChunks()
{
	for (UStaticMeshComponent* MeshComp : ChunkMeshes)
	{
		if (!MeshComp) continue;

		MeshComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
		MeshComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetEnableGravity(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	BP_OnChainReactionFinished();
}

void APreFracturedActor::OnBrokenInternal()
{
	// 필요하면 전체 파괴 처리용 확장 지점
}

void APreFracturedActor::AutoBuildNeighborGraph()
{
	// 기존 Neighbors 초기화
	for (FPreFracturedChunkData& Data : ChunkData)
	{
		Data.Neighbors.Empty();
	}

	for (int32 i = 0; i < ChunkMeshes.Num(); ++i)
	{
		UStaticMeshComponent* MeshA = ChunkMeshes[i];
		if (!MeshA) continue;

		const FVector LocA = MeshA->Bounds.Origin;

		for (int32 j = i + 1; j < ChunkMeshes.Num(); ++j)
		{
			UStaticMeshComponent* MeshB = ChunkMeshes[j];
			if (!MeshB) continue;

			const FVector LocB = MeshB->Bounds.Origin;
			const float Dist = FVector::Dist(LocA, LocB);

			if (Dist <= NeighborDistanceThreshold)
			{
				ChunkData[i].Neighbors.Add(j);
				ChunkData[j].Neighbors.Add(i);
			}
		}
	}

	for (int32 i = 0; i < ChunkData.Num(); ++i)
	{
		FString NeighborsStr;

		for (int32 N : ChunkData[i].Neighbors)
		{
			NeighborsStr += FString::Printf(TEXT("%d "), N);
		}

		UE_LOG(LogTemp, Warning, TEXT("Chunk %d -> [%s]"), i, *NeighborsStr);
	}

#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("AutoBuildNeighborGraph Done"));
	for (int32 i = 0; i < ChunkData.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Chunk %d Neighbor Count = %d"), i, ChunkData[i].Neighbors.Num());
	}
#endif
}

void APreFracturedActor::AutoSetAnchoredChunks()
{
	if (ChunkMeshes.Num() == 0)
	{
		return;
	}

	float MinZ = TNumericLimits<float>::Max();

	for (int32 i = 0; i < ChunkMeshes.Num(); ++i)
	{
		UStaticMeshComponent* MeshComp = ChunkMeshes[i];
		if (!MeshComp) continue;

		const FVector Loc = ChunkMeshes[i]->Bounds.Origin;
		UE_LOG(LogTemp, Warning, TEXT("Chunk %d Loc = X:%f Y:%f Z:%f"),
			i, Loc.X, Loc.Y, Loc.Z);
	}

	for (int32 i = 0; i < ChunkData.Num(); ++i)
	{
		if (!ChunkMeshes.IsValidIndex(i) || !ChunkMeshes[i]) continue;

		const float ChunkZ = ChunkMeshes[i]->Bounds.Origin.Z;
	}

#if WITH_EDITOR
	UE_LOG(LogTemp, Warning, TEXT("AutoSetAnchoredChunks Done"));
	for (int32 i = 0; i < ChunkData.Num(); ++i)
	{
		UE_LOG(LogTemp, Warning, TEXT("Chunk %d Anchored = %s"), i, ChunkData[i].bAnchored ? TEXT("true") : TEXT("false"));
	}
#endif
}