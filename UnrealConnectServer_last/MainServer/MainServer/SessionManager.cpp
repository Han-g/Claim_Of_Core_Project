#include "SessionManager.h"

void SessionManager::Init() 
{
	m_Sessions.resize(MAXCLIENT);

	for (int i = 0; i < MAXCLIENT; ++i) {
		m_Sessions[i] = new Session();
		m_Sessions[i]->sessionID = i;
		m_Sessions[i]->isConnected = false;
		m_FreeSessionQueue.push(i);
	}
}

Session* SessionManager::AcceptNewClient(SOCKET clientSocket)
{
    std::lock_guard<std::mutex> lock(m_SessionLock);

    if (m_FreeSessionQueue.empty()) {
        LOG_ERROR("Can't assign, Session is full");
        return nullptr;
    }

    int freeID = m_FreeSessionQueue.front();
    m_FreeSessionQueue.pop();

    Session* session = m_Sessions[freeID];

    // Init Session Data
    session->socket = clientSocket;
    session->isConnected = true;
    session->roomID = -1;
    session->playerUID = -1;
    session->now_state = ESessionState::LOGIN;

    // Init GameData
    session->gameDatas.isConnected = true;
    session->gameDatas.x = 0;
    session->gameDatas.y = 0;
    session->gameDatas.z = 0;

    session->isSending = false;
    while (!session->sendQueue.empty()) session->sendQueue.pop();

    return session;
}

void SessionManager::DisconnectClient(int clientID)
{
    if (clientID < 0 || clientID >= MAXCLIENT) { 
        LOG_ERROR("INVALID Session INDEX");
        return; 
    }

    std::lock_guard<std::mutex> lock(m_SessionLock);
    Session* session = m_Sessions[clientID];

    // 이미 반납된 세션인지 중복 체크
    if (session->isConnected) {
        session->isConnected = false;
        session->gameDatas.isConnected = false;

        if (session->socket != INVALID_SOCKET) {
            closesocket(session->socket);
            session->socket = INVALID_SOCKET;
        }

        if (session->roomID != -1) {
            Room* enteredRoom = RoomManager::GetInstance()->GetRoom(session->roomID);
            if (enteredRoom) {
                enteredRoom->RemoveMember(session->sessionID);

                if (enteredRoom->GetCurrentMemberCount() == 0) {
                    RoomManager::GetInstance()->DestroyRoom(session->roomID);
                }
            }

            session->roomID = -1;
        }

        // 다시 빈 자리 대기열에 삽입
        m_FreeSessionQueue.push(clientID);
    }
}

void SessionManager::SetState(int sessionID, ESessionState state)
{
    m_Sessions[sessionID]->now_state = state;
}

Session* SessionManager::GetSession(int sessionID)
{
    if (sessionID < 0 || sessionID >= MAXCLIENT) { return nullptr; }

    Session* session = m_Sessions[sessionID];
    if (!session->isConnected) { return nullptr; }

    return session;
}
