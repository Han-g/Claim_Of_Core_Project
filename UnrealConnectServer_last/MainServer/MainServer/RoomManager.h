#pragma once

#include <vector>
#include <unordered_map>
#include <mutex>

#include "GameLogic.h"

#define MaxMember 6
#define MaxRoom 100

class IOCPServer;
struct Session;


enum class ERoomState {
	WAITING,
	PLAYING,
	FINISHED
};

class Room {
public:
	void InitRoom(int id, Session* firstMember, IOCPServer* server);

	bool IsEmpty();
	int retID() const { return m_roomID; }

	bool addMember(Session* member);
	void LeaveRoom(int clientID);

	void SelectStage();
	void LoadStage();
	void MatchMaking();

	bool BroadcastGameDatas();

private:
	int m_roomID;
	IOCPServer* m_Server;
	ERoomState m_State;

	std::vector<Session*> m_Members;
	std::mutex m_RoomLock;

	float gameTimer;
	std::unordered_map<int, ObjectData> m_GameObjects;
	std::unordered_map<int, ItemData> m_ItemObjetcts;
};


class RoomManager
{
public:
	void InitManager(IOCPServer* server) { m_Server = server; }

	bool CreateRoom(Session* client);
	bool RemoveRoom(int roomID);
	bool JoinRoom(Session* client, int roomID);

	void UpdateRooms();

private:
	int assignRoomID();

private:
	IOCPServer* m_Server;
	int m_roomID = -1;

	std::unordered_map<int, Room*> m_Rooms;
    std::mutex m_ManagerLock;
    int m_RoomCounter = 1;
};

