#pragma once

#include <unordered_map>
#include <functional>
#include "Packet.h"
#include "GameLogic.h"
#include "logger.h"

class IOCPServer;
struct Session;
struct DBData;

class PacketProcessor
{
public:
	PacketProcessor();
	~PacketProcessor() = default;

	using HandlerFunc = std::function<void(IOCPServer*, Session*, PacketReader&)>;

	void InitHandler();
	void Process(IOCPServer* server, Session* session, int packetID, std::vector<char>& data);

private:
	// Packet Process Functions
	static void Handle_LoginReq(IOCPServer* server, Session* session, PacketReader& reader);
	static void Handle_RegisterReq(IOCPServer* server, Session* session, PacketReader& reader);
	
	static void Handle_Room_CreateReq(IOCPServer* server, Session* session, PacketReader& reader);
	static void Handle_Room_JoinReq(IOCPServer* server, Session* session, PacketReader& reader);
	static void Handle_Room_RemoveReq(IOCPServer* server, Session* session, PacketReader& reader);
	
	static void Handle_Move_KeyInput(IOCPServer* server, Session* session, PacketReader& reader);
	static void Handle_Jump_KeyInput(IOCPServer* server, Session* session, PacketReader& reader);
	static void Handle_Attack_KeyInput(IOCPServer* server, Session* session, PacketReader& reader);
	static void Handle_ItemPickup_KeyInput(IOCPServer* server, Session* session, PacketReader& reader);
	static void Handle_ItemDrop_KeyInput(IOCPServer* server, Session* session, PacketReader& reader);

private:
	std::unordered_map<int, HandlerFunc> m_FuncHanderMap;
};