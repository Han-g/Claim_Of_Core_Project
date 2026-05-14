#include "IceChillZone.h"

#include "Components/DecalComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraComponent.h"
#include "../../Sub/MyCharacter.h"

AIceChillZone::AIceChillZone()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ChillCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ChillCollision"));
	ChillCollision->SetupAttachment(Root);
	ChillCollision->SetSphereRadius(Radius);
	ChillCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ChillCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	ChillCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ChillCollision->SetGenerateOverlapEvents(true);
	ChillCollision->OnComponentBeginOverlap.AddDynamic(this, &AIceChillZone::OnChillBeginOverlap);
	ChillCollision->OnComponentEndOverlap.AddDynamic(this, &AIceChillZone::OnChillEndOverlap);

	ChillMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ChillMesh"));
	ChillMeshComponent->SetupAttachment(Root);
	ChillMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ChillMeshComponent->SetGenerateOverlapEvents(false);

	ChillDecalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("ChillDecal"));
	ChillDecalComponent->SetupAttachment(Root);
	ChillDecalComponent->DecalSize = FVector(128.f, Radius, Radius);

	ChillEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ChillEffect"));
	ChillEffectComponent->SetupAttachment(Root);
	ChillEffectComponent->SetAutoActivate(true);
}

void AIceChillZone::BeginPlay()
{
	Super::BeginPlay();

	ApplyVisualSettings();

	if (ZoneLifeTime > 0.f)
	{
		SetLifeSpan(ZoneLifeTime);
	}
}

void AIceChillZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DeltaTime <= 0.f)
	{
		return;
	}

	for (auto It = CharacterStayTimes.CreateIterator(); It; ++It)
	{
		AMyCharacter* Character = It.Key();
		if (!Character || Character->IsDead())
		{
			It.RemoveCurrent();
			continue;
		}

		It.Value() += DeltaTime;

		if (It.Value() >= FreezeBuildUpTime)
		{
			Character->ApplyFreeze();
			It.RemoveCurrent();
		}
	}
}

void AIceChillZone::OnChillBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (!Character || Character->IsDead())
	{
		return;
	}

	CharacterStayTimes.FindOrAdd(Character) = 0.f;
}

void AIceChillZone::OnChillEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
	{
		CharacterStayTimes.Remove(Character);
	}
}

void AIceChillZone::ApplyVisualSettings()
{
	if (ChillCollision)
	{
		ChillCollision->SetSphereRadius(Radius);
	}

	if (ChillMeshComponent)
	{
		if (ChillMesh)
		{
			ChillMeshComponent->SetStaticMesh(ChillMesh);
		}

		if (ChillMeshMaterial)
		{
			ChillMeshComponent->SetMaterial(0, ChillMeshMaterial);
		}
	}

	if (ChillDecalComponent)
	{
		ChillDecalComponent->DecalSize = FVector(128.f, Radius, Radius);
		if (ChillDecalMaterial)
		{
			ChillDecalComponent->SetDecalMaterial(ChillDecalMaterial);
		}
	}

	if (ChillEffectComponent && ChillVisualEffect)
	{
		ChillEffectComponent->SetAsset(ChillVisualEffect);
	}
}
