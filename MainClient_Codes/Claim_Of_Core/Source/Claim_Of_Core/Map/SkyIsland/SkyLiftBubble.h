#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkyLiftBubble.generated.h"

class AMyCharacter;
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
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> LiftCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BubbleMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	float UpdraftSpeed = 1100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	float ActiveDuration = 5.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Lift")
	bool bBubbleActive = true;

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

	UFUNCTION()
	void OnBubbleEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

	void ApplyVisualSettings();
	void SetBubbleActive(bool bNewActive);
	void ApplyUpdraft();

	TSet<TWeakObjectPtr<AMyCharacter>> OverlappingCharacters;
	float ActiveElapsed = 0.f;
};
