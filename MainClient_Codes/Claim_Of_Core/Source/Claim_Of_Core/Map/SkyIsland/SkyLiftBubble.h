#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkyLiftBubble.generated.h"

class UMaterialInterface;
class UPrimitiveComponent;
class USphereComponent;
class UStaticMesh;
class UStaticMeshComponent;

UCLASS()
class CLAIM_OF_CORE_API ASkyLiftBubble : public AActor
{
	GENERATED_BODY()

public:
	ASkyLiftBubble();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> LiftCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BubbleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	float LaunchStrength = 1450.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	float LifeTime = 12.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	bool bDestroyOnUse = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift|Visual")
	TObjectPtr<UStaticMesh> BubbleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift|Visual")
	TObjectPtr<UMaterialInterface> BubbleMaterial;

	UFUNCTION()
	void OnBubbleBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	void ApplyVisualSettings();
};
