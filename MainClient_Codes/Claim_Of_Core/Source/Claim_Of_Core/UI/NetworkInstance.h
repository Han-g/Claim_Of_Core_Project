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
class ABaseItem;
class ASmallDebrisActor;
class ALargeDebrisController;
class AIceChillZone;
class ABlackHoleActor;

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

	// Test Func
	void StartClientOnlyTestFlow();
	bool IsClientOnlyTestMode() const { return bClientOnlyTestMode; }

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
	void RequestCharacterSelect();
	void RequestReady();
	void RequestGameStart();
	void RequestAttackInput(int32 AttackType = 0);
	void RequestAttackHitReport(uint32 AttackSeq, int32 TargetID, int32 AttackType);
	void RequestJumpInput();
	void RequestItemPickup(int32 ItemID);
	void RequestItemDrop(int32 ItemID);

	void RequestIceFloorStanding(int32 FloorID, int32 PieceIndex);

	void SendMoveInputToServer(const FMovePacket& MoveData);

	// Send Packet for Test
	void SendGameplayAttackPacket(PacketID TestPacket);
	void DispatchTestAttackAction(int32 AttackType);

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
	void HandleMapSelected(int32 MapType);
	void HandleSnapshotReceived(const TArray<GameData>& SnapshotList);

	void HandleAttackActionReceived(const FAttackActionPacket& Packet);
	void HandleDamageApplied(const FDamageApplyPacket& Packet);
	void HandleItemOwnershipChanged(const FItemPacket& Packet);
	void HandleStatusUpdated(const FStatusUpdatePacket& Packet);
	void HandleStateChanged(const FStateChangePacket& Packet);
	void HandleRespawned(const FRespawnPacket& Packet);
	void HandleGameTimeSynced(float SyncedGameTime);
	void HandlePhaseChanged(const FPhaseChangePacket& Packet);
	void HandleMapEventTriggered(const FMapEventPacket& Packet);
	void HandleObjectSpawned(const FSpawnObjectPacket& Packet);

	void HandleStatusEffect(const FStatusEffectPacket& Packet);

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
	// In Game Play Setting Function
	void MarkPendingGameplayActivation();
	bool ConsumePendingGameplayActivation();

	// Character Setting Function
	AMyCharacter* FindCharacterByUID(int32 UID) const;
	AMyCharacter* EnsureRemoteCharacter(const GameData& Data);

	// Item Control Function
	ABaseItem* FindItemByID(int32 ItemID) const;


private:
	// Checker Game Play Setting
	bool bPendingGameplayActivation = false;

	// One-time initial transform sync for the local player.
	bool bLocalInitialTransformApplied = false;
	bool bPendingInitialSpawnLock = false;
	bool bLocalSpawnLockApplied = false;

	// Cached snapshot received before the local player was ready.
	TArray<GameData> PendingSnapshotList;
	bool bHasPendingSnapshot = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network|Remote", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AMyCharacter> RemoteCharacterClass;

	// Remote player instances indexed by userUID.
	TMap<int32, TWeakObjectPtr<AMyCharacter>> RemoteCharacters;


	// Control Game and Map Objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network|Map", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASmallDebrisActor> SmallDebrisClass;

	TMap<int32, TWeakObjectPtr<ASmallDebrisActor>> SpawnedSmallDebris;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network|Map", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AIceChillZone> IceChillZoneClass;

	TMap<int32, TWeakObjectPtr<AIceChillZone>> SpawnedIceChillZones;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpaceMap", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABlackHoleActor> BlackHoleClass;

	TMap<int32, TWeakObjectPtr<ABlackHoleActor>> SpawnedBlackHoles;

	// Test Checker
	bool bClientOnlyTestMode = false;
};
