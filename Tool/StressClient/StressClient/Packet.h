#pragma once

#include <cstdint>
#include <cstring>
#include <vector>
#include <string>

enum PacketID : uint16_t
{
    PKT_S2C_ACCESS_ALLOW = 100,
    PKT_S2C_LOGIN_OK = 101,
    PKT_S2C_LOGIN_DENY = 102,
    PKT_S2C_REGISTER_OK = 103,
    PKT_S2C_REGISTER_DENY = 104,
    PKT_S2C_ROOM_UPDATE = 105,
    PKT_S2C_ROOM_ENTER = 106,
    PKT_S2C_ROOM_INFO_BRD = 110,
    PKT_S2C_MATCH_START_BRD = 112,
    PKT_S2C_ROUND_START_BRD = 113,
    PKT_S2C_ROUND_PREPARE_BRD = 154,
    PKT_S2C_MATCH_END_BRD = 155,
    PKT_S2C_SNAPSHOT_NOTICE = 0,
    PKT_S2C_ERROR = 1000,

    PKT_C2S_LOGIN_REQ = 501,
    PKT_C2S_REGISTER_REQ = 502,
    PKT_C2S_ROOM_CREATE_REQ = 505,
    PKT_C2S_ROOM_JOIN_REQ = 506,
    PKT_C2S_GAME_START_REQ = 509,
    PKT_C2S_READY_REQ = 510,
    PKT_C2S_ROOM_LEAVE_REQ = 512,
    PKT_C2S_ROUND_LOAD_COMPLETE_REQ = 513,
    PKT_C2S_ROUND_COUNTDOWN_READY_REQ = 514,
    PKT_C2S_MOVE_KEYINPUT = 520,
};

#pragma pack(push, 1)
struct PacketHeader
{
    uint16_t packet_size;
    uint16_t packet_ID;
};

struct MovePacket
{
    float x, y, z;
    float yaw;
    float cameraDir;
    float velocityX, velocityY;
};
#pragma pack(pop)

inline void AppendFString(std::vector<char>& out, const std::wstring& str)
{
    int32_t len = -static_cast<int32_t>(str.size() + 1);

    const char* lenPtr = reinterpret_cast<const char*>(&len);
    out.insert(out.end(), lenPtr, lenPtr + sizeof(len));

    const char* strPtr = reinterpret_cast<const char*>(str.c_str());
    out.insert(out.end(), strPtr, strPtr + ((str.size() + 1) * sizeof(wchar_t)));
}

inline std::vector<char> MakePacket(uint16_t packetID, const std::vector<char>& body)
{
    PacketHeader header{};
    header.packet_size = static_cast<uint16_t>(sizeof(PacketHeader) + body.size());
    header.packet_ID = packetID;

    std::vector<char> packet(header.packet_size);
    memcpy(packet.data(), &header, sizeof(header));

    if (!body.empty())
    {
        memcpy(packet.data() + sizeof(header), body.data(), body.size());
    }

    return packet;
}

inline std::vector<char> MakeLoginBody(const std::wstring& id, const std::wstring& pw)
{
    std::vector<char> body;
    AppendFString(body, id);
    AppendFString(body, pw);
    return body;
}

inline std::vector<char> MakeMoveBody(float x, float y, float z, float yaw, float cameraDir, float vx, float vy)
{
    MovePacket packet{};
    packet.x = x;
    packet.y = y;
    packet.z = z;
    packet.yaw = yaw;
    packet.cameraDir = cameraDir;
    packet.velocityX = vx;
    packet.velocityY = vy;

    std::vector<char> body(sizeof(MovePacket));
    memcpy(body.data(), &packet, sizeof(MovePacket));
    return body;
}

inline std::vector<char> MakeRoomJoinBody(int32_t roomId)
{
    std::vector<char> body(sizeof(roomId));
    memcpy(body.data(), &roomId, sizeof(roomId));
    return body;
}