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

    // ------------------------------------------
    // [ Error Packets ]
    // ------------------------------------------
    PKT_S2C_ERROR = 1000,
    PKT_C2S_ERROR = 1001,

    // ------------------------------------------
    // [ System Info Packets (0 ~ 99) ]
    // ------------------------------------------
    PKT_S2C_SNAPSHOT_NOTICE = 0,       // TRANSFORM, DIRECTION, ANIMATION 등 상시 동기화
    PKT_S2C_ROOM_CREATE_NOTICE = 1,    // 시스템 알림: 방 생성 정보
    PKT_S2C_ROOM_JOIN_NOTICE = 2,      // 시스템 알림: 방 입장 정보
    PKT_S2C_ROOM_UPDATE_NOTICE = 3,    // 시스템 알림: 방 업데이트
    PKT_S2C_MAP_SELECT_NOTICE = 4,     // 시스템 알림: 맵 선택 동기화
    PKT_S2C_SYNC_GAME_TIME_NOTICE = 5, // 서버 타이머 상시 동기화 (고빈도 호출)

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

    PKT_S2C_ROOM_INFO_BRD = 110,            // 방 내부 접속 인원 및 정보 동기화
    PKT_S2C_CHARACTER_SELECT_BRD = 111,     // 다른 유저의 캐릭터(직업) 선택 결과 브로드캐스트
    PKT_S2C_GAME_START_BRD = 112,           // 방장의 시작 요청에 대한 서버의 게임 시작 명령

    // C2S (500 ~ 519)
    PKT_C2S_ACCESS_REQ = 500,
    PKT_C2S_LOGIN_REQ = 501,
    PKT_C2S_REGISTER_REQ = 502,
    PKT_C2S_ROOM_LIST_REQ = 504,            // 클라이언트 -> 서버: 방 업데이트 요청
    PKT_C2S_ROOM_CREATE_REQ = 505,          // 클라이언트 -> 서버: 방 생성 요청
    PKT_C2S_ROOM_JOIN_REQ = 506,            // 클라이언트 -> 서버: 방 입장 요청
    PKT_C2S_MAP_SELECT_REQ = 507,           // 클라이언트 -> 서버: 플레이할 맵 선택
    PKT_C2S_CHARACTER_SELECT_REQ = 508,     // 클라이언트 -> 서버: 직업(Role) 선택 요청
    PKT_C2S_GAME_START_REQ = 509,           // 클라이언트(방장) -> 서버: 게임 시작 요청
    PKT_C2S_READY_REQ = 510,

    // ------------------------------------------
    // [ InGame Sync / Combat Packets ]
    // ------------------------------------------
    // Character Movement & Action Packet
    PKT_C2S_MOVE_KEYINPUT = 520,
    PKT_C2S_JUMP_KEYINPUT = 521,
    PKT_S2C_SYNC_ANIMATION_BRD = 125,       // 스냅샷 외의 단발성 애니메이션 동기화

    // Combat Packet
    PKT_C2S_ATTACK_KEYINPUT = 550,          // 공격 키 입력 알림
    PKT_S2C_ATTACK_ACTION_BRD = 108,        // 서버 검증 후 공격 모션 재생 지시 (100번대 legacy ID)
    PKT_S2C_DAMAGE_APPLY_BRD = 120,         // 타격 판정 및 데미지/넉백 수치 전달
    PKT_S2C_STATE_CHANGE_BRD = 121,         // 사망(Dead) / 부활(Alive) 등 생존 상태 변경
    PKT_S2C_STATUS_UPDATE_BRD = 122,        // 체력(HP) 등 스탯 변화 동기화

    // Item & Objects Manage Packet
    PKT_C2S_ITEMPICKUP_KEYINPUT = 551,      // 아이템 줍기 시도
    PKT_C2S_ITEMDROP_KEYINPUT = 552,        // 장착 중인 아이템 버리기 시도
    PKT_C2S_OBJECT_HIT_REQ = 553,           // 파괴 가능한 오브젝트 타격 시도 (서버에 판정 요청)

    PKT_S2C_SPAWN_ITEM_BRD = 130,           // 맵 상에 특정 아이템 스폰 지시
    PKT_S2C_DESPAWN_ITEM_BRD = 131,         // 맵 상의 특정 아이템 삭제 지시
    PKT_S2C_ITEM_OWNERSHIP_BRD = 132,       // 아이템 소유권 획득 통보 (누가 무엇을 주웠는지)
    PKT_S2C_SPAWN_OBJECT_BRD = 133,         // 부서지는 상자 등 맵 오브젝트 생성
    PKT_S2C_OBJECT_DESTRUCT_BRD = 134,      // 오브젝트 파괴 및 카오스 파편(Chunk) 연출 지시

    // Game Logic & Event Trigger Packet
    PKT_S2C_MAPEVENT_TRIGGER_BRD = 150,     // 맵 기믹 발동 알림 (제시해주신 번호 고정)
    PKT_S2C_GAME_PHASE_CHANGE_BRD = 151,    // Waiting -> Playing -> Finished 등 진행 페이즈 전환
    PKT_S2C_GAME_RESULT_BRD = 152,          // 게임 종료 시 승패 및 킬/데스 통보
};

struct  GameData {
	int userUID = 0;
	bool isConnected = false;
	int HP = 100;
	float x = 0, y = 0, z = 0;
	float rotate = 0;

    int characterState = -1;    // 0=Alive, 1=Dead
    int roleType = -1;          // 0=Striker, 1=Guardian, 2=Manipulator
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
};

struct FRoomMemberPacketData {
    TCHAR PlayerName[20];
    bool isReady;
};

struct FGamedataPacket {
	int sessionID;
	GameData data;
};


struct FMapEventPacket {
    int32_t eventType;    // 이벤트 종류 (Icicle, Floor, Debris 등)
    int32_t objectIndex;  // 맵에 배치된 오브젝트 인덱스
    int32_t eventState;   // 상태 (Warning, Breaking, Broken 등)
};

struct FSpawnObjectPacket {
    int32_t objectType;   // SmallDebris, LargeDebris 등
    float x, y, z;        // 스폰 위치
    int32_t objectID;     // 서버 할당 ID
};

struct FPhaseChangePacket {
    int32_t roundState;   // 0 = Waiting, 1 = Playing, 2 = Finished
    int32_t mapPhase;     // 0 = None, 1 = Phase1, 2 = Phase2, 3 = Phase3
    float gameTime;       // 현재 경과 시간
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

USTRUCT()
struct FRoomMemberInfo
{
    GENERATED_BODY()
    FString PlayerName;
    bool bIsReady = false;
};


DECLARE_MULTICAST_DELEGATE_OneParam(FOnRoomListUpdated, const TArray<FRoomInfoData>& /*RoomList*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRoomEntered, bool, const TArray<FRoomMemberInfo>&);
DECLARE_MULTICAST_DELEGATE(FOnGameStartDelegate);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoginResultDelegate, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnRegisterResultDelegate, bool);
DECLARE_MULTICAST_DELEGATE(FOnDisconnectDelegate);

class FSocket;


class CLAIM_OF_CORE_API ClientNetworking
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

    void ReadyToggleRequest();
    void GameStartRequest();

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
    FOnGameStartDelegate OnGameStart;

	FOnDisconnectDelegate OnDisconnected;
	FOnLoginResultDelegate OnLoginResult;
    FOnRegisterResultDelegate OnRegisterResult;
};