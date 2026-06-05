#include "HealPackPickup.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "../Sub/MyCharacter.h"

AHealPackPickup::AHealPackPickup()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	PickupCollision = CreateDefaultSubobject<USphereComponent>(TEXT("PickupCollision"));
	SetRootComponent(PickupCollision);
	PickupCollision->SetSphereRadius(120.f);
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PickupCollision->OnComponentBeginOverlap.AddDynamic(this, &AHealPackPickup::OnPickupBeginOverlap);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	PickupMesh->SetupAttachment(PickupCollision);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (DefaultMesh.Succeeded())
	{
		PickupMesh->SetStaticMesh(DefaultMesh.Object);
		PickupMesh->SetRelativeScale3D(FVector(0.45f, 0.45f, 0.25f));
	}
}

void AHealPackPickup::OnPickupBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (bConsumed || !HasAuthority())
	{
		return;
	}

	AMyCharacter* Character = Cast<AMyCharacter>(OtherActor);
	if (!Consume(Character))
	{
		return;
	}

	Destroy();
}

bool AHealPackPickup::Consume(AMyCharacter* Character)
{
	if (bConsumed || !Character || Character->IsDead())
	{
		return false;
	}

	bConsumed = true;
	Character->Heal(HealAmount);
	return true;
}
