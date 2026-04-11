// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"
#include "Tickable.h"
#include "Blueprint/UserWidget.h"

#include "NetworkInstance.generated.h"

class ClientNetworking;
class URoomWidget;
struct FRoomInfoData;
struct FRoomMemberInfo;

/**
 * 
 */
UCLASS()
class CLAIM_OF_CORE_API UNetworkInstance : public UGameInstance, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UNetworkInstance();

	virtual void Init() override;
	virtual void Shutdown() override;

	// Timer Func
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override { RETURN_QUICK_DECLARE_CYCLE_STAT(UNetworkInstance, STATGROUP_Tickables); }
	
	UFUNCTION(BlueprintCallable, Category = "Network|UI")
	
	void ShowLoginHUD();
	void TryLogin(FString ID, FString PW);
	void TryRegister(FString ID, FString PW);
	void CreateRoom();
	void JoinRoom(int32 RoomID);
	void RequestReady();
	void RequestGameStart();
	
	void HandleLoginResult(bool bSuccess);
	void HandleRegisterResult(bool bSuccess);
	void HandleRoomListUpdate(const TArray<FRoomInfoData>& RoomList);
	void HandleRoomEnterResult(bool bSuccess, const TArray<FRoomMemberInfo>& playerList);
	void HandleGameStart();

	void TryReconnect();

protected:
	void ConnectionLost();

private:
	//Getter Function For Accessing Widget from External
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LoginWidgetClass;
	UPROPERTY()
	UUserWidget* LoginWidgetInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LobbyWidgetClass;
	UPROPERTY()
	UUserWidget* LobbyWidgetInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<URoomWidget> RoomWidgetClass;
	UPROPERTY()
	URoomWidget* RoomWidgetInstance;

	UPROPERTY(Config)
	FString ServerIPAddress = TEXT("127.0.0.1");
	TSharedPtr<ClientNetworking> Client;
	FTimerHandle NetworkTimer;
	float SendAcc = 0.f;
	FTimerHandle ReconnectTimer;
	int32 RetryCounter = 0;
	const int32 MaxRetryCount = 10;
};