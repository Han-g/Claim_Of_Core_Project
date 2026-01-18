#pragma once

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
	PKT_S2C_LOGIN = 0,
	PKT_S2C_UPDATE = 1,
	PKT_C2S_LOGIN = 10,
	PKT_C2S_MOVE = 11,
	PKT_C2S_ATTACK = 12,
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
struct LoginPacket {
	std::wstring userID, userPW;
};

struct GameDataPacket {
	int Session_ID;
	GameData data;
};

struct MovePacket {

};

struct AttackPacket {

};
#pragma pack(pop)

/*
// Packet ID List

 0 : Connect 
 1 : Synchronization Data
 2 : Event Process (Move)

*/