#include "HealthPackSystem.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "TimerManager.h"
#include "Engine/World.h"

AHealthPackActor::AHealthPackActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	Collision->SetupAttachment(SceneRoot);
	Collision->SetSphereRadius(90.0f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECC_WorldDynamic);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	VerticalBar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VerticalBar"));
	VerticalBar->SetupAttachment(SceneRoot);
	VerticalBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HorizontalBar = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HorizontalBar"));
	HorizontalBar->SetupAttachment(SceneRoot);
	HorizontalBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(
		TEXT("/Engine/BasicShapes/Cube.Cube")
	);

	if (CubeMesh.Succeeded())
	{
		VerticalBar->SetStaticMesh(CubeMesh.Object);
		HorizontalBar->SetStaticMesh(CubeMesh.Object);
	}

	VerticalBar->SetRelativeScale3D(FVector(0.25f, 0.08f, 0.8f));
	HorizontalBar->SetRelativeScale3D(FVector(0.75f, 0.08f, 0.25f));

	VerticalBar->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
	HorizontalBar->SetRelativeLocation(FVector(0.0f, 0.0f, 60.0f));
}

void AHealthPackActor::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(
		this,
		&AHealthPackActor::OnOverlap
	);
}

void AHealthPackActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bWasPickedUp)
	{
		AddActorWorldRotation(
			FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f)
		);
	}
}

void AHealthPackActor::OnOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (!HasAuthority())
	{
		return;
	}

	if (bWasPickedUp || OtherActor == nullptr || OtherActor == this)
	{
		return;
	}

	if (OtherActor->GetClass()->ImplementsInterface(UHealableInterface::StaticClass()))
	{
		const bool bHealed = IHealableInterface::Execute_TryHeal(
			OtherActor,
			HealAmount
		);

		if (bHealed)
		{
			Pickup();
		}
	}
}

void AHealthPackActor::Pickup()
{
	if (bWasPickedUp)
	{
		return;
	}

	bWasPickedUp = true;

	if (PickupEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			PickupEffect,
			GetActorLocation(),
			GetActorRotation()
		);
	}

	if (PickupSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			GetWorld(),
			PickupSound,
			GetActorLocation()
		);
	}

	SetActorEnableCollision(false);
	SetActorHiddenInGame(true);

	OnPicked.Broadcast(this);

	Destroy();
}

AHealthPackSpawner::AHealthPackSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CurrentHealthPack = nullptr;
}

void AHealthPackSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (!HasAuthority())
	{
		return;
	}

	if (InitialSpawnDelay <= 0.0f)
	{
		SpawnHealthPack();
	}
	else
	{
		GetWorldTimerManager().SetTimer(
			SpawnTimerHandle,
			this,
			&AHealthPackSpawner::SpawnHealthPack,
			InitialSpawnDelay,
			false
		);
	}
}

void AHealthPackSpawner::SpawnHealthPack()
{
	if (!HasAuthority())
	{
		return;
	}

	if (CurrentHealthPack != nullptr || HealthPackClass == nullptr)
	{
		return;
	}

	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	if (SpawnPoints.Num() > 0)
	{
		const int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);

		if (SpawnPoints[RandomIndex])
		{
			SpawnLocation = SpawnPoints[RandomIndex]->GetActorLocation();
			SpawnRotation = SpawnPoints[RandomIndex]->GetActorRotation();
		}
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	CurrentHealthPack = GetWorld()->SpawnActor<AHealthPackActor>(
		HealthPackClass,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	if (CurrentHealthPack)
	{
		CurrentHealthPack->OnPicked.AddDynamic(
			this,
			&AHealthPackSpawner::OnHealthPackPicked
		);
	}
}

void AHealthPackSpawner::OnHealthPackPicked(AHealthPackActor* PickedPack)
{
	if (!HasAuthority())
	{
		return;
	}

	if (CurrentHealthPack == PickedPack)
	{
		CurrentHealthPack = nullptr;
	}

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle,
		this,
		&AHealthPackSpawner::SpawnHealthPack,
		RespawnDelay,
		false
	);
}
