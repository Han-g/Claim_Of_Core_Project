// Fill out your copyright notice in the Description page of Project Settings.


#include "JunglePoisonFogActor.h"

#include "DrawDebugHelpers.h"
#include "NiagaraComponent.h"
#include "Sub/MyCharacter.h"
#include "GameState/InGame_GameState.h"
#include "Components/LocalFogVolumeComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
AJunglePoisonFogActor::AJunglePoisonFogActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	FogVolume = CreateDefaultSubobject<USphereComponent>(TEXT("FogVolume"));
	FogVolume->SetupAttachment(SceneRoot);
	FogVolume->SetSphereRadius(FogRadius);
	FogVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FogVolume->SetCollisionObjectType(ECC_WorldDynamic);
	FogVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	FogVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	FogVolume->SetGenerateOverlapEvents(false);
	FogVolume->SetHiddenInGame(true);
	FogVolume->ShapeColor = FColor(170, 32, 255);

	LocalFogVolume = CreateDefaultSubobject<ULocalFogVolumeComponent>(TEXT("LocalFogVolume"));
	LocalFogVolume->SetupAttachment(SceneRoot);
	LocalFogVolume->SetVisibility(false, true);
	LocalFogVolume->SetHiddenInGame(true, true);

	FogNiagara = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FogNiagara"));
	FogNiagara->SetupAttachment(SceneRoot);
	FogNiagara->SetAutoActivate(false);

	PurpleGlow = CreateDefaultSubobject<UPointLightComponent>(TEXT("PurpleGlow"));
	PurpleGlow->SetupAttachment(SceneRoot);
	PurpleGlow->SetVisibility(false, true);
	PurpleGlow->SetHiddenInGame(true, true);
	PurpleGlow->SetIntensity(GlowIntensity);
	PurpleGlow->SetLightColor(GlowColor);
	PurpleGlow->AttenuationRadius = FogRadius;
}

void AJunglePoisonFogActor::BeginPlay()
{
	Super::BeginPlay();

	if (FogVolume)
	{
		FogVolume->OnComponentBeginOverlap.AddDynamic(this, &AJunglePoisonFogActor::OnFogBeginOverlap);
		FogVolume->OnComponentEndOverlap.AddDynamic(this, &AJunglePoisonFogActor::OnFogEndOverlap);
	}

	ApplyVisualSettings();
	ApplyActiveState();

	if (bStartActive)
	{
		ActivateFog();
	}
	else
	{
		ScheduleActivation(ActivationDelay);
	}
}

void AJunglePoisonFogActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (GetWorld())
	{
		GetWorldTimerManager().ClearTimer(ActivationTimerHandle);
	}

	ClearCharactersFromFog();

	Super::EndPlay(EndPlayReason);
}

void AJunglePoisonFogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bFogActive)
	{
		return;
	}

	float ShrinkSpeed = 0.0f;

	if (const AInGame_GameState* GS = GetWorld() ? GetWorld()->GetGameState<AInGame_GameState>() : nullptr)
	{
		if (GS->CurrentPhase == EMapPhase::Phase2)
		{
			ShrinkSpeed = Phase2InnerShrinkSpeed;
		}
		else if (GS->CurrentPhase == EMapPhase::Phase3)
		{
			ShrinkSpeed = Phase3InnerShrinkSpeed;
		}
	}

	if (ShrinkSpeed > 0.0f)
	{
		InnerRadius = FMath::Max(MinInnerRadius, InnerRadius - ShrinkSpeed * DeltaTime);
	}

	if (FogNiagara)
	{
		FogNiagara->SetVariableFloat(TEXT("User.OuterRadius"), FogRadius);
		FogNiagara->SetVariableFloat(TEXT("User.InnerRadius"), InnerRadius);
		FogNiagara->SetVariableFloat(TEXT("User.FogHeightMin"), 0.0f);
		FogNiagara->SetVariableFloat(TEXT("User.FogHeightMax"), 1200.0f);
		FogNiagara->SetVariableFloat(TEXT("User.EdgeSoftness"), 500.0f);
	}

	CharacterRefreshAccumulator += DeltaTime;
	if (CharacterRefreshAccumulator >= CharacterRefreshInterval)
	{
		CharacterRefreshAccumulator = 0.0f;
		RefreshCharactersInFog();
	}

	if (bDrawDebug && GetWorld())
	{
		/*DrawDebugSphere(
			GetWorld(),
			GetActorLocation(),
			FogRadius,
			48,
			FColor(170, 32, 255),
			false,
			0.0f,
			0,
			3.0f
		);*/
	}
}

#if WITH_EDITOR
void AJunglePoisonFogActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	SyncFogShape();
	ApplyVisualSettings();
}
#endif

void AJunglePoisonFogActor::ScheduleActivation(float Delay)
{
	if (bFogActive || !GetWorld())
	{
		return;
	}

	GetWorldTimerManager().ClearTimer(ActivationTimerHandle);

	if (Delay <= KINDA_SMALL_NUMBER)
	{
		ActivateFog();
		return;
	}

	GetWorldTimerManager().SetTimer(
		ActivationTimerHandle,
		this,
		&AJunglePoisonFogActor::ActivateFog,
		Delay,
		false
	);
}

void AJunglePoisonFogActor::ActivateFog()
{
	if (bFogActive)
	{
		return;
	}

	bFogActive = true;
	FogActiveElapsed = 0.0f;
	InnerRadius = InitialInnerRadius;

	HandleFogActiveChanged();

	UE_LOG(LogTemp, Warning, TEXT("[JunglePoisonFog] Activated: %s"), *GetName());
}

void AJunglePoisonFogActor::DeactivateFog()
{
	if (!bFogActive)
	{
		return;
	}

	bFogActive = false;
	HandleFogActiveChanged();

	UE_LOG(LogTemp, Warning, TEXT("[JunglePoisonFog] Deactivated: %s"), *GetName());
}

void AJunglePoisonFogActor::HandleFogActiveChanged()
{
	ApplyActiveState();

	if (bFogActive)
	{
		BP_OnFogActivated();
	}
	else
	{
		BP_OnFogDeactivated();
	}
}

void AJunglePoisonFogActor::OnFogBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (!bFogActive || !IsActorInsideFog(OtherActor))
	{
		return;
	}


	AddCharacterToFog(Cast<AMyCharacter>(OtherActor));
}

void AJunglePoisonFogActor::OnFogEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	RemoveCharacterFromFog(Cast<AMyCharacter>(OtherActor));
}

void AJunglePoisonFogActor::ApplyActiveState()
{
	SyncFogShape();
	ApplyVisualSettings();

	if (FogVolume)
	{
		FogVolume->SetGenerateOverlapEvents(bFogActive);
		FogVolume->SetCollisionEnabled(bFogActive ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);

		if (bFogActive)
		{
			FogVolume->UpdateOverlaps();
		}
	}

	if (LocalFogVolume)
	{
		LocalFogVolume->SetVisibility(false, true);
		LocalFogVolume->SetHiddenInGame(true, true);
		LocalFogVolume->SetComponentTickEnabled(false);
	}

	if (FogNiagara)
	{
		if (FogNiagaraSystem)
		{
			FogNiagara->SetAsset(FogNiagaraSystem);
		}

		if (bFogActive && FogNiagara->GetAsset())
		{
			FogNiagara->Activate(true);
		}
		else
		{
			FogNiagara->Deactivate();
		}
	}

	if (PurpleGlow)
	{
		PurpleGlow->SetVisibility(bFogActive, true);
		PurpleGlow->SetHiddenInGame(!bFogActive, true);
		PurpleGlow->SetIntensity(bFogActive ? GlowIntensity : 0.0f);
		PurpleGlow->SetLightColor(GlowColor);
	}

	if (bFogActive)
	{
		RefreshCharactersInFog();
	}
	else
	{
		ClearCharactersFromFog();
	}
}

void AJunglePoisonFogActor::ApplyVisualSettings()
{
	SyncFogShape();

	if (LocalFogVolume)
	{
		LocalFogVolume->SetRadialFogExtinction(RadialFogDensity);
		LocalFogVolume->SetHeightFogExtinction(HeightFogDensity);
		LocalFogVolume->SetHeightFogFalloff(HeightFogFalloff);
		LocalFogVolume->SetHeightFogOffset(HeightFogOffset);
		LocalFogVolume->SetFogPhaseG(FogPhaseG);
		LocalFogVolume->SetFogAlbedo(FogAlbedo);
		LocalFogVolume->SetFogEmissive(FogEmissive);
		LocalFogVolume->FogSortPriority = FMath::Clamp(FogSortPriority, -127, 127);
	}

	if (PurpleGlow)
	{
		PurpleGlow->AttenuationRadius = 0;
		PurpleGlow->SetIntensity(bFogActive ? GlowIntensity : 0.0f);
		PurpleGlow->SetLightColor(GlowColor);
	}
}

void AJunglePoisonFogActor::SyncFogShape()
{
	FogRadius = FMath::Max(100.0f, FogRadius);

	if (FogVolume)
	{
		FogVolume->SetSphereRadius(FogRadius, true);
	}

	if (LocalFogVolume)
	{
		const float VolumeScale = FogRadius / ULocalFogVolumeComponent::GetBaseVolumeSize();
		LocalFogVolume->SetRelativeScale3D(FVector(VolumeScale));
	}

	if (FogNiagara)
	{
		FogNiagara->SetRelativeScale3D(FVector::OneVector);
	}
}

void AJunglePoisonFogActor::RefreshCharactersInFog()
{
	for (int32 Index = CharactersInFog.Num() - 1; Index >= 0; --Index)
	{
		AMyCharacter* Character = CharactersInFog[Index].Get();
		if (!IsValid(Character) || !bFogActive || !IsActorInsideFog(Character))
		{
			if (IsValid(Character))
			{
				Character->ExitPoisonFog(this);
			}

			CharactersInFog.RemoveAtSwap(Index);
		}
	}

	if (!bFogActive || !GetWorld())
	{
		return;
	}

	TArray<AActor*> FoundCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), FoundCharacters);

	for (AActor* Actor : FoundCharacters)
	{
		AMyCharacter* Character = Cast<AMyCharacter>(Actor);
		if (IsValid(Character) && IsActorInsideFog(Character))
		{
			AddCharacterToFog(Character);
		}
	}
}

void AJunglePoisonFogActor::AddCharacterToFog(AMyCharacter* Character)
{
	if (!IsValid(Character))
	{
		return;
	}

	for (const TWeakObjectPtr<AMyCharacter>& WeakCharacter : CharactersInFog)
	{
		if (WeakCharacter.Get() == Character)
		{
			return;
		}
	}

	CharactersInFog.Add(Character);
	Character->EnterPoisonFog(this);
}

void AJunglePoisonFogActor::RemoveCharacterFromFog(AMyCharacter* Character)
{
	if (!IsValid(Character))
	{
		return;
	}

	const int32 RemovedCount = CharactersInFog.RemoveAll(
		[Character](const TWeakObjectPtr<AMyCharacter>& WeakCharacter)
		{
			return WeakCharacter.Get() == Character || !WeakCharacter.IsValid();
		}
	);

	if (RemovedCount > 0)
	{
		Character->ExitPoisonFog(this);
	}
}

void AJunglePoisonFogActor::ClearCharactersFromFog()
{
	for (const TWeakObjectPtr<AMyCharacter>& WeakCharacter : CharactersInFog)
	{
		if (AMyCharacter* Character = WeakCharacter.Get())
		{
			Character->ExitPoisonFog(this);
		}
	}

	CharactersInFog.Empty();
}

bool AJunglePoisonFogActor::IsActorInsideFog(const AActor* Actor) const
{
	if (!Actor)
	{
		return false;
	}

	const float DistSq = FVector::DistSquared2D(GetActorLocation(), Actor->GetActorLocation());

	const bool bInsideOuter = DistSq <= FMath::Square(FogRadius);
	const bool bInsideSafeHole = InnerRadius > 0.0f && DistSq < FMath::Square(InnerRadius);

	return bInsideOuter && !bInsideSafeHole;
}