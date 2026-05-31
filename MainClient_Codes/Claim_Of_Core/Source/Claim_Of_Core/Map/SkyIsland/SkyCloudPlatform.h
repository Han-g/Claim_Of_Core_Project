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
	ASkyCloudPlatform();

	UFUNCTION(BlueprintCallable, Category = "CloudPlatform")
	void NotifyPlayerStanding(AMyCharacter* StandingCharacter);

protected:
	virtual void BeginPlay() override;
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

	UPROPERTY()
	TObjectPtr<AInGame_GameState> CachedGameState;

	UPROPERTY()
	TArray<TObjectPtr<UMaterialInterface>> OriginalMaterials;

	TSet<TWeakObjectPtr<AMyCharacter>> StandingCharacters;
	FVector InitialScale = FVector::OneVector;
	float VisibleElapsed = 0.f;
	float HiddenElapsed = 0.f;
	float StandingProgress = 0.f;
	bool bPlatformVisible = true;
	bool bWarningActive = false;

	void InitializeGameState();
	void UpdateVisible(float DeltaTime);
	void UpdateHidden(float DeltaTime);
	void ShowPlatform();
	void HidePlatform();
	void ActivateWarning();
	void ApplyPlatformEnabled(bool bEnabled);
	void ApplyStableVisual();
	void ApplyWarningVisual();
	float GetCurrentVisibleDuration() const;
	void ApplyInitialCycleOffset();
	int32 GetStandingPlayerCount() const;
};
