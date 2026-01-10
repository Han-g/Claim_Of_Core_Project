#pragma once

#pragma pack(push, 1)
struct LoginPacket {
	unsigned short packet_ID;
	int Session_ID;
};
#pragma pack(pop)

struct PacketHeader {
	unsigned short packet_size;
	unsigned short packet_ID;
};

/*
// Packet ID List

 0 : Connect 
 1 : Synchronization Data
 2 : Event Process (Move)

*/