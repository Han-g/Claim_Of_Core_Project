// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../../GameState/InGame_GameState.h"
#include "SkyCloudPlatform.generated.h"

class AMyCharacter;
class UMaterialInterface;
class UPrimitiveComponent;
class UStaticMesh;
class UStaticMeshComponent;


UCLASS()
class CLAIM_OF_CORE_API ASkyCloudPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkyCloudPlatform();

	UFUNCTION(BlueprintCallable, Category = "CloudPlatform")
	void NotifyPlayerStanding(AMyCharacter* StandingCharacter);

	UFUNCTION(BlueprintCallable, Category = "CloudPlatform")
	void NotifyPlayerLanded(AMyCharacter* LandingCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> CloudMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform")
	float VisibleDuration = 7.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform")
	float HiddenDuration = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform")
	float WarningDuration = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform")
	float StandingBreakTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform")
	bool bUseAutoCycle = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform")
	bool bRandomizeInitialCycleOffset = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform")
	float ManualInitialCycleOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Phase")
	float Phase2DurationMultiplier = 0.75f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Phase")
	float Phase3DurationMultiplier = 0.45f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Visual")
	TObjectPtr<UMaterialInterface> StableMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Visual")
	TObjectPtr<UMaterialInterface> WarningMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Visual")
	float WarningScaleMultiplier = 0.92f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Motion")
	float MotionPhaseOffset = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Motion")
	bool bRandomizeMotionPhase = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Motion")
	bool bUseCloudMotion = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Motion")
	FVector MotionAmplitude = FVector(120.f, 80.f, 16.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Motion")
	float MotionSpeed = 0.55f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Landing")
	float LandingBounceDuration = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Landing")
	float LandingBounceSpreadScale = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CloudPlatform|Landing")
	float LandingBounceSquashScale = 0.025f;

	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState;

	UPROPERTY()
	TArray<TObjectPtr<UMaterialInterface>> OriginalMaterials;

	FVector InitialScale = FVector::OneVector;
	FVector InitialLocation = FVector::ZeroVector;


	TSet<TWeakObjectPtr<AMyCharacter>> StandingCharacters;

	bool bPlatformVisible = true;
	bool bWarningActive = false;

	float VisibleElapsed = 0.f;
	float HiddenElapsed = 0.f;
	float StandingProgress = 0.f;
	float MotionElapsed = 0.f;
	float LandingBounceElapsed = 0.f;
	float VisualScaleMultiplier = 1.f;

public:	
	void UpdateVisible(float DeltaTime);
	void UpdateHidden(float DeltaTime);
	void ShowPlatform();
	void HidePlatform();
	void ActivateWarning();
	void ApplyPlatformEnabled(bool bEnabled);
	float GetCurrentVisibleDuration() const;
	void UpdateCloudMotion(float DeltaTime);

private:
	void InitializeGameState();
	void ApplyStableVisual();
	void ApplyWarningVisual();
	void ApplyInitialCycleOffset();
	void UpdateLandingBounce(float DeltaTime);
	void TriggerLandingBounce();
	void ApplyVisualScale();
	int32 GetStandingPlayerCount() const;
};
