#pragma once

#define WIN32_LEAN_AND_MEAN

#include <vector>
#include <string>
#include <windows.h>

class PacketReader
{
public:
    // 생성자: 패킷 데이터의 시작 주소와 전체 크기를 받음
    // offset을 두어 헤더(4바이트) 이후부터 읽도록 설정 가능
    PacketReader(std::vector<char>& buffer, int offset = 0)
        : _buffer(buffer), _pos(offset)
    {
        _size = (int)buffer.size();
    }

    // 기본 타입(int, float 등) 읽기
    template<typename T>
    bool Read(T& outValue)
    {
        // 읽으려는 크기가 버퍼를 초과하는지 검사
        if (_pos + sizeof(T) > _size) return false;

        // 현재 위치에서 데이터 복사
        memcpy(&outValue, &_buffer[_pos], sizeof(T));
        _pos += sizeof(T);
        return true;
    }

    // Unreal FString 읽기 (ANSI/UTF-16 자동 판별)
    bool ReadString(std::wstring& outString)
    {
        // 1. 문자열 길이(int32) 먼저 읽기
        int32_t len = 0;
        if (!Read(len)) return false;

        // 길이가 0이면 빈 문자열
        if (len == 0) {
            outString.clear();
            return true;
        }

        // 2. 문자열 내용 읽기
        // Case A: ANSI (len > 0) -> 덤프 데이터가 이 경우입니다 (len=6)
        if (len > 0)
        {
            if (_pos + len > _size) return false;

            char* ptr = &_buffer[_pos];

            // ANSI(char) -> Wide(wchar_t) 변환
            // len에는 NULL 문자가 포함되어 있으므로 len-1 만큼만 변환하거나
            // 변환 후 NULL을 제거해야 합니다.
            int wLen = MultiByteToWideChar(CP_ACP, 0, ptr, len, NULL, 0);
            outString.resize(wLen - 1); // NULL 제외하고 사이즈 확보
            MultiByteToWideChar(CP_ACP, 0, ptr, len - 1, &outString[0], wLen - 1);

            _pos += len; // 포인터는 NULL 포함한 길이만큼 이동
        }
        // Case B: UTF-16 (len < 0) -> 한글 등을 보낼 때 발생 가능
        else
        {
            int32_t realLen = -len; // 실제 글자 수 (NULL 포함)
            int32_t byteSize = realLen * sizeof(wchar_t); // 바이트 크기 (2배)

            if (_pos + byteSize > _size) return false;

            // 바로 wstring에 복사 (Windows wchar_t는 2바이트라 호환됨)
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
    // Packet Name Rule
    // 9999      : Test Code
    // 1000 ~    : Error Code
    // 0 ~ 99    : System Info (고빈도 동기화 및 시스템 브로드캐스트)
    // 100 ~ 499 : Server Packet (S2C - 서버 응답 및 이벤트 지시)
    // 500 ~ 999 : Client Packet (C2S - 클라이언트 요청 및 키 입력)
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
    // 110번은 아래 Event Trigger Packet에서 사용

    PKT_S2C_ROOM_INFO_BRD = 110,            // 방 내부 접속 인원 및 정보 동기화
    PKT_S2C_CHARACTER_SELECT_BRD = 111,     // 다른 유저의 캐릭터(직업) 선택 결과 브로드캐스트
    PKT_S2C_GAME_START_BRD = 112,           // 방장의 시작 요청에 대한 서버의 게임 시작 명령

    // C2S (500 ~ 999)
    PKT_C2S_ACCESS_REQ = 500,
    PKT_C2S_LOGIN_REQ = 501,
    PKT_C2S_REGISTER_REQ = 502,
    PKT_C2S_ROOM_LIST_REQ = 504,            // 클라이언트 -> 서버: 방 업데이트 요청
    PKT_C2S_ROOM_CREATE_REQ = 505,          // 클라이언트 -> 서버: 방 생성 요청
    PKT_C2S_ROOM_JOIN_REQ = 506,            // 클라이언트 -> 서버: 방 입장 요청
    PKT_C2S_MAP_SELECT_REQ = 507,           // 클라이언트 -> 서버: 플레이할 맵 선택
    PKT_C2S_CHARACTER_SELECT_REQ = 508,     // 클라이언트 -> 서버: 직업(Role) 선택 요청
    PKT_C2S_GAME_START_REQ = 509,           // 클라이언트(방장) -> 서버: 게임 시작 요청

    // ------------------------------------------
    // [ InGame Process Packets ]
    // ------------------------------------------
    // Character Movement & Action Packet
    PKT_C2S_MOVE_KEYINPUT = 510,
    PKT_C2S_JUMP_KEYINPUT = 511,
    PKT_S2C_SYNC_ANIMATION_BRD = 107,       // 스냅샷 외의 단발성 애니메이션 동기화

    // Combat Packet
    PKT_C2S_ATTACK_KEYINPUT = 512,          // 공격 키 입력 알림
    PKT_S2C_ATTACK_ACTION_BRD = 108,        // 서버 검증 후 공격 모션 재생 지시
    PKT_S2C_DAMAGE_APPLY_BRD = 109,         // 타격 판정 및 데미지/넉백 수치 전달
    PKT_S2C_STATE_CHANGE_BRD = 110,         // 사망(Dead) / 부활(Alive) 등 생존 상태 변경
    PKT_S2C_STATUS_UPDATE_BRD = 111,        // 체력(HP) 등 스탯 변화 동기화

    // Item & Objects Manage Packet
    PKT_C2S_ITEMPICKUP_KEYINPUT = 513,      // 아이템 줍기 시도
    PKT_C2S_ITEMDROP_KEYINPUT = 514,        // 장착 중인 아이템 버리기 시도
    PKT_C2S_OBJECT_HIT_REQ = 515,           // 파괴 가능한 오브젝트 타격 시도 (서버에 판정 요청)

    PKT_S2C_SPAWN_ITEM_BRD = 112,           // 맵 상에 특정 아이템 스폰 지시
    PKT_S2C_DESPAWN_ITEM_BRD = 113,         // 맵 상의 특정 아이템 삭제 지시
    PKT_S2C_ITEM_OWNERSHIP_BRD = 114,       // 아이템 소유권 획득 통보 (누가 무엇을 주웠는지)
    PKT_S2C_SPAWN_OBJECT_BRD = 115,         // 부서지는 상자 등 맵 오브젝트 생성
    PKT_S2C_OBJECT_DESTRUCT_BRD = 116,      // 오브젝트 파괴 및 카오스 파편(Chunk) 연출 지시

    // Game Logics & Event Trigger Packet
    PKT_S2C_MAPEVENT_TRIGGER_BRD = 105,     // 맵 기믹 발동 알림 (제시해주신 번호 고정)
    PKT_S2C_GAME_PHASE_CHANGE_BRD = 117,    // Waiting -> Playing -> Finished 등 진행 페이즈 전환
    PKT_S2C_GAME_RESULT_BRD = 118           // 게임 종료 시 승패 및 킬/데스 통보
    
    /*
    // Error Packets
    PKT_S2C_ERROR = 1000,
    PKT_C2S_ERROR = 1001,

    // Game Setting Packets
    PKT_S2C_SNAPSHOT_BRD = 0,   // TRANSFORM, DIRECTION, ANIMATION

    PKT_S2C_ROOM_CREATE_REQ = 1,
    PKT_S2C_ROOM_JOIN_REQ = 2,
    PKT_S2C_MAP_SELECT_REQ = 3,

    PKT_S2C_ACCESS_ALLOW = 100,
    PKT_C2S_ACCESS_REQ = 500,
    PKT_C2S_LOGIN_REQ = 501,
    PKT_S2C_LOGIN_OK = 101,
    PKT_S2C_LOGIN_DENY = 102,

    // InGame Process Packets
    // Character Movement & Action Packet
    PKT_C2S_MOVE_KEYINPUT = 502,
    PKT_C2S_JUMP_KEYINPUT = 503,

    // Combat Packet
    PKT_C2S_ATTACK_KEYINPUT = 504,

    // Item & Objects Manage Packet
    PKT_C2S_ITEMPICKUP_KEYINPUT = 505,
    PKT_C2S_ITEMDROP_KEYINPUT = 506,

    // Game Logics & Event Trigger Packet
    PKT_S2C_MAPEVENT_TRIGGER_BRD = 105
    */
};

struct PacketHeader {
	unsigned short packet_size;
	unsigned short packet_ID;
};

struct GameData {
	int userUID = 0;
	bool isConnected = false;

	int HP = 100;
	float x = 0, y = 0, z = 0;
	float rotate = 0;
	int animationNum = 0;
};

#pragma pack(push, 1)
struct ErrorCodePacket {
    int16_t ErrorCode; 
    /*      Error Code List
    10 : Register Sueccess,
    11 : Room Enter,
    0: Unknown , 
    1: InValid ID Login Try ,
    2: Failed to Register Account,
    3: Room Error,
    */
};

struct LoginPacket {
    WCHAR userID[20];
    WCHAR userPW[20];
};

struct RoomPacket {
    int roomID; 
    WCHAR RoomName[20];
    int CurrentPlayers;
};

struct GameDataPacket {
	int Session_ID;
	GameData data;
};

struct MovePacket {

};

struct JumpPakcet {

};

struct AttackPacket {

};

struct ItemPacket {

};

#pragma pack(pop)