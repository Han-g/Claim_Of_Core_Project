#pragma once

#include "CoreMinimal.h"
#include "ClientNetworkTypes.h"
//#include "ClientNetworking.generated.h"

class FClientNetworkWorker;

/**
 * Main-thread facade for network communication.
 * All socket I/O runs on a dedicated worker thread.
 * This class only enqueues commands and pumps events.
 */
class CLAIM_OF_CORE_API ClientNetworking
{
public:
    ClientNetworking();
    ~ClientNetworking();

    ClientNetworking* GetClientNetworking() { return this; }

    // Test Fuctions
    void TestFuncInput(PacketID testPacket);

    // Lifecycle
    void Start(const FString& IP, int32 Port);
    void Shutdown();

    // Called every game-thread Tick to drain worker events ¡æ fire delegates
    void PumpEvents();

    // Request methods (enqueue commands to worker)
    void RequestConnect(const FString& IP, int32 Port);
    void RequestDisconnect();
    void RequestReconnect();

    void LoginAccess(FString& ID, FString& PW);
    void RegisterRequest(FString& ID, FString& PW);
    void CreateRoomRequest();
    void LeaveRoomRequest();
    void CharacterSelectRequest(int32 RoleType);
    void JoinRoomRequest(int32 RoomID);
    void RoomSlotSelectRequest(int32 SlotIndex);
    void ReadyToggleRequest();
    void GameStartRequest();

    void RoleSkillRequest();
    void ItemPickupRequest(int32 ItemID);
    void ItemDropRequest(int32 ItemID);
    void AttackHitReportRequest(uint32 AttackSeq, int32 TargetID, int32 AttackType);
    void ObjectHitRequest(int32 ObjectID, int32 ObjectType, int32 SubID, int32 HitKind);
    void HitscanShotRequest(int32 ItemID, int32 TargetID, const FVector& TraceStart, const FVector& TraceDirection);

    void IceFloorStandRequest(int32 FloorID, int32 PieceIndex);
    void GrenadeBlackHoleRequest(int32 ItemID, const FVector& SpawnLocation);

    void SendMoveInput(const FMovePacket& MoveData);
    void SendJumpInput();

    // Delegates (broadcast on game thread only)
    FOnConnectedDelegate      OnConnected;
    FOnConnectFailedDelegate  OnConnectFailed;
    FOnDisconnectDelegate     OnDisconnected;
    FOnLoginResultDelegate    OnLoginResult;
    FOnRegisterResultDelegate OnRegisterResult;
    FOnRoomListUpdated        OnRoomListUpdated;
    FOnRoomEntered            OnRoomEnterResult;
    FOnRoundPrepare           OnRoundPrepare;
    FOnMapSelected            OnMapSelected;
    FOnGameStartDelegate      OnGameStart;
    FOnMatchEnd               OnMatchEnd;

    FOnDamageApplied          OnDamageApplied;
    FOnStatusUpdated          OnStatusUpdated;
    FOnStateChanged           OnStateChanged;
    FOnRespawned              OnRespawned;
    FOnRoleChanged            OnRoleChanged;
    FOnGameTimeSynced         OnGameTimeSynced;
    FOnPhaseChanged           OnPhaseChanged;
    FOnRoundResult            OnRoundResult;
    FOnMapEventTriggered      OnMapEventTriggered;
    FOnItemSpawned            OnItemSpawned;
    FOnItemDespawned          OnItemDespawned;
    FOnObjectSpawned          OnObjectSpawned;
    FOnLargeDebrisChunkBroken OnLargeDebrisChunkBroken;
    FOnAttackActionReceived   OnAttackAction;
    FOnRoleSkillStateChanged OnRoleSkillStateChanged;

    FOnSyncAnimationReceived  OnSyncAnimation;
    FOnSnapshotReceived       OnSnapshotReceived;
    FOnItemOwnershipChanged   OnItemOwnershipChanged;

    FOnStatusEffect OnStatusEffect;

    // Player data (updated from login response)
    int32 ClientSessionID = -1;
    GameData ClientPlayerData;
    bool IsLogin = false;

private:
    void EnqueueSendCommand(uint16 PacketID, const TArray<uint8>& Payload);
    void EnqueueSendCommand(uint16 PacketID);


    TSharedPtr<FClientNetworkWorker> Worker;

    FString CachedIP;
    int32 CachedPort = 9000;
    bool bDisconnectNotified = false;
};
