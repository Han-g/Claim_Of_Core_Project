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

	static void InitLogger();
	bool Init(int port, int maxSessionCount);
	void Start();

	void SendPacket(int sessionIndex, int packetID, const char* data, int len);

	void GameFrameProtocol();
	void PushDBTask(DBData data);
	void CreateRoomTry(Session* Client);
	void JoinRoomTry(Session* Client, int roomID);
	void GameStartTry(Session* Client);
	void BroadcastRoomList();

	// ----------------Test Func----------------
	void TestPacketProcessor();
	// -----------------------------------------


private:
	void WorkerThread();
	void AcceptThread();

	void OnConnect(Session* newSession, SOCKADDR_IN clientAddr);
	void OnDisconnect(int sessionIndex);
	void OnRecv(int sessionIndex, DWORD transferredBytes);
	void OnSend(int sessionIndex, DWORD transferredBytes);

	void SendProtocol(Session* session);

	void PacketProcess(int sessionIndex, int packetID, std::vector<char>& data);

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