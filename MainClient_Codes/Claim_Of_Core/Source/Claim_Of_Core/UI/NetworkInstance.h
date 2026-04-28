#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"
#include "Tickable.h"
#include "ClientNetworkTypes.h"
#include "Blueprint/UserWidget.h"

#include "NetworkInstance.generated.h"

class ClientNetworking;
class URoomWidget;
class AMyCharacter;
struct FRoomInfoData;
struct FRoomMemberInfo;
enum PacketID : uint16;


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
	virtual int32 GetPlayerUID() const;

	UFUNCTION(BlueprintCallable, Category = "Network|Room")
	void SelectCharacterAndReady(int32 SelectedRoleType);

	UFUNCTION(BlueprintCallable, Category = "Network|UI")

	void ShowLoginHUD();
	void TryLogin(FString ID, FString PW);
	void TryRegister(FString ID, FString PW);
	void CreateRoom();
	void JoinRoom(int32 RoomID);
	void CharacterSelectRequest();
	void RequestReady();
	void RequestGameStart();
	void SendMoveInputToServer(const FMovePacket& MoveData);

	// Send Packet for Test
	void SendGameplayTestPacket(PacketID TestPacket);

	// Send Prepare Game Packet
	void HandleLoginResult(bool bSuccess);
	void HandleRegisterResult(bool bSuccess);
	void HandleRoomListUpdate(const TArray<FRoomInfoData>& RoomList);
	void HandleRoomEnterResult(bool bSuccess, const TArray<FRoomMemberInfo>& playerList);
	void HandleGameStart();

	// Server Setting Packet
	void HandleConnected();
	void HandleConnectFailed();
	void HandleDisconnected();

	// Game Logic Packet
	void HandleSnapshotReceived(const TArray<GameData>& SnapshotList);

	void HandleAttackActionReceived(const FAttackActionPacket& Packet);
	void HandleDamageApplied(const FDamageApplyPacket& Packet);
	void HandleStatusUpdated(const FStatusUpdatePacket& Packet);
	void HandleStateChanged(const FStateChangePacket& Packet);
	void HandleRespawned(const FRespawnPacket& Packet);

protected:

private:
	// Getter Function For Accessing Widget from External
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

	// Getter Function For Server Connection
	UPROPERTY(Config)
	FString ServerIPAddress = TEXT("127.0.0.1");
	TSharedPtr<ClientNetworking> Client;
	int32 RetryCounter = 0;
	const int32 MaxRetryCount = 10;

	// Getter Function For Robby Setting
	bool bReadySent = false;
	int32 CachedSelectedRoleType = -1;

	// Getter Function For Map Control 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level", meta = (AllowPrivateAccess =
		"true"))
	TSoftObjectPtr<UWorld> InGameLevel;

public:
	AMyCharacter* FindCharacterByUID(int32 UID) const;
	AMyCharacter* EnsureRemoteCharacter(const GameData& Data);

private:
	// One-time initial transform sync for the local player.
	bool bLocalInitialTransformApplied = false;

	// Cached snapshot received before the local player was ready.
	TArray<GameData> PendingSnapshotList;
	bool bHasPendingSnapshot = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network|Remote", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMyCharacter> RemoteCharacterClass;

	// Remote player instances indexed by userUID.
	TMap<int32, TWeakObjectPtr<AMyCharacter>> RemoteCharacters;
};
