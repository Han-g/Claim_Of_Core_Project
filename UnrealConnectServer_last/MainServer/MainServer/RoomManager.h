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

struct Vector3 {
	float x, y, z;
};

class Room {
public:
	Room(){}
	~Room() { 
		if (m_GameLogic) { delete m_GameLogic; }
		m_Members.clear();
	}

	// Initializes a room instance before members are added.
	void InitRoom(int id, Session* firstMember, IOCPServer* server);
	// Attaches game logic and seeds player runtime data for the room.
	void InitGameLogic(GameLogic* logic);

	bool IsEmpty() { return m_Members.empty(); }
	int GetID() const { return m_roomID; }
	GameLogic* GetgameLogic() { return m_GameLogic; }
	ERoomState GetState() const { return m_State; }
	int GetOwnerSessionID() const { return m_OwnerSessionID; }
	bool IsOwner(int sessionID) const { return m_OwnerSessionID == sessionID; }

	void SetState(ERoomState state) { m_State = state; }
	// Returns true only when every room member is marked ready.
	bool IsAllReady();

	// Adds a member if the room still has capacity.
	bool addMember(Session* member);
	// Removes a member from the room by session ID.
	void RemoveMember(int clientID);
	// Transfers host ownership to the next member or clears it when the room is empty.
	void TransferOwnership();

	void SelectStage();
	void LoadStage();
	// Returns the spawn location used when players enter or respawn.
	Vector3 GetRespwanLocation();
	// Placeholder for future matchmaking-driven room assembly.
	void MatchMaking();

	// Ticks room-owned game logic when the room is in PLAYING state.
	void UpdateGameLogic(float deltaTime);

	// Broadcasts a gameplay snapshot to every connected member.
	bool BroadcastGameDatas();
	// Returns the current number of members in the room.
	int GetCurrentMemberCount();

	// Builds the serialized room member list used by room UI packets.
	std::vector<RoomMemberPacket> GetMemberInfoList();
	// Broadcasts a packet to room members, optionally excluding one session.
	void BroadcastToMembers(int packetID, const char* data, int len, int excludeSessionID = -1);

private:
	int m_roomID = -1;
	int m_OwnerSessionID = -1;
	IOCPServer* m_Server = nullptr;
	GameLogic* m_GameLogic = nullptr;
	ERoomState m_State = ERoomState::WAITING;

	std::vector<Session*> m_Members;
	std::mutex m_RoomLock;

	int selectedMapType = 0;
	float gameTimer = 0.f;
	std::unordered_map<int, ObjectData> m_GameObjects;
	std::unordered_map<int, ItemData> m_ItemObjects;
};


class RoomManager
{
public:
	void InitManager(IOCPServer* server) { m_Server = server; }
	static RoomManager* GetInstance() { static RoomManager instance; return &instance; }

	// Creates a new room and places the requesting client into it.
	bool CreateRoom(Session* client);
	// Removes a connected client from its current room.
	void LeaveRoom(Session* client);
	// Removes a disconnected session from its room while preserving host transfer logic.
	void LeaveRoomByDisconnect(int sessionID, int roomID);
	// Destroys an empty room and notifies lobby clients.
	void DestroyRoom(int roomID);
	// Adds a client to an existing waiting room.
	bool JoinRoom(Session* client, int roomID);
	// Starts the game for the client's room after validation.
	void GameStart(Session* client);

	// Ticks active rooms and removes any that no longer have valid game players.
	void UpdateRooms(float deltaTime);
	// Builds the lobby-visible list of waiting rooms.
	std::vector<RoomPacket> GetRoomList();
	// Looks up a room by its ID.
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

