#include "VineClimbActor.h"
#include "Components/BoxComponent.h"
#include "Sub/MyCharacter.h"

AVineClimbActor::AVineClimbActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	ClimbBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ClimbBox"));
	ClimbBox->SetupAttachment(SceneRoot);

	ClimbBox->SetBoxExtent(FVector(80.f, 80.f, 500.f));
	ClimbBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ClimbBox->SetCollisionObjectType(ECC_WorldDynamic);
	ClimbBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	ClimbBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ClimbBox->SetGenerateOverlapEvents(true);
	ClimbBox->OnComponentBeginOverlap.AddDynamic(this, &AVineClimbActor::OnClimbBoxBeginOverlap);
	ClimbBox->OnComponentEndOverlap.AddDynamic(this, &AVineClimbActor::OnClimbBoxEndOverlap);

#if WITH_EDITORONLY_DATA
	ClimbBox->ShapeColor = FColor::Green;
#endif
}

void AVineClimbActor::BeginPlay()
{
	Super::BeginPlay();
}

void AVineClimbActor::OnClimbBoxBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
	{
		Character->EnterVineClimb(this);
	}
}

void AVineClimbActor::OnClimbBoxEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	if (AMyCharacter* Character = Cast<AMyCharacter>(OtherActor))
	{
		Character->ExitVineClimb(this);
	}
}
