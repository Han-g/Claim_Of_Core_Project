#include "PacketProcessor.h"
#include "server.h"

PacketProcessor::PacketProcessor()
{
	InitHandler();
}

void PacketProcessor::InitHandler()
{
	// Test Code
	m_FuncHanderMap[9999] = &PacketProcessor::Handle_LoginReq;
	// (if Not used Change to Comment!)

	// Bind Packet ID and Member Function

	m_FuncHanderMap[PKT_C2S_LOGIN_REQ] = &PacketProcessor::Handle_LoginReq;
	m_FuncHanderMap[PKT_C2S_REGISTER_REQ] = &PacketProcessor::Handle_RegisterReq;

	m_FuncHanderMap[PKT_C2S_ROOM_CREATE_REQ] = &PacketProcessor::Handle_Room_CreateReq;
	m_FuncHanderMap[PKT_C2S_ROOM_JOIN_REQ] = &PacketProcessor::Handle_Room_JoinReq;
}

void PacketProcessor::Process(IOCPServer* server, Session* session, int packetID, std::vector<char>& data)
{
	auto it = m_FuncHanderMap.find(packetID);

	if (it != m_FuncHanderMap.end()) {
		PacketReader reader(data, sizeof(PacketHeader));
		it->second(server, session, reader);
	}
	else {
		LOG_WARN("INVALID PACKET ID : %d", packetID);
	}
}

// -----------------------------
// Packet Handler Functions (Unifrom Interface)
// all Function need arguments (IOCPServer* server, Session* session, PacketReader& reader)
// Not used arguments made Commect and skip like that бщ
// (IOCPServer* server, Session* session, PacketReader& /*reader*/)
// -----------------------------


// -----------------------------
// Game Setting Part
// -----------------------------
void PacketProcessor::Handle_LoginReq(IOCPServer* server, Session* session, PacketReader& reader)
{
	std::wstring ID, PW;

	if (!reader.ReadString(ID) || !reader.ReadString(PW)) {
		LOG_ERROR("[Session: %d] Failed to read Login Infomation", session->sessionID);
		ErrorCodePacket failPacket;
		failPacket.ErrorCode = 1;
		server->SendPacket(session->sessionID, PKT_S2C_LOGIN_DENY, (char*)&failPacket, sizeof(failPacket));
		return;
	}

	LOG_INFO("[Login Req] ID: %ls, PW: %ls", ID.c_str(), PW.c_str());

	server->PushDBTask({ session->sessionID, ID, PW, EDBTaskType::LOGIN });
}

void PacketProcessor::Handle_RegisterReq(IOCPServer* server, Session* session, PacketReader& reader)
{
	std::wstring ID, PW;

	if (!reader.ReadString(ID) || !reader.ReadString(PW)) {
		LOG_ERROR("[Session: %d] Failed to read Register Infomation", session->sessionID);
		ErrorCodePacket failPacket;
		failPacket.ErrorCode = 1;
		server->SendPacket(session->sessionID, PKT_S2C_REGISTER_DENY, (char*)&failPacket, sizeof(failPacket));
		return;
	}

	LOG_INFO("[Login Req] ID: %ls, PW: %ls", ID.c_str(), PW.c_str());

	server->PushDBTask({ session->sessionID, ID, PW, EDBTaskType::REGISTER });
}

void PacketProcessor::Handle_Room_CreateReq(IOCPServer* server, Session* session, PacketReader& /*reader*/)
{
	server->CreateRoomTry(session);
}

void PacketProcessor::Handle_Room_JoinReq(IOCPServer* server, Session* session, PacketReader& reader)
{
	int roomID;

	if (!reader.Read(roomID)) {
		LOG_ERROR("[Session: %d] Failed to join at Game Room", session->sessionID);
		ErrorCodePacket failPacket;
		failPacket.ErrorCode = 2;
		server->SendPacket(session->sessionID, PKT_S2C_ERROR, (char*)&failPacket, sizeof(failPacket));
		return;
	}

	server->JoinRoomTry(session, roomID);
}

void PacketProcessor::Handle_Room_RemoveReq(IOCPServer* server, Session* session, PacketReader& reader)
{

}



// -----------------------------
// Game Play Logic Part
// -----------------------------
void PacketProcessor::Handle_Move_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{

}

void PacketProcessor::Handle_Jump_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{

}

void PacketProcessor::Handle_Attack_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{

}

void PacketProcessor::Handle_ItemPickup_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{

}

void PacketProcessor::Handle_ItemDrop_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{

}
