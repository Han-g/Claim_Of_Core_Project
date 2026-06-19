// Fill out your copyright notice in the Description page of Project Settings.


#include "Map/SkyIsland/SkyCloudPlatform.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMesh.h"
#include "UObject/ConstructorHelpers.h"

#include "Sub/MyCharacter.h"
#include "UI/NetworkInstance.h"

// Sets default values
ASkyCloudPlatform::ASkyCloudPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	CloudMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CloudMesh"));
	CloudMeshComponent->SetupAttachment(Root);
	CloudMeshComponent->SetMobility(EComponentMobility::Movable);
	CloudMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CloudMeshComponent->SetCollisionObjectType(ECC_WorldStatic);
	CloudMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (DefaultMesh.Succeeded())
	{
		CloudMeshComponent->SetStaticMesh(DefaultMesh.Object);
		CloudMeshComponent->SetRelativeScale3D(FVector(6.f, 6.f, 0.35f));
	}
}

void ASkyCloudPlatform::NotifyPlayerStanding(AMyCharacter* StandingCharacter)
{
	if (!bPlatformVisible || !StandingCharacter || StandingCharacter->IsDead())
	{
		return;
	}

	StandingCharacters.Add(StandingCharacter);
}

void ASkyCloudPlatform::NotifyPlayerLanded(AMyCharacter* LandingCharacter)
{
	if (!bPlatformVisible || !LandingCharacter || LandingCharacter->IsDead())
	{
		return;
	}

	TriggerLandingBounce();
}

// Called when the game starts or when spawned
void ASkyCloudPlatform::BeginPlay()
{
	Super::BeginPlay();

	InitializeGameState();
	Tags.Add(TEXT("CloudPlatform"));

	InitialScale = GetActorScale3D();
	InitialLocation = GetActorLocation();

	MotionElapsed = bRandomizeMotionPhase
		? FMath::FRandRange(0.f, 2.f * PI)
		: MotionPhaseOffset;

	LandingBounceElapsed = LandingBounceDuration;

	OriginalMaterials.Empty();
	if (CloudMeshComponent)
	{
		const int32 MaterialCount = CloudMeshComponent->GetNumMaterials();
		for (int32 i = 0; i < MaterialCount; ++i)
		{
			OriginalMaterials.Add(CloudMeshComponent->GetMaterial(i));
		}
	}

	ShowPlatform();

	if (bUseAutoCycle)
	{
		ApplyInitialCycleOffset();
	}
}

// Called every frame
void ASkyCloudPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DeltaTime <= 0.f)
	{
		return;
	}

	InitializeGameState();
	UpdateCloudMotion(DeltaTime);
	UpdateLandingBounce(DeltaTime);

	if (bPlatformVisible)
	{
		UpdateOneWayCollision();
		UpdateVisible(DeltaTime);
	}
	else
	{
		UpdateHidden(DeltaTime);
	}
}

void ASkyCloudPlatform::UpdateOneWayCollision()
{
	if (!CloudMeshComponent || !bPlatformVisible)
	{
		return;
	}

	if (!bUseOneWayCollision)
	{
		CloudMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		return;
	}

	AMyCharacter* LocalCharacter = Cast<AMyCharacter>(
		UGameplayStatics::GetPlayerCharacter(this, 0)
	);

	const bool bShouldBlock =
		LocalCharacter &&
		!LocalCharacter->IsDead() &&
		ShouldBlockPawnCollisionForCharacter(LocalCharacter);

	CloudMeshComponent->SetCollisionResponseToChannel(
		ECC_Pawn,
		bShouldBlock ? ECR_Block : ECR_Ignore
	);
}

bool ASkyCloudPlatform::ShouldBlockPawnCollisionForCharacter(const AMyCharacter* Character)
{
	if (!Character || !CloudMeshComponent)
	{
		return false;
	}

	const UCapsuleComponent* Capsule = Character->GetCapsuleComponent();
	const UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement();

	if (!Capsule || !MoveComp)
	{
		return false;
	}

	const FBox PlatformBox = CloudMeshComponent->Bounds.GetBox();
	const float PlatformBottomZ = PlatformBox.Min.Z;
	const float PlatformTopZ = PlatformBox.Max.Z;

	const float CharacterBottomZ =
		Character->GetActorLocation().Z - Capsule->GetScaledCapsuleHalfHeight();

	const float CharacterTopZ =
		Character->GetActorLocation().Z + Capsule->GetScaledCapsuleHalfHeight();

	const bool bCharacterInPlatformHeight =
		CharacterTopZ >= PlatformBottomZ &&
		CharacterBottomZ <= PlatformTopZ;

	if (!bWasLocalCharacterInPlatformHeight && bCharacterInPlatformHeight)
	{
		bLocalCharacterEnteredPlatformFromBelow =
			CharacterBottomZ < PlatformBottomZ;
	}

	bWasLocalCharacterInPlatformHeight = bCharacterInPlatformHeight;

	const bool bCharacterAbovePlatform =
		CharacterBottomZ >= PlatformTopZ - OneWayTopTolerance;

	const bool bDescendingOrStanding =
		MoveComp->Velocity.Z <= OneWayVelocityTolerance;

	if (bLocalCharacterEnteredPlatformFromBelow && !bCharacterAbovePlatform)
	{
		return false;
	}

	if (bCharacterAbovePlatform && bDescendingOrStanding)
	{
		bLocalCharacterEnteredPlatformFromBelow = false;
		return true;
	}

	return false;
}

void ASkyCloudPlatform::UpdateVisible(float DeltaTime)
{
	const float CurrentVisibleDuration = GetCurrentVisibleDuration();
	if (bUseAutoCycle)
	{
		VisibleElapsed += DeltaTime;
	}

	const int32 StandingPlayerCount = GetStandingPlayerCount();
	if (StandingPlayerCount > 0 && StandingBreakTime > 0.f)
	{
		StandingProgress += (DeltaTime / StandingBreakTime) * StandingPlayerCount;
	}
	else
	{
		StandingProgress = FMath::Max(0.f, StandingProgress - DeltaTime);
	}

	StandingCharacters.Empty();

	const float StandingWarningThreshold = StandingBreakTime > 0.f
		? FMath::Clamp(1.f - (WarningDuration / StandingBreakTime), 0.f, 1.f)
		: 1.f;

	const bool bShouldWarnByStanding = StandingProgress >= StandingWarningThreshold;
	const bool bShouldWarnByAutoCycle = bUseAutoCycle &&
		VisibleElapsed >= FMath::Max(0.f, CurrentVisibleDuration - WarningDuration);

	if (!bWarningActive && (bShouldWarnByStanding || bShouldWarnByAutoCycle))
	{
		//ActivateWarning();
		RequestNetworkState(2);
	}

	if (StandingProgress >= 1.f || (bUseAutoCycle && VisibleElapsed >= CurrentVisibleDuration))
	{
		//HidePlatform();
		RequestNetworkState(0);
	}
}

void ASkyCloudPlatform::UpdateHidden(float DeltaTime)
{
	HiddenElapsed += DeltaTime;

	if (HiddenElapsed >= HiddenDuration)
	{
		//ShowPlatform();
		RequestNetworkState(1);
	}
}

void ASkyCloudPlatform::ShowPlatform()
{
	bPlatformVisible = true;
	bWarningActive = false;
	VisibleElapsed = 0.f;
	HiddenElapsed = 0.f;
	StandingProgress = 0.f;
	StandingCharacters.Empty();

	ApplyPlatformEnabled(true);
	ApplyStableVisual();

	UE_LOG(LogTemp, Warning, TEXT("[SkyCloudPlatform] Show: %s"), *GetName());
}

void ASkyCloudPlatform::HidePlatform()
{
	if (!bPlatformVisible)
	{
		return;
	}

	bPlatformVisible = false;
	bWarningActive = false;
	VisibleElapsed = 0.f;
	HiddenElapsed = 0.f;
	StandingProgress = 0.f;
	StandingCharacters.Empty();

	ApplyPlatformEnabled(false);

	UE_LOG(LogTemp, Warning, TEXT("[SkyCloudPlatform] Hide: %s"), *GetName());
}

void ASkyCloudPlatform::ActivateWarning()
{
	bWarningActive = true;
	ApplyWarningVisual();

	UE_LOG(LogTemp, Warning, TEXT("[SkyCloudPlatform] Warning: %s"), *GetName());
}

void ASkyCloudPlatform::ApplyPlatformEnabled(bool bEnabled)
{
	if (!CloudMeshComponent)
	{
		return;
	}

	CloudMeshComponent->SetVisibility(bEnabled, true);
	CloudMeshComponent->SetHiddenInGame(!bEnabled, true);
	CloudMeshComponent->SetCollisionEnabled(
		bEnabled ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision
	);

	if (bEnabled)
	{
		UpdateOneWayCollision();
	}
}

float ASkyCloudPlatform::GetCurrentVisibleDuration() const
{
	float DurationMultiplier = 1.f;

	if (CachedGameState)
	{
		if (CachedGameState->CurrentPhase == EMapPhase::Phase2)
		{
			DurationMultiplier = Phase2DurationMultiplier;
		}
		else if (CachedGameState->CurrentPhase == EMapPhase::Phase3)
		{
			DurationMultiplier = Phase3DurationMultiplier;
		}
	}

	return FMath::Max(0.1f, VisibleDuration * DurationMultiplier);
}

void ASkyCloudPlatform::UpdateCloudMotion(float DeltaTime)
{
	if (!bUseCloudMotion)
	{
		return;
	}

	MotionElapsed += DeltaTime * MotionSpeed;

	const FVector MotionOffset(
		FMath::Sin(MotionElapsed) * MotionAmplitude.X,
		FMath::Cos(MotionElapsed * 0.73f) * MotionAmplitude.Y,
		FMath::Sin(MotionElapsed * 1.31f) * MotionAmplitude.Z);

	SetActorLocation(InitialLocation + MotionOffset);
}

void ASkyCloudPlatform::RequestNetworkState(int32 EventState)
{
	if (bWaitingNetworkState)
	{
		return;
	}

	if (CloudPlatformIndex < 0)
	{
		ApplyNetworkState(EventState);
		return;
	}

	if (UNetworkInstance* NetInst = GetGameInstance<UNetworkInstance>())
	{
		bWaitingNetworkState = true;

		constexpr int32 CloudPlatformType = 6;
		NetInst->RequestObjectHit(CloudPlatformIndex, CloudPlatformType, -1, EventState);
		return;
	}

	ApplyNetworkState(EventState);
}

void ASkyCloudPlatform::ApplyNetworkState(int32 EventState)
{
	bWaitingNetworkState = false;

	if (EventState == 0)
	{
		HidePlatform();
	}
	else if (EventState == 1)
	{
		ShowPlatform();
	}
	else if (EventState == 2)
	{
		ActivateWarning();
	}
}

void ASkyCloudPlatform::InitializeGameState()
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

void ASkyCloudPlatform::ApplyStableVisual()
{
	VisualScaleMultiplier = 1.f;
	ApplyVisualScale();

	if (!CloudMeshComponent)
	{
		return;
	}

	if (StableMaterial)
	{
		CloudMeshComponent->SetMaterial(0, StableMaterial);
		return;
	}

	for (int32 i = 0; i < OriginalMaterials.Num(); ++i)
	{
		CloudMeshComponent->SetMaterial(i, OriginalMaterials[i]);
	}
}

void ASkyCloudPlatform::ApplyWarningVisual()
{
	VisualScaleMultiplier = WarningScaleMultiplier;
	ApplyVisualScale();

	if (CloudMeshComponent && WarningMaterial)
	{
		CloudMeshComponent->SetMaterial(0, WarningMaterial);
	}
}

void ASkyCloudPlatform::ApplyInitialCycleOffset()
{
	const float CurrentVisibleDuration = GetCurrentVisibleDuration();
	const float CycleDuration = CurrentVisibleDuration + HiddenDuration;

	if (CycleDuration <= 0.f)
	{
		return;
	}

	const float InitialCycleOffset = bRandomizeInitialCycleOffset
		? FMath::FRandRange(0.f, CycleDuration)
		: ManualInitialCycleOffset;

	const float WrappedOffset = FMath::Fmod(FMath::Max(0.f, InitialCycleOffset), CycleDuration);

	if (WrappedOffset <= 0.f)
	{
		return;
	}

	if (WrappedOffset < CurrentVisibleDuration)
	{
		VisibleElapsed = WrappedOffset;

		const float WarningStartTime = FMath::Max(0.f, CurrentVisibleDuration - WarningDuration);
		if (VisibleElapsed >= WarningStartTime)
		{
			ActivateWarning();
		}
	}
	else
	{
		HidePlatform();
		HiddenElapsed = WrappedOffset - CurrentVisibleDuration;
	}
}

void ASkyCloudPlatform::UpdateLandingBounce(float DeltaTime)
{
	if (LandingBounceElapsed >= LandingBounceDuration)
	{
		return;
	}

	LandingBounceElapsed = FMath::Min(LandingBounceElapsed + DeltaTime, LandingBounceDuration);
	ApplyVisualScale();
}

void ASkyCloudPlatform::TriggerLandingBounce()
{
	if (LandingBounceDuration <= 0.f || LandingBounceElapsed < LandingBounceDuration)
	{
		return;
	}

	LandingBounceElapsed = 0.f;
	ApplyVisualScale();
}

void ASkyCloudPlatform::ApplyVisualScale()
{
	const float BounceAlpha = LandingBounceDuration > 0.f
		? FMath::Clamp(LandingBounceElapsed / LandingBounceDuration, 0.f, 1.f)
		: 1.f;

	const float BounceAmount = FMath::Sin(BounceAlpha * PI);

	const FVector BounceScale(
		1.f + LandingBounceSpreadScale * BounceAmount,
		1.f + LandingBounceSpreadScale * BounceAmount,
		1.f - LandingBounceSquashScale * BounceAmount
	);

	FVector TargetScale = InitialScale * VisualScaleMultiplier;
	TargetScale.X *= BounceScale.X;
	TargetScale.Y *= BounceScale.Y;
	TargetScale.Z *= BounceScale.Z;

	SetActorScale3D(TargetScale);
}

int32 ASkyCloudPlatform::GetStandingPlayerCount() const
{
	int32 StandingPlayerCount = 0;

	for (const TWeakObjectPtr<AMyCharacter>& StandingCharacter : StandingCharacters)
	{
		const AMyCharacter* Character = StandingCharacter.Get();
		if (Character && !Character->IsDead())
		{
			StandingPlayerCount++;
		}
	}

	return StandingPlayerCount;
}
