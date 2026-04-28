#include "ClientNetworking.h"
#include "ClientNetworkWorker.h"
#include "Serialization/BufferArchive.h"

ClientNetworking::ClientNetworking()
{
}

ClientNetworking::~ClientNetworking()
{
    Shutdown();
}

void ClientNetworking::TestFuncInput(PacketID testPacket)
{
    switch (testPacket)
    {
    case PKT_C2S_ATTACK_KEYINPUT:
        UE_LOG(LogTemp, Display, TEXT("[ClientTest] Send test packet: %d"), static_cast<uint16>(testPacket));
        EnqueueSendCommand(static_cast<uint16>(testPacket));
        break;

    case PKT_C2S_READY_REQ:
        break;

    case PKT_C2S_GAME_START_REQ:
        break;

    case PKT_C2S_ITEMPICKUP_KEYINPUT:
        break;

    case PKT_C2S_ITEMDROP_KEYINPUT:
        UE_LOG(LogTemp, Display, TEXT("[ClientTest] Send test packet: %d"), static_cast<uint16>(testPacket));
        EnqueueSendCommand(static_cast<uint16>(testPacket));
        break;

    default:
        UE_LOG(LogTemp, Warning,
            TEXT("[ClientTest] TestFuncInput does not support packet %d. Use a dedicated request function."),
            static_cast<uint16>(testPacket));
        break;
    }
}

// ============================================================
// Lifecycle
// ============================================================
void ClientNetworking::Start(const FString& IP, int32 Port)
{
    CachedIP = IP;
    CachedPort = Port;
    bDisconnectNotified = false;

    if (!Worker.IsValid())
    {
        Worker = MakeShared<FClientNetworkWorker>();
    }

    RequestConnect(IP, Port);
}

void ClientNetworking::Shutdown()
{
    if (Worker.IsValid())
    {
        FNetCommand Cmd;
        Cmd.Type = ENetCommandType::Shutdown;
        Worker->InboundCommandQueue.Enqueue(Cmd);
        Worker->WakeUp();

        Worker.Reset();
    }
}

// ============================================================
// PumpEvents — game thread only
// ============================================================
void ClientNetworking::PumpEvents()
{
    check(IsInGameThread());

    if (!Worker.IsValid()) { return; }

    static int32 SnapshotLogCounter = 0;
    SnapshotLogCounter++;

    FNetEvent Evt;
    while (Worker->OutboundEventQueue.Dequeue(Evt))
    {
        switch (Evt.Type)
        {
        case ENetEventType::Connected:
            UE_LOG(LogTemp, Display, TEXT("Connected to server!"));
            bDisconnectNotified = false;
            OnConnected.Broadcast();
            break;

        case ENetEventType::ConnectFailed:
            UE_LOG(LogTemp, Error, TEXT("Connect failed!"));
            OnConnectFailed.Broadcast();
            break;

        case ENetEventType::Disconnected:
            if (!bDisconnectNotified)
            {
                bDisconnectNotified = true;
                UE_LOG(LogTemp, Warning, TEXT("Disconnected from server!"));
                OnDisconnected.Broadcast();
            }
            break;

        case ENetEventType::AccessAllow:
            UE_LOG(LogTemp, Display, TEXT("Server Access Allowed!"));
            break;

        case ENetEventType::LoginResult:
            if (Evt.bSuccess)
            {
                IsLogin = true;
                ClientSessionID = Evt.SessionID;
                ClientPlayerData = Evt.PlayerData;
                UE_LOG(LogTemp, Display, TEXT("Login OK! SessionID=%d, UID=%d"), ClientSessionID, ClientPlayerData.userUID);
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("Login Denied!"));
            }
            OnLoginResult.Broadcast(Evt.bSuccess);
            break;

        case ENetEventType::RegisterResult:
            UE_LOG(LogTemp, Display, TEXT("Register %s"), Evt.bSuccess ? TEXT("OK") : TEXT("Denied"));
            OnRegisterResult.Broadcast(Evt.bSuccess);
            break;

        case ENetEventType::RoomListUpdated:
            UE_LOG(LogTemp, Display, TEXT("Room list updated: %d rooms"), Evt.RoomList.Num());
            OnRoomListUpdated.Broadcast(Evt.RoomList);
            break;

        case ENetEventType::RoomEntered:
            UE_LOG(LogTemp, Display, TEXT("Room entered! Members: %d"), Evt.MemberList.Num());
            OnRoomEnterResult.Broadcast(Evt.bSuccess, Evt.MemberList);
            break;

        case ENetEventType::RoomInfoUpdated:
            UE_LOG(LogTemp, Display, TEXT("Room info updated! Members: %d"), Evt.MemberList.Num());
            OnRoomEnterResult.Broadcast(true, Evt.MemberList);
            break;

        case ENetEventType::GameStart:
            UE_LOG(LogTemp, Display, TEXT("Game Start!"));
            OnGameStart.Broadcast();
            break;

        case ENetEventType::SnapshotReceived:
            if (SnapshotLogCounter % 30 == 0)
            {
                UE_LOG(LogTemp, Display, TEXT("Snapshot received: Count=%d"), Evt.SnapshotList.Num());
            }
            OnSnapshotReceived.Broadcast(Evt.SnapshotList);
            break;

        case ENetEventType::AttackAction:
            UE_LOG(LogTemp, Display, TEXT("Attack Action received"));
            OnAttackAction.Broadcast(Evt.AttackAction);
            break;
        case ENetEventType::DamageApply:
            UE_LOG(LogTemp, Display, TEXT("Damage Apply received"));
            OnDamageApplied.Broadcast(Evt.DamageApply);
            break;
        case ENetEventType::StateChange:
            UE_LOG(LogTemp, Display, TEXT("State Change received"));
            OnStateChanged.Broadcast(Evt.StateChange);
            break;
        case ENetEventType::StatusUpdate:
            UE_LOG(LogTemp, Display, TEXT("Status Update received"));
            OnStatusUpdated.Broadcast(Evt.StatusUpdate);
            break;
        case ENetEventType::Respawn:
            UE_LOG(LogTemp, Display, TEXT("Respawn received"));
            OnRespawned.Broadcast(Evt.Respawn);
            break;
        case ENetEventType::SyncAnimation:
            UE_LOG(LogTemp, Display, TEXT("Sync Animation received"));
            OnSyncAnimation.Broadcast(Evt.SyncAnimation);
            break;
        }
    }
}

// ============================================================
// Command Enqueue Helpers
// ============================================================
void ClientNetworking::EnqueueSendCommand(uint16 PacketID, const TArray<uint8>& Payload)
{
    if (!Worker.IsValid()) { return; }

    FNetCommand Cmd;
    Cmd.Type = ENetCommandType::SendPacket;
    Cmd.PacketID = PacketID;
    Cmd.Payload = Payload;
    Worker->InboundCommandQueue.Enqueue(Cmd);
    Worker->WakeUp();
}

void ClientNetworking::EnqueueSendCommand(uint16 PacketID)
{
    TArray<uint8> Empty;
    EnqueueSendCommand(PacketID, Empty);
}

// ============================================================
// Request Methods (main thread — enqueue only)
// ============================================================
void ClientNetworking::RequestConnect(const FString& IP, int32 Port)
{
    if (!Worker.IsValid()) { return; }

    CachedIP = IP;
    CachedPort = Port;

    FNetCommand Cmd;
    Cmd.Type = ENetCommandType::Connect;
    Cmd.IP = IP;
    Cmd.Port = Port;
    Worker->InboundCommandQueue.Enqueue(Cmd);
    Worker->WakeUp();
}

void ClientNetworking::RequestDisconnect()
{
    if (!Worker.IsValid()) { return; }

    FNetCommand Cmd;
    Cmd.Type = ENetCommandType::Disconnect;
    Worker->InboundCommandQueue.Enqueue(Cmd);
    Worker->WakeUp();
}

void ClientNetworking::RequestReconnect()
{
    if (!Worker.IsValid()) { return; }

    bDisconnectNotified = false;

    FNetCommand Cmd;
    Cmd.Type = ENetCommandType::Reconnect;
    Cmd.IP = CachedIP;
    Cmd.Port = CachedPort;
    Worker->InboundCommandQueue.Enqueue(Cmd);
    Worker->WakeUp();
}

void ClientNetworking::LoginAccess(FString& ID, FString& PW)
{
    FBufferArchive Data;
    Data << ID;
    Data << PW;

    TArray<uint8> Payload;
    // Build header + payload in old PacketAssemble format
    FPacketHeader Header;
    Header.PacketID = PKT_C2S_LOGIN_REQ;
    Header.PacketSize = sizeof(FPacketHeader) + Data.Num();

    Payload.Append((uint8*)&Header, sizeof(FPacketHeader));
    if (Data.Num() > 0) { Payload.Append(Data); }

    // For login, we send the full assembled packet as raw bytes
    // The worker's SendRawPacket adds its own header, so we send payload only
    TArray<uint8> PayloadOnly;
    PayloadOnly.Append(Data.GetData(), Data.Num());
    EnqueueSendCommand(PKT_C2S_LOGIN_REQ, PayloadOnly);
}

void ClientNetworking::RegisterRequest(FString& ID, FString& PW)
{
    FBufferArchive Data;
    Data << ID;
    Data << PW;

    TArray<uint8> PayloadOnly;
    PayloadOnly.Append(Data.GetData(), Data.Num());
    EnqueueSendCommand(PKT_C2S_REGISTER_REQ, PayloadOnly);
}

void ClientNetworking::CreateRoomRequest()
{
    EnqueueSendCommand(PKT_C2S_ROOM_CREATE_REQ);
}

void ClientNetworking::CharacterSelectRequest(int32 RoleType)
{
    TArray<uint8> Payload;
    Payload.SetNumUninitialized(sizeof(int32));
    FMemory::Memcpy(Payload.GetData(), &RoleType, sizeof(int32));

    EnqueueSendCommand(PKT_C2S_CHARACTER_SELECT_REQ, Payload);
}

void ClientNetworking::JoinRoomRequest(int32 RoomID)
{
    TArray<uint8> Payload;
    Payload.Append((uint8*)&RoomID, sizeof(int32));
    EnqueueSendCommand(PKT_C2S_ROOM_JOIN_REQ, Payload);
}

void ClientNetworking::ReadyToggleRequest()
{
    EnqueueSendCommand(PKT_C2S_READY_REQ);
}

void ClientNetworking::GameStartRequest()
{
    EnqueueSendCommand(PKT_C2S_GAME_START_REQ);
}

void ClientNetworking::SendMoveInput(const FMovePacket& MoveData)
{
    TArray<uint8> Payload;
    Payload.Append((const uint8*)&MoveData, sizeof(FMovePacket));
    EnqueueSendCommand(PKT_C2S_MOVE_KEYINPUT, Payload);
}
