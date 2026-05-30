// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "UObject/ObjectKey.h"

#include "GlassBreakController.generated.h"

UCLASS()
class CLAIM_OF_CORE_API AGlassBreakController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGlassBreakController();

	UFUNCTION(BlueprintCallable, Category = "GlassBreak")
	void PrepareGlassActors();

	UFUNCTION(BlueprintCallable, Category = "GlassBreak")
	void ResetGlassActors();

	UFUNCTION(BlueprintCallable, Category = "GlassBreak")
	void BreakGlassActorsByTag(FName TargetGlassTag);

	UFUNCTION(BlueprintCallable, Category = "GlassBreak")
	void BreakPhase2GlassActors();

	UFUNCTION(BlueprintCallable, Category = "GlassBreak")
	void BreakPhase3GlassActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak|Tag")
	FName Phase2GlassTag = TEXT("Glass03");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak|Tag")
	FName Phase3GlassTagA = TEXT("Glass02");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak|Tag")
	FName Phase3GlassTagB = TEXT("Glass01");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	float BreakImpulseStrength = 10000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	float UpImpulseStrength = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	bool bUseGravityAfterBreak = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	bool bIgnorePawnCollisionAfterBreak = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	bool bUseControllerLocationAsBreakOrigin = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	FVector BreakOriginLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	float BreakRandomSpreadStrength = 0.25f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	TArray<TObjectPtr<AActor>> FoundGlassActors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GlassBreak")
	bool bGlassBroken = false;

private:
	TMap<FName, TArray<TWeakObjectPtr<AActor>>> GlassActorsByTag;
	TMap<TObjectKey<AActor>, FTransform> InitialGlassTransforms;
	TSet<FName> BrokenGlassTags;

	void FindGlassActorsByTag();
	void FreezeGlassActor(AActor* Actor);
	void BreakGlassActor(AActor* Actor);

	UStaticMeshComponent* GetStaticMeshComponentFromActor(AActor* Actor) const;
};
