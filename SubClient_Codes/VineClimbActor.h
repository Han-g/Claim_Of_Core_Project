#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VineClimbActor.generated.h"

class UBoxComponent;
class UPrimitiveComponent;

UCLASS()
class CLAIM_OF_CORE_API AVineClimbActor : public AActor
{
	GENERATED_BODY()

public:
	AVineClimbActor();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* ClimbBox;

private:
	UFUNCTION()
	void OnClimbBoxBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnClimbBoxEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);
};
