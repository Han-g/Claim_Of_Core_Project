#pragma once

#include "logger.h"
#include "session.h"

#include <vector>
#include <queue>
#include <mutex>

#define MAXCLIENT 3000

class SessionManager
{
public:
	static SessionManager* GetInstance() { static SessionManager instance; return &instance; }

	// Pre-allocates reusable session slots and the free-session queue.
	void Init();
	
	// Assigns a free session slot to a newly accepted client socket.
	Session* AcceptNewClient(SOCKET clientSocket);
	// Disconnects a session, removes it from any room, and recycles the slot.
	void DisconnectClient(int clientID);
	// Updates the current high-level state for a session.
	void SetState(int sessionID, ESessionState state);
	// Returns the active session pointer when the slot is connected.
	Session* GetSession(int sessionID);

private:
	SessionManager() {}
	~SessionManager() {
		for (Session* s : m_Sessions) {
			delete s;
		}
		m_Sessions.clear();
	}

private:
	std::vector<Session*> m_Sessions;
	std::queue<int> m_FreeSessionQueue;
	std::mutex m_SessionLock;
	int m_MaxClient = MAXCLIENT;
};