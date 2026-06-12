// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "ClientNetworking.generated.h"
/**
 * 
 */
 // Sort by 1Byte For Communicate Protocol with Server
enum PacketID : uint16 {
    // ==========================================
    // Packet Name Rule
    // 9999      : Test Code
    // 1000 ~    : Error Code
    // 0 ~ 99    : System Info (??? ??? ? ??? ??????)
    // 100 ~ 499 : Server Packet (S2C - ?? ?? ? ??? ??)
    // 500 ~ 999 : Client Packet (C2S - ????? ?? ? ? ??)
    // ==========================================
    //          Client To Server
    // 500 ~ 520 : Prepare Game Setting Packet
    // 520 ~ 550 : KeyInput Packet
    // 550 ~ 600 : InGame Calculation Logics Packet
    //          Server To Clients
    // 100 ~ 120 : Prepare Game Setting Packet
    // 120 ~ 150 : InGame Calculation Logics Packet
    // 150 ~ 200 : Map Logics Packet
    // ==========================================
    // ------------------------------------------
    // [ Error Packets ]
    // ------------------------------------------
    PKT_S2C_ERROR = 1000,
    PKT_C2S_ERROR = 1001,
    // ------------------------------------------
    // [ System Info Packets (0 ~ 99) ]
    // ------------------------------------------
    PKT_S2C_SNAPSHOT_NOTICE = 0,       // TRANSFORM, DIRECTION, ANIMATION ? ?? ???
    PKT_S2C_ROOM_CREATE_NOTICE = 1,    // ??? ??: ? ?? ??
    PKT_S2C_ROOM_JOIN_NOTICE = 2,      // ??? ??: ? ?? ??
    PKT_S2C_ROOM_UPDATE_NOTICE = 3,    // ??? ??: ? ????
    PKT_S2C_MAP_SELECT_NOTICE = 4,     // ??? ??: ? ?? ???
    PKT_S2C_SYNC_GAME_TIME_NOTICE = 5, // ?? ??? ?? ??? (??? ??)
    // ------------------------------------------
    // [ Game Setting Packets ]
    // ------------------------------------------
      // S2C (100 ~ 499)
    PKT_S2C_ACCESS_ALLOW = 100,
    PKT_S2C_LOGIN_OK = 101,
    PKT_S2C_LOGIN_DENY = 102,
    PKT_S2C_REGISTER_OK = 103,
    PKT_S2C_REGISTER_DENY = 104,
    PKT_S2C_ROOM_UPDATE = 105,
    PKT_S2C_ROOM_ENTER = 106,
    // 110?? ?? Event Trigger Packet?? ??
    PKT_S2C_ROOM_INFO_BRD = 110,            // ? ?? ?? ?? ? ?? ???
    PKT_S2C_CHARACTER_SELECT_BRD = 111,     // ?? ??? ???(??) ?? ?? ??????
    PKT_S2C_GAME_START_BRD = 112,           // ??? ?? ??? ?? ??? ?? ?? ??
    // C2S (500 ~ 999)
    PKT_C2S_ACCESS_REQ = 500,
    PKT_C2S_LOGIN_REQ = 501,
    PKT_C2S_REGISTER_REQ = 502,
    PKT_C2S_ROOM_LIST_REQ = 504,            // ????? -> ??: ? ???? ??
    PKT_C2S_ROOM_CREATE_REQ = 505,          // ????? -> ??: ? ?? ??
    PKT_C2S_ROOM_JOIN_REQ = 506,            // ????? -> ??: ? ?? ??
    PKT_C2S_MAP_SELECT_REQ = 507,           // ????? -> ??: ???? ? ??
    PKT_C2S_CHARACTER_SELECT_REQ = 508,     // ????? -> ??: ??(Role) ?? ??
    PKT_C2S_GAME_START_REQ = 509,           // ?????(??) -> ??: ?? ?? ??
    // ------------------------------------------
    // [ InGame Process Packets ]
    // ------------------------------------------
    // Character Movement & Action Packet
    PKT_C2S_MOVE_KEYINPUT = 520,
    PKT_C2S_JUMP_KEYINPUT = 521,
    PKT_S2C_SYNC_ANIMATION_BRD = 125,       // ??? ?? ??? ????? ???
    // Combat Packet
    PKT_C2S_ATTACK_KEYINPUT = 550,          // ?? ? ?? ??
    PKT_S2C_ATTACK_ACTION_BRD = 108,        // ?? ?? ? ?? ?? ?? ??
    PKT_S2C_DAMAGE_APPLY_BRD = 120,         // ?? ?? ? ???/?? ?? ??
    PKT_S2C_STATE_CHANGE_BRD = 121,         // ??(Dead) / ??(Alive) ? ?? ?? ??
    PKT_S2C_STATUS_UPDATE_BRD = 122,        // ??(HP) ? ?? ?? ???
    // Item & Objects Manage Packet
    PKT_C2S_ITEMPICKUP_KEYINPUT = 551,      // ??? ?? ??
    PKT_C2S_ITEMDROP_KEYINPUT = 552,        // ?? ?? ??? ??? ??
    PKT_C2S_OBJECT_HIT_REQ = 553,           // ?? ??? ???? ?? ?? (??? ?? ??)
    PKT_S2C_SPAWN_ITEM_BRD = 130,           // ? ?? ?? ??? ?? ??
    PKT_S2C_DESPAWN_ITEM_BRD = 131,         // ? ?? ?? ??? ?? ??
    PKT_S2C_ITEM_OWNERSHIP_BRD = 132,       // ??? ??? ?? ?? (?? ??? ????)
    PKT_S2C_SPAWN_OBJECT_BRD = 133,         // ???? ?? ? ? ???? ??
    PKT_S2C_OBJECT_DESTRUCT_BRD = 134,      // ???? ?? ? ??? ??(Chunk) ?? ??
    // Game Logics & Event Trigger Packet
    PKT_S2C_MAPEVENT_TRIGGER_BRD = 150,     // ? ?? ?? ?? (????? ?? ??)
    PKT_S2C_GAME_PHASE_CHANGE_BRD = 151,    // Waiting -> Playing -> Finished ? ?? ??? ??
    PKT_S2C_GAME_RESULT_BRD = 152           // ?? ?? ? ?? ? ?/?? ??
};

struct  GameData {
	int userUID = 0;
	bool isConnected = false;
	int HP = 100;
	float x = 0, y = 0, z = 0;
	float rotate = 0;
	int animationNum = 0;
};


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
    TCHAR RoomName[20];
    int32 CurrentPlayers;
    int32 MaxPlayers;
};

struct FGamedataPacket {
	int sessionID;
	GameData data;
};

struct FMovePacket {
	float X, Y, Z;
	float Yaw;
	float VelocityX, VelocityY;
};

#pragma pack(pop)


USTRUCT(BlueprintType)
struct FRoomInfoData
{
    GENERATED_BODY()
    UPROPERTY(BlueprintReadOnly)
    int32 RoomID;
    UPROPERTY(BlueprintReadOnly)
    FString RoomName;
    UPROPERTY(BlueprintReadOnly)
    int32 CurrentPlayers;
    UPROPERTY(BlueprintReadOnly)
    int32 MaxPlayers;
};


DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoomListUpdated, const TArray<FRoomInfoData>& /*RoomList*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRoomEntered, bool, const TArray<FString>&);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginResultDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterResultDelegate, bool);
DECLARE_MULTICAST_DELEGATE(FOnDisconnectDelegate);

class FSocket;


class SERVERTEST_API ClientNetworking
{
public:
	ClientNetworking();
	~ClientNetworking();

	bool Connect(FString IP, int32 Port);
	void Disconnect();

	bool SendPacket(uint16 PacketID, const void* Data, uint16 PacketSize);
	void RecvPacketProcess();

	void LoginAccess(FString& ID, FString& PW);
    void RegisterRequest(FString& ID, FString& PW);
    void CreateRoomRequest();
    void JoinRoomRequest(int32 RoomID);

	TArray<uint8> PacketAssemble(PacketID _ID, TArray<uint8> data);
	void PacketHandle(FPacketHeader* Header, uint8* LoadData);
	void PacketDeserialize(uint8* Data, uint16 DataSize);

private:
	FSocket* Socket;
	TArray<uint8> RecvBuffer;

public:
	bool IsLogin;
	bool IsConnected() const;

    FOnRoomListUpdated OnRoomListUpdated;
    FOnRoomEntered OnRoomEnterResult;

	FOnDisconnectDelegate OnDisconnected;
	FOnLoginResultDelegate OnLoginResult;
    FOnRegisterResultDelegate OnRegisterResult;
};