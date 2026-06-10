#include "RoomManager.h"
#include "session.h"
#include "server.h"

#include <random>

void Room::InitRoom(int id, Session* firstMember, IOCPServer* server) {
	//std::lock_guard<std::mutex> lock(m_RoomLock);
	m_roomID = id;
    m_Server = server;
    m_State = ERoomState::WAITING;
    gameTimer = 0.f;
    //selectedMapType = 1;
	
    //addMember(firstMember);
}

void Room::InitGameLogic(GameLogic* logic)
{
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
        }
    }

    logic->SetMapType(selectedMapType);
    //logic->StartGameRound();
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
    gd.teamType = member->teamID;

    logic->ApplyRoleStats(member->sessionID);
    gd.currentHP = gd.maxHP;
    gd.equippedItemID = -1;

    const Vector3 spawn = GetRespawnLocation(slot);

    gd.x = spawn.x;
    gd.y = spawn.y;
    gd.z = spawn.z;//logic->GetGroundActorZ(); //
    gd.rotate = GetSpawnYawBySlot(slot);

    member->VerticalVelocity = 0.0f;
    member->isGrounded = true;
    member->JumpCount = 0;
    member->HorizontalVelocityX = 0.0f;
    member->HorizontalVelocityY = 0.0f;
    member->bOnIce = false;
    member->IceContactRemainTime = 0.0f;

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

bool Room::ChangeMemberSlot(Session* member, int targetSlot)
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    if (!member) return false;
    if (targetSlot < 0 || targetSlot >= MaxMember) return false;
    if (UsedSlots[targetSlot]) return false;

    const int oldSlot = member->roomSlot;
    if (oldSlot >= 0 && oldSlot < MaxMember)
    {
        UsedSlots[oldSlot] = false;
    }

    UsedSlots[targetSlot] = true;
    member->roomSlot = targetSlot;
    member->teamID = TeamCalculateBySlot(targetSlot);
    member->gameDatas.teamType = member->teamID;

    return true;
}

int Room::TeamCalculateBySlot(int roomSlot) const
{
    if (roomSlot >= 0 && roomSlot < 3) { return 0; }
    if (roomSlot >= 3 && roomSlot < 6) { return 1; }
    return -1;
}

void Room::SelectStage(int stageNum)
{
    if (stageNum < 1 || stageNum > 5) {
        LOG_ERROR("Select %d is Invalid Stage", stageNum);
        return;
    }

    selectedMapType = stageNum;
}

ItemData Room::SpawnRandomItem(const ItemSpawnRange& range)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> distX(range.MinX, range.MaxX);
    std::uniform_real_distribution<float> distY(range.MinY, range.MaxY);

    ItemData item{};
    item.ObjectID = range.ObjectID;
    item.ObjectType = e_ObjectType::WEAPON_ITEM;
    item.ItemKind = range.ItemKind;
    item.x = distX(gen);
    item.y = distY(gen);
    item.z = range.Z;
    item.ownerUID = -1;
    item.bEquipped = false;

    m_ItemObjects[item.ObjectID] = item;
    return item;
}

void Room::LoadStage(int stageNum)
{
    m_ItemObjects.clear();

    if (stageNum == 1) // BuildingStage
    {
        ItemData item1{};
        item1.ObjectID = 1;
        item1.ObjectType = e_ObjectType::WEAPON_ITEM;
        item1.x = 630.0f;
        item1.y = -5070.0f;
        item1.z = 450.0f;
        item1.ownerUID = -1;
        item1.bEquipped = false;
        m_ItemObjects[item1.ObjectID] = item1;

        ItemData item2{};
        item2.ObjectID = 2;
        item2.ObjectType = e_ObjectType::WEAPON_ITEM;
        item2.x = 760.0f;
        item2.y = -4030.0f;
        item2.z = 10.0f;
        item2.ownerUID = -1;
        item2.bEquipped = false;
        m_ItemObjects[item2.ObjectID] = item2;

        ItemData item3{};
        item3.ObjectID = 3;
        item3.ObjectType = e_ObjectType::WEAPON_ITEM;
        item3.x = -330.0f;
        item3.y = -3300.0f;
        item3.z = 10.0f;
        item3.ownerUID = -1;
        item3.bEquipped = false;
        m_ItemObjects[item3.ObjectID] = item3;
    }

    if (stageNum == 2) // IceCaveStage
    {
        ItemData torch{};
        torch.ObjectID = 101;
        torch.ObjectType = e_ObjectType::WEAPON_ITEM;
        torch.ItemKind = EItemKind::Torch;
        torch.x = 0.0f;
        torch.y = 0.0f;
        torch.z = 500.0f;
        torch.ownerUID = -1;
        torch.bEquipped = false;

        m_ItemObjects[torch.ObjectID] = torch;
    }
}

void Room::InitRoundCharacters(GameLogic* logic)
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    for (Session* member : m_Members)
    {
        if (!member) { continue; }

        logic->players[member->sessionID] = member;
        InitCharacter(member, logic);
    }
}

Vector3 Room::GetRespawnLocation(int slot)
{
    if (slot < 0 || slot >= 6)
    {
        return { -100.f, -100.f, -100.f };
    }

    static const Vector3 BuildingSpawnTable[6] =
    {
        {  5000.f, -1500.f, 2000.f },
        {  5000.f,     0.f, 2000.f },
        {  5000.f,  1500.f, 2000.f },
        { -5000.f, -1500.f, 2000.f },
        { -5000.f,     0.f, 2000.f },
        { -5000.f,  1500.f, 2000.f }
    };

    static const Vector3 IceCaveSpawnTable[6] =
    {
        {  5000.f, -1500.f, 2000.f },
        {  5000.f,     0.f, 2000.f },
        {  5000.f,  1500.f, 2000.f },
        { -5000.f, -1500.f, 2000.f },
        { -5000.f,     0.f, 2000.f },
        { -5000.f,  1500.f, 2000.f }
    };

    static const Vector3 SpaceStationSpawnTable[6] =
    {
        {  5000.f, -1500.f, 2000.f },
        {  5000.f,     0.f, 2000.f },
        {  5000.f,  1500.f, 2000.f },
        { -5000.f, -1500.f, 2000.f },
        { -5000.f,     0.f, 2000.f },
        { -5000.f,  1500.f, 2000.f }
    };

    static const Vector3 JungleSpawnTable[6] =
    {
        {  5000.f, -1500.f, 2000.f },
        {  5000.f,     0.f, 2000.f },
        {  5000.f,  1500.f, 2000.f },
        { -5000.f, -1500.f, 2000.f },
        { -5000.f,     0.f, 2000.f },
        { -5000.f,  1500.f, 2000.f }
    };

    static const Vector3 SkyIslandSpawnTable[6] =
    {
        {  5000.f, -1500.f, 10000.f },
        {  5000.f,     0.f, 10000.f },
        {  5000.f,  1500.f, 10000.f },
        { -5000.f, -1500.f, 10000.f },
        { -5000.f,     0.f, 10000.f },
        { -5000.f,  1500.f, 10000.f }
    };

    const Vector3* spawnTable = BuildingSpawnTable;

    switch (selectedMapType)
    {
    case 1:
        spawnTable = BuildingSpawnTable;
        break;

    case 2:
        spawnTable = IceCaveSpawnTable;
        break;

    case 3:
        spawnTable = SpaceStationSpawnTable;
        break;

    case 4:
        spawnTable = JungleSpawnTable;
        break;

    case 5:
        spawnTable = SkyIslandSpawnTable;
        break;

    default:
        spawnTable = BuildingSpawnTable;
        break;
    }

    return spawnTable[slot];
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

void Room::BeginDeferredRoundStart(float DelaySec)
{
    bPendingRoundStart = true;
    PendingRoundStartDelay = DelaySec;
}

void Room::UpdateGameLogic(float deltaTime)
{
    if (m_State != ERoomState::PLAYING) { return; }
    if (!m_GameLogic) { return; }

    if (bPendingRoundStart)
    {
        PendingRoundStartDelay -= deltaTime;
        if (PendingRoundStartDelay <= 0.f)
        {
            bPendingRoundStart = false;
            m_GameLogic->StartGameRound();
        }
        return;
    }

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

void Room::ReturnMembersToLobby()
{
    std::lock_guard<std::mutex> lock(m_RoomLock);

    for (Session* member : m_Members)
    {
        if (!member) { continue; }

        SessionManager::GetInstance()->SetState(member->sessionID, ESessionState::LOBBY);
        member->roomID = -1;
        member->isReady = false;
        member->roomSlot = -1;
    }

    m_Members.clear();
    m_OwnerSessionID = -1;

    for (int i = 0; i < MaxMember; ++i)
    {
        UsedSlots[i] = false;
    }
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
        info.isHost = IsOwner(member->sessionID) ? 1 : 0;
        info.userUID = member->playerUID;
        info.roomSlot = member->roomSlot;
        info.roleType = member->gameDatas.roleType;

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

            if (room->GetState() == ERoomState::PLAYING)
            {
                if (GameLogic* logic = room->GetgameLogic())
                {
                    logic->HandlePlayerLeaveDuringGame(leavingSessionID);
                }
            }

            wasOwner = room->IsOwner(leavingSessionID);
            room->RemoveMember(leavingSessionID);

            SessionManager::GetInstance()->SetState(client->sessionID, ESessionState::LOBBY);
            client->roomID = -1;
            client->isReady = false;
            client->roomSlot = -1;
            client->teamID = -1;
            client->gameDatas.roleType = -1;

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

    if (room->GetState() != ERoomState::WAITING)
    {
        LOG_WARN("JoinRoom failed - Room [%d] is not waiting", roomID);

        ErrorCodePacket failPacket{};
        failPacket.ErrorCode = 3; // Room error
        m_Server->SendPacket(client->sessionID, PKT_S2C_ERROR, (char*)&failPacket, sizeof(failPacket));

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
    
    std::vector<int> AvailableMaps = { 1, 2, 3, 4, 5 }; // 1: Building, 2: IceCave, 3: Space, 4: Jungle, 5: SkyIsland

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, static_cast<int>(AvailableMaps.size()) - 1);

    GameLogic* logic = new GameLogic();
    logic->ownerRoom = room;
    logic->SetAvailableMaps(AvailableMaps);

    room->SetState(ERoomState::PLAYING);
    room->InitGameLogic(logic);
    m_Server->BroadcastRoomList();

    LOG_INFO("Game Started! Room [%d]", client->roomID);
    logic->StartMatch();
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

        if (room != nullptr)
        {
            room->UpdateGameLogic(deltaTime);

            if (room->GetState() == ERoomState::FINISHED)
            {
                DestroyRoom(roomID);
                continue;
            }

            if (!room->BroadcastGameDatas())
            {
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

