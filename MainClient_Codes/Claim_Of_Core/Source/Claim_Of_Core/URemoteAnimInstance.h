// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "URemoteAnimInstance.generated.h"

/**
 * 
 */
class AMyCharacter;

UCLASS()
class CLAIM_OF_CORE_API UURemoteAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	float GroundSpeed = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	bool bShouldMove = false;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	bool bHasAcceleration = false;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	float Direction = 0.f;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	bool bUseRunState = false;

	UPROPERTY(BlueprintReadOnly, Category = "Locomotion")
	bool bIsLocalCharacter = false;

private:
	TWeakObjectPtr<AMyCharacter> CachedCharacter;
};
