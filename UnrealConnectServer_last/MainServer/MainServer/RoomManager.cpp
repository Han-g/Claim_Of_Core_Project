#include "RoomManager.h"
#include "session.h"
#include "server.h"

void Room::InitRoom(int id, Session* firstMember, IOCPServer* server) {
	//std::lock_guard<std::mutex> lock(m_RoomLock);
	m_roomID = id;
    m_Server = server;
    m_State = ERoomState::WAITING;
    gameTimer = 0.f;
	
    //addMember(firstMember);
}

void Room::InitGameLogic(GameLogic* logic)
{
    std::lock_guard<std::mutex> lock(m_RoomLock);
    m_GameLogic = logic;
    LOG_INFO("[InitGameLogic] memberCount=%d", static_cast<int>(m_Members.size()));

    for (Session* member : m_Members) {
        logic->players[member->sessionID] = member;
        LOG_INFO("[InitLoop] session=%d uid=%d slot=%d team=%d",
            member->sessionID,
            member->playerUID,
            member->roomSlot,
            member->teamID);

        GameData& pd = member->gameDatas;
        pd.userUID = member->playerUID;
        /*pd.maxHP = 100;
        //pd.currentHP = 100;
        //pd.characterState = 0;
        //pd.roleType = 0;
        //pd.baseWalkSpeed = 500.f;
        //// Reset spawn-related player data to default values until map-specific spawn points are wired in.
        pd.x = 0; pd.y = 0; pd.z = 0;*/

        InitCharacter(member, logic);
    }

    logic->SetMapType(selectedMapType);
    logic->StartGameRound();
}

void Room::InitCharacter(Session* member, GameLogic* logic)
{
    if (member == nullptr) { return; }

    const int slot = member->roomSlot;
    if (slot < 0) {
        LOG_WARN("[Init Character] failed to find empty slot.");
        return;
    }

    member->teamID = TeamCalculateBySlot(slot);

    GameData& gd = member->gameDatas;
    gd.userUID = member->playerUID;
    gd.isConnected = true;
    gd.characterState = 0; // Alive

    logic->ApplyRoleStats(member->sessionID);
    gd.currentHP = gd.maxHP;

    const Vector3 spawn = GetRespawnLocation(slot);

    gd.x = spawn.x;
    gd.y = spawn.y;
    gd.z = spawn.z;
    gd.rotate = GetSpawnYawBySlot(slot);

    LOG_INFO("InitCharacter session=%d uid=%d slot=%d team=%d pos=(%.1f, %.1f, %.1f)",
        member->sessionID,
        gd.userUID,
        member->roomSlot,
        member->teamID,
        gd.x, gd.y, gd.z);
}

bool Room::IsAllReady()
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    if (m_Members.empty()) { return false; }

    for (Session* member : m_Members) {
        if (!member->isReady) { return false; }
    }
    return true;
}

bool Room::addMember(Session* member)
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    if (m_Members.size() >= MaxMember || !member) {
        LOG_ERROR("Invalid Member Access");
        return false;
    }

    int slot = AllocateRoomSlot();
    if (slot == -1) {
        LOG_ERROR("Failed to Allocate Room Slot");
        return false; 
    }

    member->roomSlot = slot;
    member->teamID = TeamCalculateBySlot(slot);
    member->roomID = m_roomID;

    // The first member added to the room becomes the host.
    if (m_Members.empty()) {
        m_OwnerSessionID = member->sessionID;
        LOG_INFO("Room [%d] Owner set to Session [%d]", m_roomID, m_OwnerSessionID);
    }

    m_Members.push_back(member);
    return true;
}

int Room::AllocateRoomSlot()
{
    for (int i = 0; i < MaxMember; ++i)
    {
        if (!UsedSlots[i])
        {
            UsedSlots[i] = true;
            return i;
        }
    }

    return -1;
}

void Room::RemoveMember(int clientID)
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    for (auto it = m_Members.begin(); it != m_Members.end(); ++it)
    {
        Session* member = *it;
        if (member->sessionID == clientID)
        {
            if (member->roomSlot >= 0 && member->roomSlot < MaxMember)
            {
                UsedSlots[member->roomSlot] = false;
            }
            member->roomSlot = -1;

            m_Members.erase(it);
            break;
        }
    }
}

void Room::TransferOwnership()
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    if (m_Members.empty()) {
        m_OwnerSessionID = -1;
        return;
    }

    m_OwnerSessionID = m_Members.front()->sessionID;
    LOG_INFO("Room [%d] New owner = Session [%d]", m_roomID, m_OwnerSessionID);
}

int Room::TeamCalculateBySlot(int roomSlot) const
{
    if (roomSlot >= 0 && roomSlot < 3) { return 0; }
    if (roomSlot >= 3 && roomSlot < 6) { return 1; }
    return -1;
}

void Room::SelectStage(int stageNum)
{

}

void Room::LoadStage()
{

}

Vector3 Room::GetRespawnLocation(int slot)
{
    static const Vector3 SpawnTable[6] =
    {
        {   0.f,   0.f, 1200.f },  // team 1 Member1
        { 300.f,   0.f, 1200.f },  // team 1 Member2
        { 600.f,   0.f, 1200.f },  // team 1 Member3
        {   0.f, 800.f, 1200.f },  // team 2 Member4
        { 300.f, 800.f, 1200.f },  // team 2 Member5
        { 600.f, 800.f, 1200.f }   // team 2 Member6
    };

    if (slot < 0 || slot >= 6) {
        // Invalid slot Connect
        return { -100.f, -100.f, -100.f };
    }

    return SpawnTable[slot];
}

float Room::GetSpawnYawBySlot(int slot) const
{
    static const float SpawnYawTable[6] =
    {
        0.0f,   // slot 0
        0.0f,   // slot 1
        0.0f,   // slot 2
        180.0f, // slot 3
        180.0f, // slot 4
        180.0f  // slot 5
    };

    if (slot < 0 || slot >= 6)
    {
        return 0.0f;
    }

    return SpawnYawTable[slot];
}

void Room::MatchMaking()
{

}

void Room::UpdateGameLogic(float deltaTime)
{
    if (m_State != ERoomState::PLAYING) { return; }
    if (!m_GameLogic) { return; }

    m_GameLogic->Update(deltaTime);
}

bool Room::BroadcastGameDatas()
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    if (m_State != ERoomState::PLAYING) {
        return true;
    }

    // Collect a gameplay snapshot for every connected member.
    std::vector<GameData> roomSnapshot;
    for (Session* member : m_Members) {
        if (member->gameDatas.isConnected) {
            roomSnapshot.push_back(member->gameDatas);
        }
    }

    int userCnt = static_cast<int>(roomSnapshot.size());

    // Return false when no active gameplay participants remain in the room.
    if (userCnt == 0) {
        LOG_ERROR("Not exist GamePlayer at this room [%d]", m_roomID);
        return false;
    }

    // Allocate the payload buffer and serialize the snapshot header.
    int dataSize = sizeof(int) + (userCnt * sizeof(GameData));
    std::vector<char> sendBuffer(dataSize);

    int offset = 0;

    // Write the player count header.
    memcpy(sendBuffer.data() + offset, &userCnt, sizeof(int));
    offset += sizeof(int);
    
    // Append the serialized GameData array.
    memcpy(sendBuffer.data() + offset, roomSnapshot.data(), userCnt * sizeof(GameData));

    // Send the snapshot to every connected gameplay client.
    for (Session* member : m_Members) {
        if (member->gameDatas.isConnected) {
            m_Server->SendPacket(member->sessionID, PKT_S2C_SNAPSHOT_NOTICE, sendBuffer.data(), dataSize);
        }
        else {
            LOG_WARN("[%d] Client is not Connected Now", member->playerUID);
        }
    }


    // Disconnected client recovery can be added here later.




    return true;
}

int Room::GetCurrentMemberCount()
{
    return static_cast<int>(m_Members.size());
}

std::vector<RoomMemberPacket> Room::GetMemberInfoList()
{
    std::lock_guard<std::mutex> lock(m_RoomLock);
    std::vector<RoomMemberPacket> result;

    for (Session* member : m_Members) {
        RoomMemberPacket info;
        ZeroMemory(&info, sizeof(info));

        if (!member->playerName.empty()) {
            wcsncpy_s(info.PlayerName, member->playerName.c_str(), 19);
        }
        else {
            std::wstring fallback = L"Player_" + std::to_wstring(member->sessionID);
            wcsncpy_s(info.PlayerName, fallback.c_str(), 19);
        }

        info.isReady = member->isReady ? 1 : 0;

        result.push_back(info);
    }

    return result;
}

void Room::BroadcastToMembers(int packetID, const char* data, int len, int excludeSessionID)
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    for (Session* member : m_Members)
    {
        if (member->sessionID == excludeSessionID) continue;

        m_Server->SendPacket(member->sessionID, packetID, data, len);
    }
}




bool RoomManager::CreateRoom(Session* client) {
    if (client == nullptr) {
        LOG_ERROR("Client is not exist to Create GameRoom");
        return false;
    }

    int newRoomID = -1;
    {
        std::lock_guard<std::mutex> lock(m_ManagerLock);

        int roomID = assignRoomID();
        if (roomID != -1) { newRoomID = roomID; }
        else { LOG_ERROR("Can't Assign Room ID"); return false; }
        ++m_RoomCounter;

        Room* newRoom = new Room();
        newRoom->InitRoom(newRoomID, client, m_Server);

        m_Rooms[newRoomID] = newRoom;
    }

    // m_Server->GetSessionManager()->SetState(client->sessionID, ESessionState::ROOM);
    client->roomID = newRoomID;

    // m_Server->BroadcastRoomList();
    JoinRoom(client, client->roomID);
    return true;
}

void RoomManager::DestroyRoom(int roomID)
{
    {
        std::lock_guard<std::mutex> lock(m_ManagerLock);

        auto it = m_Rooms.find(roomID);
        if (it != m_Rooms.end()) {
            Room* room = it->second;

            delete room;
            m_Rooms.erase(it);
            --m_RoomCounter;

            LOG_INFO("Room [%d] is Empty and Destroyed by Server.", roomID);
        }
    }

    m_Server->BroadcastRoomList();
}

void RoomManager::LeaveRoom(Session* client)
{
    if (client == nullptr || client->roomID == -1) { return; }

    int targetRoomID = client->roomID;
    int leavingSessionID = client->sessionID;
    bool wasOwner = false;
    bool roomDestroyed = false;

    {
        std::lock_guard<std::mutex> lock(m_ManagerLock);

        auto it = m_Rooms.find(targetRoomID);
        if (it != m_Rooms.end()) {
            Room* room = it->second;

            wasOwner = room->IsOwner(leavingSessionID);
            room->RemoveMember(leavingSessionID);

            SessionManager::GetInstance()->SetState(client->sessionID, ESessionState::LOBBY);
            client->roomID = -1;

            if (room->IsEmpty()) {
                delete room;
                m_Rooms.erase(it);
                --m_RoomCounter;
                roomDestroyed = true;
                LOG_INFO("Room [%d] is Empty and Destroyed.", targetRoomID);
            }
            else if (wasOwner) {
                room->TransferOwnership();
                LOG_INFO("Room [%d] Owner transferred to Session [%d]",
                    targetRoomID, room->GetOwnerSessionID());
            }
        }
    }

    // Broadcast the updated member list to the remaining room members.
    if (!roomDestroyed) {
        Room* room = GetRoom(targetRoomID);
        if (room) {
            std::vector<RoomMemberPacket> memberList = room->GetMemberInfoList();
            int32_t memberCount = (int32_t)memberList.size();

            int dataSize = sizeof(int32_t) + (memberCount * sizeof(RoomMemberPacket));
            std::vector<char> sendBuffer(dataSize);

            int offset = 0;
            memcpy(sendBuffer.data() + offset, &memberCount, sizeof(int32_t));
            offset += sizeof(int32_t);

            if (memberCount > 0) {
                memcpy(sendBuffer.data() + offset, memberList.data(), memberCount * sizeof(RoomMemberPacket));
            }

            room->BroadcastToMembers(PKT_S2C_ROOM_INFO_BRD, sendBuffer.data(), dataSize);
        }
    }

    m_Server->BroadcastRoomList();
}

void RoomManager::LeaveRoomByDisconnect(int sessionID, int roomID)
{
    if (roomID == -1) { return; }

    bool wasOwner = false;
    bool roomDestroyed = false;

    {
        std::lock_guard<std::mutex> lock(m_ManagerLock);

        auto it = m_Rooms.find(roomID);
        if (it != m_Rooms.end()) {
            Room* room = it->second;

            wasOwner = room->IsOwner(sessionID);
            room->RemoveMember(sessionID);

            if (room->IsEmpty()) {
                delete room;
                m_Rooms.erase(it);
                --m_RoomCounter;
                roomDestroyed = true;
                LOG_INFO("Room [%d] is Empty and Destroyed (disconnect).", roomID);
            }
            else if (wasOwner) {
                room->TransferOwnership();
                LOG_INFO("Room [%d] Owner transferred to Session [%d] (disconnect)",
                    roomID, room->GetOwnerSessionID());
            }
        }
    }

    // Broadcast the updated member list to the remaining room members.
    if (!roomDestroyed) {
        Room* room = GetRoom(roomID);
        if (room) {
            std::vector<RoomMemberPacket> memberList = room->GetMemberInfoList();
            int32_t memberCount = (int32_t)memberList.size();

            int dataSize = sizeof(int32_t) + (memberCount * sizeof(RoomMemberPacket));
            std::vector<char> sendBuffer(dataSize);

            int offset = 0;
            memcpy(sendBuffer.data() + offset, &memberCount, sizeof(int32_t));
            offset += sizeof(int32_t);

            if (memberCount > 0) {
                memcpy(sendBuffer.data() + offset, memberList.data(), memberCount * sizeof(RoomMemberPacket));
            }

            room->BroadcastToMembers(PKT_S2C_ROOM_INFO_BRD, sendBuffer.data(), dataSize);
        }
    }

    m_Server->BroadcastRoomList();
}

bool RoomManager::JoinRoom(Session* client, int roomID)
{
    if (client == nullptr) { LOG_ERROR("Client is not exist to join GameRoom"); return false; }
   
    Room* room = GetRoom(roomID);
    if (room == nullptr) {
        LOG_ERROR("Room [%d] does not exist", roomID);
        return false;
    }
    
    if (!room->addMember(client)) {
        LOG_ERROR("Room is full");
        return false;
    }

    SessionManager::GetInstance()->SetState(client->sessionID, ESessionState::ROOM);
    
    // Send the full room payload to the player who just joined.
    // [int32 RoomID][int32 MemberCount][RoomMemberPacket * N]
    std::vector<RoomMemberPacket> memberList = room->GetMemberInfoList();
    int32_t memberCount = (int32_t)memberList.size();

    int dataSize = sizeof(int32_t) + sizeof(int32_t) + (memberCount * sizeof(RoomMemberPacket));
    std::vector<char> sendBuffer(dataSize);

    int offset = 0;
    memcpy(sendBuffer.data() + offset, &roomID, sizeof(int32_t));
    offset += sizeof(int32_t);

    memcpy(sendBuffer.data() + offset, &memberCount, sizeof(int32_t));
    offset += sizeof(int32_t);

    if (memberCount > 0) {
        memcpy(sendBuffer.data() + offset, memberList.data(), memberCount * sizeof(RoomMemberPacket));
    }
    
    m_Server->SendPacket(client->sessionID, PKT_S2C_ROOM_ENTER, sendBuffer.data(), dataSize);
   
    // Build the broadcast payload for existing members.
    // [int32 MemberCount][RoomMemberPacket * N]
    int brdDataSize = sizeof(int32_t) + (memberCount * sizeof(RoomMemberPacket));
    std::vector<char> brdBuffer(brdDataSize);

    int brdOffset = 0;
    memcpy(brdBuffer.data() + brdOffset, &memberCount, sizeof(int32_t));
    brdOffset += sizeof(int32_t);

    if (memberCount > 0) {
        memcpy(brdBuffer.data() + brdOffset, memberList.data(), memberCount * sizeof(RoomMemberPacket));
    }

    // Notify the rest of the room about the updated member list.
    room->BroadcastToMembers(PKT_S2C_ROOM_INFO_BRD, brdBuffer.data(), brdDataSize, client->sessionID);

    // Refresh the lobby-visible room list.
    m_Server->BroadcastRoomList();
    return true;
}

void RoomManager::GameStart(Session* client)
{
    if (client == nullptr || client->roomID == -1) { return; }

    Room* room = GetRoom(client->roomID);
    if (room == nullptr) return;

    if (!room->IsOwner(client->sessionID)) {
        LOG_WARN("GameStart failed - Session [%d] is not room owner", client->sessionID);

        ErrorCodePacket failPacket{};
        failPacket.ErrorCode = 5; // Host only
        m_Server->SendPacket(client->sessionID, PKT_S2C_ERROR, (char*)&failPacket, sizeof(failPacket));
        return;
    }

    // Validate that every player in the room is ready before starting.
    if (!room->IsAllReady()) {
        LOG_WARN("GameStart failed - not all players ready");
        ErrorCodePacket failPacket;
        failPacket.ErrorCode = 4;  // Not all players are ready yet.
        m_Server->SendPacket(client->sessionID, PKT_S2C_ERROR, (char*)&failPacket, sizeof(failPacket));
        return;
    }

    // Switch the room into PLAYING state.
    room->SetState(ERoomState::PLAYING);

    GameLogic* logic = new GameLogic();
    logic->ownerRoom = room;
    room->InitGameLogic(logic);

    // Set Player Data Init
    //room->InitCharacter(client, logic);

    // Broadcast the game-start event to every room member.
    room->BroadcastToMembers(PKT_S2C_GAME_START_BRD, nullptr, 0);

    LOG_INFO("Game Started! Room [%d]", client->roomID);
}

void RoomManager::UpdateRooms(float deltaTime)
{
    std::vector<int> activeRoomIDs;

    {
        std::lock_guard<std::mutex> lock(m_ManagerLock);
        for (auto& pair : m_Rooms) {
            activeRoomIDs.push_back(pair.first);
        }
    }

    for (int roomID : activeRoomIDs) {
        Room* room = GetRoom(roomID); // Re-resolve the room because it may have been destroyed after the ID snapshot was built.

        if (room != nullptr) {
            room->UpdateGameLogic(deltaTime);

            if (!room->BroadcastGameDatas()) {
                DestroyRoom(roomID);
            }
        }
    }
}

std::vector<RoomPacket> RoomManager::GetRoomList()
{
    std::lock_guard<std::mutex> lock(m_ManagerLock);
    std::vector<RoomPacket> roomList;

    for (auto& pair : m_Rooms) {
        Room* room = pair.second;
        RoomPacket info;

        if (room->GetState() != ERoomState::WAITING) continue;

        info.roomID = room->GetID();

        std::wstring title = L"Game Room " + std::to_wstring(info.roomID);
        wcscpy_s(info.RoomName, sizeof(info.RoomName) / sizeof(WCHAR), title.c_str());

        info.CurrentPlayers = room->GetCurrentMemberCount();

        roomList.push_back(info);
    }
    return roomList;
}

Room* RoomManager::GetRoom(int roomID)
{
    std::lock_guard<std::mutex> lock(m_ManagerLock);

    auto it = m_Rooms.find(roomID);

    if (it != m_Rooms.end()) {
        return it->second;
    }

    return nullptr;
}

int RoomManager::assignRoomID()
{
    for (int i = 0; i < m_RoomCounter; ++i) {
        if (m_Rooms.find(i) == m_Rooms.end()) { return i; }
    }

    return -1;
}

