#include "RoomManager.h"
#include "session.h"

void Room::InitRoom(int id, Session* firstMember) {
	std::lock_guard<std::mutex> lock(m_RoomLock);
	m_roomID = id;
	m_Members.push_back(firstMember);
};

void Room::addMember(Session* member)
{
    if (m_Members.size() < MaxMember) {
        std::lock_guard<std::mutex> lock(m_RoomLock);
        m_Members.push_back(member);
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

void Room::BroadcastGameDatas()
{

}


void RoomManager::CreateRoom(Session* client) {
    std::lock_guard<std::mutex> lock(m_ManagerLock);

    int newRoomID = m_RoomCounter++;

    Room* newRoom = new Room();
    newRoom->InitRoom(newRoomID, client);

    m_Rooms[newRoomID] = newRoom;

    client->roomID = newRoomID;
}