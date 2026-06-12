// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/Building/AUmbrellaItem.h"

#include "Components/MeshComponent.h"

AAUmbrellaItem::AAUmbrellaItem()
{
	ItemAnimPoseType = EItemAnimPoseType::Umbrella;
}

void AAUmbrellaItem::BeginPlay()
{
	Super::BeginPlay();

	if (VisualScaleMultiplier <= 0.f)
	{
		return;
	}

	TArray<UMeshComponent*> MeshComponents;
	GetComponents<UMeshComponent>(MeshComponents);

	TSet<const USceneComponent*> MeshComponentSet;
	for (UMeshComponent* MeshComp : MeshComponents)
	{
		if (MeshComp)
		{
			MeshComponentSet.Add(MeshComp);
		}
	}

	for (UMeshComponent* MeshComp : MeshComponents)
	{
		if (!MeshComp)
		{
			continue;
		}

		if (MeshComponentSet.Contains(MeshComp->GetAttachParent()))
		{
			continue;
		}

		MeshComp->SetRelativeScale3D(MeshComp->GetRelativeScale3D() * VisualScaleMultiplier);
	}
}
