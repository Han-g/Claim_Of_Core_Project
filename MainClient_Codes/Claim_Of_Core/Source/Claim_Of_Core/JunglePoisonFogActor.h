// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "JunglePoisonFogActor.generated.h"

class AMyCharacter;
class ULocalFogVolumeComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UPointLightComponent;
class UPrimitiveComponent;
class USphereComponent;

UCLASS()
class CLAIM_OF_CORE_API AJunglePoisonFogActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJunglePoisonFogActor();

	UFUNCTION(BlueprintCallable, Category = "JunglePoisonFog")
	void ActivateFog();

	UFUNCTION(BlueprintCallable, Category = "JunglePoisonFog")
	void DeactivateFog();

	UFUNCTION(BlueprintPure, Category = "JunglePoisonFog")
	bool IsFogActive() const { return bFogActive; }

	UFUNCTION(BlueprintImplementableEvent, Category = "JunglePoisonFog")
	void BP_OnFogActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "JunglePoisonFog")
	void BP_OnFogDeactivated();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Components")
	TObjectPtr<USceneComponent> SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Components")
	TObjectPtr<USphereComponent> FogVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Components")
	TObjectPtr<ULocalFogVolumeComponent> LocalFogVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Components")
	TObjectPtr<UNiagaraComponent> FogNiagara;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Components")
	TObjectPtr<UPointLightComponent> PurpleGlow;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Timing")
	bool bStartActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Timing", meta = (ClampMin = "0.0"))
	float ActivationDelay = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Shape", meta = (ClampMin = "100.0"))
	float FogRadius = 15000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Shape", meta = (ClampMin = "0.0"))
	float InnerRadius = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Shape", meta = (ClampMin = "0.0"))
	float InitialInnerRadius = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Shape", meta = (ClampMin = "0.0"))
	float MinInnerRadius = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Timing", meta = (ClampMin = "0.1"))
	float InnerShrinkDuration = 60.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "JunglePoisonFog")
	float FogActiveElapsed = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Timing", meta = (ClampMin = "0.0"))
	float Phase2InnerShrinkSpeed = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Timing", meta = (ClampMin = "0.0"))
	float Phase3InnerShrinkSpeed = 150.0f;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual")
	TObjectPtr<UNiagaraSystem> FogNiagaraSystem;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual", meta = (ClampMin = "0.0"))
	float RadialFogDensity = 2.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual", meta = (ClampMin = "0.0"))
	float HeightFogDensity = 1.35f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual", meta = (ClampMin = "1.0"))
	float HeightFogFalloff = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual")
	float HeightFogOffset = -0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual", meta = (ClampMin = "0.0", ClampMax = "0.999"))
	float FogPhaseG = 0.45f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual")
	FLinearColor FogAlbedo = FLinearColor(0.62f, 0.12f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual")
	FLinearColor FogEmissive = FLinearColor(0.18f, 0.02f, 0.38f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual", meta = (ClampMin = "-127", ClampMax = "127"))
	int32 FogSortPriority = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual", meta = (ClampMin = "0.0"))
	float GlowIntensity = 2200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Visual")
	FLinearColor GlowColor = FLinearColor(0.72f, 0.12f, 1.0f, 1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Debug")
	bool bDrawDebug = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JunglePoisonFog|Debug", meta = (ClampMin = "0.05"))
	float CharacterRefreshInterval = 0.2f;


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "JunglePoisonFog")
	bool bFogActive = false;


	TArray<TWeakObjectPtr<AMyCharacter>> CharactersInFog;

	FTimerHandle ActivationTimerHandle;
	float CharacterRefreshAccumulator = 0.0f;



protected:
	UFUNCTION()
	void OnFogBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnFogEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

	void ScheduleActivation(float Delay);
	void HandleFogActiveChanged();
	void ApplyActiveState();
	void ApplyVisualSettings();
	void SyncFogShape();
	void RefreshCharactersInFog();
	void AddCharacterToFog(AMyCharacter* Character);
	void RemoveCharacterFromFog(AMyCharacter* Character);
	void ClearCharactersFromFog();
	bool IsActorInsideFog(const AActor* Actor) const;

public:	
};
