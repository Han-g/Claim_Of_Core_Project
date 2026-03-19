#include "RoomManager.h"
#include "session.h"
#include "server.h"

void Room::InitRoom(int id, Session* firstMember, IOCPServer* server) {
	//std::lock_guard<std::mutex> lock(m_RoomLock);
	m_roomID = id;
    m_Server = server;
    m_State = ERoomState::WAITING;
    gameTimer = 0.f;
	
    addMember(firstMember);
}

bool Room::IsEmpty()
{
    return m_Members.empty();
}
;

bool Room::addMember(Session* member)
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    if (m_Members.size() >= MaxMember) {
        return false;
    }

    member->roomID = m_roomID;
    m_Members.push_back(member);
    return true;
}

void Room::LeaveRoom(int clientID)
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    for (auto it = m_Members.begin(); it != m_Members.end(); ++it)
    {
        if ((*it)->sessionID == clientID)
        {
            m_Members.erase(it);
            break;
        }
    }
}

void Room::SelectStage()
{

}

void Room::LoadStage()
{

}

void Room::MatchMaking()
{

}

bool Room::BroadcastGameDatas()
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    // Get Game Snapshot Data
    std::vector<GameData> roomSnapshot;
    for (Session* member : m_Members) {
        if (member->gameDatas.isConnected) {
            roomSnapshot.push_back(member->gameDatas);
        }
    }

    int userCnt = roomSnapshot.size();

    // If not exist Player, return false for Remove room
    if (userCnt == 0) {
        LOG_ERROR("Not exist GamePlayer at this room [%d]", m_roomID);
        return false;
    }

    // Calc and Assign Buffer
    int dataSize = sizeof(int) + (userCnt * sizeof(GameData));
    std::vector<char> sendBuffer(dataSize);

    int offset = 0;

    // Header
    memcpy(sendBuffer.data() + offset, &userCnt, sizeof(int));
    offset += sizeof(int);
    
    // GameData
    memcpy(sendBuffer.data() + offset, roomSnapshot.data(), userCnt * sizeof(GameData));

    // Send Snapshot to Client
    for (Session* member : m_Members) {
        if (member->gameDatas.isConnected) {
            m_Server->SendPacket(member->sessionID, PKT_S2C_SNAPSHOT_NOTICE, sendBuffer.data(), dataSize);
        }
        else {
            LOG_WARN("[%d] Client is not Connected Now", member->playerUID);
        }
    }


    // try reconnect to Disconnected clinet




    return true;
}




bool RoomManager::CreateRoom(Session* client) {
    if (client == nullptr) {
        LOG_ERROR("Client is not exist to Create GameRoom");
        return false;
    }

    int newRoomID = -1;
    {
        std::lock_guard<std::mutex> lock(m_ManagerLock);

        if (assignRoomID() != -1) { newRoomID = assignRoomID(); }
        else { LOG_ERROR("Can't Assign Room ID"); }
        ++m_RoomCounter;

        Room* newRoom = new Room();
        newRoom->InitRoom(newRoomID, client, m_Server);

        m_Rooms[newRoomID] = newRoom;
    }

    return true;
}

bool RoomManager::RemoveRoom(int roomID)
{
    std::lock_guard<std::mutex> lock(m_ManagerLock);

    auto it = m_Rooms.find(roomID);
    if (it == m_Rooms.end()) { LOG_ERROR("Room [%d] does not exist.", roomID); return false; }

    Room* targetRoom = it->second;
    if (!targetRoom->IsEmpty()) { LOG_ERROR("GameRoom still exist Player"); return false; }

    // Room Remove Logic
    delete targetRoom;
    m_Rooms.erase(it);

    --m_RoomCounter;
    return true;
}

bool RoomManager::JoinRoom(Session* client, int roomID)
{
    if (client == nullptr) { LOG_ERROR("Client is not exist to join GameRoom"); return false; }
   
    if (!m_Rooms[roomID]->addMember(client)) {
        LOG_ERROR("Room is full");
    return false;
    }

    return true;
}

void RoomManager::UpdateRooms()
{
    std::vector<Room*> activeRooms;

    {
        std::lock_guard<std::mutex> lock(m_ManagerLock);
        for (auto& pair : m_Rooms) {
            activeRooms.push_back(pair.second);
        }
    }

    for (Room* room : activeRooms) {
        if (!room->BroadcastGameDatas()) {
            RemoveRoom(room->retID());
        }
    }
}



int RoomManager::assignRoomID()
{
    for (int i = 0; i < m_RoomCounter; ++i) {
        if (m_Rooms.find(i) == m_Rooms.end()) { return i; }
    }

    return -1;
}

