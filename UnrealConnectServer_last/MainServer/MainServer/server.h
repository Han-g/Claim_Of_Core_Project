#pragma once

#include <vector>
#include <thread>
#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>

#include "Packet.h"
#include "logger.h"
#include "session.h"

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

	void UpdateGameData();

private:
	HANDLE m_hIOCP;
	SOCKET m_ListenSocket;
	std::vector<Session*> m_Sessions;
	std::vector<std::thread> m_WorkerThreads;
	std::thread m_AcceptThread;

	int m_MaxSessionCount;
	std::mutex m_SessionLock;
	bool m_IsRunning;
};