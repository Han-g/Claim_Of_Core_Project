#pragma once

#include "CoreMinimal.h"
#include "ClientNetworkTypes.generated.h"

// ============================================================
// Packet ID
// ============================================================
enum PacketID : uint16 {
    // ==========================================
    // Packet ID Rules
    // 9999      : Test Code
    // 1000 ~    : Error Code
    // 0   ~  99 : System Info (high-frequency sync / notices)
    // 100 ~ 119 : Server Prepare / Lobby Packet
    // 120 ~ 149 : Server InGame Sync / Combat Packet
    // 150 ~ 199 : Server Map / Match Flow Packet
    // 500 ~ 519 : Client Prepare / Lobby Request Packet
    // 520 ~ 549 : Client KeyInput Packet
    // 550 ~ 599 : Client InGame Logic Packet
    // ==========================================

    // [ Error Packets ]
    PKT_S2C_ERROR = 1000,
    PKT_C2S_ERROR = 1001,

    // [ System Info Packets (0 ~ 99) ]
    PKT_S2C_SNAPSHOT_NOTICE = 0,
    PKT_S2C_ROOM_CREATE_NOTICE = 1,
    PKT_S2C_ROOM_JOIN_NOTICE = 2,
    PKT_S2C_ROOM_UPDATE_NOTICE = 3,
    PKT_S2C_MAP_SELECT_NOTICE = 4,
    PKT_S2C_SYNC_GAME_TIME_NOTICE = 5,

    // [ Prepare / Lobby Packets ]
    // S2C (100 ~ 119)
    PKT_S2C_ACCESS_ALLOW = 100,
    PKT_S2C_LOGIN_OK = 101,
    PKT_S2C_LOGIN_DENY = 102,
    PKT_S2C_REGISTER_OK = 103,
    PKT_S2C_REGISTER_DENY = 104,
    PKT_S2C_ROOM_UPDATE = 105,
    PKT_S2C_ROOM_ENTER = 106,

    PKT_S2C_ROOM_INFO_BRD = 110,
    PKT_S2C_CHARACTER_SELECT_BRD = 111,
    PKT_S2C_GAME_START_BRD = 112,

    // C2S (500 ~ 519)
    PKT_C2S_ACCESS_REQ = 500,
    PKT_C2S_LOGIN_REQ = 501,
    PKT_C2S_REGISTER_REQ = 502,
    PKT_C2S_ROOM_LIST_REQ = 504,
    PKT_C2S_ROOM_CREATE_REQ = 505,
    PKT_C2S_ROOM_JOIN_REQ = 506,
    PKT_C2S_MAP_SELECT_REQ = 507,
    PKT_C2S_CHARACTER_SELECT_REQ = 508,
    PKT_C2S_GAME_START_REQ = 509,
    PKT_C2S_READY_REQ = 510,

    // [ InGame Sync / Combat Packets ]
    PKT_C2S_MOVE_KEYINPUT = 520,
    PKT_C2S_JUMP_KEYINPUT = 521,
    PKT_S2C_SYNC_ANIMATION_BRD = 115,

    PKT_C2S_ATTACK_KEYINPUT = 550,
    PKT_S2C_ATTACK_ACTION_BRD = 120,
    PKT_S2C_DAMAGE_APPLY_BRD = 121,
    PKT_S2C_STATE_CHANGE_BRD = 122,
    PKT_S2C_STATUS_UPDATE_BRD = 123,
    PKT_S2C_RESPAWN_BRD = 124,

    PKT_C2S_ITEMPICKUP_KEYINPUT = 551,
    PKT_C2S_ITEMDROP_KEYINPUT = 552,
    PKT_C2S_OBJECT_HIT_REQ = 553,

    PKT_S2C_SPAWN_ITEM_BRD = 130,
    PKT_S2C_DESPAWN_ITEM_BRD = 131,
    PKT_S2C_ITEM_OWNERSHIP_BRD = 132,
    PKT_S2C_SPAWN_OBJECT_BRD = 133,
    PKT_S2C_OBJECT_DESTRUCT_BRD = 134,

    PKT_S2C_MAPEVENT_TRIGGER_BRD = 150,
    PKT_S2C_GAME_PHASE_CHANGE_BRD = 151,
    PKT_S2C_GAME_RESULT_BRD = 152,
};

// ============================================================
// Game Data
// ============================================================
struct GameData {
    int userUID = -1;
    bool isConnected = false;

    int maxHP = 100;
    int currentHP = 100;

    float x = 0, y = 0, z = 0;
    float rotate = 0;
    float baseWalkSpeed = 500.f;

    int characterState = -1;    // 0=Alive, 1=Dead
    int roleType = -1;          // 0=Striker, 1=Guardian, 2=Manipulator

    int animationNum = 0;
};

// ============================================================
// Wire-format Packet Structs (packed)
// ============================================================
#pragma pack(push, 1)
struct FPacketHeader {
    uint16 PacketSize;
    uint16 PacketID;
};

struct FLoginPacket {
    FString userID;
    FString userPW;
};

struct FRoomPacketData {
    int32 RoomID;
    wchar_t RoomName[20];
    int32 CurrentPlayers;
};

struct FRoomMemberPacketData {
    wchar_t PlayerName[20];
    bool isReady;
    bool isHost;
};

struct FGamedataPacket {
    int sessionID;
    GameData data;
};

struct FMapEventPacket {
    int32_t eventType;
    int32_t objectIndex;
    int32_t eventState;
};

struct FSpawnObjectPacket {
    int32_t objectType;
    float x, y, z;
    int32_t objectID;
};

struct FPhaseChangePacket {
    int32_t roundState;
    int32_t mapPhase;
    float gameTime;
};

struct FMovePacket {
    float X, Y, Z;
    float Yaw;
    float VelocityX, VelocityY;
};

struct FDamageApplyPacket { int32 TargetID; int32 Damage; int32 RemainHP; };

struct FStatusUpdatePacket { int32 TargetID; int32 CurrentHP; };        

struct FStateChangePacket { int32 TargetID; int32 NewState; };

struct FRespawnPacket { int32 TargetID; float X, Y, Z; int32 HP; };

struct FRoleChangePacket { int32 TargetID; int32 NewRoleType; };

struct FSyncGameTimePacket { float GameTime; };

struct FAttackActionPacket { int32 AttackerID; int32 AttackType; };

struct FSyncAnimationPacket { int32 TargetID; int32 AnimationNum; };

#pragma pack(pop)

// ============================================================
// USTRUCTs (for UMG / Blueprint)
// ============================================================
USTRUCT(BlueprintType)
struct FRoomInfoData
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly)
    int32 RoomID = 0;
    UPROPERTY(BlueprintReadOnly)
    FString RoomName;
    UPROPERTY(BlueprintReadOnly)
    int32 CurrentPlayers = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 MaxPlayers = 0;
};

USTRUCT()
struct FRoomMemberInfo
{
    GENERATED_BODY()
    FString PlayerName;
    bool bIsReady = false;
};

// ============================================================
// Multicast Delegates
// ============================================================
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoomListUpdated, const TArray<FRoomInfoData>&);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRoomEntered, bool, const TArray<FRoomMemberInfo>&);
DECLARE_MULTICAST_DELEGATE(FOnGameStartDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginResultDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterResultDelegate, bool);
DECLARE_MULTICAST_DELEGATE(FOnDisconnectDelegate);
DECLARE_MULTICAST_DELEGATE(FOnConnectedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnConnectFailedDelegate);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnDamageApplied, const FDamageApplyPacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatusUpdated, const FStatusUpdatePacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateChanged, const FStateChangePacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRespawned, const FRespawnPacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoleChanged, const FRoleChangePacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameTimeSynced, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, const FPhaseChangePacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMapEventTriggered, const FMapEventPacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnObjectSpawned, const FSpawnObjectPacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttackActionReceived, const FAttackActionPacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSyncAnimationReceived, const FSyncAnimationPacket&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSnapshotReceived, const TArray<GameData>&);

// ============================================================
// Worker Thread ↔ Main Thread Communication
// ============================================================

// --- Commands (Main Thread → Worker Thread) ---
enum class ENetCommandType : uint8
{
    Connect,
    Disconnect,
    SendPacket,
    Reconnect,
    Shutdown,
};

struct FNetCommand
{
    ENetCommandType Type;
    FString IP;
    int32 Port = 0;
    uint16 PacketID = 0;
    TArray<uint8> Payload;
};

// --- Events (Worker Thread → Main Thread) ---
enum class ENetEventType : uint8
{
    Connected,
    ConnectFailed,
    Disconnected,
    LoginResult,
    RegisterResult,
    RoomListUpdated,
    RoomEntered,
    RoomInfoUpdated,
    GameStart,
    SnapshotReceived,
    AttackAction,
    DamageApply,
    StateChange,
    StatusUpdate,
    Respawn,
    SyncAnimation,
    AccessAllow,
    GameTimeSynced,
    RoleChanged,
    MapEventTriggered,
    ObjectSpawned,
    PhaseChanged,
};

struct FNetEvent
{
    ENetEventType Type;

    bool bSuccess = false;

    TArray<FRoomInfoData> RoomList;
    TArray<FRoomMemberInfo> MemberList;
    TArray<GameData> SnapshotList;

    int32 SessionID = -1;
    GameData PlayerData;

    float SyncedGameTime = 0.f;

    FDamageApplyPacket   DamageApply;
    FStatusUpdatePacket  StatusUpdate;
    FStateChangePacket   StateChange;
    FRespawnPacket       Respawn;
    FRoleChangePacket    RoleChange;
    FPhaseChangePacket   PhaseChange;
    FMapEventPacket      MapEvent;
    FSpawnObjectPacket   SpawnObject;
    FAttackActionPacket  AttackAction;
    FSyncAnimationPacket SyncAnimation;
};
