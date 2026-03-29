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

	void Init();
	
	Session* AcceptNewClient(SOCKET clientSocket);
	void DisconnectClient(int clientID);
	void SetState(int sessionID, ESessionState state);
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