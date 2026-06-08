#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkyLiftBubble.generated.h"

class AMyCharacter;
class UCapsuleComponent;
class UMaterialInterface;
class UNiagaraComponent;
class UNiagaraSystem;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> LiftCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BubbleMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> UpdraftCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UNiagaraComponent> UpdraftEffectComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	float UpdraftSpeed = 1100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	float ActiveDuration = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	float UpdraftRadius = 280.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift")
	float UpdraftHeight = 1200.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, ReplicatedUsing = OnRep_Consumed, Category = "Lift")
	bool bConsumed = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Lift")
	bool bUpdraftActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift|Visual")
	TObjectPtr<UStaticMesh> BubbleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift|Visual")
	TObjectPtr<UMaterialInterface> BubbleMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Lift|Visual")
	TObjectPtr<UNiagaraSystem> UpdraftEffect;

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
	void ApplyUpdraftCollisionSettings();
	void ConsumeBubble(AMyCharacter* Character);
	void ApplyConsumedVisual();
	void ApplyUpdraft();

	UFUNCTION()
	void OnRep_Consumed();

	TSet<TWeakObjectPtr<AMyCharacter>> OverlappingCharacters;
	float ActiveElapsed = 0.f;
};
