#include "BlackHoleActor.h"

#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#include "../../Sub/MyCharacter.h"

ABlackHoleActor::ABlackHoleActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	BlackHoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlackHoleMesh"));
	BlackHoleMesh->SetupAttachment(SceneRoot);
	BlackHoleMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PullRange = CreateDefaultSubobject<USphereComponent>(TEXT("PullRange"));
	PullRange->SetupAttachment(SceneRoot);
	PullRange->SetSphereRadius(PullRadius);
	PullRange->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PullRange->SetCollisionResponseToAllChannels(ECR_Ignore);
	PullRange->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ABlackHoleActor::BeginPlay()
{
	Super::BeginPlay();

	PullRange->SetSphereRadius(PullRadius);

	// 처음에는 보이는 상태로 시작
	// 실제 끌어당김은 SpaceMapController의 Phase에 따라 결정
	ShowBlackHole();
	DeactivateBlackHole();

	UE_LOG(LogTemp, Warning,
		TEXT("[BlackHoleActor] Visual BeginPlay / Active=%s / VisualOnly=true"),
		bActive ? TEXT("true") : TEXT("false"));
}

void ABlackHoleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bDrawDebug)
	{
		/*DrawDebugSphere(
			GetWorld(),
			GetActorLocation(),
			PullRadius,
			32,
			FColor::Purple,
			false,
			0.0f,
			0,
			3.0f
		);*/
	}

	if (!bActive)
	{
		return;
	}

	TArray<AActor*> Characters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), Characters);

	for (AActor* Actor : Characters)
	{
		AMyCharacter* Character = Cast<AMyCharacter>(Actor);

		if (!IsValid(Character))
		{
			continue;
		}

		UCharacterMovementComponent* Movement = Character->GetCharacterMovement();

		if (!IsValid(Movement))
		{
			continue;
		}

		FVector ToBlackHole = GetActorLocation() - Character->GetActorLocation();

		// 수평 방향으로만 끌어당김
		ToBlackHole.Z = 0.0f;

		const float Distance = ToBlackHole.Size();

		if (Distance > PullRadius || Distance < MinDistance)
		{
			continue;
		}

		const FVector PullDirection = ToBlackHole.GetSafeNormal();

		if (PullDirection.IsNearlyZero())
		{
			continue;
		}

		const float DistanceAlpha = 1.0f - FMath::Clamp(Distance / PullRadius, 0.0f, 1.0f);

		// 너무 멀리 있어도 약간은 끌리도록 최소 보정
		const float StrengthAlpha = FMath::Max(DistanceAlpha, 0.25f);

		const float FinalStrength = PullStrength * StrengthAlpha;

		// 1. 가만히 있는 지상 캐릭터도 끌려오도록 이동 입력 추가
		Character->AddMovementInput(PullDirection, 1.0f);

		// 2. 실제 속도에도 직접 영향을 줌
		FVector CurrentVelocity = Movement->Velocity;
		FVector HorizontalVelocity = FVector(CurrentVelocity.X, CurrentVelocity.Y, 0.0f);

		HorizontalVelocity += PullDirection * FinalStrength * DeltaTime;
		HorizontalVelocity = HorizontalVelocity.GetClampedToMaxSize(MaxPullSpeed);

		Movement->Velocity = FVector(
			HorizontalVelocity.X,
			HorizontalVelocity.Y,
			CurrentVelocity.Z
		);

		if (bDrawDebug)
		{
			/*DrawDebugLine(
				GetWorld(),
				Character->GetActorLocation(),
				GetActorLocation(),
				FColor::Red,
				false,
				0.0f,
				0,
				2.0f
			);*/
		}
	}
}

void ABlackHoleActor::ApplyVisibleState(bool bVisible)
{
	SetActorHiddenInGame(!bVisible);

	if (IsValid(BlackHoleMesh))
	{
		BlackHoleMesh->SetVisibility(bVisible, true);
	}
}


void ABlackHoleActor::ApplyActiveState()
{
	if (IsValid(PullRange))
	{
		PullRange->SetCollisionEnabled(bActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
	}
}

void ABlackHoleActor::ShowBlackHole()
{
	ApplyVisibleState(true);

	UE_LOG(LogTemp, Warning, TEXT("[BlackHoleActor] Show"));
}

void ABlackHoleActor::HideBlackHole()
{
	bActive = false;

	ApplyActiveState();
	ApplyVisibleState(false);

	UE_LOG(LogTemp, Warning, TEXT("[BlackHoleActor] Hide"));
}

void ABlackHoleActor::ActivateBlackHole()
{
	bActive = true;

	ApplyVisibleState(true);
	ApplyActiveState();

	UE_LOG(LogTemp, Warning, TEXT("[BlackHoleActor] Activated"));
}

void ABlackHoleActor::DeactivateBlackHole()
{
	bActive = false;

	ApplyActiveState();

	// 여기서는 숨기지 않음
	// Phase1에서 블랙홀은 보이지만 끌어당기지 않아야 하기 때문
	UE_LOG(LogTemp, Warning, TEXT("[BlackHoleActor] Deactivated"));
}
