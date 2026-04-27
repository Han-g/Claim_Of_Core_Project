#include "PacketProcessor.h"
#include "server.h"

PacketProcessor::PacketProcessor()
{
	InitHandler();
}

GameLogic* PacketProcessor::GameLogicHelper(IOCPServer* server, Session* session)
{
	if (session->roomID < 0) { return nullptr; }

	Room* room = RoomManager::GetInstance()->GetRoom(session->roomID);
	if (!room) return nullptr;
	if (room->GetState() != ERoomState::PLAYING) return nullptr;

	return room->GetgameLogic();
}

void PacketProcessor::InitHandler()
{
	// Temporary test binding used by the local packet processor smoke test.
	m_FuncHandlerMap[9999] = &PacketProcessor::Handle_LoginReq;
	// Comment out this mapping when the manual test packet is no longer needed.

	// Bind each packet ID to its matching handler.

	m_FuncHandlerMap[PKT_C2S_LOGIN_REQ] = &PacketProcessor::Handle_LoginReq;
	m_FuncHandlerMap[PKT_C2S_REGISTER_REQ] = &PacketProcessor::Handle_RegisterReq;

	m_FuncHandlerMap[PKT_C2S_ROOM_CREATE_REQ] = &PacketProcessor::Handle_Room_CreateReq;
	m_FuncHandlerMap[PKT_C2S_ROOM_JOIN_REQ] = &PacketProcessor::Handle_Room_JoinReq;

	m_FuncHandlerMap[PKT_C2S_GAME_START_REQ] = &PacketProcessor::Handle_Game_StartReq;
	m_FuncHandlerMap[PKT_C2S_CHARACTER_SELECT_REQ] = &PacketProcessor::Handle_Character_SelectReq;
	m_FuncHandlerMap[PKT_C2S_READY_REQ] = &PacketProcessor::Handle_Game_ReadyReq;

	m_FuncHandlerMap[PKT_C2S_MOVE_KEYINPUT] = &PacketProcessor::Handle_Move_KeyInput;
	m_FuncHandlerMap[PKT_C2S_JUMP_KEYINPUT] = &PacketProcessor::Handle_Jump_KeyInput;
	m_FuncHandlerMap[PKT_C2S_ATTACK_KEYINPUT] = &PacketProcessor::Handle_Attack_KeyInput;
	m_FuncHandlerMap[PKT_C2S_ITEMPICKUP_KEYINPUT] = &PacketProcessor::Handle_ItemPickup_KeyInput;
	m_FuncHandlerMap[PKT_C2S_ITEMDROP_KEYINPUT] = &PacketProcessor::Handle_ItemDrop_KeyInput;
}

void PacketProcessor::Process(IOCPServer* server, Session* session, int packetID, std::vector<char>& data)
{
	auto it = m_FuncHandlerMap.find(packetID);

	if (it != m_FuncHandlerMap.end()) {
		PacketReader reader(data, sizeof(PacketHeader));
		it->second(server, session, reader);
	}
	else {
		LOG_WARN("INVALID PACKET ID : %d", packetID);
	}
}

// -----------------------------
// Packet handler functions share one uniform interface.
// Every handler accepts (IOCPServer* server, Session* session, PacketReader& reader).
// If an argument is intentionally unused, mark it like this:
// (IOCPServer* server, Session* session, PacketReader& /*reader*/)
// -----------------------------


// -----------------------------
// Lobby and match setup handlers
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

void PacketProcessor::Handle_Game_StartReq(IOCPServer* server, Session* session, PacketReader& reader)
{
	server->GameStartTry(session);
}

void PacketProcessor::Handle_Character_SelectReq(IOCPServer* server, Session* session, PacketReader& reader)
{
	if (server == nullptr || session == nullptr) {
		LOG_WARN("[RoleSelect] Failed to Find Client.");
		return;
	}

	int roleType = -1;
	if (!reader.Read(roleType))
	{
		LOG_WARN("[RoleSelect] Failed to read roleType. session=%d", session->sessionID);
		return;
	}

	if (roleType < 0 || roleType > 2)
	{
		LOG_WARN("[RoleSelect] Invalid roleType=%d session=%d", roleType, session->sessionID);
		return;
	}

	if (session->roomID < 0)
	{
		LOG_WARN("[RoleSelect] session=%d is not in room", session->sessionID);
		return;
	}

	session->gameDatas.roleType = roleType;

	Room* room = RoomManager::GetInstance()->GetRoom(session->roomID);
	if (!room)
	{
		return;
	}

	RoleChangePacket pkt{};
	pkt.targetID = session->playerUID;
	pkt.newRoleType = roleType;

	room->BroadcastToMembers(PKT_S2C_CHARACTER_SELECT_BRD, reinterpret_cast<const char*>(&pkt), sizeof(pkt));

	LOG_INFO("[RoleSelect] session=%d uid=%d role=%d",
		session->sessionID, session->playerUID, roleType);
}

void PacketProcessor::Handle_Game_ReadyReq(IOCPServer* server, Session* session, PacketReader& reader)
{
	session->isReady = !session->isReady;
	LOG_INFO("[Session: %d] Ready toggled -> %s", session->sessionID, session->isReady ? "READY" : "WAITING");

	server->BroadcastRoomInfo(session);
}



// -----------------------------
// In-game input handlers
// -----------------------------
bool PacketProcessor::Handle_Move_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{
	if (session == nullptr || server == nullptr) {
		LOG_WARN("[MoveInput] Failed to Find Move Objects!");
		return false;
	}

	MovePacket packet{};

	if (!reader.Read(packet.x) || !reader.Read(packet.y) || !reader.Read(packet.z) ||
		!reader.Read(packet.yaw) ||
		!reader.Read(packet.velocityX) || !reader.Read(packet.velocityY)) {
		LOG_WARN("[MoveInput] Failed to deserialize MovePacket!");
		return false;
	}

	if (packet.velocityX < -1.0f) { packet.velocityX = -1.0f; }
	if (packet.velocityX > 1.0f) { packet.velocityX = 1.0f; }

	if (packet.velocityY < -1.0f) { packet.velocityY = -1.0f; }
	if (packet.velocityY > 1.0f) { packet.velocityY = 1.0f; }

	if (_isnan(packet.yaw)) { packet.yaw = 0.0f; }

	{
		std::lock_guard<std::mutex> lock(session->MoveIntentLock);
		session->LastMoveIntent.Right = packet.velocityX;
		session->LastMoveIntent.Forward = packet.velocityY;
		session->LastMoveIntent.Yaw = packet.yaw;
		session->LastMoveIntent.bHasInput =
			(packet.velocityX != 0.0f || packet.velocityY != 0.0f);
	}

	session->gameDatas.y = packet.y;
	session->gameDatas.x = packet.x;
	session->gameDatas.z = packet.z;
	session->gameDatas.rotate = packet.yaw;

	session->gameDatas.animationNum =
		(std::abs(packet.velocityX) > 0.01f || std::abs(packet.velocityY) > 0.01f) ? 1 : 0;

	LOG_INFO("[MoveRecv] session=%d uid=%d pos=(%.1f, %.1f, %.1f) vel=(%.2f, %.2f) yaw=%.2f",
		session->sessionID,
		session->playerUID,
		packet.x, packet.y, packet.z,
		packet.velocityX, packet.velocityY,
		packet.yaw);

	return true;
}

void PacketProcessor::Handle_Jump_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{

}

void PacketProcessor::Handle_Attack_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{
	GameLogic* logic = GameLogicHelper(server, session);
	if (!logic) { return; }

	logic->HandleAttackInput(session->sessionID);
	LOG_INFO("[Attack] Handle_Attack_KeyInput session=%d", session->sessionID);
}

void PacketProcessor::Handle_ItemPickup_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{

}

void PacketProcessor::Handle_ItemDrop_KeyInput(IOCPServer* server, Session* session, PacketReader& reader)
{

}
