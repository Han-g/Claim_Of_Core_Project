#include "LargeDebrisActor.h"
#include "Components/StaticMeshComponent.h"
#include "Containers/Queue.h"
#include "TimerManager.h"

ALargeDebrisActor::ALargeDebrisActor()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorHiddenInGame(true);
}

void ALargeDebrisActor::BeginPlay()
{
	Super::BeginPlay();

	for (UStaticMeshComponent* MeshComp : ChunkMeshes)
	{
		if (!MeshComp) continue;

		MeshComp->SetNotifyRigidBodyCollision(true);
		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetEnableGravity(false);
		MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void ALargeDebrisActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bDebrisActivated || bLanded || !bUseActorFall)
	{
		return;
	}

	UpdateActorFall(DeltaTime);
}

void ALargeDebrisActor::PrepareDebris()
{
	PrepareFracture();

	bDebrisActivated = false;
	bLanded = false;
	CurrentFallSpeed = 0.f;

	SetActorHiddenInGame(true);

	for (UStaticMeshComponent* MeshComp : ChunkMeshes)
	{
		if (!MeshComp) continue;

		MeshComp->SetHiddenInGame(false);

		MeshComp->SetSimulatePhysics(false);
		MeshComp->SetEnableGravity(false);
		MeshComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
		MeshComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);
		MeshComp->SetMassOverrideInKg(NAME_None, 5000.f, true);
		MeshComp->SetLinearDamping(0.f);
		MeshComp->SetAngularDamping(0.f);
	}
}

void ALargeDebrisActor::ActivateDebris(float InitialImpulseStrength)
{
	if (bDebrisActivated || ChunkMeshes.Num() == 0)
	{
		return;
	}

	bDebrisActivated = true;
	bLanded = false;
	SetActorHiddenInGame(false);

	CurrentFallSpeed = FMath::Max(0.f, InitialImpulseStrength);

	BP_OnDebrisActivated();
}

void ALargeDebrisActor::UpdateActorFall(float DeltaTime)
{
	CurrentFallSpeed += GravityAcceleration * DeltaTime;
	CurrentFallSpeed = FMath::Min(CurrentFallSpeed, MaxFallSpeed);

	FVector Origin, Extent;
	GetActorBounds(false, Origin, Extent);

	FVector NewLocation = GetActorLocation();
	NewLocation.Z -= CurrentFallSpeed * DeltaTime;

	const float TargetGroundZ = GroundZ + GroundOffset;
	const float BottomZAfterMove = NewLocation.Z - Extent.Z;

	if (BottomZAfterMove <= TargetGroundZ)
	{
		NewLocation.Z = TargetGroundZ + Extent.Z;
		SetActorLocation(NewLocation, true);
		LandAndFracture();
		return;
	}

	SetActorLocation(NewLocation, true);
}

void ALargeDebrisActor::LandAndFracture()
{
	if (bLanded)
	{
		return;
	}

	bLanded = true;
	BP_OnDebrisLanded();

	const float ImpactSpeed = CurrentFallSpeed;
	CurrentFallSpeed = 0.f;

	if (ImpactSpeed < MinBreakSpeed)
	{
		return;
	}

	BreakInitialBottomChunks(ImpactSpeed);
}

void ALargeDebrisActor::GetBottomChunks(TArray<int32>& OutChunkIndices) const
{
	OutChunkIndices.Empty();

	if (ChunkMeshes.Num() == 0)
	{
		return;
	}

	float MinY = TNumericLimits<float>::Max();

	for (int32 i = 0; i < ChunkMeshes.Num(); ++i)
	{
		const UStaticMeshComponent* MeshComp = ChunkMeshes[i];
		if (!MeshComp) continue;
		if (ChunkData.IsValidIndex(i) && ChunkData[i].bBroken) continue;

		MinY = FMath::Min(MinY, MeshComp->GetComponentLocation().Z);
	}

	for (int32 i = 0; i < ChunkMeshes.Num(); ++i)
	{
		const UStaticMeshComponent* MeshComp = ChunkMeshes[i];
		if (!MeshComp) continue;
		if (ChunkData.IsValidIndex(i) && ChunkData[i].bBroken) continue;

		const float ChunkY = MeshComp->GetComponentLocation().Z;
		if (FMath::Abs(ChunkY - MinY) <= BottomChunkTolerance)
		{
			OutChunkIndices.Add(i);
		}
	}

	OutChunkIndices.Sort([this](int32 A, int32 B)
		{
			const UStaticMeshComponent* MeshA = ChunkMeshes.IsValidIndex(A) ? ChunkMeshes[A] : nullptr;
			const UStaticMeshComponent* MeshB = ChunkMeshes.IsValidIndex(B) ? ChunkMeshes[B] : nullptr;

			if (!MeshA || !MeshB) return A < B;

			return MeshA->GetComponentLocation().Z < MeshB->GetComponentLocation().Z;
		});
}

void ALargeDebrisActor::BreakInitialBottomChunks(float ImpactSpeed)
{
	TArray<int32> BottomChunks;
	GetBottomChunks(BottomChunks);

	if (BottomChunks.Num() == 0)
	{
		return;
	}

	const float DamageAmount = ImpactSpeed * SpeedToDamageScale;
	const int32 BreakCount = FMath::Clamp(
		FMath::CeilToInt(ImpactSpeed / 300.f),
		1,
		MaxInitialBreakCount
	);

	const int32 CountToBreak = FMath::Min(BreakCount, BottomChunks.Num());

	for (int32 i = 0; i < CountToBreak; ++i)
	{
		const int32 ChunkIndex = BottomChunks[i];
		ApplyDamageToChunk(ChunkIndex, DamageAmount * 0.4);
	}
}

void ALargeDebrisActor::BreakChunk(int32 ChunkIndex, bool bFromImpact)
{
	if (!IsValidChunkIndex(ChunkIndex)) return;
	if (ChunkData[ChunkIndex].bBroken) return;

	ChunkData[ChunkIndex].bBroken = true;

	if (UStaticMeshComponent* MeshComp = ChunkMeshes[ChunkIndex])
	{
		MeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		MeshComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
		MeshComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

		MeshComp->SetSimulatePhysics(true);
		MeshComp->SetEnableGravity(true);
		MeshComp->WakeAllRigidBodies();
		MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
		MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
		MeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

		MeshComp->SetMassOverrideInKg(NAME_None, 200.f, true);
		MeshComp->SetLinearDamping(0.15f);
		MeshComp->SetAngularDamping(1.5f);

		MeshComp->SetPhysicsLinearVelocity(FVector(0.f, 0.f, -80.f));

		FVector Vel = MeshComp->GetPhysicsLinearVelocity();
		Vel.Z = FMath::Min(Vel.Z, 0.f);
		MeshComp->SetPhysicsLinearVelocity(Vel);
	}

	BP_OnChunkBroken(ChunkIndex);
	OnChunkBrokenInternal(ChunkIndex, bFromImpact);
}

void ALargeDebrisActor::DropUnsupportedChunks()
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
				MeshComp->SetPhysicsLinearVelocity(FVector::ZeroVector);

				MeshComp->SetPhysicsAngularVelocityInDegrees(FVector::ZeroVector);

				MeshComp->SetSimulatePhysics(true);
				MeshComp->SetEnableGravity(true);
				MeshComp->WakeAllRigidBodies();

				MeshComp->SetCollisionObjectType(ECC_PhysicsBody);
				MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
				FTimerHandle TempHandle;
				UStaticMeshComponent* LocalMesh = MeshComp;

				MeshComp->SetMassOverrideInKg(NAME_None, 200.f, true);
				MeshComp->SetLinearDamping(0.15f);
				MeshComp->SetAngularDamping(1.5f);

				MeshComp->SetPhysicsLinearVelocity(FVector(0.f, 0.f, -80.f));

				FVector Vel = MeshComp->GetPhysicsLinearVelocity();
				Vel.Y = FMath::Min(Vel.Z, 0.f);
				MeshComp->SetPhysicsLinearVelocity(Vel);

			}

			BP_OnChunkBroken(i);
		}
	}
}

void ALargeDebrisActor::OnChunkBrokenInternal(int32 BrokenChunkIndex, bool bFromImpact)
{
	DropUnsupportedChunks();

	if (bFreezeAfterChainReaction)
	{
		FTimerHandle TempHandle;
		GetWorldTimerManager().SetTimer(
			TempHandle,
			this,
			&ALargeDebrisActor::FreezeRemainingChunks,
			4.0f,
			false
		);
	}
}