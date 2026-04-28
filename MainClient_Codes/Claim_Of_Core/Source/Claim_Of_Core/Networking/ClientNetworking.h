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
    void CharacterSelectRequest(int32 RoleType);
    void JoinRoomRequest(int32 RoomID);
    void ReadyToggleRequest();
    void GameStartRequest();

    void SendMoveInput(const FMovePacket& MoveData);

    // Delegates (broadcast on game thread only)
    FOnConnectedDelegate OnConnected;
    FOnConnectFailedDelegate OnConnectFailed;
    FOnDisconnectDelegate OnDisconnected;
    FOnLoginResultDelegate OnLoginResult;
    FOnRegisterResultDelegate OnRegisterResult;
    FOnRoomListUpdated OnRoomListUpdated;
    FOnRoomEntered OnRoomEnterResult;
    FOnGameStartDelegate OnGameStart;

    FOnDamageApplied OnDamageApplied;
    FOnStatusUpdated OnStatusUpdated;
    FOnStateChanged OnStateChanged;
    FOnRespawned OnRespawned;
    FOnRoleChanged OnRoleChanged;
    FOnGameTimeSynced OnGameTimeSynced;
    FOnPhaseChanged OnPhaseChanged;
    FOnMapEventTriggered OnMapEventTriggered;
    FOnObjectSpawned OnObjectSpawned;
    FOnAttackActionReceived OnAttackAction;
    FOnSyncAnimationReceived OnSyncAnimation;
    FOnSnapshotReceived OnSnapshotReceived;

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
