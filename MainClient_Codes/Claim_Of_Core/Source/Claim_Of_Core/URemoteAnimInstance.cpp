// Fill out your copyright notice in the Description page of Project Settings.


#include "URemoteAnimInstance.h"

#include "Sub/MyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UURemoteAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	CachedCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
}

void UURemoteAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CachedCharacter.IsValid())
	{
		CachedCharacter = Cast<AMyCharacter>(TryGetPawnOwner());
	}

	AMyCharacter* Character = CachedCharacter.Get();
	if (!Character)
	{
		GroundSpeed = 0.f;
		bShouldMove = false;
		bHasAcceleration = false;
		Direction = 0.f;
		bUseRunState = false;
		bIsLocalCharacter = false;
		return;
	}

	bIsLocalCharacter = Character->IsLocallyControlled();

	if (bIsLocalCharacter)
	{
		const FVector Velocity = Character->GetVelocity();
		const FVector HorizontalVelocity(Velocity.X, Velocity.Y, 0.f);

		GroundSpeed = HorizontalVelocity.Size();
		bShouldMove = GroundSpeed > 3.f;

		if (const UCharacterMovementComponent* MoveComp = Character->GetCharacterMovement())
		{
			bHasAcceleration = !MoveComp->GetCurrentAcceleration().IsNearlyZero();
		}
		else
		{
			bHasAcceleration = false;
		}

		Direction = CalculateDirection(Velocity, Character->GetActorRotation());
		bUseRunState = GroundSpeed > 600.f;
	}
	else
	{
		const int32 AnimNum = Character->GetNetworkAnimationNum();

		switch (AnimNum)
		{
		case 0:
			GroundSpeed = 0.f;
			bShouldMove = false;
			bHasAcceleration = false;
			Direction = 0.f;
			bUseRunState = false;
			break;

		case 1:
			GroundSpeed = 300.f;
			bShouldMove = true;
			bHasAcceleration = true;
			Direction = 0.f;
			bUseRunState = false;
			break;

		case 2:
			GroundSpeed = 800.f;
			bShouldMove = true;
			bHasAcceleration = true;
			Direction = 0.f;
			bUseRunState = true;
			break;

		default:
			GroundSpeed = 0.f;
			bShouldMove = false;
			bHasAcceleration = false;
			Direction = 0.f;
			bUseRunState = false;
			break;
		}
	}
}
