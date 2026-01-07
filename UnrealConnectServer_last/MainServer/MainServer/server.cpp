#include "server.h"

IOCPServer::IOCPServer() : m_hIOCP(INVALID_HANDLE_VALUE), 
m_ListenSocket(INVALID_SOCKET), m_IsRunning(false), m_MaxSessionCount(0) {}

IOCPServer::~IOCPServer() {
	m_IsRunning = false;
	closesocket(m_ListenSocket);
	WSACleanup();
}


void IOCPServer::InitLogger() {
	// Create Log setting
	logging::logging_config_t config;
	config["type"] = "file";
	config["file_name"] = "ServerLog.txt";

	logging::configure(config);

	LOG_INFO("------------- LOGGING START -------------");
}

bool IOCPServer::Init(int port, int maxSessionCount) {
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { return false; }
	m_MaxSessionCount = maxSessionCount;

	// Create IOCP Object
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
	if (m_hIOCP == nullptr) { return false; }

	// Create and Set Listen Socket
	m_ListenSocket = WSASocket(AF_INET, SOCK_STREAM, 0, nullptr, 0, WSA_FLAG_OVERLAPPED);
	if (m_ListenSocket == INVALID_SOCKET) { return false; }

	SOCKADDR_IN serverAddr;
	ZeroMemory(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(m_ListenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr))
		== SOCKET_ERROR) { return false; }
	if (listen(m_ListenSocket, SOMAXCONN) == SOCKET_ERROR) { return false; }

	return true;
}

void IOCPServer::Start() {
	m_IsRunning = true;

	// Num of WorkerThread == Num of CPU Core * 2
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int threadCount = sysInfo.dwNumberOfProcessors * 2;

	for (int i = 0; i < threadCount; ++i) {
		m_WorkerThreads.emplace_back([this]() { this->WorkerThread(); });
	}

	m_AcceptThread = std::thread([this]() { this->AcceptThread(); });
	LOG_INFO("Server Start Successful!");
}

void IOCPServer::AcceptThread() {
	while (m_IsRunning) {
		SOCKADDR_IN clientAddr;
		int addrLen = sizeof(clientAddr);
		SOCKET clientSocket = accept(m_ListenSocket, (SOCKADDR*)&clientAddr, &addrLen);

		if (clientSocket == INVALID_SOCKET) { continue; }

		// Operate Session with Lock
		std::lock_guard<std::mutex> lock(m_SessionLock);

		// Check Session connected User
		if (m_Sessions.size() >= m_MaxSessionCount) {
			LOG_ERROR("User can't connect by Session is full!");
			closesocket(clientSocket);
			continue;
		}

		OnConnect(clientSocket, clientAddr);
	}
}

void IOCPServer::WorkerThread() {
    DWORD transferredBytes = 0;
    ULONG_PTR completionKey = 0;
    LPOVERLAPPED p_Overlapped = nullptr;

	while (m_IsRunning) {
		BOOL ret = GetQueuedCompletionStatus(m_hIOCP, &transferredBytes, &completionKey,
			&p_Overlapped, INFINITE);
		Session* session = reinterpret_cast<Session*> (completionKey);
		OverlappedEx* p_Ex = static_cast<OverlappedEx*> (p_Overlapped);

		if (!ret || (ret && transferredBytes == 0)) {
			if (session) { 
				LOG_ERROR("[ID: %d] Fail to Register IOCP handle", session->sessionID); 
				OnDisconnect(session->sessionID); 
			}

			continue;
		}

		// work by task type
		if (p_Ex->type == IO_OPERATION::RECV) { OnRecv(session->sessionID, transferredBytes); }
		
		else if (p_Ex->type == IO_OPERATION::SEND) {
			// Send progess
		}
		
		else if (p_Ex->type == IO_OPERATION::AWAIT) {
			// Await progess
		}
		
		else {
			// Error progess
		}
	}
}

void IOCPServer::OnConnect(SOCKET clientSocket, SOCKADDR_IN clientAddr) {
	// Create Session
	Session* newSession = new Session();
	newSession->socket = clientSocket;
	newSession->sessionID = static_cast<int> (m_Sessions.size());

	// Socket connect with IOCP handle
	CreateIoCompletionPort((HANDLE)clientSocket, m_hIOCP, (ULONG_PTR)newSession, 0);

	m_Sessions.push_back(newSession);

	char clientIP[32];
	inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));

	LOG_INFO("Client Session Connect with IOCP handle successful!");

	// Request Asyn Recv
	DWORD flags = 0;
	DWORD recvBytes = 0;
	WSABUF wsaBuf;
	wsaBuf.buf = newSession->recvBuffer;
	wsaBuf.len = sizeof(newSession->recvBuffer);

	// init Overlapped struct ( very important )
	ZeroMemory(&newSession->recvOverlapped, sizeof(WSAOVERLAPPED));
	newSession->recvOverlapped.type = IO_OPERATION::RECV;

	WSARecv(clientSocket, &wsaBuf, 1, &recvBytes, &flags, (LPWSAOVERLAPPED)&newSession->recvOverlapped, nullptr);
}

void IOCPServer::OnDisconnect(int sessionIndex) {
	// Deque at vector
	for (std::vector<Session*>::iterator it = m_Sessions.begin(); it != m_Sessions.end();) {
		Session* delSession = *it;
		
		if ((*it)->sessionID == sessionIndex) {
			delete delSession;
			it = m_Sessions.erase(it);
			break;
		}
		else { ++it; }
	}
}

void IOCPServer::OnRecv(int sessionIndex, DWORD transferredBytes) {
	// need mapping system between sessionID and Index
	Session* recvSession = m_Sessions[sessionIndex];

	// Recv Data Progressing
	LOG_INFO("Recv Data");

	// After Recv Data need to Recv again

	DWORD flags = 0;
	DWORD recvBytes = 0;
	WSABUF wsaBuf;
	wsaBuf.buf = recvSession->recvBuffer;
	wsaBuf.len = sizeof(recvSession->recvBuffer);

	ZeroMemory(&recvSession->recvOverlapped, sizeof(WSAOVERLAPPED));
	recvSession->recvOverlapped.type = IO_OPERATION::RECV;

	if (WSARecv(recvSession->socket, &wsaBuf, 1, &recvBytes, &flags,
		(LPWSAOVERLAPPED)&recvSession->recvOverlapped, nullptr) == SOCKET_ERROR &&
		WSAGetLastError() != ERROR_IO_PENDING) {
		LOG_ERROR("[ID: %d] Failed to Register IOCP Recv Process", sessionIndex);
		OnDisconnect(sessionIndex);
	}
}