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

    // Reset session-owned socket and identity data.
    session->socket = clientSocket;
    session->isConnected = true;
    session->roomID = -1;
    session->playerUID = -1;
    session->now_state = ESessionState::LOGIN;

    // Reset gameplay state for the reused session slot.
    session->gameDatas.isConnected = true;
    session->gameDatas.userUID = -1;
    session->gameDatas.x = 0;
    session->gameDatas.y = 0;
    session->gameDatas.z = 0;

    ZeroMemory(session->TempBuffer, sizeof(session->TempBuffer));
    ZeroMemory(&session->recvBuffer, sizeof(s_ringbuf));
    ZeroMemory(&session->recvOverlapped, sizeof(OverlappedEx));
    session->recvOverlapped.type = IO_OPERATION::RECV;

    session->isSending = false;
    while (!session->sendQueue.empty()) session->sendQueue.pop();

    ZeroMemory(&session->sendOverlapped, sizeof(OverlappedEx));
    return session;
}

void SessionManager::DisconnectClient(int clientID)
{
    if (clientID < 0 || clientID >= MAXCLIENT) {
        LOG_ERROR("INVALID Session INDEX");
        return;
    }

    Session* session = m_Sessions[clientID];
    int roomToLeave = -1;

    // Phase 1: Mark session as disconnected and close socket.
    // Keep the slot reserved (not yet returned to FreeSessionQueue) so that
    // AcceptThread cannot recycle this slot while Room still holds the pointer.
    {
        std::lock_guard<std::mutex> lock(m_SessionLock);

        if (!session->isConnected) { LOG_ERROR("Session is Expired"); return; }

        roomToLeave = session->roomID;

        session->isConnected = false;
        session->gameDatas.isConnected = false;
        session->gameDatas.userUID = -1;

        if (session->socket != INVALID_SOCKET) {
            closesocket(session->socket);
            session->socket = INVALID_SOCKET;
        }
    }

    // Phase 2: Clean up the room (owner transfer + broadcast) while slot is
    // still unclaimed. RoomManager looks up the Session* from m_Sessions[clientID]
    // so it is safe as long as we have not returned the slot yet.
    if (roomToLeave != -1) {
        RoomManager::GetInstance()->LeaveRoomByDisconnect(clientID, roomToLeave);
    }

    // Phase 3: Reset the remaining fields and return the slot to the free queue.
    {
        std::lock_guard<std::mutex> lock(m_SessionLock);

        session->roomID = -1;
        session->isReady = false;
        session->playerUID = -1;
        session->playerName.clear();
        session->now_state = ESessionState::LOGIN;

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
