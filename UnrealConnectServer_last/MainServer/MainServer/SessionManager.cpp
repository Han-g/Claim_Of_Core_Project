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
    session->generation++;
    session->isClosing = false;
    session->pendingIo = 0;

    session->isConnected = true;
    session->roomID = -1;
    session->playerUID = -1;
    session->now_state = ESessionState::LOGIN;

    session->roomSlot = -1;
    session->teamID = -1;
    session->isReady = false;
    session->isAttack = false;
    session->isGrounded = true;

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
    session->recvOverlapped.sessionID = session->sessionID;
    session->recvOverlapped.generation = session->generation;

    {
        std::lock_guard<std::mutex> sendLock(session->sendLock);

        session->isSending = false;

        while (!session->sendQueue.empty())
        {
            session->sendQueue.pop();
        }

        ZeroMemory(&session->sendOverlapped, sizeof(OverlappedEx));
        session->sendOverlapped.type = IO_OPERATION::SEND;
        session->sendOverlapped.sessionID = session->sessionID;
        session->sendOverlapped.generation = session->generation;
    }

    return session;
}

void SessionManager::DisconnectClient(int clientID)
{
    if (clientID < 0 || clientID >= MAXCLIENT) {
        LOG_ERROR("INVALID Session INDEX");
        return;
    }

    Session* session = m_Sessions[clientID];
    if (session->isClosing.exchange(true)) { return; }

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
    bool shouldTryRecycle = false;

    {
        std::lock_guard<std::mutex> lock(m_SessionLock);

        if (session->playerUID > 0)
        {
            auto it = m_LoggedInUsers.find(session->playerUID);
            if (it != m_LoggedInUsers.end() && it->second == clientID)
            {
                m_LoggedInUsers.erase(it);
            }
        }

        session->roomID = -1;
        session->isReady = false;
        session->playerUID = -1;
        session->playerName.clear();
        session->now_state = ESessionState::LOGIN;

        shouldTryRecycle = (session->pendingIo == 0);
    }

    if (shouldTryRecycle)
    {
        TryRecycleSession(clientID);
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

bool SessionManager::TryBindLoggedInUser(int userUID, int sessionID)
{
    std::lock_guard<std::mutex> lock(m_SessionLock);

    auto it = m_LoggedInUsers.find(userUID);
    if (it != m_LoggedInUsers.end())
    {
        int oldSessionID = it->second;
        if (oldSessionID >= 0 && oldSessionID < MAXCLIENT && m_Sessions[oldSessionID]->isConnected)
        {
            return false;
        }

        m_LoggedInUsers.erase(it);
    }

    m_LoggedInUsers[userUID] = sessionID;
    return true;
}

void SessionManager::TryRecycleSession(int clientID)
{
    if (clientID < 0 || clientID >= MAXCLIENT)
    {
        return;
    }

    std::lock_guard<std::mutex> lock(m_SessionLock);

    Session* session = m_Sessions[clientID];

    if (!session->isClosing)
    {
        return;
    }

    if (session->pendingIo != 0)
    {
        return;
    }

    session->roomID = -1;
    session->roomSlot = -1;
    session->teamID = -1;
    session->isReady = false;
    session->isAttack = false;
    session->playerUID = -1;
    session->playerName.clear();
    session->now_state = ESessionState::LOGIN;
    session->isSending = false;
    session->isClosing = false;

    while (!session->sendQueue.empty())
    {
        session->sendQueue.pop();
    }

    m_FreeSessionQueue.push(clientID);
}
