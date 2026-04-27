#pragma once

#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <string>
#include <cstdint>
#include <windows.h>

class PacketReader
{
public:
    // Initializes a reader over the packet buffer and optional payload offset.
    // Use the offset to skip the packet header and start from the payload.
    PacketReader(std::vector<char>& buffer, int offset = 0)
        : _buffer(buffer), _pos(offset)
    {
        _size = (int)buffer.size();
    }

    // Reads primitive types such as integers and floats.
    template<typename T>
    bool Read(T& outValue)
    {
        // Stop if the read would move past the available buffer.
        if (_pos + sizeof(T) > _size) return false;

        // Copy raw bytes from the current cursor position.
        memcpy(&outValue, &_buffer[_pos], sizeof(T));
        _pos += sizeof(T);
        return true;
    }

    // Reads an Unreal FString and auto-detects ANSI versus UTF-16 storage.
    bool ReadString(std::wstring& outString)
    {
        // 1. Read the FString length prefix first.
        int32_t len = 0;
        if (!Read(len)) return false;

        // A zero length means an empty string.
        if (len == 0) {
            outString.clear();
            return true;
        }

        // 2. Read the string payload.
        // Case A: ANSI string data (len > 0).
        if (len > 0)
        {
            if (_pos + len > _size) return false;

            char* ptr = &_buffer[_pos];

            // Convert ANSI bytes into a wide string.
            // len includes the null terminator, so only the visible characters are copied.
            // The terminator itself is skipped in the destination string.
            int wLen = MultiByteToWideChar(CP_ACP, 0, ptr, len, NULL, 0);
            outString.resize(wLen - 1); // reserve size excluding NULL
            MultiByteToWideChar(CP_ACP, 0, ptr, len - 1, &outString[0], wLen - 1);

            _pos += len; // Advance by the full byte count, including the null terminator.
        }
        // Case B: UTF-16 string data (len < 0).
        else
        {
            int32_t realLen = -len; // Actual UTF-16 character count, including the null terminator.
            int32_t byteSize = realLen * sizeof(wchar_t); // Total byte count for the UTF-16 payload.

            if (_pos + byteSize > _size) return false;

            // Copy directly into wstring because Windows wchar_t uses UTF-16 code units.
            outString.assign(reinterpret_cast<wchar_t*>(&_buffer[_pos]), realLen - 1);
            _pos += byteSize;
        }

        return true;
    }

private:
    std::vector<char>& _buffer;
    int _size;
    int _pos;
};

enum PacketID {
    // ==========================================
    // Packet ID ranges
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

    // ------------------------------------------
    // [ Error Packets ]
    // ------------------------------------------
    PKT_S2C_ERROR = 1000,
    PKT_C2S_ERROR = 1001,

    // ------------------------------------------
    // [ System Info Packets (0 ~ 99) ]
    // ------------------------------------------
    PKT_S2C_SNAPSHOT_NOTICE = 0,       // Continuous sync of TRANSFORM, DIRECTION, ANIMATION, etc.
    PKT_S2C_ROOM_CREATE_NOTICE = 1,    // System notice: room creation info
    PKT_S2C_ROOM_JOIN_NOTICE = 2,      // System notice: room join info
    PKT_S2C_ROOM_UPDATE_NOTICE = 3,    // System notice: room update
    PKT_S2C_MAP_SELECT_NOTICE = 4,     // System notice: map selection sync
    PKT_S2C_SYNC_GAME_TIME_NOTICE = 5, // Continuous server-timer sync (high-frequency)

    // ------------------------------------------
    // [ Prepare / Lobby Packets ]
    // ------------------------------------------
    // S2C (100 ~ 119)
    PKT_S2C_ACCESS_ALLOW = 100,
    PKT_S2C_LOGIN_OK = 101,
    PKT_S2C_LOGIN_DENY = 102,
    PKT_S2C_REGISTER_OK = 103,
    PKT_S2C_REGISTER_DENY = 104,
    PKT_S2C_ROOM_UPDATE = 105,
    PKT_S2C_ROOM_ENTER = 106,

    PKT_S2C_ROOM_INFO_BRD = 110,            // Sync of in-room member list and info
    PKT_S2C_CHARACTER_SELECT_BRD = 111,     // Broadcast of other users' character (role) selections
    PKT_S2C_GAME_START_BRD = 112,           // Server's game-start command in response to host's request

    // C2S (500 ~ 519)
    PKT_C2S_ACCESS_REQ = 500,
    PKT_C2S_LOGIN_REQ = 501,
    PKT_C2S_REGISTER_REQ = 502,
    PKT_C2S_ROOM_LIST_REQ = 504,            // Client -> Server: request room list update
    PKT_C2S_ROOM_CREATE_REQ = 505,          // Client -> Server: request to create a room
    PKT_C2S_ROOM_JOIN_REQ = 506,            // Client -> Server: request to join a room
    PKT_C2S_MAP_SELECT_REQ = 507,           // Client -> Server: select map to play
    PKT_C2S_CHARACTER_SELECT_REQ = 508,     // Client -> Server: character (role) selection request
    PKT_C2S_GAME_START_REQ = 509,           // Client (host) -> Server: game-start request
    PKT_C2S_READY_REQ = 510,

    // ------------------------------------------
    // [ InGame Sync / Combat Packets ]
    // ------------------------------------------
    // Character movement and action packets
    PKT_C2S_MOVE_KEYINPUT = 520,
    PKT_C2S_JUMP_KEYINPUT = 521,
    PKT_S2C_SYNC_ANIMATION_BRD = 115,       // One-shot animation sync outside the snapshot stream

    // Combat packets
    PKT_C2S_ATTACK_KEYINPUT = 550,          // Attack key-input notification
    PKT_S2C_ATTACK_ACTION_BRD = 120,        // After server validation, instruct attack motion playback (legacy 100-range ID)
    PKT_S2C_DAMAGE_APPLY_BRD = 121,         // Hit judgment + damage/knockback values
    PKT_S2C_STATE_CHANGE_BRD = 122,         // Life-state change (Dead / Alive, etc.)
    PKT_S2C_STATUS_UPDATE_BRD = 123,        // Stat change sync (HP, etc.)
    PKT_S2C_RESPAWN_BRD = 124,              // Character respawn info

    // Item and object management packets
    PKT_C2S_ITEMPICKUP_KEYINPUT = 551,      // Attempt to pick up an item
    PKT_C2S_ITEMDROP_KEYINPUT = 552,        // Attempt to drop the currently equipped item
    PKT_C2S_OBJECT_HIT_REQ = 553,           // Hit attempt on a destructible object (asks server to judge)

    PKT_S2C_SPAWN_ITEM_BRD = 130,           // Instruct spawning a specific item on the map
    PKT_S2C_DESPAWN_ITEM_BRD = 131,         // Instruct removing a specific item from the map
    PKT_S2C_ITEM_OWNERSHIP_BRD = 132,       // Item ownership acquisition (who picked up what)
    PKT_S2C_SPAWN_OBJECT_BRD = 133,         // Spawn map objects (breakable crates, etc.)
    PKT_S2C_OBJECT_DESTRUCT_BRD = 134,      // Object destruction + chaos-chunk VFX trigger

    // Game-logic and event-trigger packets
    PKT_S2C_MAPEVENT_TRIGGER_BRD = 150,     // Map gimmick trigger notice (ID fixed per spec)
    PKT_S2C_GAME_PHASE_CHANGE_BRD = 151,    // Phase transition (Waiting -> Playing -> Finished, etc.)
    PKT_S2C_GAME_RESULT_BRD = 152,          // End-of-game result: win/loss + kills/deaths
};

struct PacketHeader {
	unsigned short packet_size;
	unsigned short packet_ID;
};

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

#pragma pack(push, 1)
struct ErrorCodePacket {
    int16_t ErrorCode; 
    /*      Error code list
    10 : Register success,
    11 : Room Enter,
    0: Unknown , 
    1  : Invalid login credentials,
    2  : Failed to register account,
    3  : Room error,
    */
};


// ---------------------------------------
// ------   Game Prepare Packets    ------
// ---------------------------------------

struct LoginPacket {
    WCHAR userID[20];
    WCHAR userPW[20];
};

struct RoomPacket {
    int roomID; 
    WCHAR RoomName[20];
    int CurrentPlayers;
};

struct RoomMemberPacket {
    WCHAR PlayerName[20];
    bool isReady;
    bool isHost;
};

struct GameDataPacket {
	int Session_ID;
	GameData data;
};


// ---------------------------------------
// ------   Game Start Packets      ------
// ---------------------------------------

struct MapEventPacket {
    int32_t eventType;    // Event kind (Icicle, Floor, Debris, etc.)
    int32_t objectIndex;  // Index of the object placed on the map
    int32_t eventState;   // State (Warning, Breaking, Broken, etc.)
};

struct SpawnObjectPacket {
    int32_t objectType;   // SmallDebris, LargeDebris, etc.
    float x, y, z;        // Spawn position
    int32_t objectID;     // Server-assigned ID
};

struct PhaseChangePacket {
    int32_t roundState;   // 0 = Waiting, 1 = Playing, 2 = Finished
    int32_t mapPhase;     // 0 = None, 1 = Phase1, 2 = Phase2, 3 = Phase3
    float gameTime;       // Elapsed game time
};


// ---------------------------------------
// ------   Game Logic Packets      ------
// ---------------------------------------

struct DamageApplyPacket {
    int32_t targetID;
    int32_t damage;
    int32_t remainHP;
};

struct AttackActionPacket
{
    int32_t attackerID;   // userUID 기준 권장
    int32_t attackType;   // 0 = 기본 공격, 나중에 콤보/무기/스킬로 확장
};

struct StatusUpdatePacket {
    int32_t targetID;
    int32_t currentHP;
};

struct StateChangePacket {
    int32_t targetID;
    int32_t newState;    // 0=Alive, 1=Dead
};

struct RespawnPacket {
    int32_t targetID;
    float x, y, z;
    int32_t hp;
};

struct RoleChangePacket {
    int32_t targetID;
    int32_t newRoleType;  // 0=Striker, 1=Guardian, 2=Manipulator
};


// ---------------------------------------
// ------   Event Handle Packets    ------
// ---------------------------------------

struct MovePacket {
    float x, y, z;
    float yaw;
    float velocityX, velocityY;
};

struct JumpPakcet {

};

struct AttackPacket {

};

struct ItemPacket {

};

#pragma pack(pop)
