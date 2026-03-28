#include "server.h"


// ----------------Test Func----------------

void IOCPServer::TestPacketProcessor()
{
	LOG_INFO("====================================");
	LOG_INFO("========== Packet Processor Test Start ==========");
	LOG_INFO("====================================\n");
	
	Session dummySession;
	dummySession.sessionID = 999;     
	dummySession.roomID = -1;         
	dummySession.gameDatas.x = 0.0f;  
	dummySession.gameDatas.y = 0.0f;
	dummySession.gameDatas.z = 0.0f;

	std::vector<char> dummyPacketData;

	int32_t dummyHeader = 0;
	const char* headerPtr = reinterpret_cast<const char*>(&dummyHeader);
	dummyPacketData.insert(dummyPacketData.end(), headerPtr, headerPtr + sizeof(int32_t));

	// 문자열을 버퍼에 직렬화하는 람다 함수 (PacketReader의 규격과 일치시킴)
	auto AppendStringToBuffer = [&dummyPacketData](const std::wstring& str) {
		// 1. 길이를 부호 있는 정수로 캐스팅한 뒤, NULL 문자(+1)를 포함하여 음수로 만듭니다.
		int32_t len = -(static_cast<int32_t>(str.length()) + 1);

		// 길이 4바이트 삽입 (예: L"admin"이면 -6이 삽입됨)
		const char* lenPtr = reinterpret_cast<const char*>(&len);
		dummyPacketData.insert(dummyPacketData.end(), lenPtr, lenPtr + sizeof(int32_t));

		// 2. 실제 와이드 문자열 삽입
		int32_t realLen = -len;
		const char* strPtr = reinterpret_cast<const char*>(str.c_str());
		dummyPacketData.insert(dummyPacketData.end(), strPtr, strPtr + (realLen * sizeof(wchar_t)));
	};

	AppendStringToBuffer(L"admin");
	AppendStringToBuffer(L"admin");

	int TEST_PKT = 9999;

	m_PacketProcessor.Process(this, &dummySession, TEST_PKT, dummyPacketData);

	if (!m_DBLoginQueue.empty()) {
		DBData queuedData = m_DBLoginQueue.back(); // 큐의 맨 뒤에 방금 넣은 데이터 확인

		LOG_INFO("[Test Result] DB Queue Pushed - ID: %ls, PW: %ls",
			queuedData.UserID.c_str(), queuedData.UserPW.c_str());

		LOG_INFO("========== Login Packet Test SUCCESS ==========");

		// (선택) 실제 DB 스레드가 가져가기 전에 테스트용 데이터를 지우려면 pop 처리
		// m_DBLoginQueue.pop(); 
	}
	else {
		LOG_ERROR("========== Login Packet Test FAILED ==========\n\n\n");
	}
}

//-----------------------------------------

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

	m_SessionManager.Init();
	m_RoomManager.InitManager(this);

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
		Session* newSession = m_SessionManager.AcceptNewClient(clientSocket);

		// Check Session connected User
		if (newSession == nullptr) {
			LOG_ERROR("User can't connect by Session is full!");
			closesocket(clientSocket);
			continue;
		}

		OnConnect(newSession, clientAddr);
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

void IOCPServer::OnConnect(Session* newSession, SOCKADDR_IN clientAddr) {
	//// Create Session
	//Session* newSession = new Session();
	//newSession->socket = clientSocket;
	//newSession->sessionID = static_cast<int> (m_Sessions.size());

	//// Init new Game Data
	//GameData newData;
	//newData.isConnected = true;
	//newData.x = 0; newData.y = 0; newData.z = 0;

	//newSession->gameDatas = newData;

	// Socket connect with IOCP handle
	CreateIoCompletionPort((HANDLE)newSession->socket, m_hIOCP, (ULONG_PTR)newSession, 0);

	char clientIP[32];
	inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));

	LOG_INFO("Client Session Connect with IOCP handle successful!");

	GameDataPacket loginPacket;
	loginPacket.Session_ID = newSession->sessionID;

	SendPacket(newSession->sessionID, PKT_S2C_ACCESS_ALLOW, (char*)&loginPacket, sizeof(GameDataPacket));

	// Request Asyn Recv
	DWORD flags = 0;
	DWORD recvBytes = 0;
	WSABUF wsaBuf;
	wsaBuf.buf = newSession->TempBuffer;
	wsaBuf.len = sizeof(newSession->TempBuffer);

	// init Overlapped struct ( very important )
	ZeroMemory(&newSession->recvOverlapped, sizeof(WSAOVERLAPPED));
	newSession->recvOverlapped.type = IO_OPERATION::RECV;

	WSARecv(newSession->socket, &wsaBuf, 1, &recvBytes, &flags, (LPWSAOVERLAPPED)&newSession->recvOverlapped, nullptr);
}

void IOCPServer::OnDisconnect(int sessionIndex) {
	// Deque at vector
	/*for (std::vector<Session*>::iterator it = m_Sessions.begin(); it != m_Sessions.end();) {
		Session* delSession = *it;
		
		if ((*it)->sessionID == sessionIndex) {
			delete delSession;
			it = m_Sessions.erase(it);
			break;
		}
		else { ++it; }
	}*/
	m_SessionManager.DisconnectClient(sessionIndex);
}

void IOCPServer::OnRecv(int sessionIndex, DWORD transferredBytes) {
	// need mapping system between sessionID and Index
	Session* recvSession = m_SessionManager.GetSession(sessionIndex);

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
			//LOG_WARN("Check Data is gathered by size of header [Left Buffer Size: %d| Header Size: %d]", GetRingBufSize(&recvSession->recvBuffer), sizeof(PacketHeader));
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

void IOCPServer::OnSend(int sessionIndex, DWORD transferredBytes) {
	Session* session = m_SessionManager.GetSession(sessionIndex);

	std::lock_guard<std::mutex> sendlock(session->sendLock);

	if (!session->sendQueue.empty()) { session->sendQueue.pop(); }
	if (!session->sendQueue.empty()) { SendProtocol(session); }
	else { session->isSending = false; }

	//LOG_INFO("Send Data");
}

void IOCPServer::SendPacket(int sessionIndex, int packetID, const char* data, int len) {
	Session* session = m_SessionManager.GetSession(sessionIndex);
	if (session == nullptr) {
		LOG_ERROR("Session is Invalid Session");
		return; 
	}

	PacketHeader header;
	header.packet_ID = (unsigned int)packetID;
	header.packet_size = sizeof(PacketHeader) + len;

	std::vector<char> sendData;
	sendData.resize(header.packet_size);

	memcpy(sendData.data(), &header, sizeof(PacketHeader));
	if (len > 0 && data != nullptr) {
		memcpy(sendData.data() + sizeof(PacketHeader), data, len);
	}

	// Critical Section Start
	{
		std::lock_guard<std::mutex> sendlock(session->sendLock);

		session->sendQueue.push(std::move(sendData));

		if (session->isSending == false) {
			SendProtocol(session);
		}
	}
	// Critical Section End
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

// Recive Data Process
void IOCPServer::PacketProcess(int sessionIndex, int packetID, std::vector<char>& data)
{
	if (sessionIndex < 0 || sessionIndex >= m_MaxSessionCount) {
		LOG_ERROR("[%d] is Invalid Session Index", sessionIndex);
		return;
	}

	Session* session = m_SessionManager.GetSession(sessionIndex);
	if (session == nullptr) { return; }

	m_PacketProcessor.Process(this, session, packetID, data);
}

void IOCPServer::DBWorkerThread()
{
	if (!m_DB.Connect()) {
		LOG_ERROR("DB Connection Failed!");
	}

	while (m_IsRunning) {
		DBData data;

		{
			std::unique_lock<std::mutex> lock(m_DBMutex);
			m_DBControler.wait(lock, [this]() { return !m_DBLoginQueue.empty() || !m_IsRunning; });

			if (!m_IsRunning && m_DBLoginQueue.empty()) { break; }

			data = m_DBLoginQueue.front();
			m_DBLoginQueue.pop();
		}


		int userUID = -1;
		int newAccountUID = -1;

		switch (data.TaskType)
		{
		case EDBTaskType::LOGIN:
			// Check Valid Login Data
			if (m_DB.CheckLogin(data.UserID, data.UserPW, userUID)) {
				LOG_INFO("[%d] Session Login Success! [UID: %d]", data.SessionIndex, userUID);

				// Init Game Data and Assign UID to Client
				GameDataPacket dataPacket;
				dataPacket.Session_ID = data.SessionIndex;
				GameData newData;
				newData.userUID = userUID;
				dataPacket.data = newData;

				// Change session state
				m_SessionManager.SetState(data.SessionIndex, ESessionState::LOBBY);

				SendPacket(data.SessionIndex, PKT_S2C_LOGIN_OK, (char*)&dataPacket, sizeof(GameDataPacket));
				BroadcastRoomList();
			}

			else {
				LOG_INFO("[%d] Session Login Failed!", data.SessionIndex);

				ErrorCodePacket failPacket;
				failPacket.ErrorCode = 1;
				SendPacket(data.SessionIndex, PKT_S2C_LOGIN_DENY, (char*)&failPacket, sizeof(failPacket));
			}

			break;
		case EDBTaskType::REGISTER:
			if (m_DB.CreateAccount(data.UserID, data.UserPW)) {
				LOG_INFO("[%d] Session Register Success! [New UID: %d]", data.SessionIndex, newAccountUID);

				ErrorCodePacket successPacket;
				successPacket.ErrorCode = 10;
				SendPacket(data.SessionIndex, PKT_S2C_REGISTER_OK, (char*)&successPacket, sizeof(successPacket));
			}
			else {
				LOG_INFO("[%d] Session Register Failed! (Duplicate ID)", data.SessionIndex);

				ErrorCodePacket failPacket;
				failPacket.ErrorCode = 2;
				SendPacket(data.SessionIndex, PKT_S2C_REGISTER_DENY, (char*)&failPacket, sizeof(failPacket));
			}

			break;
		default:
			break;
		}
		
	}

	LOG_INFO("DB is Disconnected!");
}

void IOCPServer::PushDBTask(DBData data)
{
	{
		std::lock_guard<std::mutex> lock(m_DBMutex);
		m_DBLoginQueue.push(data);
	}

	m_DBControler.notify_one();
}



void IOCPServer::CreateRoomTry(Session* Client)
{
	m_RoomManager.CreateRoom(Client);
}

void IOCPServer::JoinRoomTry(Session* Client, int roomID)
{
	m_RoomManager.JoinRoom(Client, roomID);
}

void IOCPServer::BroadcastRoomList()
{
	std::vector<RoomPacket> roomList = m_RoomManager.GetRoomList();
	int roomCount = (int)roomList.size();

	// Packet Serializetion
	int dataSize = sizeof(int) + (roomCount * sizeof(RoomPacket));
	std::vector<char> sendBuffer(dataSize);

	int offset = 0;
	memcpy(sendBuffer.data() + offset, &roomCount, sizeof(int));
	offset += sizeof(int);

	if (roomCount > 0) {
		memcpy(sendBuffer.data() + offset, roomList.data(), roomCount * sizeof(RoomPacket));
	}

	// Only Sent to LOBBY State Clients
	for (int i = 0; i < m_MaxSessionCount; ++i) {
		Session* session = m_SessionManager.GetSession(i);

		if (session != nullptr && session->now_state == ESessionState::LOBBY) {
			SendPacket(session->sessionID, PKT_S2C_ROOM_UPDATE, sendBuffer.data(), dataSize);
		}
	}

	LOG_INFO("Send Update Room List Packets!");
}



void IOCPServer::GameFrameProtocol() {
	/*
	if (m_Sessions.empty()) { 
		//LOG_ERROR("Now Connected Client is not Exist!"); 
		return; 
	}

	std::vector<GameData> roomSnapshot;

	{
		std::lock_guard<std::mutex> lock(m_SessionLock);

		for (Session* s : m_Sessions) {
			if (s->gameDatas.isConnected) {
				roomSnapshot.push_back(s->gameDatas);
			}
		}
	}

	if (roomSnapshot.empty()) { LOG_ERROR("Not Exist Game Data!"); return; }

	// Packet & User Data Serialization
	int userCnt = roomSnapshot.size();
	int dataSize = sizeof(int) + (userCnt * sizeof(GameData));
	std::vector<char> sendBuffer(dataSize);

	// Send Snapshot to all Clients
	for (int i = 0; i < m_Sessions.size(); ++i) {
		if (m_Sessions[i]->gameDatas.isConnected) {
			SendPacket(m_Sessions[i]->sessionID, PKT_S2C_SNAPSHOT_NOTICE, sendBuffer.data(), dataSize);
		}
	}
	*/
	m_RoomManager.UpdateRooms();
}