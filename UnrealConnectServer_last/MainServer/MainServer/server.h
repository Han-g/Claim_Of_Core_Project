#pragma once

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")

#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>

#include <windows.h>

#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <cstdio>
#include <string>

#include "logging.hpp"

// Check kind of IO Work
enum class IO_OPERATION {
	RECV,
	SEND,
	AWAIT
};

// Extend WSAOVERLAPPED by containing IO work type
struct OverlappedEx : public WSAOVERLAPPED {
	IO_OPERATION type;
};

// Client Session Info (need to contain at "session.h")
struct Session {
	SOCKET socket;
	int sessionID;
	char recvBuffer[1024];
	OverlappedEx recvOverlapped;

	Session() {
		socket = INVALID_SOCKET;
		sessionID = -1;
		ZeroMemory(recvBuffer, sizeof(recvBuffer));
		ZeroMemory(&recvOverlapped, sizeof(OverlappedEx));
		recvOverlapped.type = IO_OPERATION::RECV;
	}
};

class IOCPServer {
public:
	IOCPServer();
	~IOCPServer();

	static void InitLogger();
	bool Init(int port, int maxSessionCount);
	void Start();

private:
	void WorkerThread();
	void AcceptThread();

	void OnConnect(SOCKET clinentSocket, SOCKADDR_IN clientAddr);
	void OnDisconnect(int sessionIndex);
	void OnRecv(int sessionIndex, DWORD transferredBytes);

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

// logger Macro
template<typename ... Args>
void LogWrapper(const char* level, const char* format, Args ... args) {
	char buffer[1024];
	snprintf(buffer, sizeof(buffer), format, args ...);

	char finalBuffer[1200];
	snprintf(finalBuffer, sizeof(finalBuffer), "[%s] %s", level, buffer);

	logging::log(finalBuffer);
}

inline void LofWrapper(const char* level, const char* msg) {
	char buffer[1200];
	snprintf(buffer, sizeof(buffer), "[%s] %s", level, msg);
	logging::log(buffer);
}

#define LOG_INFO(...) LogWrapper("INFO", __VA_ARGS__)
#define LOG_ERROR(...) LogWrapper("ERROR", __VA_ARGS__)
#define LOG_WARN(...) LogWrapper("WARN", __VA_ARGS__)