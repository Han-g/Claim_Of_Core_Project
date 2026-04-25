#include "SmallDebrisActor.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "../Sub/MyCharacter.h"

ASmallDebrisActor::ASmallDebrisActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	CollisionComp->SetupAttachment(Root);
	CollisionComp->SetSphereRadius(20.f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComp->SetCollisionObjectType(ECC_WorldDynamic);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Block);
	CollisionComp->SetNotifyRigidBodyCollision(true);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(CollisionComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComp->SetCollisionObjectType(ECC_WorldDynamic);
	MeshComp->SetCollisionResponseToAllChannels(ECR_Block);
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetNotifyRigidBodyCollision(true);

	Tags.AddUnique(TEXT("FallingDebris"));
}

void ASmallDebrisActor::BeginPlay()
{
	Super::BeginPlay();

	if (CollisionComp)
	{
		CollisionComp->OnComponentHit.AddDynamic(this, &ASmallDebrisActor::OnDebrisHit);
	}

	if (MeshComp)
	{
		MeshComp->OnComponentHit.AddDynamic(this, &ASmallDebrisActor::OnDebrisHit);
	}
}

void ASmallDebrisActor::OnDebrisHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{

	if (!OtherActor || OtherActor == this)
	{
		return;
	}

	// 플레이어 맞았을 때 데미지
	if (OtherActor->IsA<AMyCharacter>())
	{
		AMyCharacter* Player = Cast<AMyCharacter>(OtherActor);

		Player->ApplyDamage(Damage);
		DestroySelf();

		return;
	}

	StartDestroyTimer();
}

void ASmallDebrisActor::StartDestroyTimer()
{
	if (GetWorldTimerManager().IsTimerActive(TimerHandle_Destroy))
	{
		return;
	}

	// 충돌 더 안 나게 정리
	if (CollisionComp)
	{
		CollisionComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	if (MeshComp)
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComp->SetSimulatePhysics(false);
	}

	GetWorldTimerManager().SetTimer(
		TimerHandle_Destroy,
		this,
		&ASmallDebrisActor::DestroySelf,
		DestroyDelayAfterHitGround,
		false
	);
}

void ASmallDebrisActor::DestroySelf()
{
	Destroy();
}