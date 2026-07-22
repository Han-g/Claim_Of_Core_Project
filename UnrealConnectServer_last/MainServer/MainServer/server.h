#pragma once

#include <vector>
#include <thread>
#include <iostream>
#include <cstdio>
#include <string>
#include <atomic>
#include <ctime>

#include "logger.h"
#include "SessionManager.h"
#include "RoomManager.h"
#include "Packet.h"
#include "PacketProcessor.h"
#include "Database.h"

namespace
{
	constexpr unsigned short MAX_CLIENT_PACKET_SIZE = 1024;

	bool IsClientPacketID(unsigned short packetID)
	{
		switch (packetID)
		{
		case PKT_C2S_ACCESS_REQ:
		case PKT_C2S_LOGIN_REQ:
		case PKT_C2S_REGISTER_REQ:
		case PKT_C2S_ROOM_LIST_REQ:
		case PKT_C2S_ROOM_CREATE_REQ:
		case PKT_C2S_ROOM_JOIN_REQ:
		case PKT_C2S_MAP_SELECT_REQ:
		case PKT_C2S_CHARACTER_SELECT_REQ:
		case PKT_C2S_GAME_START_REQ:
		case PKT_C2S_READY_REQ:
		case PKT_C2S_ROOM_SLOT_SELECT_REQ:
		case PKT_C2S_ROOM_LEAVE_REQ:
		case PKT_C2S_ROUND_LOAD_COMPLETE_REQ:
		case PKT_C2S_ROUND_COUNTDOWN_READY_REQ:
		case PKT_C2S_MOVE_KEYINPUT:
		case PKT_C2S_JUMP_KEYINPUT:
		case PKT_C2S_ATTACK_KEYINPUT:
		case PKT_C2S_ITEMPICKUP_KEYINPUT:
		case PKT_C2S_ITEMDROP_KEYINPUT:
		case PKT_C2S_OBJECT_HIT_REQ:
		case PKT_C2S_ATTACK_HIT_REPORT:
		case PKT_C2S_HITSCAN_SHOT_REQ:
		case PKT_C2S_ICE_FLOOR_STAND_REQ:
		case PKT_C2S_GRENADE_BLACKHOLE_REQ:
		case PKT_C2S_ROLE_SKILL_REQ:
			return true;

		default:
			return false;
		}
	}

	bool IsValidPacketHeader(const PacketHeader& header)
	{
		if (header.packet_size < sizeof(PacketHeader))
		{
			return false;
		}

		if (header.packet_size > MAX_CLIENT_PACKET_SIZE)
		{
			return false;
		}

		if (!IsClientPacketID(header.packet_ID))
		{
			return false;
		}

		return true;
	}

	bool IsPacketAllowedInState(ESessionState state, unsigned short packetID)
	{
		switch (state)
		{
		case ESessionState::LOGIN:
			return packetID == PKT_C2S_ACCESS_REQ
				|| packetID == PKT_C2S_LOGIN_REQ
				|| packetID == PKT_C2S_REGISTER_REQ;

		case ESessionState::LOBBY:
			return packetID == PKT_C2S_ROOM_LIST_REQ
				|| packetID == PKT_C2S_ROOM_CREATE_REQ
				|| packetID == PKT_C2S_ROOM_JOIN_REQ;

		case ESessionState::ROOM:
			return packetID == PKT_C2S_ROOM_LEAVE_REQ
				|| packetID == PKT_C2S_READY_REQ
				|| packetID == PKT_C2S_CHARACTER_SELECT_REQ
				|| packetID == PKT_C2S_ROOM_SLOT_SELECT_REQ
				|| packetID == PKT_C2S_MAP_SELECT_REQ
				|| packetID == PKT_C2S_GAME_START_REQ;

		case ESessionState::INGAME:
			return packetID == PKT_C2S_MOVE_KEYINPUT
				|| packetID == PKT_C2S_JUMP_KEYINPUT
				|| packetID == PKT_C2S_ATTACK_KEYINPUT
				|| packetID == PKT_C2S_ATTACK_HIT_REPORT
				|| packetID == PKT_C2S_HITSCAN_SHOT_REQ
				|| packetID == PKT_C2S_ITEMPICKUP_KEYINPUT
				|| packetID == PKT_C2S_ITEMDROP_KEYINPUT
				|| packetID == PKT_C2S_OBJECT_HIT_REQ
				|| packetID == PKT_C2S_ICE_FLOOR_STAND_REQ
				|| packetID == PKT_C2S_GRENADE_BLACKHOLE_REQ
				|| packetID == PKT_C2S_ROLE_SKILL_REQ
				|| packetID == PKT_C2S_ROUND_LOAD_COMPLETE_REQ
				|| packetID == PKT_C2S_ROUND_COUNTDOWN_READY_REQ;

		default:
			return false;
		}
	}
}

class IOCPServer {
public:
	IOCPServer();
	~IOCPServer();

	// Configures the logging backend and applies log retention cleanup.
	static void InitLogger();
	// Initializes sockets, IOCP, session state, and room management.
	bool Init(int port, int maxSessionCount);
	// Starts worker, accept, and database threads.
	void Start();

	void Stop();

	// Serializes and queues a packet for asynchronous sending.
	void SendPacket(int sessionIndex, int packetID, const char* data, int len);

	// Advances room-level gameplay updates once per server frame.
	void GameFrameProtocol(float deltaTime);
	// Queues a database task for the dedicated DB worker thread.
	void PushDBTask(DBData data);
	// Attempts to create a room for the requesting client.
	void CreateRoomTry(Session* Client);
	// Attempts to join the requested room.
	void JoinRoomTry(Session* Client, int roomID);
	// Attempts to start the room game as the host.
	void GameStartTry(Session* Client);
	// Broadcasts the latest waiting-room list to lobby clients.
	void BroadcastRoomList();
	// Broadcasts the room member list to everyone in the client's room.
	void BroadcastRoomInfo(Session* client);

	// ---------------- Test Helpers ----------------
	// Exercises packet processing with a local synthetic login packet.
	void TestPacketProcessor();
	// ----------------------------------------------


private:
	// Waits on IOCP completions and dispatches socket work.
	void WorkerThread();
	// Accepts new client sockets and assigns them a session.
	void AcceptThread();

	// Finalizes a new connection and posts the first asynchronous receive.
	void OnConnect(Session* newSession, SOCKADDR_IN clientAddr);
	// Tears down a disconnected session.
	void OnDisconnect(int sessionIndex);
	// Consumes received bytes, reconstructs packets, and reposts WSARecv.
	void OnRecv(int sessionIndex, DWORD transferredBytes);
	// Completes one asynchronous send and starts the next queued packet.
	void OnSend(int sessionIndex, DWORD transferredBytes);

	// Issues the next WSASend request for the session queue.
	void SendProtocol(Session* session);

	// Routes a fully assembled packet to the packet processor.
	void PacketProcess(int sessionIndex, int packetID, std::vector<char>& data);

	// Processes queued database login and registration work.
	void DBWorkerThread();

private:
	HANDLE m_hIOCP;
	SOCKET m_ListenSocket;

	DBHelper* m_DB;
	std::queue<DBData> m_DBLoginQueue;
	std::mutex m_DBMutex;
	std::condition_variable m_DBControler;

	PacketProcessor m_PacketProcessor;

	SessionManager* m_SessionManager;
	RoomManager* m_RoomManager;

	std::vector<std::thread> m_WorkerThreads;
	std::thread m_AcceptThread;
	std::thread m_DBConnectThread;

	int m_MaxSessionCount;
	std::atomic_bool m_IsRunning;
};