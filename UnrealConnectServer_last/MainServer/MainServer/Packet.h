#pragma once

enum PacketID {
	PKT_S2C_LOGIN = 0,
	PKT_S2C_UPDATE = 1,
	PKT_C2S_MOVE = 2,
	PKT_C2S_ATTACK = 3,
};

struct PacketHeader {
	unsigned short packet_size;
	unsigned short packet_ID;
};

struct GameData {
	bool isConnected = false;

	int HP = 100;
	float x, y, z = 0;
	float rotate = 0;
	int animationNum = 0;
};

#pragma pack(push, 1)
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