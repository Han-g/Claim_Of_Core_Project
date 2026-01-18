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

	m_DBConnectThread = std::thread([this]() {this->DBWorkerThread(); });
	LOG_INFO("DB Connect Successful!");
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
		if (p_Ex->type == IO_OPERATION::RECV) { 
			OnRecv(session->sessionID, transferredBytes); 
		}
		
		else if (p_Ex->type == IO_OPERATION::SEND) {
			OnSend(session->sessionID, transferredBytes);
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

	// Init new Game Data
	GameData newData;
	newData.isConnected = true;
	newData.x = 0; newData.y = 0; newData.z = 0;

	newSession->gameDatas = newData;

	// Socket connect with IOCP handle
	CreateIoCompletionPort((HANDLE)clientSocket, m_hIOCP, (ULONG_PTR)newSession, 0);

	m_Sessions.push_back(newSession);

	char clientIP[32];
	inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));

	LOG_INFO("Client Session Connect with IOCP handle successful!");

	GameDataPacket loginPacket;
	loginPacket.Session_ID = newSession->sessionID;

	SendPacket(newSession->sessionID, PKT_S2C_LOGIN, (char*)&loginPacket, sizeof(GameDataPacket));

	// Request Asyn Recv
	DWORD flags = 0;
	DWORD recvBytes = 0;
	WSABUF wsaBuf;
	wsaBuf.buf = newSession->TempBuffer;
	wsaBuf.len = sizeof(newSession->TempBuffer);

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
	//LOG_INFO("Recv Data");

	// After Recv Data need to Recv again
	if (RingBufPush(&recvSession->recvBuffer, recvSession->TempBuffer, transferredBytes) == false) {
		LOG_ERROR("RingBuffer Overflow!");
		OnDisconnect(sessionIndex);
		return;
	}

	while (true) {
		// Check Data is gathered by size of header
		if (GetRingBufSize(&recvSession->recvBuffer) < sizeof(PacketHeader)) { 
			LOG_WARN("Check Data is gathered by size of header");
			break; 
		}

		PacketHeader header;
		RingBufPeek(&recvSession->recvBuffer, (char*)&header, sizeof(PacketHeader));

		// Entire Data doesn't receive wait next Recv
		if (GetRingBufSize(&recvSession->recvBuffer) < header.packet_size) {
			LOG_WARN("Entire Data doesn't receive wait next Recv");
			break; 
		}

		// Packet assamble Complete
		std::vector<char> packetData(header.packet_size);

		RingBufPeek(&recvSession->recvBuffer, packetData.data(), header.packet_size);

		RingBufpop(&recvSession->recvBuffer, header.packet_size);

		LOG_INFO("[SESSION ID: %d] [PACKET ID: %d - SIZE: %d] Pakcet Received!",
			sessionIndex, header.packet_ID, header.packet_size);

		// Call Packet Process Function
		PacketProcess(sessionIndex, header.packet_ID, packetData);

		// -----------------------------
	}

	DWORD flags = 0;
	DWORD recvBytes = 0;
	WSABUF wsaBuf;
	wsaBuf.buf = recvSession->TempBuffer;
	wsaBuf.len = sizeof(recvSession->TempBuffer);

	ZeroMemory(&recvSession->recvOverlapped, sizeof(WSAOVERLAPPED));
	recvSession->recvOverlapped.type = IO_OPERATION::RECV;

	if (WSARecv(recvSession->socket, &wsaBuf, 1, &recvBytes, &flags,
		(LPWSAOVERLAPPED)&recvSession->recvOverlapped, nullptr) == SOCKET_ERROR &&
		WSAGetLastError() != ERROR_IO_PENDING) {
		LOG_ERROR("[ID: %d] Failed to Register IOCP Recv Process", sessionIndex);
		OnDisconnect(sessionIndex);
	}
}

void IOCPServer::SendPacket(int sessionIndex, int packetID, const char* data, int len) {
	if (sessionIndex < 0 || sessionIndex >= m_Sessions.size()) { 
		LOG_ERROR("Session is Invalid Session");
		return; 
	}

	Session* session = m_Sessions[sessionIndex];

	PacketHeader header;
	header.packet_ID = (unsigned int)packetID;
	header.packet_size = sizeof(PacketHeader) + len;

	std::vector<char> sendData;
	sendData.resize(header.packet_size);

	memcpy(sendData.data(), &header, sizeof(PacketHeader));
	if (len > 0 && data != nullptr) {
		memcpy(sendData.data() + sizeof(PacketHeader), data, len);
	}

	// Critical Section
	{
		std::lock_guard<std::mutex> sendlock(session->sendLock);

		session->sendQueue.push(std::move(sendData));

		if (session->isSending == false) {
			SendProtocol(session);
		}
	}
	// Critical Section
}

void IOCPServer::SendProtocol(Session* session) {
	if (session->sendQueue.empty()) {
		LOG_ERROR("Send data is not exist");
		return;
	}

	std::vector<char>& packet = session->sendQueue.front();

	// Init Overlapped 
	session->isSending = true;

	WSABUF wsaBuf;
	wsaBuf.buf = packet.data();
	wsaBuf.len = (ULONG)packet.size();

	DWORD sentBytes = 0;
	DWORD flags = 0;

	ZeroMemory(&session->sendOverlapped, sizeof(WSAOVERLAPPED));
	session->sendOverlapped.type = IO_OPERATION::SEND;

	// Async Send request
	if (WSASend(session->socket, &wsaBuf, 1, &sentBytes, flags,
		(LPWSAOVERLAPPED)&session->sendOverlapped, nullptr) == SOCKET_ERROR) {
		if (WSAGetLastError() != ERROR_IO_PENDING) {
			LOG_ERROR("WSASend Failed! Error: %d", WSAGetLastError());
			session->isSending = false;
			OnDisconnect(session->sessionID);
		}
	}
}

void IOCPServer::PacketProcess(int sessionIndex, int packetID, std::vector<char>& data)
{
	PacketReader reader(data, sizeof(PacketHeader));
	std::wstring ID, PW;
	int userUID = -1;

	switch (packetID)
	{
	case PKT_S2C_UPDATE:
		// Update Packet
		break;
	case PKT_C2S_LOGIN:
		// Login Packet
		// Packet Deserialization
		if (reader.ReadString(ID) == false) {
			LOG_ERROR("[Session: %d] Failed to read ID", sessionIndex);
			return;
		}
		if (reader.ReadString(PW) == false) {
			LOG_ERROR("[Session: %d] Failed to read PW", sessionIndex);
			return;
		}

		// 3. DB 스레드에 작업 요청 (비동기)
		// (이전 대화에서 구현한 Task Queue 방식 사용 권장)
		// RequestLogin(sessionIndex, ID, PW);

		LOG_INFO("[Login Req] ID: %ls, PW: %ls", ID.c_str(), PW.c_str());
		
		if (m_DB.CheckLogin(ID, PW, userUID)) { 
			// CheckLogin 함수 내부 구현에 따라 인자 맞춤 필요
			// 로그인 성공 처리...
		}

		break;
	case PKT_C2S_MOVE:
		// (Move) Event Packet

		break;
	case PKT_C2S_ATTACK:
		// (Attack) Event Packet

		break;
	default:
		LOG_WARN("Not Valid Pakcet ID");
		break;
	}
}

void IOCPServer::DBWorkerThread()
{
	// 1. 서버 켜질 때 DB 연결 시도
	if (!m_DB.Connect()) {
		LOG_ERROR("DB Connection Failed!");
	}

	while (m_IsRunning) {
		// ... 큐에서 작업 꺼내기 ...

		// 2. DB 작업 수행
		// bool result = db.CheckLogin(L"TestUser");

		// ... 결과 처리 ...
	}

	// 3. 소멸자에서 자동으로 Disconnect 됨
}

void IOCPServer::OnSend(int sessionIndex, DWORD transferredBytes) {
	Session* session = m_Sessions[sessionIndex];

	std::lock_guard<std::mutex> sendlock(session->sendLock);

	if (!session->sendQueue.empty()) { session->sendQueue.pop(); }
	if (!session->sendQueue.empty()) { SendProtocol(session); }
	else { session->isSending = false; }

	//LOG_INFO("Send Data");
}

void IOCPServer::GameFrameProtocol() {
	if (m_Sessions.empty()) { return; }

	GameData clientData;

	std::vector<GameData> roomSnapshot;

	for (Session* data : m_Sessions) {
		roomSnapshot.push_back(data->gameDatas);
	}

	{
		std::lock_guard<std::mutex> lock(m_SessionLock);

		for (Session* s : m_Sessions) {
			if (s->gameDatas.isConnected) {
				GameData info;
				info.x = s->gameDatas.x;
				info.y = s->gameDatas.y;
				info.z = s->gameDatas.z;

				roomSnapshot.push_back(info);
			}
		}
	}

	if (roomSnapshot.empty()) { LOG_ERROR("Not Exist Game Data!"); return; }

	// Packet & User Data Serialization


	// Send Snapshot to all Clients
	for (int i = 0; i < m_Sessions.size(); ++i) {
		if (m_Sessions[i]->gameDatas.isConnected) {
			SendPacket(m_Sessions[i]->sessionID, 1, (char*)roomSnapshot.data(), sizeof(roomSnapshot));
		}
	}
}