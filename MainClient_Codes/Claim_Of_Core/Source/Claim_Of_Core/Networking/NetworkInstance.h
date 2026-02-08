// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Tickable.h"
#include "NetworkInstance.generated.h"

class ClientNetworking;

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API UNetworkInstance : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	// Timer Func
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }

	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UNetworkInstance, STATGROUP_Tickables); }

private:
	UPROPERTY(Config)
	FString ServerIPAddress = TEXT("127.0.0.1");
	TSharedPtr<ClientNetworking> Client;
	FTimerHandle NetworkTimer;

	float SendAcc = 0.f;
};
