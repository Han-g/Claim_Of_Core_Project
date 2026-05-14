#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IceChillZone.generated.h"

class AMyCharacter;
class UDecalComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class USphereComponent;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS()
class CLAIM_OF_CORE_API AIceChillZone : public AActor
{
	GENERATED_BODY()

public:
	AIceChillZone();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> ChillCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ChillMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDecalComponent> ChillDecalComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> ChillEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chill")
	float Radius = 650.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chill")
	float FreezeBuildUpTime = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chill")
	float ZoneLifeTime = 7.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chill|Visual")
	TObjectPtr<UStaticMesh> ChillMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chill|Visual")
	TObjectPtr<UMaterialInterface> ChillMeshMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chill|Visual")
	TObjectPtr<UMaterialInterface> ChillDecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chill|Visual")
	TObjectPtr<UNiagaraSystem> ChillVisualEffect;

	UPROPERTY()
	TMap<TObjectPtr<AMyCharacter>, float> CharacterStayTimes;

	UFUNCTION()
	void OnChillBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnChillEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void ApplyVisualSettings();
};
