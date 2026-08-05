#include "server.h"


// ---------------- Test Helpers ----------------

void IOCPServer::TestPacketProcessor()
{
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

	// Helper lambda that serializes strings in the same format PacketReader expects.
	auto AppendStringToBuffer = [&dummyPacketData](const std::wstring& str) {
		// 1. Encode the UTF-16 string length as a negative value including the null terminator.
		int32_t len = -(static_cast<int32_t>(str.length()) + 1);

		// Insert the 4-byte length prefix. For example, L"admin" becomes -6.
		const char* lenPtr = reinterpret_cast<const char*>(&len);
		dummyPacketData.insert(dummyPacketData.end(), lenPtr, lenPtr + sizeof(int32_t));

		// 2. Append the raw wide-character payload.
		int32_t realLen = -len;
		const char* strPtr = reinterpret_cast<const char*>(str.c_str());
		dummyPacketData.insert(dummyPacketData.end(), strPtr, strPtr + (realLen * sizeof(wchar_t)));
	};

	AppendStringToBuffer(L"admin");
	AppendStringToBuffer(L"admin");

	int TEST_PKT = 9999;

	m_PacketProcessor.Process(this, &dummySession, TEST_PKT, dummyPacketData);

	if (!m_DBLoginQueue.empty()) {
		// Optionally pop the test item before the real DB worker consumes it.
		// m_DBLoginQueue.pop(); 
	}
}

//-----------------------------------------

IOCPServer::IOCPServer() : m_hIOCP(INVALID_HANDLE_VALUE), 
m_ListenSocket(INVALID_SOCKET), m_IsRunning(false), m_MaxSessionCount(0), 
m_RoomManager(RoomManager::GetInstance()), m_DB(DBHelper::GetInstance()), m_SessionManager(SessionManager::GetInstance()) { }

IOCPServer::~IOCPServer() {
	Stop();
}

void IOCPServer::InitLogger() {
	// Configure file-based logging.
	logging::logging_config_t config;
	config["type"] = "file";
	config["file_name"] = "ServerLog";

	logging::configure(config);

	CleanupOldLogs("ServerLog", 14);

	LOG_INFO("------------- LOGGING START -------------");
}

bool IOCPServer::Init(int port, int maxSessionCount) {
	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) { return false; }
	m_MaxSessionCount = maxSessionCount;

	// Create the shared I/O completion port.
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
	if (m_hIOCP == nullptr) { return false; }

	// Create and bind the listening socket.
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

	m_SessionManager->Init();
	m_RoomManager->InitManager(this);

	return true;
}

void IOCPServer::Start() {
	m_IsRunning = true;

	// Use roughly two worker threads per CPU core.
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	int threadCount = sysInfo.dwNumberOfProcessors * 2;

	for (int i = 0; i < threadCount; ++i) {
		m_WorkerThreads.emplace_back([this]() { this->WorkerThread(); });
	}

	m_AcceptThread = std::thread([this]() { this->AcceptThread(); });
	LOG_INFO("Server Start Successful!");

	m_DBConnectThread = std::thread([this]() {this->DBWorkerThread(); });
}

void IOCPServer::Stop()
{
	const bool wasRunning = m_IsRunning.exchange(false);
	if (!wasRunning) { return; }

	if (m_ListenSocket != INVALID_SOCKET)
	{
		shutdown(m_ListenSocket, SD_BOTH);
		closesocket(m_ListenSocket);
		m_ListenSocket = INVALID_SOCKET;
	}

	m_DBControler.notify_all();

	if (m_hIOCP && m_hIOCP != INVALID_HANDLE_VALUE)
	{
		for (size_t i = 0; i < m_WorkerThreads.size(); ++i)
		{
			PostQueuedCompletionStatus(m_hIOCP, 0, 0, nullptr);
		}
	}

	if (m_AcceptThread.joinable())
	{
		m_AcceptThread.join();
	}

	for (std::thread& worker : m_WorkerThreads)
	{
		if (worker.joinable())
		{
			worker.join();
		}
	}
	m_WorkerThreads.clear();

	if (m_DBConnectThread.joinable())
	{
		m_DBConnectThread.join();
	}

	m_DB->Disconnect();

	if (m_hIOCP && m_hIOCP != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hIOCP);
		m_hIOCP = INVALID_HANDLE_VALUE;
	}

	WSACleanup();
}

void IOCPServer::AcceptThread() {
	while (m_IsRunning) {
		SOCKADDR_IN clientAddr;
		int addrLen = sizeof(clientAddr);
		SOCKET clientSocket = accept(m_ListenSocket, (SOCKADDR*)&clientAddr, &addrLen);

		if (clientSocket == INVALID_SOCKET) {
			if (!m_IsRunning)
			{
				break;
			}

			LOG_ERROR("accept failed. error=%d", WSAGetLastError());

			continue; 
		}

		// Allocate a session slot for the accepted socket.
		Session* newSession = m_SessionManager->AcceptNewClient(clientSocket);

		// Reject the connection when all session slots are already in use.
		if (!newSession) {
			LOG_ERROR("User can't connect by Session is full!");
			closesocket(clientSocket);
			continue;
		}

		OnConnect(newSession, clientAddr);
	}
}

void IOCPServer::WorkerThread() 
{
	while (true) {
		DWORD transferredBytes = 0;
		ULONG_PTR completionKey = 0;
		LPOVERLAPPED p_Overlapped = nullptr;

		BOOL ret = GetQueuedCompletionStatus(m_hIOCP, &transferredBytes, &completionKey,
			&p_Overlapped, INFINITE);

		if (!m_IsRunning && p_Overlapped == nullptr)
		{
			break;
		}

		if (p_Overlapped == nullptr)
		{
			continue;
		}

		Session* session = reinterpret_cast<Session*> (completionKey);
		OverlappedEx* p_Ex = static_cast<OverlappedEx*> (p_Overlapped);

		if (session == nullptr)
		{
			continue;
		}

		auto CompleteIo = [this](Session* session)
		{
			unsigned int value = session->pendingIo.load();

			while (value > 0 &&
				!session->pendingIo.compare_exchange_weak(value, value - 1))
			{
			}

			m_SessionManager->TryRecycleSession(session->sessionID);
		};

		if (p_Ex->sessionID != session->sessionID ||
			p_Ex->generation != session->generation)
		{
			LOG_WARN("[IOCP] stale completion ignored. session=%d", p_Ex->sessionID);

			CompleteIo(session);
			continue;
		}

		if (!ret || transferredBytes == 0) {
			if (session && m_IsRunning) {
				LOG_INFO("[ID: %d] client disconnected or IO completed with zero bytes", session->sessionID);
				OnDisconnect(session->sessionID);
			}

			CompleteIo(session);
			continue;
		}

		// Dispatch the completion based on the operation type.
		if (p_Ex->type == IO_OPERATION::RECV) {
			OnRecv(session->sessionID, transferredBytes);
		}

		else if (p_Ex->type == IO_OPERATION::SEND) {
			OnSend(session->sessionID, transferredBytes);
		}

		else if (p_Ex->type == IO_OPERATION::AWAIT) {
			// Reserved for future await-style completions.
		}

		else {
			// Reserved for unsupported or invalid completion types.
		}

		CompleteIo(session);
	}
}

void IOCPServer::OnConnect(Session* newSession, SOCKADDR_IN clientAddr) {
	// Verify CreateIoCompletionProt function is Called Sueccesfully
	HANDLE h = CreateIoCompletionPort((HANDLE)newSession->socket, m_hIOCP, (ULONG_PTR)newSession, 0);
	if (h == nullptr) {
		LOG_ERROR("CreateIoCompletionPort failed. err=%d", GetLastError());
		OnDisconnect(newSession->sessionID);
		return;
	}

	GameDataPacket loginPacket;
	loginPacket.Session_ID = newSession->sessionID;

	SendPacket(newSession->sessionID, PKT_S2C_ACCESS_ALLOW, (char*)&loginPacket, sizeof(GameDataPacket));

	// Post the first asynchronous receive request.
	DWORD flags = 0;
	DWORD recvBytes = 0;
	WSABUF wsaBuf;
	wsaBuf.buf = newSession->TempBuffer;
	wsaBuf.len = sizeof(newSession->TempBuffer);

	// Initialize the overlapped structure before WSARecv.
	ZeroMemory(&newSession->recvOverlapped, sizeof(OverlappedEx));
	newSession->recvOverlapped.type = IO_OPERATION::RECV;
	newSession->recvOverlapped.sessionID = newSession->sessionID;
	newSession->recvOverlapped.generation = newSession->generation;

	newSession->pendingIo++;

	int ret = WSARecv(newSession->socket, &wsaBuf, 1, &recvBytes, &flags, (LPWSAOVERLAPPED)&newSession->recvOverlapped, nullptr);

	if (ret == SOCKET_ERROR) {
		int err = WSAGetLastError();
		if (err != ERROR_IO_PENDING) {
			LOG_ERROR("First WSARecv failed. session=%d err=%d", newSession->sessionID, err);
			newSession->pendingIo--;
			OnDisconnect(newSession->sessionID);
			return;
		}
	}
}

void IOCPServer::OnDisconnect(int sessionIndex) {
	m_SessionManager->DisconnectClient(sessionIndex);
}

void IOCPServer::OnRecv(int sessionIndex, DWORD transferredBytes) {
	// Resolve the active session object from the session ID.
	Session* recvSession = m_SessionManager->GetSession(sessionIndex);
	if (recvSession == nullptr) { LOG_ERROR("Session is empty!"); return; }

	// Push received bytes into the ring buffer before decoding packets.
	if (RingBufPush(&recvSession->recvBuffer, recvSession->TempBuffer, transferredBytes) == false) {
		LOG_ERROR("RingBuffer Overflow!");
		OnDisconnect(sessionIndex);
		return;
	}

	while (true) {
		// Wait until at least a full packet header is available.
		if (GetRingBufSize(&recvSession->recvBuffer) < sizeof(PacketHeader)) { 
			break; 
		}

		PacketHeader header;
		RingBufPeek(&recvSession->recvBuffer, (char*)&header, sizeof(PacketHeader));

		if (!IsValidPacketHeader(header))
		{
			LOG_WARN("[Session: %d] Invalid packet header. size=%u id=%u",
				sessionIndex,
				header.packet_size,
				header.packet_ID);

			OnDisconnect(sessionIndex);
			return;
		}

		// Wait for the remainder when the full packet body has not arrived yet.
		if (GetRingBufSize(&recvSession->recvBuffer) < header.packet_size) {
			//LOG_WARN("Entire Data doesn't receive wait next Recv");
			break; 
		}

		// The full packet is available, so assemble it into a contiguous buffer.
		std::vector<char> packetData(header.packet_size);

		RingBufPeek(&recvSession->recvBuffer, packetData.data(), header.packet_size);

		RingBufpop(&recvSession->recvBuffer, header.packet_size);

		if (!IsPacketAllowedInState(recvSession->now_state, header.packet_ID))
		{
			LOG_WARN("[Session: %d] Packet not allowed in state. state=%d id=%u",
				sessionIndex,
				static_cast<int>(recvSession->now_state),
				header.packet_ID);

			OnDisconnect(sessionIndex);
			return;
		}

		// Hand the decoded packet to the packet processor.
		PacketProcess(sessionIndex, header.packet_ID, packetData);
	}

	DWORD flags = 0;
	DWORD recvBytes = 0;
	WSABUF wsaBuf;
	wsaBuf.buf = recvSession->TempBuffer;
	wsaBuf.len = sizeof(recvSession->TempBuffer);

	ZeroMemory(&recvSession->recvOverlapped, sizeof(OverlappedEx));
	recvSession->recvOverlapped.type = IO_OPERATION::RECV;
	recvSession->recvOverlapped.sessionID = recvSession->sessionID;
	recvSession->recvOverlapped.generation = recvSession->generation;

	recvSession->pendingIo++;

	if (WSARecv(recvSession->socket, &wsaBuf, 1, &recvBytes, &flags,
		(LPWSAOVERLAPPED)&recvSession->recvOverlapped, nullptr) == SOCKET_ERROR &&
		WSAGetLastError() != ERROR_IO_PENDING) 
	{
		LOG_ERROR("[ID: %d] Failed to Register IOCP Recv Process", sessionIndex);

		recvSession->pendingIo--;
		OnDisconnect(sessionIndex);
	}
}

void IOCPServer::OnSend(int sessionIndex, DWORD transferredBytes) {
	Session* session = m_SessionManager->GetSession(sessionIndex);
	if (session == nullptr) { LOG_ERROR("Session is empty!"); return; }

	std::lock_guard<std::mutex> sendlock(session->sendLock);

	if (!session->sendQueue.empty()) { session->sendQueue.pop(); }
	if (!session->sendQueue.empty()) { SendProtocol(session); }
	else { session->isSending = false; }
}

void IOCPServer::SendPacket(int sessionIndex, int packetID, const char* data, int len) {
	Session* session = m_SessionManager->GetSession(sessionIndex);
	if (session == nullptr) {
		LOG_ERROR("Session is Invalid Session");
		return; 
	}

	if (session->isClosing)
	{
		return;
	}

	PacketHeader header;
	header.packet_ID = (unsigned int)packetID;
	header.packet_size = static_cast <unsigned short>(sizeof(PacketHeader) + len);

	std::vector<char> sendData;
	sendData.resize(header.packet_size);

	memcpy(sendData.data(), &header, sizeof(PacketHeader));
	if (len > 0 && data != nullptr) {
		memcpy(sendData.data() + sizeof(PacketHeader), data, len);
	}

	// Guard the outgoing queue while appending a new packet.
	{
		std::lock_guard<std::mutex> sendlock(session->sendLock);

		session->sendQueue.push(std::move(sendData));

		if (session->isSending == false) {
			SendProtocol(session);
		}
	}

	// Leave the send queue critical section.

}

void IOCPServer::SendProtocol(Session* session) {
	if (session->isClosing || session->sendQueue.empty()) {
		LOG_ERROR("Send data is not exist");
		session->isSending = false;
		return;
	}

	std::vector<char>& packet = session->sendQueue.front();

	// Initialize the overlapped structure for WSASend.
	session->isSending = true;

	WSABUF wsaBuf;
	wsaBuf.buf = packet.data();
	wsaBuf.len = (ULONG)packet.size();

	DWORD sentBytes = 0;
	DWORD flags = 0;

	ZeroMemory(&session->sendOverlapped, sizeof(OverlappedEx));
	session->sendOverlapped.type = IO_OPERATION::SEND;
	session->sendOverlapped.sessionID = session->sessionID;
	session->sendOverlapped.generation = session->generation;

	session->pendingIo++;

	// Submit the asynchronous send request.
	if (WSASend(session->socket, &wsaBuf, 1, &sentBytes, flags,
		(LPWSAOVERLAPPED)&session->sendOverlapped, nullptr) == SOCKET_ERROR) {
		if (WSAGetLastError() != ERROR_IO_PENDING) {
			LOG_ERROR("WSASend Failed! Error: %d", WSAGetLastError());
			session->isSending = false;
			session->pendingIo--;
			OnDisconnect(session->sessionID);
		}
	}
}

// Packet dispatch entry point after a full payload has been assembled.
void IOCPServer::PacketProcess(int sessionIndex, int packetID, std::vector<char>& data)
{
	if (sessionIndex < 0 || sessionIndex >= MAXCLIENT) {
		LOG_ERROR("[%d] is Invalid Session Index", sessionIndex);
		return;
	}

	Session* session = m_SessionManager->GetSession(sessionIndex);
	if (session == nullptr) { return; }

	m_PacketProcessor.Process(this, session, packetID, data);
}

void IOCPServer::DBWorkerThread()
{
	if (!m_DB->Connect()) {
		LOG_ERROR("DB Connection Failed!");
		return;
	}

	LOG_INFO("DB Connect Successful!");
	while (m_IsRunning || !m_DBLoginQueue.empty()) {
		DBData data;

		{
			std::unique_lock<std::mutex> lock(m_DBMutex);
			m_DBControler.wait(lock, [this]() { return !m_DBLoginQueue.empty() || !m_IsRunning; });

			if (!m_IsRunning && m_DBLoginQueue.empty()) { break; }

			data = m_DBLoginQueue.front();
			m_DBLoginQueue.pop();
		}

		int userUID = -1;

		// Verify DB generation
		Session* session = m_SessionManager->GetSession(data.SessionIndex);
		if (!session || session->generation != data.SessionGeneration) {
			LOG_WARN("[DB] stale DB result ignored. session=%d", data.SessionIndex);
			continue;
		}

		switch (data.TaskType)
		{
		case EDBTaskType::LOGIN:
			// Validate credentials and transition the session to the lobby on success.
			if (m_DB->CheckLogin(data.UserID, data.UserPW, userUID)) {
				if (!m_SessionManager->TryBindLoggedInUser(userUID, data.SessionIndex))
				{
					LOG_INFO("[%d] Duplicate Login Blocked! [UID: %d]", data.SessionIndex, userUID);

					ErrorCodePacket failPacket;
					failPacket.ErrorCode = 6; // duplicate login
					SendPacket(data.SessionIndex, PKT_S2C_LOGIN_DENY, (char*)&failPacket, sizeof(failPacket));
					continue;
				}

				// Cache player identity data on the session object.
				Session* loginSession = m_SessionManager->GetSession(data.SessionIndex);
				GameData loginSessionGD;
				if (loginSession) {
					loginSession->playerName = data.UserID;
					loginSession->playerUID = userUID;

					loginSession->gameDatas.userUID = userUID;
					loginSession->gameDatas.isConnected = true;
					loginSession->gameDatas.characterState = 0;
					loginSession->gameDatas.roleType = -1;
					loginSession->gameDatas.animationNum = 0;
					loginSessionGD = loginSession->gameDatas;
				}

				// Build the login-success payload with the assigned user UID.
				GameDataPacket dataPacket;
				dataPacket.Session_ID = data.SessionIndex;
				dataPacket.data = loginSessionGD;

				// Move the session into the lobby state.
				m_SessionManager->SetState(data.SessionIndex, ESessionState::LOBBY);

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
			if (m_DB->CreateAccount(data.UserID, data.UserPW)) {
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

	m_DB->Disconnect();
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
	m_RoomManager->CreateRoom(Client);
}

void IOCPServer::JoinRoomTry(Session* Client, int roomID)
{
	m_RoomManager->JoinRoom(Client, roomID);
}

void IOCPServer::GameStartTry(Session* Client)
{
	m_RoomManager->GameStart(Client);
}

void IOCPServer::BroadcastRoomList()
{
	std::vector<RoomPacket> roomList = m_RoomManager->GetRoomList();
	int roomCount = (int)roomList.size();

	// Serialize the room list payload.
	int dataSize = sizeof(int) + (roomCount * sizeof(RoomPacket));
	std::vector<char> sendBuffer(dataSize);

	int offset = 0;
	memcpy(sendBuffer.data() + offset, &roomCount, sizeof(int));
	offset += sizeof(int);

	if (roomCount > 0) {
		memcpy(sendBuffer.data() + offset, roomList.data(), roomCount * sizeof(RoomPacket));
	}

	// Send room-list updates only to lobby sessions.
	for (int i = 0; i < m_MaxSessionCount; ++i) {
		Session* session = m_SessionManager->GetSession(i);

		if (session != nullptr && session->now_state == ESessionState::LOBBY) {
			SendPacket(session->sessionID, PKT_S2C_ROOM_UPDATE, sendBuffer.data(), dataSize);
		}
	}
}

void IOCPServer::BroadcastRoomInfo(Session* client)
{
	if (client->roomID == -1) { return; }

	Room* room = m_RoomManager->GetRoom(client->roomID);
	if (room == nullptr) { return; }

	std::vector<RoomMemberPacket> memberList = room->GetMemberInfoList();
	int32_t memberCount = (int32_t)memberList.size();

	int dataSize = sizeof(int32_t) + (memberCount * sizeof(RoomMemberPacket));
	std::vector<char> sendBuffer(dataSize);

	int offset = 0;
	memcpy(sendBuffer.data() + offset, &memberCount, sizeof(int32_t));
	offset += sizeof(int32_t);

	if (memberCount > 0) {
		memcpy(sendBuffer.data() + offset, memberList.data(), memberCount * sizeof(RoomMemberPacket));
	}

	// Broadcast to every member in the room without exclusions.
	room->BroadcastToMembers(PKT_S2C_ROOM_INFO_BRD, sendBuffer.data(), dataSize);
}



void IOCPServer::GameFrameProtocol(float deltaTime) {
	m_RoomManager->UpdateRooms(deltaTime);
}
