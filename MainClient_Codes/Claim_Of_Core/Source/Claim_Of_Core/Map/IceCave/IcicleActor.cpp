#include "IcicleActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"

AIcicleActor::AIcicleActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	IcicleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("IcicleMesh"));
	IcicleMesh->SetupAttachment(Root);
	IcicleMesh->SetSimulatePhysics(false);
	IcicleMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	IcicleMesh->SetCollisionProfileName(TEXT("BlockAll"));

	WarningRange = CreateDefaultSubobject<USphereComponent>(TEXT("WarningRange"));
	WarningRange->SetupAttachment(Root);
	WarningRange->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WarningRange->SetSphereRadius(100.f);

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageCollision"));
	DamageCollision->SetupAttachment(IcicleMesh);
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DamageCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	DamageCollision->SetBoxExtent(FVector(20.f, 20.f, 60.f));

	IcicleMesh->OnComponentHit.AddDynamic(this, &AIcicleActor::OnIcicleHit);
}

void AIcicleActor::BeginPlay()
{
	Super::BeginPlay();
}

void AIcicleActor::StartWarning()
{
	if (CurrentState != EIcicleState::Idle)
	{
		return;
	}

	CurrentState = EIcicleState::Warning;

	BP_OnWarningStarted();

	GetWorldTimerManager().SetTimer(
		WarningTimerHandle,
		this,
		&AIcicleActor::StartFalling,
		WarningTime,
		false
	);
}

void AIcicleActor::StartFalling()
{
	if (CurrentState != EIcicleState::Warning)
	{
		return;
	}

	CurrentState = EIcicleState::Falling;

	IcicleMesh->SetSimulatePhysics(true);
	IcicleMesh->SetEnableGravity(true);
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	BP_OnFallingStarted();
}

void AIcicleActor::OnIcicleHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit
)
{
	if (CurrentState != EIcicleState::Falling)
	{
		return;
	}

	// 캐릭터 맞았을 때 간단 처리
	if (OtherActor && OtherActor != this)
	{
		if (ACharacter* HitCharacter = Cast<ACharacter>(OtherActor))
		{
			UE_LOG(LogTemp, Warning, TEXT("Icicle hit character: %s / Damage: %.1f"), *HitCharacter->GetName(), Damage);

			// 여기서 나중에 ApplyDamage 붙이면 됨
			// UGameplayStatics::ApplyDamage(...)
		}
	}

	BreakIcicle();
}

void AIcicleActor::BreakIcicle()
{
	if (CurrentState == EIcicleState::Broken)
	{
		return;
	}

	CurrentState = EIcicleState::Broken;

	IcicleMesh->SetSimulatePhysics(false);
	IcicleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BP_OnBroken();

	if (bDestroyAfterHitGround)
	{
		SetLifeSpan(DestroyDelay);
	}
}