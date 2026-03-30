#pragma once

#include <vector>
#include <unordered_map>
#include <mutex>

#include "GameLogic.h"
#include "Packet.h"

#define MaxMember 6
#define MaxRoom 500

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
	int GetID() const { return m_roomID; }
	ERoomState GetState() const { return m_State; }

	bool addMember(Session* member);
	void RemoveMember(int clientID);

	void SelectStage();
	void LoadStage();
	void MatchMaking();

	bool BroadcastGameDatas();
	int GetCurrentMemberCount();

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
	static RoomManager* GetInstance() { static RoomManager instance; return &instance; }

	bool CreateRoom(Session* client);
	void LeaveRoom(Session* client);
	void DestroyRoom(int roomID);
	bool JoinRoom(Session* client, int roomID);
	void GameStart(Session* client);

	void UpdateRooms();
	std::vector<RoomPacket> GetRoomList();
	Room* GetRoom(int roomID);

private:
	RoomManager() {}
	~RoomManager() {}

	RoomManager(const RoomManager&) = delete;
	RoomManager& operator=(const RoomManager&) = delete;

	int assignRoomID();

private:
	IOCPServer* m_Server;
	int m_roomID = -1;

	std::unordered_map<int, Room*> m_Rooms;
    std::mutex m_ManagerLock;
    int m_RoomCounter = 1;
};

