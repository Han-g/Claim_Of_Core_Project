#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GlassBreakController.generated.h"

UCLASS()
class CLAIM_OF_CORE_API AGlassBreakController : public AActor
{
	GENERATED_BODY()

public:
	AGlassBreakController();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	FName GlassTag = TEXT("BreakGlass");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	float BreakStartTime = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	float BreakImpulseStrength = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	float UpImpulseStrength = 80.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	bool bUseGravityAfterBreak = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	TArray<TObjectPtr<AActor>> FoundGlassActors;

	FTimerHandle BreakTimerHandle;

protected:
	void FindGlassActorsByTag();
	void FreezeGlassActors();
	void BreakGlassActors();

	UStaticMeshComponent* GetStaticMeshComponentFromActor(AActor* Actor) const;
};
