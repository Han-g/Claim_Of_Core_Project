#pragma once

#include <vector>
#include <thread>
#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>

#include "logger.h"
#include "session.h"
#include "Database.h"
#include "Packet.h"

class IOCPServer {
public:
	IOCPServer();
	~IOCPServer();

	static void InitLogger();
	bool Init(int port, int maxSessionCount);
	void Start();

	void SendPacket(int sessionIndex, int packetID, const char* data, int len);

	void GameFrameProtocol();

private:
	void WorkerThread();
	void AcceptThread();

	void OnConnect(SOCKET clinentSocket, SOCKADDR_IN clientAddr);
	void OnDisconnect(int sessionIndex);
	void OnRecv(int sessionIndex, DWORD transferredBytes);
	void OnSend(int sessionIndex, DWORD transferredBytes);

	void SendProtocol(Session* session);

	void PacketProcess(int sessionIndex, int packetID, std::vector<char>& data);

	void DBWorkerThread();

private:
	HANDLE m_hIOCP;
	SOCKET m_ListenSocket;
	DBHelper m_DB;

	std::vector<Session*> m_Sessions;
	std::vector<std::thread> m_WorkerThreads;
	std::thread m_AcceptThread;
	std::thread m_DBConnectThread;

	int m_MaxSessionCount;
	std::mutex m_SessionLock;
	bool m_IsRunning;
};