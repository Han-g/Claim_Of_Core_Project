#pragma once

#include <vector>
#include <unordered_map>
#include <mutex>

#define MaxMember 6

struct Session;

class Room {
public:
	void InitRoom(int id, Session* firstMember);

	void addMember(Session* member);

	void SelectStage();
	void LoadStage();
	void MatchMaking();

	void BroadcastGameDatas();

private:
	int m_roomID;
	std::vector<Session*> m_Members;
	std::mutex m_RoomLock;
};


class RoomManager
{
public:
	void CreateRoom(Session* client);

private:
	int m_roomID = -1;

	std::unordered_map<int, Room*> m_Rooms;
    std::mutex m_ManagerLock;
    int m_RoomCounter = 1;
	float gameTimer;
};

