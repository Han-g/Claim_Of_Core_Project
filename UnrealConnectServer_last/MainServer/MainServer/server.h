#pragma once

#include <vector>
#include <thread>
#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>

#include "logger.h"
#include "SessionManager.h"
#include "RoomManager.h"
#include "Packet.h"
#include "PacketProcessor.h"
#include "Database.h"

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

	//std::vector<Session*> m_Sessions;
	//std::mutex m_SessionLock;
	int m_MaxSessionCount;
	bool m_IsRunning;
};