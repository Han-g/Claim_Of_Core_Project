#include "ClientNetworkWorker.h"

#include "Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Serialization/BufferArchive.h"

FClientNetworkWorker::FClientNetworkWorker()
    : Socket(nullptr)
    , Thread(nullptr)
    , WakeEvent(nullptr)
    , bStopRequested(false)
{
    WakeEvent = FPlatformProcess::GetSynchEventFromPool(false);
    Thread = FRunnableThread::Create(this, TEXT("ClientNetworkWorker"), 0, TPri_Normal);
}

FClientNetworkWorker::~FClientNetworkWorker()
{
    bStopRequested = true;
    if (WakeEvent) { WakeEvent->Trigger(); }

    if (Thread)
    {
        Thread->WaitForCompletion();
        delete Thread;
        Thread = nullptr;
    }

    CloseSocket();

    if (WakeEvent)
    {
        FPlatformProcess::ReturnSynchEventToPool(WakeEvent);
        WakeEvent = nullptr;
    }
}

// ============================================================
// FRunnable Interface
// ============================================================
bool FClientNetworkWorker::Init()
{
    return true;
}

uint32 FClientNetworkWorker::Run()
{
    while (!bStopRequested)
    {
        FlushInboundCommands();

        if (bReconnecting)
        {
            HandleReconnect();
        }

        if (Socket && Socket->GetConnectionState() == SCS_Connected)
        {
            RecvAndParsePackets();
        }

        // Wait up to 10ms or until woken by a new command
        if (WakeEvent) { WakeEvent->Wait(10); }
    }

    CloseSocket();
    return 0;
}

void FClientNetworkWorker::Stop()
{
    bStopRequested = true;
    if (WakeEvent) { WakeEvent->Trigger(); }
}

void FClientNetworkWorker::Exit()
{
}

void FClientNetworkWorker::WakeUp()
{
    if (WakeEvent) { WakeEvent->Trigger(); }
}

// ============================================================
// Socket Operations (worker thread only)
// ============================================================
bool FClientNetworkWorker::TryConnectBlocking(const FString& IP, int32 Port)
{
    CloseSocket();

    Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("ClientSocket"), false);
    if (!Socket) { return false; }

    FIPv4Address IPAddress;
    if (!FIPv4Address::Parse(IP, IPAddress))
    {
        CloseSocket();
        return false;
    }

    TSharedRef<FInternetAddr> ServerAddr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    ServerAddr->SetIp(IPAddress.Value);
    ServerAddr->SetPort(Port);

    UE_LOG(LogTemp, Display, TEXT("[Worker] Connecting to %s:%d..."), *IP, Port);

    bool bConnected = Socket->Connect(*ServerAddr);
    if (bConnected)
    {
        Socket->SetNonBlocking(true);
        UE_LOG(LogTemp, Display, TEXT("[Worker] Connected!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("[Worker] Connect failed!"));
        CloseSocket();
    }

    return bConnected;
}

void FClientNetworkWorker::CloseSocket()
{
    if (Socket)
    {
        Socket->Close();
        ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(Socket);
        Socket = nullptr;
    }
    RecvBuffer.Empty();
}

// ============================================================
// Command Processing
// ============================================================
void FClientNetworkWorker::FlushInboundCommands()
{
    FNetCommand Cmd;
    while (InboundCommandQueue.Dequeue(Cmd))
    {
        switch (Cmd.Type)
        {
        case ENetCommandType::Connect:
        {
            bool bOk = TryConnectBlocking(Cmd.IP, Cmd.Port);
            FNetEvent Evt;
            Evt.Type = bOk ? ENetEventType::Connected : ENetEventType::ConnectFailed;
            PushEvent(MoveTemp(Evt));

            if (bOk)
            {
                ReconnectIP = Cmd.IP;
                ReconnectPort = Cmd.Port;
                bReconnecting = false;
                ReconnectRetryCount = 0;
            }
            break;
        }
        case ENetCommandType::Disconnect:
        {
            CloseSocket();
            bReconnecting = false;
            FNetEvent Evt;
            Evt.Type = ENetEventType::Disconnected;
            PushEvent(MoveTemp(Evt));
            break;
        }
        case ENetCommandType::SendPacket:
        {
            SendRawPacket(Cmd.PacketID, Cmd.Payload);
            break;
        }
        case ENetCommandType::Reconnect:
        {
            ReconnectIP = Cmd.IP;
            ReconnectPort = Cmd.Port;
            bReconnecting = true;
            ReconnectRetryCount = 0;
            CloseSocket();
            break;
        }
        case ENetCommandType::Shutdown:
        {
            CloseSocket();
            bStopRequested = true;
            break;
        }
        }
    }
}

// ============================================================
// Recv & Parse
// ============================================================
void FClientNetworkWorker::RecvAndParsePackets()
{
    if (!Socket) { return; }

    // Check for disconnect
    if (Socket->GetConnectionState() != SCS_Connected)
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::Disconnected;
        PushEvent(MoveTemp(Evt));
        CloseSocket();
        return;
    }

    uint32 PendingDataSize = 0;
    if (Socket->HasPendingData(PendingDataSize) && PendingDataSize > 0)
    {
        TArray<uint8> TempBuffer;
        TempBuffer.SetNumUninitialized(PendingDataSize);

        int32 ReadBytes = 0;
        if (!Socket->Recv(TempBuffer.GetData(), PendingDataSize, ReadBytes))
        {
            FNetEvent Evt;
            Evt.Type = ENetEventType::Disconnected;
            PushEvent(MoveTemp(Evt));
            CloseSocket();
            return;
        }

        if (ReadBytes == 0)
        {
            FNetEvent Evt;
            Evt.Type = ENetEventType::Disconnected;
            PushEvent(MoveTemp(Evt));
            CloseSocket();
            return;
        }

        if (ReadBytes > 0)
        {
            RecvBuffer.Append(TempBuffer.GetData(), ReadBytes);
        }
    }

    // Parse complete packets
    while (RecvBuffer.Num() >= (int32)sizeof(FPacketHeader))
    {
        FPacketHeader* Header = reinterpret_cast<FPacketHeader*>(RecvBuffer.GetData());

        if (RecvBuffer.Num() < Header->PacketSize) { break; }

        uint16 PayloadSize = Header->PacketSize - sizeof(FPacketHeader);
        uint8* PayloadData = RecvBuffer.GetData() + sizeof(FPacketHeader);

        HandlePacket(Header, PayloadData, PayloadSize);

        RecvBuffer.RemoveAt(0, Header->PacketSize);
    }
}

// ============================================================
// Packet Handling → Push Events
// ============================================================
void FClientNetworkWorker::HandlePacket(FPacketHeader* Header, uint8* PayloadData, uint16 PayloadSize)
{
    switch (Header->PacketID)
    {
    case PKT_S2C_ACCESS_ALLOW:
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::AccessAllow;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_LOGIN_OK:
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::LoginResult;
        Evt.bSuccess = true;

        if (PayloadSize >= sizeof(FGamedataPacket))
        {
            FGamedataPacket Pkt;
            FMemory::Memcpy(&Pkt, PayloadData, sizeof(FGamedataPacket));
            Evt.SessionID = Pkt.sessionID;
            Evt.PlayerData = Pkt.data;
        }

        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_LOGIN_DENY:
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::LoginResult;
        Evt.bSuccess = false;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_REGISTER_OK:
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::RegisterResult;
        Evt.bSuccess = true;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_REGISTER_DENY:
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::RegisterResult;
        Evt.bSuccess = false;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_SNAPSHOT_NOTICE:
    {
        if (PayloadSize < sizeof(int32)) { break; }

        int32 UserCount = 0;
        FMemory::Memcpy(&UserCount, PayloadData, sizeof(int32));

        int32 ExpectedSize = sizeof(int32) + UserCount * sizeof(GameData);
        if (PayloadSize < ExpectedSize || UserCount < 0 || UserCount > 100) { break; }

        FNetEvent Evt;
        Evt.Type = ENetEventType::SnapshotReceived;
        int32 Offset = sizeof(int32);
        for (int32 i = 0; i < UserCount; ++i)
        {
            GameData TempData;
            FMemory::Memcpy(&TempData, PayloadData + Offset, sizeof(GameData));
            Evt.SnapshotList.Add(TempData);
            Offset += sizeof(GameData);
        }
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_ROOM_UPDATE:
    {
        if (PayloadSize < sizeof(int32)) { break; }

        int32 RoomCount = 0;
        FMemory::Memcpy(&RoomCount, PayloadData, sizeof(int32));

        int32 CurrentOffset = sizeof(int32);
        int32 ExpectedSize = sizeof(int32) + RoomCount * sizeof(FRoomPacketData);
        if (PayloadSize < ExpectedSize || RoomCount < 0 || RoomCount > 1000) { break; }

        FNetEvent Evt;
        Evt.Type = ENetEventType::RoomListUpdated;
        for (int32 i = 0; i < RoomCount; ++i)
        {
            FRoomPacketData RoomTempData;
            FMemory::Memcpy(&RoomTempData, PayloadData + CurrentOffset, sizeof(FRoomPacketData));

            FRoomInfoData Info;
            Info.RoomID = RoomTempData.RoomID;
            Info.RoomName = FString(RoomTempData.RoomName);
            Info.CurrentPlayers = RoomTempData.CurrentPlayers;
            Evt.RoomList.Add(Info);

            CurrentOffset += sizeof(FRoomPacketData);
        }
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_ROOM_ENTER:
    {
        int32 CurrentOffset = 0;

        if (PayloadSize < sizeof(int32) * 2) { break; }

        int32 EnteredRoomID = 0;
        FMemory::Memcpy(&EnteredRoomID, PayloadData, sizeof(int32));
        CurrentOffset += sizeof(int32);

        int32 MemberCount = 0;
        FMemory::Memcpy(&MemberCount, PayloadData + CurrentOffset, sizeof(int32));
        CurrentOffset += sizeof(int32);

        int32 ExpectedSize = CurrentOffset + MemberCount * sizeof(FRoomMemberPacketData);
        if (PayloadSize < ExpectedSize || MemberCount < 0 || MemberCount > 100) { break; }

        FNetEvent Evt;
        Evt.Type = ENetEventType::RoomEntered;
        Evt.bSuccess = true;
        for (int32 i = 0; i < MemberCount; ++i)
        {
            FRoomMemberPacketData MemberData;
            FMemory::Memcpy(&MemberData, PayloadData + CurrentOffset, sizeof(FRoomMemberPacketData));
            CurrentOffset += sizeof(FRoomMemberPacketData);

            FRoomMemberInfo MInfo;
            MInfo.PlayerName = FString(MemberData.PlayerName);
            MInfo.bIsReady = MemberData.isReady;
            Evt.MemberList.Add(MInfo);
        }
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_ROOM_INFO_BRD:
    {
        if (PayloadSize < sizeof(int32)) { break; }

        int32 CurrentOffset = 0;
        int32 MemberCount = 0;
        FMemory::Memcpy(&MemberCount, PayloadData + CurrentOffset, sizeof(int32));
        CurrentOffset += sizeof(int32);

        int32 ExpectedSize = CurrentOffset + MemberCount * sizeof(FRoomMemberPacketData);
        if (PayloadSize < ExpectedSize || MemberCount < 0 || MemberCount > 100) { break; }

        FNetEvent Evt;
        Evt.Type = ENetEventType::RoomInfoUpdated;
        Evt.bSuccess = true;
        for (int32 i = 0; i < MemberCount; ++i)
        {
            FRoomMemberPacketData MemberData;
            FMemory::Memcpy(&MemberData, PayloadData + CurrentOffset, sizeof(FRoomMemberPacketData));
            CurrentOffset += sizeof(FRoomMemberPacketData);

            FRoomMemberInfo MInfo;
            MInfo.PlayerName = FString(MemberData.PlayerName);
            MInfo.bIsReady = MemberData.isReady;
            Evt.MemberList.Add(MInfo);
        }
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_GAME_START_BRD:
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::GameStart;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_ATTACK_ACTION_BRD:
    {
        if (PayloadSize < sizeof(FAttackActionPacket)) { break; }

        FAttackActionPacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FAttackActionPacket));
        UE_LOG(LogTemp, Display, TEXT("[Attack Packet Trace] AttackerID=%d AttackType=%d"),
            Packet.AttackerID, Packet.AttackType);

        FNetEvent Evt;
        Evt.Type = ENetEventType::AttackAction;
        Evt.AttackAction = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_DAMAGE_APPLY_BRD:
    {
        if (PayloadSize < sizeof(FDamageApplyPacket)) { break; }

        FDamageApplyPacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FDamageApplyPacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::DamageApply;
        Evt.DamageApply = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_STATE_CHANGE_BRD:
    {
        if (PayloadSize < sizeof(FStateChangePacket)) { break; }

        FStateChangePacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FStateChangePacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::StateChange;
        Evt.StateChange = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_STATUS_UPDATE_BRD:
    {
        if (PayloadSize < sizeof(FStatusUpdatePacket)) { break; }

        FStatusUpdatePacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FStatusUpdatePacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::StatusUpdate;
        Evt.StatusUpdate = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_RESPAWN_BRD:
    {
        if (PayloadSize < sizeof(FRespawnPacket)) { break; }

        FRespawnPacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FRespawnPacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::Respawn;
        Evt.Respawn = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_SYNC_ANIMATION_BRD:
    {
        if (PayloadSize < sizeof(FSyncAnimationPacket)) { break; }

        FSyncAnimationPacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FSyncAnimationPacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::SyncAnimation;
        Evt.SyncAnimation = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_CHARACTER_SELECT_BRD:
    {
        if (PayloadSize < sizeof(FRoleChangePacket)) { break; }

        FRoleChangePacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FRoleChangePacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::RoleChanged;
        Evt.RoleChange = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_SYNC_GAME_TIME_NOTICE:
    {
        if (PayloadSize < sizeof(FSyncGameTimePacket)) { break; }

        FSyncGameTimePacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FSyncGameTimePacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::GameTimeSynced;
        Evt.SyncedGameTime = Packet.GameTime;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_MAPEVENT_TRIGGER_BRD:
    {
        if (PayloadSize < sizeof(FMapEventPacket)) { break; }

        FMapEventPacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FMapEventPacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::MapEventTriggered;
        Evt.MapEvent = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_SPAWN_OBJECT_BRD:
    {
        if (PayloadSize < sizeof(FSpawnObjectPacket)) { break; }

        FSpawnObjectPacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FSpawnObjectPacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::ObjectSpawned;
        Evt.SpawnObject = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    case PKT_S2C_GAME_PHASE_CHANGE_BRD:
    {
        if (PayloadSize < sizeof(FPhaseChangePacket)) { break; }

        FPhaseChangePacket Packet;
        FMemory::Memcpy(&Packet, PayloadData, sizeof(FPhaseChangePacket));

        FNetEvent Evt;
        Evt.Type = ENetEventType::PhaseChanged;
        Evt.PhaseChange = Packet;
        PushEvent(MoveTemp(Evt));
        break;
    }
    default:
        UE_LOG(LogTemp, Warning, TEXT("[Worker] Unknown Packet ID: %d"), Header->PacketID);
        break;
    }
}

// ============================================================
// Send (worker thread)
// ============================================================
void FClientNetworkWorker::SendRawPacket(uint16 PacketID, const TArray<uint8>& Payload)
{
    if (!Socket || Socket->GetConnectionState() != SCS_Connected)
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::Disconnected;
        PushEvent(MoveTemp(Evt));
        return;
    }

    uint16 BufferSize = sizeof(FPacketHeader) + Payload.Num();
    TArray<uint8> SendBuffer;
    SendBuffer.SetNum(BufferSize);

    FPacketHeader* Header = reinterpret_cast<FPacketHeader*>(SendBuffer.GetData());
    Header->PacketID = PacketID;
    Header->PacketSize = BufferSize;

    if (Payload.Num() > 0)
    {
        FMemory::Memcpy(SendBuffer.GetData() + sizeof(FPacketHeader), Payload.GetData(), Payload.Num());
    }

    int32 BytesSent = 0;
    if (!Socket->Send(SendBuffer.GetData(), SendBuffer.Num(), BytesSent))
    {
        FNetEvent Evt;
        Evt.Type = ENetEventType::Disconnected;
        PushEvent(MoveTemp(Evt));
        CloseSocket();
    }
}

// ============================================================
// Event Push
// ============================================================
void FClientNetworkWorker::PushEvent(FNetEvent&& Event)
{
    OutboundEventQueue.Enqueue(MoveTemp(Event));
}

// ============================================================
// Reconnection
// ============================================================
void FClientNetworkWorker::HandleReconnect()
{
    if (!bReconnecting) { return; }

    if (ReconnectRetryCount >= MaxReconnectRetries)
    {
        UE_LOG(LogTemp, Error, TEXT("[Worker] Max reconnect retries reached (%d). Giving up."), MaxReconnectRetries);
        bReconnecting = false;

        FNetEvent Evt;
        Evt.Type = ENetEventType::Disconnected;
        PushEvent(MoveTemp(Evt));
        return;
    }

    ReconnectRetryCount++;
    UE_LOG(LogTemp, Warning, TEXT("[Worker] Reconnect attempt %d/%d..."), ReconnectRetryCount, MaxReconnectRetries);

    bool bOk = TryConnectBlocking(ReconnectIP, ReconnectPort);
    if (bOk)
    {
        bReconnecting = false;
        ReconnectRetryCount = 0;

        FNetEvent Evt;
        Evt.Type = ENetEventType::Connected;
        PushEvent(MoveTemp(Evt));
    }
    else
    {
        // Wait before next retry (interruptible)
        int32 WaitMs = (int32)(ReconnectIntervalSec * 1000.f);
        if (WakeEvent) { WakeEvent->Wait(WaitMs); }
    }
}
