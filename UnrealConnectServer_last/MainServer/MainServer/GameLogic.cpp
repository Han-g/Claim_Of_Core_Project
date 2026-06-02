#include "GameLogic.h"

#include "RoomManager.h"
#include "Packet.h"
#include "session.h"

#include <algorithm>
#include <random>

GameLogic::GameLogic() { ownerRoom = nullptr; }

GameLogic::~GameLogic() { }

void GameLogic::Update(float deltaTime)
{
    elapsedTime += deltaTime;

    // Advance the shared one-second round timer.
    timeAccumlator += deltaTime;
    while (timeAccumlator >= 1.f) {
        timeAccumlator -= 1.f;
        CountdownTick();
    }

    // Map Select
    if (matchFlowState == EMatchFlow::RoundFinish)
    {
        matchFlowRemainTime -= deltaTime;
        if (matchFlowRemainTime <= 0.0f)
        {
            BeginNextRoundOrEndMatch();
        }
        return;
    }

    if (matchFlowState == EMatchFlow::MapSelectedWait)
    {
        matchFlowRemainTime -= deltaTime;
        if (matchFlowRemainTime <= 0.0f)
        {
            matchFlowState = EMatchFlow::RoundPlaying;

            ownerRoom->BroadcastToMembers(PKT_S2C_GAME_START_BRD, nullptr, 0);
            ownerRoom->BeginDeferredRoundStart(roundStartDelay);
        }
        return;
    }

    if (roundState != ERoundState::Playing) { return; }
    
    // Adapt Player Movement
    for (auto& Pair : players)
    {
        Session* player = Pair.second;
        if (!player) { continue; }

        UpdatePlayerMovement(player, deltaTime);

        {
            std::lock_guard<std::mutex> lock(player->AttackStateLock);

            if (player->isAttack)
            {
                player->attackRemainTime -= deltaTime;

                if (player->attackRemainTime <= 0.0f)
                {
                    player->isAttack = false;
                    player->attackRemainTime = 0.0f;

                    LOG_INFO("[Attack] End session=%d uid=%d",
                        player->sessionID,
                        player->playerUID);
                }
            }
        }
    }


    // Update map-specific hazard logic.
    if      (mapType == 1)  { UpdateBuildingMap(deltaTime); } 
    else if (mapType == 2)  { UpdateIceCaveMap(deltaTime); }
    else if (mapType == 3)  { UpdateSpaceStation(deltaTime); }
    else if (mapType == 4)  { UpdateIceCaveMap(deltaTime); }
    else if (mapType == 5)  { UpdateIceCaveMap(deltaTime); }
    else { LOG_ERROR("InValid Map Type!"); return; }
}

void GameLogic::StartGameReady()
{
    roundState = ERoundState::Waiting;
    currentReadyTime = readyTime;
    elapsedTime = 0.f;
    timeAccumlator = 0.f;
}

void GameLogic::StartGameRound()
{
    roundState = ERoundState::Playing;
    gameTime = phase1Time + phase2Time + phase3Time;
    currentGameTime = gameTime;
    currentMapPhase = 1;

    // Initialize map gimmicks
    if (mapType == 1) {
        LOG_INFO("Building Map Select");
        StartBuildingMap();
    }
    else if (mapType == 2) {
        LOG_INFO("IceCave Map Select");
        StartIceMap();
    }
    else if (mapType == 3) {
        LOG_INFO("Space Map Select");
        StartSpaceStation();
    }
    else if (mapType == 4) {
        LOG_INFO("SkyIsland Map Select");
    }
    else if (mapType == 5) {
        LOG_INFO("Jungle Map Select");
    }
    else {
        LOG_ERROR("InValid Map Selection");
        return;
    }

    PhaseChangePacket pkt;
    pkt.roundState = 1;
    pkt.mapPhase = 1;
    pkt.gameTime = (float)currentGameTime;
    if (mapType == 3) {
        pkt.blackHoleX = SpaceBlackHoleCenter.x;
        pkt.blackHoleY = SpaceBlackHoleCenter.y;
        pkt.blackHoleZ = SpaceBlackHoleCenter.z;
    }

    ownerRoom->BroadcastToMembers(PKT_S2C_GAME_PHASE_CHANGE_BRD, (char*)&pkt, sizeof(pkt));
}

void GameLogic::EndGameRound()
{
    if (roundState == ERoundState::Finished) { return; }

    roundState = ERoundState::Finished;

    PhaseChangePacket phasePkt;
    phasePkt.roundState = 2;
    phasePkt.mapPhase = currentMapPhase;
    phasePkt.gameTime = 0.f;

    ownerRoom->BroadcastToMembers(PKT_S2C_GAME_PHASE_CHANGE_BRD,
        reinterpret_cast<const char*>(&phasePkt), sizeof(phasePkt));

    RoundResultPacket resultPkt{};
    resultPkt.winnerTeamID = CalculateWinnerTeam();
    resultPkt.endReason = 0; // TimeOver 등

    RoundChangePacket finishPkt{};
    finishPkt.currentMap = mapType;
    finishPkt.currentRound = roundCount;
    finishPkt.nextRoundStartSec = 5;
    finishPkt.result = resultPkt;

    BroadcastRoundResult(finishPkt);
}

void GameLogic::CountdownTick()
{
    if (roundState != ERoundState::Playing) { return; }

    else {
        currentGameTime--;

        BroadcastGameTime((float)currentGameTime);

        const int elapsed = gameTime - currentGameTime;

        if (currentGameTime <= phase3Time && currentMapPhase == 2)
        {
            currentMapPhase = 3;
            HandlePhaseChanged(3);
        }
        else if (currentGameTime <= phase2Time + phase3Time && currentMapPhase == 1)
        {
            currentMapPhase = 2;
            HandlePhaseChanged(2);
        }

        if (currentGameTime <= 0)
        {
            EndGameRoundWithResult(CalculateWinnerTeam(), 0); // 0 = TimeOver
        }
    }
}

void GameLogic::HandlePhaseChanged(int newPhase)
{
    PhaseChangePacket pkt;
    pkt.roundState = 1;  // Playing
    pkt.mapPhase = newPhase;
    pkt.gameTime = (float)currentGameTime;

    if (mapType == 3) {
        pkt.blackHoleX = SpaceBlackHoleCenter.x;
        pkt.blackHoleY = SpaceBlackHoleCenter.y;
        pkt.blackHoleZ = SpaceBlackHoleCenter.z;
    }

    ownerRoom->BroadcastToMembers(PKT_S2C_GAME_PHASE_CHANGE_BRD, (const char*)&pkt, sizeof(pkt));
}

int GameLogic::CalculateWinnerTeam()
{
    int team0AliveCount = 0;
    int team1AliveCount = 0;

    for (const auto& player : players)
    {
        Session* session = player.second;

        if (session == nullptr) {  continue;  }

        const GameData& data = session->gameDatas;

        if (!data.isConnected || data.characterState != Alive) { continue; }

        if (session->teamID == 0)
        {
            ++team0AliveCount;
        }
        else if (session->teamID == 1)
        {
            ++team1AliveCount;
        }
    }

    if (team0AliveCount > team1AliveCount) { return 0; }
    if (team1AliveCount > team0AliveCount) { return 1; }

    return -1; // draw
}

void GameLogic::StartMatch()
{
    team1Score = 0;
    team2Score = 0;
    currentRound = 0;
    roundCount = 0;

    selectedMapType = 0;
    currentMapPhase = 0;
    currentGameTime = 0;
    timeAccumlator = 0.0f;
    elapsedTime = 0.0f;

    roundState = ERoundState::Waiting;
    matchFlowState = EMatchFlow::Robby;

    BeginRoundPrepare();
}

void GameLogic::BeginRoundPrepare()
{
    if (currentRound >= maxRound)
    {
        EndMatch();
        return;
    }

    ++currentRound;
    roundCount = currentRound;

    selectedMapType = 0;
    currentMapPhase = 0;
    roundState = ERoundState::Waiting;

    matchFlowState = EMatchFlow::MapSelectedWait;
    matchFlowRemainTime = mapSelectTime;

    if (!TrySelectMap())
    {
        EndMatch();
        return;
    }

    mapType = selectedMapType;

    ownerRoom->SelectStage(selectedMapType);
    ownerRoom->LoadStage(selectedMapType);

    ownerRoom->InitRoundCharacters(this);

    RoundPreparePacket pkt{};
    pkt.currentRound = currentRound;
    pkt.maxRound = maxRound;
    pkt.team1Score = team1Score;
    pkt.team2Score = team2Score;
    pkt.mapSelectTime = mapSelectTime;

    ownerRoom->BroadcastToMembers(PKT_S2C_ROUND_PREPARE_BRD,
        reinterpret_cast<const char*>(&pkt), sizeof(pkt));

    ownerRoom->BroadcastToMembers(
        PKT_S2C_MAP_SELECT_NOTICE,
        reinterpret_cast<const char*>(&selectedMapType),
        sizeof(selectedMapType)
    );
}

void GameLogic::SetAvailableMaps(const std::vector<int>& maps)
{
    availableMaps = maps;
    remainingMaps = maps;
}

bool GameLogic::TrySelectMap()
{
    //if (matchFlowState != EMatchFlow::MapSelecting) { return false; }

    if (availableMaps.empty())
    {
        LOG_ERROR("[MapSelect] AvailableMaps is empty");
        return false;
    }

    if (remainingMaps.empty())
    {
        remainingMaps = availableMaps;
    }

    const int index = rand() % static_cast<int>(remainingMaps.size());
    selectedMapType = remainingMaps[index];

    remainingMaps.erase(remainingMaps.begin() + index);

    return true;
}

void GameLogic::FinishMapSelection()
{
    if (matchFlowState != EMatchFlow::MapSelecting)
    {
        return;
    }

    if (selectedMapType < 1) {
        if (!TrySelectMap()) {
            return;
        }
    }

    mapType = selectedMapType;

    ownerRoom->SelectStage(selectedMapType);
    ownerRoom->LoadStage(selectedMapType);

    ownerRoom->BroadcastToMembers(
        PKT_S2C_MAP_SELECT_NOTICE,
        reinterpret_cast<const char*>(&selectedMapType),
        sizeof(selectedMapType)
    );

    /*matchFlowState = EMatchFlow::RoundPlaying;
    ownerRoom->BeginDeferredRoundStart(roundStartDelay);*/
    matchFlowState = EMatchFlow::MapSelectedWait;
    matchFlowRemainTime = roundStartDelay;
}

void GameLogic::BeginNextRoundOrEndMatch()
{
    if (team1Score >= requiredWinScore || team2Score >= requiredWinScore)
    {
        EndMatch();
        return;
    }

    if (currentRound >= maxRound)
    {
        EndMatch();
        return;
    }

    BeginRoundPrepare();
}

void GameLogic::EndMatch()
{
    if (!ownerRoom)
    {
        return;
    }

    matchFlowState = EMatchFlow::MatchFinish;
    roundState = ERoundState::Finished;

    ownerRoom->BroadcastToMembers(PKT_S2C_MATCH_END_BRD, nullptr, 0);

    LOG_INFO("[MatchEnd] round=%d/%d finalScore=%d:%d",
        currentRound,
        maxRound,
        team1Score,
        team2Score
    );

    ownerRoom->ReturnMembersToLobby();
    ownerRoom->SetState(ERoomState::FINISHED);
}



void GameLogic::BroadcastGameTime(float currentTime)
{
    if (!ownerRoom) { LOG_ERROR("Room is not exist for broadcasting"); return; }

    float timeData = currentTime;
    ownerRoom->BroadcastToMembers(PKT_S2C_SYNC_GAME_TIME_NOTICE, (const char*)&timeData, sizeof(float));
}


void GameLogic::BroadcastDamageApply(int targetID, int damage, int remainHP)
{
    if (!ownerRoom) { return; }

    DamageApplyPacket pkt;
    pkt.targetID = targetID;
    pkt.damage = damage;
    pkt.remainHP = remainHP;

    ownerRoom->BroadcastToMembers(PKT_S2C_DAMAGE_APPLY_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::BroadcastStatusUpdate(int targetID, int currentHP)
{
    if (!ownerRoom) { return; }

    StatusUpdatePacket pkt;
    pkt.targetID = targetID;
    pkt.currentHP = currentHP;

    ownerRoom->BroadcastToMembers(PKT_S2C_STATUS_UPDATE_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::BroadcastStateChange(int targetID, int newState)
{
    if (!ownerRoom) { return; }

    StateChangePacket pkt;
    pkt.targetID = targetID;
    pkt.newState = newState;

    ownerRoom->BroadcastToMembers(PKT_S2C_STATE_CHANGE_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::BroadcastRespawn(int targetID, float x, float y, float z, int hp)
{
    if (!ownerRoom) { return; }

    RespawnPacket pkt;
    pkt.targetID = targetID;
    pkt.x = x;
    pkt.y = y;
    pkt.z = z;
    pkt.hp = hp;

    ownerRoom->BroadcastToMembers(PKT_S2C_RESPAWN_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::BroadcastRoleChange(int targetID, int newRoleType)
{
    if (!ownerRoom) { return; }

    RoleChangePacket pkt;
    pkt.targetID = targetID;
    pkt.newRoleType = newRoleType;

    ownerRoom->BroadcastToMembers(PKT_S2C_CHARACTER_SELECT_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::BroadcastRoundResult(const RoundChangePacket& packet)
{
    if (!ownerRoom) { return; }

    ownerRoom->BroadcastToMembers(
        PKT_S2C_GAME_RESULT_BRD,
        reinterpret_cast<const char*>(&packet),
        sizeof(packet)
    );
}



void GameLogic::ApplyDamage(int sessionID, int damageAmount)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    GameData& gd = targetSession->gameDatas;
    if (damageAmount <= 0 || gd.characterState == 1) { return; } // non-positive damage or already dead

    const int prevHP = gd.currentHP;
    SetCurrentHP(sessionID, gd.currentHP - damageAmount);

    LOG_INFO("[ATK_TRACE][4_ServerDamage] targetSession=%d targetUID=%d damage=%d hpBefore=%d hpAfter=%d",
        sessionID,
        targetSession->playerUID,
        damageAmount,
        prevHP,
        gd.currentHP);

    // Broadcast the damage result to all clients in the room.
    // PKT_S2C_DAMAGE_APPLY_BRD: target session, damage, remaining HP
    BroadcastDamageApply(targetSession->playerUID, damageAmount, gd.currentHP);

    if (prevHP > 0 && gd.currentHP <= 0)
    {
        HandleDeath(sessionID);
    }
}

void GameLogic::Heal(int sessionID, int healAmount)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    GameData& gd = targetSession->gameDatas;
    if (healAmount <= 0) { return; }

    SetCurrentHP(sessionID, gd.currentHP + healAmount);

    // PKT_S2C_STATUS_UPDATE_BRD: target session and updated HP
    BroadcastStatusUpdate(targetSession->playerUID, gd.currentHP);
}

void GameLogic::ResetHP(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    GameData& gd = targetSession->gameDatas;

    if (gd.characterState == 1) {  // Dead
        HandleRespawn(sessionID);
        return;
    }
    
    SetCurrentHP(sessionID, gd.maxHP);
    BroadcastStatusUpdate(targetSession->playerUID, gd.currentHP);
}

void GameLogic::SetCurrentHP(int sessionID, int newHP)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    GameData& gd = targetSession->gameDatas;
    // Clamp the value to the valid HP range.
    if (newHP < 0) { newHP = 0; }
    if (newHP > gd.maxHP) { newHP = gd.maxHP; }
    gd.currentHP = newHP;

    // If HP reaches zero while the player is alive, trigger death handling.
    // Death handle Move to ApplyDamage
    /*if (gd.characterState == 0 && gd.currentHP <= 0) {
        HandleDeath(sessionID);
    }*/
}

void GameLogic::EndGameRoundByElimination(int eliminatedTeamID)
{
    if (roundState == ERoundState::Finished) { return; }

    const int winnerTeamID = (eliminatedTeamID == 0) ? 1 : 0;

    EndGameRoundWithResult(winnerTeamID, 1); // 1 = TeamEliminated
}

void GameLogic::EndGameRoundWithResult(int winnerTeamID, int endReason)
{
    if (roundState == ERoundState::Finished) { return; }

    roundState = ERoundState::Finished;
    matchFlowState = EMatchFlow::RoundFinish;
    matchFlowRemainTime = resultRemainTime;

    // Match Logic
    if      (winnerTeamID == 0) { team1Score++; }
    else if (winnerTeamID == 1) { team2Score++; }
    else { LOG_ERROR("InValid Winner Team"); }

    /*if (currentRound == maxRound) {
        EndMatch();
    }
    else if (currentRound < maxRound) {
        BeginRoundPrepare();
    }
    else {  LOG_ERROR("InValid Round"); }*/

    PhaseChangePacket phasePkt{};
    phasePkt.roundState = Finished;
    phasePkt.mapPhase = currentMapPhase;
    phasePkt.gameTime = 0.f;

    ownerRoom->BroadcastToMembers(
        PKT_S2C_GAME_PHASE_CHANGE_BRD,
        reinterpret_cast<const char*>(&phasePkt),
        sizeof(phasePkt)
    );

    RoundChangePacket finishPkt{};
    finishPkt.currentMap = mapType;
    finishPkt.currentRound = roundCount;
    finishPkt.nextRoundStartSec = 5;

    finishPkt.result.winnerTeamID = winnerTeamID;
    finishPkt.result.endReason = endReason;
    finishPkt.result.team1Score = team1Score;
    finishPkt.result.team2Score = team2Score;

    BroadcastRoundResult(finishPkt);
}

void GameLogic::SetCharacterState(int sessionID, int newState)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    GameData& gd = targetSession->gameDatas;
    if (gd.characterState == newState) { return; }

    gd.characterState = newState;

    // PKT_S2C_STATE_CHANGE_BRD: target session and new life state
    BroadcastStateChange(targetSession->playerUID, newState);
}

void GameLogic::HandleDeath(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* deadSession = it->second;
    if (deadSession == nullptr) { return; }

    SetCharacterState(sessionID, 1);  // Dead

    const int deadTeamID = deadSession->teamID;

    if (IsTeamEliminated(deadTeamID))
    {
        EndGameRoundByElimination(deadTeamID);
    }
}

void GameLogic::HandleRespawn(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    const int slot = targetSession->roomSlot;
    if (slot < 0)
    {
        LOG_WARN("HandleRespawn failed - invalid roomSlot. session=%d", sessionID);
        return;
    }

    GameData& gd = targetSession->gameDatas;
    if (gd.characterState != 1) { return; } // ignore if not currently dead

    // Restore HP before sending the respawn update.
    gd.currentHP = gd.maxHP;

    // Mark the player as alive again.
    gd.characterState = 0;

    // Resolve a server-authoritative respawn position.
    // This will eventually use map-specific predefined spawn locations.
    // It currently falls back to the room-provided spawn helper.
    Vector3 spawnPoint = ownerRoom->GetRespawnLocation(slot);
    gd.x = spawnPoint.x;
    gd.y = spawnPoint.y;
    gd.z = spawnPoint.z;

    targetSession->HorizontalVelocityX = 0.0f;
    targetSession->HorizontalVelocityY = 0.0f;
    targetSession->bOnIce = false;
    targetSession->IceContactRemainTime = 0.0f;

    // PKT_S2C_RESPAWN_BRD: target session, position, and HP
    BroadcastRespawn(targetSession->playerUID, gd.x, gd.y, gd.z, gd.currentHP);
}

bool GameLogic::IsTeamEliminated(int teamID) const
{
    bool hasTeamMember = false;

    for (const auto& pair : players)
    {
        Session* session = pair.second;
        if (session == nullptr ||
            !session->gameDatas.isConnected ||
            session->teamID != teamID) { continue; }

        hasTeamMember = true;

        if (session->gameDatas.characterState == Alive) { return false; }
    }

    return hasTeamMember;
}

void GameLogic::SetRole(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    GameData& gd = targetSession->gameDatas;
    if (gd.characterState == 1) { return; }  // cannot change while Dead

    ApplyRoleStats(sessionID);

    BroadcastRoleChange(targetSession->playerUID, gd.roleType);
}

void GameLogic::ApplyRoleStats(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;
    gd.baseWalkSpeed = 2000.f * GetRoleSpeedMultiplier(gd.roleType);

    // Apply role-specific max HP values.
    switch (gd.roleType) {
        case 0: 
            gd.maxHP = 100; // Striker
            break;  
        case 1: 
            gd.maxHP = 200; // Guardian
            break;  
        case 2: 
            gd.maxHP = 120; // Manipulator
            break;  
    }
}

float GameLogic::GetRoleSpeedMultiplier(int roleType)
{
    switch (roleType) {
        case 0: return 1.2f;   // Striker
        case 1: return 0.8f;   // Guardian
        case 2: return 1.0f;   // Manipulator
        default: return 1.0f;
    }
}

void GameLogic::HandleItemPickup(int sessionID, int itemID)
{
    if (!ownerRoom) { return; }

    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    GameData& gd = targetSession->gameDatas;

    ItemData* pickUpItemData = ownerRoom->GetItemData(itemID);
    if (!pickUpItemData) { return; }

    if (pickUpItemData->bEquipped) {
        LOG_WARN("[ItemPickup] already equipped. session=%d uid=%d itemID=%d ownerUID=%d",
            sessionID,
            targetSession->playerUID,
            itemID,
            pickUpItemData->ownerUID);
        return;
    }

    if (gd.equippedItemID != -1)
    {
        LOG_WARN("[ItemPickup] player already has item. session=%d uid=%d currentItemID=%d tryItemID=%d",
            sessionID,
            targetSession->playerUID,
            gd.equippedItemID,
            itemID);
        return;
    }
    else if (!pickUpItemData->bEquipped) {
        pickUpItemData->ownerUID = targetSession->playerUID;
        pickUpItemData->bEquipped = true;
        gd.equippedItemID = itemID;

        ItemPacket pkt{};
        pkt.itemID = itemID;
        pkt.itemKind = static_cast<int32_t>(pickUpItemData->ItemKind);
        pkt.ownerUID = targetSession->playerUID;
        pkt.bEquipped = 1;
        pkt.x = pickUpItemData->x;
        pkt.y = pickUpItemData->y;
        pkt.z = pickUpItemData->z;

        ownerRoom->BroadcastToMembers(
            PKT_S2C_ITEM_OWNERSHIP_BRD,
            (const char*)&pkt,
            sizeof(pkt)
        );
    }

    else {
        LOG_WARN("[ItemPickup] Failed to Pick up Item");
    }
}

void GameLogic::DropCurrentItem(int sessionID, int itemID)
{
    if (!ownerRoom) { return; }

    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* targetSession = it->second;
    if (!targetSession) { return; }

    GameData& gd = targetSession->gameDatas;

    ItemData* dropItemData = ownerRoom->GetItemData(itemID);
    if (!dropItemData) { return; }

    if (!dropItemData->bEquipped)
    {
        return;
    }

    if (dropItemData->ownerUID != targetSession->playerUID)
    {
        return;
    }

    if (gd.equippedItemID != itemID)
    {
        return;
    }

    dropItemData->bEquipped = false;
    dropItemData->ownerUID = -1;

    // 1차 구현은 플레이어 현재 위치에 드롭해도 충분
    dropItemData->x = gd.x;
    dropItemData->y = gd.y;
    dropItemData->z = gd.z;

    gd.equippedItemID = -1;

    ItemPacket pkt{};
    pkt.itemID = itemID;
    pkt.itemKind = static_cast<int32_t>(dropItemData->ItemKind);
    pkt.ownerUID = -1;
    pkt.bEquipped = 0;
    pkt.x = dropItemData->x;
    pkt.y = dropItemData->y;
    pkt.z = dropItemData->z;

    ownerRoom->BroadcastToMembers(
        PKT_S2C_ITEM_OWNERSHIP_BRD,
        (const char*)&pkt,
        sizeof(pkt)
    );

    LOG_INFO("[ItemDrop] success. session=%d uid=%d itemID=%d",
        sessionID,
        targetSession->playerUID,
        itemID);
}

auto MoveVelocityToward = [](float& vx, float& vy, float tx, float ty, float maxDelta)
    {
        float dx = tx - vx;
        float dy = ty - vy;
        float len = GameMath::Length2D(dx, dy);

        if (len <= maxDelta || len <= 0.0001f)
        {
            vx = tx;
            vy = ty;
            return;
        }

        vx += (dx / len) * maxDelta;
        vy += (dy / len) * maxDelta;
    };

void GameLogic::UpdatePlayerMovement(Session* player, float deltaTime)
{
    if (player == nullptr) { return; }

    if (player->bFrozen)
    {
        player->HorizontalVelocityX = 0.0f;
        player->HorizontalVelocityY = 0.0f;
        player->gameDatas.animationNum = 0;
        return;
    }

    // Movement Update data
    GameData& gd = player->gameDatas;

    if (!gd.isConnected) { return; }            // If Client Connection is disconnected
    if (gd.characterState != 0) { return; }     // If Character is Dead state

    // Synchronizate Character Coordination datas
    MoveIntent input;
    bool bJumpRequested = false;
    bool bServerOnIce = false;

    {
        std::lock_guard<std::mutex> lock(player->MoveIntentLock);

        input = player->LastMoveIntent;
        bJumpRequested = player->LastMoveIntent.bJumpRequested;
        player->LastMoveIntent.bJumpRequested = false;

        if (player->IceContactRemainTime > 0.0f)
        {
            player->IceContactRemainTime -= deltaTime;
            if (player->IceContactRemainTime < 0.0f)
            {
                player->IceContactRemainTime = 0.0f;
                player->bOnIce = false;
            }
        }

        player->bOnIce = player->IceContactRemainTime > 0.0f;
        bServerOnIce = player->bOnIce;
    }

    if (mapType == 3)
    {
        UpdatePlayerVertical(player, deltaTime, bJumpRequested);
    }
    else if (!input.bHasClientPosition)
    {
        UpdatePlayerVertical(player, deltaTime, bJumpRequested);
    }


    // Calculate Forward and Side Vector On the basis of Client Sight
    float moveX = 0.0f;
    float moveY = 0.0f;

    if (input.bHasInput)
    {
        const float yawRad = GameMath::DegreesToRadians(input.CameraDir);

        const float forwardX = std::cos(yawRad);
        const float forwardY = std::sin(yawRad);

        const float rightX = -std::sin(yawRad);
        const float rightY = std::cos(yawRad);

        moveX = forwardX * input.Forward + rightX * input.Right;
        moveY = forwardY * input.Forward + rightY * input.Right;

        GameMath::Normalize2D(moveX, moveY);
    }


    const bool bInAir = !player->isGrounded;

    const float targetVelX = moveX * gd.baseWalkSpeed;
    const float targetVelY = moveY * gd.baseWalkSpeed;

    /*const float acceleration = input.bHasInput
        ? (bServerOnIce ? IceMoveAcceleration : NormalMoveAcceleration)
        : (bServerOnIce ? IceBrakingDeceleration : NormalBrakingDeceleration);*/
    const float acceleration = bInAir
        ? (input.bHasInput ? AirMoveAcceleration : AirBrakingDeceleration)
        : (input.bHasInput
            ? (bServerOnIce ? IceMoveAcceleration : NormalMoveAcceleration)
            : (bServerOnIce ? IceBrakingDeceleration : NormalBrakingDeceleration));


    MoveVelocityToward(
        player->HorizontalVelocityX,
        player->HorizontalVelocityY,
        targetVelX,
        targetVelY,
        acceleration * deltaTime
    );

    const float maxSpeed = gd.baseWalkSpeed * (bServerOnIce ? IceMaxSpeedMultiplier : 1.0f);
    const float currentSpeed = GameMath::Length2D(player->HorizontalVelocityX, player->HorizontalVelocityY);

    if (currentSpeed > maxSpeed)
    {
        const float scale = maxSpeed / currentSpeed;
        player->HorizontalVelocityX *= scale;
        player->HorizontalVelocityY *= scale;
    }

    const float animationSpeed =
        GameMath::Length2D(player->HorizontalVelocityX, player->HorizontalVelocityY);

    Vector3 currentPos;
    currentPos.x = gd.x;
    currentPos.y = gd.y;
    currentPos.z = gd.z;

    Vector3 desiredPos;
    desiredPos.x = currentPos.x + player->HorizontalVelocityX * deltaTime;
    desiredPos.y = currentPos.y + player->HorizontalVelocityY * deltaTime;
    desiredPos.z = currentPos.z;

    const float collisionRadius = GetCollisionRadius(gd.roleType);
    const Vector3 resolvedPos = ResolveMovementWithCollision(currentPos, desiredPos, collisionRadius);

    gd.x = resolvedPos.x;
    gd.y = resolvedPos.y;
    gd.z = resolvedPos.z;
    //gd.rotate = input.CameraDir;

    // Check Z axis for Reflect game z
    if (input.bHasClientPosition)
    {
        const float MaxZCorrectionPerTick = 300.0f;
        const float ClientZ = input.ClientZ;
        const float ZDelta = ClientZ - gd.z;

        if (std::abs(ZDelta) <= MaxZCorrectionPerTick)
        {
            gd.z = ClientZ;
        }
        else
        {
            gd.z += (ZDelta > 0.0f ? MaxZCorrectionPerTick : -MaxZCorrectionPerTick);
        }

        const bool bClientGrounded = ClientZ <= GetGroundActorZ() + GroundSnapTolerance + 5.0f;

        player->isGrounded = bClientGrounded;

        if (bClientGrounded)
        {
            player->VerticalVelocity = 0.0f;
            player->JumpCount = 0;
        }
    }

    gd.animationNum = animationSpeed > StopVelocityThreshold ? 1 : 0;
}

void GameLogic::UpdatePlayerVertical(Session* player, float deltaTime, bool bJumpRequested)
{
    if (player == nullptr) { return; }

    GameData& gd = player->gameDatas;

    const float GroundActorZ = FixedGroundZ + ServerCapsuleHalfHeight;

    if (!player->isGrounded && gd.z <= GroundActorZ + GroundSnapTolerance)
    {
        gd.z = GroundActorZ;
        player->isGrounded = true;
        player->VerticalVelocity = 0.0f;
        player->JumpCount = 0;
    }

    if (bJumpRequested && player->isGrounded)
    {
        player->VerticalVelocity = GetCurrentServerJumpZVelocity();
        player->isGrounded = false;
        player->JumpCount = 1;
    }

    if (!player->isGrounded)
    {
        player->VerticalVelocity += GetCurrentServerGravityZ() * deltaTime;
        gd.z += player->VerticalVelocity * deltaTime;

        if (gd.z <= GroundActorZ)
        {
            gd.z = GroundActorZ;
            player->VerticalVelocity = 0.0f;
            player->isGrounded = true;
            player->JumpCount = 0;
        }
    }
}

float GameLogic::GetCollisionRadius(int roleType) const
{
    switch (roleType)
    {
    case 0: return 45.0f; // Striker
    case 1: return 55.0f; // Guardian
    case 2: return 45.0f; // Manipulator
    default: return 50.0f;
    }
}

bool GameLogic::CanOccupyPosition(const Vector3& pos, float radius) const
{
    return false;
}

Vector3 GameLogic::ResolveMovementWithCollision(const Vector3& currentPos, const Vector3& desiredPos, float radius) const
{
    // Temporary Treat
    return desiredPos;
}



void GameLogic::HandleAttackInput(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* attackerSession = it->second;
    if (!attackerSession || attackerSession->bFrozen) { return; }

    GameData& gd = attackerSession->gameDatas;

    if (!gd.isConnected || gd.characterState != 0 || attackerSession->playerUID <= 0) { return; }

    int attackType = 0;

    ItemData* EquippedItem = nullptr;
    if (gd.equippedItemID != -1 && ownerRoom)
    {
        EquippedItem = ownerRoom->GetItemData(gd.equippedItemID);
    }

    if (EquippedItem && EquippedItem->ItemKind == EItemKind::Torch)
    {
        attackType = 2; // Torch
    }
    else if (gd.equippedItemID != -1)
    {
        attackType = 1; // Normal item
    }

    {
        std::lock_guard<std::mutex> lock(attackerSession->AttackStateLock);

        if (attackerSession->isAttack)
        {
            LOG_INFO("[Attack] Reject duplicate attack session=%d uid=%d",
                sessionID,
                attackerSession->playerUID);
            return;
        }

        attackerSession->isAttack = true;
        attackerSession->attackRemainTime = 1.8f;
        attackerSession->attackSeq++;
        attackerSession->hasAttackHit = false;
    }

    BroadcastAttackAction(attackerSession->playerUID, attackType, attackerSession->attackSeq);
    //LOG_INFO("[Attack] HandleAttackInput session=%d uid=%d room ok", sessionID, gd.userUID);

   /* Session* bestTarget = nullptr;
    switch (gd.roleType)
    {
    case Guardian:
        Range = 500.f;
        break;

    case Striker:
        Range = 400.f;
        break;

    case Manipulator:
        Range = 400.f;
        break;

    default:
        Range = 400.f;
        break;
    }
    float bestDist = Range;

    const float yawRad = GameMath::DegreesToRadians(gd.rotate);
    const float forwardX = std::cos(yawRad);
    const float forwardY = std::sin(yawRad);
    const float minDot = std::cos(GameMath::DegreesToRadians(50.0f));

    for (const auto& pair : players)
    {
        Session* targetSession = pair.second;
        if (!targetSession || targetSession == attackerSession) { continue; }

        GameData& targetData = targetSession->gameDatas;
        if (!targetData.isConnected) { continue; }
        if (targetData.characterState != 0) { continue; }

        float toX = targetData.x - gd.x;
        float toY = targetData.y - gd.y;
        float dist = GameMath::Length2D(toX, toY);
        if (dist > Range) { continue; }

        GameMath::Normalize2D(toX, toY);
        const float dot = forwardX * toX + forwardY * toY;
        if (dot < minDot) { continue; }

        LOG_INFO(
            "[ATK_TEST][Target] attackerUID=%d targetUID=%d "
            "aPos=(%.1f, %.1f) tPos=(%.1f, %.1f) rotate=%.2f "
            "dist=%.1f range=%.1f dot=%.3f minDot=%.3f",
            attackerSession->playerUID,
            targetSession->playerUID,
            gd.x, gd.y,
            targetData.x, targetData.y,
            gd.rotate,
            dist,
            Range,
            dot,
            minDot
        );

        if (dist < bestDist)
        {
            bestDist = dist;
            bestTarget = targetSession;
        }
    }

    if (!bestTarget) { 
        LOG_INFO("Attack Miss to target");
        return; 
    }

    int damageAmount = 20;
    switch (gd.roleType)
    {
    case Striker: damageAmount = 30; break;
    case Guardian: damageAmount = 15; break;
    case Manipulator: damageAmount = 20; break;
    default: break;
    }

    ApplyDamage(bestTarget->sessionID, damageAmount);*/
}

void GameLogic::HandleAttackHitReport(int sessionID, const AttackHitReportPacket& pkt)
{
    auto attackerIt = players.find(sessionID);
    if (attackerIt == players.end()) return;

    Session* attackerSession = attackerIt->second;
    if (!attackerSession) return;

    GameData& attackerData = attackerSession->gameDatas;
    if (!attackerData.isConnected || attackerData.characterState != 0) return;

    {
        std::lock_guard<std::mutex> lock(attackerSession->AttackStateLock);

        if (!attackerSession->isAttack) return;
        if (pkt.attackSeq != attackerSession->attackSeq) return;
        if (attackerSession->hasAttackHit) return;
    }

    Session* targetSession = nullptr;

    for (const auto& pair : players)
    {
        Session* candidate = pair.second;
        if (!candidate) continue;

        if (candidate->playerUID == pkt.targetID)
        {
            targetSession = candidate;
            break;
        }
    }

    if (!targetSession || targetSession == attackerSession) return;

    GameData& targetData = targetSession->gameDatas;
    if (!targetData.isConnected || targetData.characterState != 0) return;

    float attackRange = 1200.f;

    switch (attackerData.roleType)
    {
    case Guardian:
        attackRange = 1500.f;
        break;
    case Striker:
    case Manipulator:
        attackRange = 1200.f;
        break;
    default:
        attackRange = 1200.f;
        break;
    }

    const float serverTolerance = 120.f;
    const float maxRange = attackRange + serverTolerance;

    float toX = targetData.x - attackerData.x;
    float toY = targetData.y - attackerData.y;
    const float dist = GameMath::Length2D(toX, toY);

    if (dist > maxRange)
    {
        LOG_INFO("[AttackHit] Reject range attackerUID=%d targetUID=%d dist=%.1f maxRange=%.1f",
            attackerSession->playerUID, targetSession->playerUID, dist, maxRange);
        return;
    }

    const float yawRad = GameMath::DegreesToRadians(attackerData.rotate);
    const float forwardX = std::cos(yawRad);
    const float forwardY = std::sin(yawRad);

    GameMath::Normalize2D(toX, toY);

    const float dot = forwardX * toX + forwardY * toY;
    const float minDot = std::cos(GameMath::DegreesToRadians(65.f));

    if (dot < minDot)
    {
        LOG_INFO("[AttackHit] Reject angle attackerUID=%d targetUID=%d dot=%.3f minDot=%.3f",
            attackerSession->playerUID, targetSession->playerUID, dot, minDot);
        return;
    }

    int damageAmount = 20;

    switch (attackerData.roleType)
    {
    case Striker:
        damageAmount = 30;
        break;
    case Guardian:
        damageAmount = 15;
        break;
    case Manipulator:
        damageAmount = 20;
        break;
    }

    {
        std::lock_guard<std::mutex> lock(attackerSession->AttackStateLock);

        if (!attackerSession->isAttack) return;
        if (pkt.attackSeq != attackerSession->attackSeq) return;
        if (attackerSession->hasAttackHit) return;

        attackerSession->hasAttackHit = true;
    }

    LOG_INFO("[AttackHit] Confirm attackerUID=%d targetUID=%d seq=%u dist=%.1f range=%.1f damage=%d",
        attackerSession->playerUID,
        targetSession->playerUID,
        pkt.attackSeq,
        dist,
        attackRange,
        damageAmount);

    ItemData* EquippedItem = nullptr;
    if (attackerData.equippedItemID != -1 && ownerRoom)
    {
        EquippedItem = ownerRoom->GetItemData(attackerData.equippedItemID);
    }

    const bool bUsingTorch =
        EquippedItem &&
        EquippedItem->ObjectType == e_ObjectType::WEAPON_ITEM &&
        EquippedItem->ItemKind == EItemKind::Torch;

    if (bUsingTorch)
    {
        if (targetSession->bFrozen)
        {
            EndFreezeOnPlayer(targetSession->sessionID);
        }
    }

    ApplyDamage(targetSession->sessionID, damageAmount);
}

void GameLogic::BroadcastAttackAction(int attackerUID, int attackType, uint32_t attackSeq)
{
    if (!ownerRoom) { return; }

    AttackActionPacket pkt{};
    pkt.attackerID = attackerUID;
    pkt.attackType = attackType;
    pkt.attackSeq = attackSeq;

    LOG_INFO("[Attack] BroadcastAttackAction attackerUID=%d type=%d",
        attackerUID, attackType);
    ownerRoom->BroadcastToMembers(
        PKT_S2C_ATTACK_ACTION_BRD,
        reinterpret_cast<const char*>(&pkt),
        sizeof(pkt));
}


// ------------------------------------
// ---------   Map Control   ----------
// ---------   Building Map  ----------
// ------------------------------------
void GameLogic::UpdateBuildingMap(float deltaTime)
{
    UpdateMapItemSpawner(deltaTime, EItemKind::Umbrella);

    // Advance the small debris spawn timer once the phase is active.
    if (currentMapPhase >= 1) { UpdateDebrisSpawner(deltaTime); }

    // Trigger large debris phases only once per phase gate.
    if (currentMapPhase >= 2 && !bBuildingPhase2Trigger) {
        bBuildingPhase2Trigger = true;
        TriggerBuildingPhase2();
    }

    if (currentMapPhase >= 3 && !bBuildingPhase3Trigger) {
        bBuildingPhase3Trigger = true;
        TriggerBuildingPhase3();
    }
}

void GameLogic::UpdateDebrisSpawner(float deltaTime)
{
    debrisSpawnAccumulator += deltaTime;

    if (debrisSpawnAccumulator >= nextDebrisSpawnTime) {
        debrisSpawnAccumulator = 0.f;
        SpawnDebrisByPhase();

        // Randomize the next spawn delay inside the current phase range.
        int phaseIdx = (currentMapPhase >= 1 && currentMapPhase <= 3) ? currentMapPhase - 1 : 0;

        DebrisSpawnConfig& cfg = debrisPhaseConfigs[phaseIdx];
        float range = cfg.max_Interval - cfg.min_Interval;
        nextDebrisSpawnTime = cfg.min_Interval + ((float)rand() / RAND_MAX) * range;
    }
}

void GameLogic::SpawnDebrisByPhase()
{
    int phaseIdx = (currentMapPhase >= 1 && currentMapPhase <= 3) ? currentMapPhase - 1 : 0;
    DebrisSpawnConfig& cfg = debrisPhaseConfigs[phaseIdx];

    // Spawn a random count of debris objects for the current phase.
    int count = cfg.min_Count + (rand() % (cfg.max_Count - cfg.min_Count + 1));

    for (int i = 0; i < count; ++i) {
        SpawnObjectPacket pkt;
        pkt.objectType = (int32_t)EMapEventType::SmallDebris;
        pkt.objectID = nextObjectID++;

        // Temporary spawn range until map-authored spawn points are wired in.
        pkt.x = (float)(rand() % 2000 - 1000);
        pkt.y = (float)(rand() % 2000 - 1000);
        pkt.z = 1000.f;

        ownerRoom->BroadcastToMembers(PKT_S2C_SPAWN_OBJECT_BRD, (const char*)&pkt, sizeof(pkt));
    }
}

void GameLogic::TriggerBuildingPhase2()
{
    MapEventPacket pkt;
    pkt.eventType = (int32_t)EMapEventType::LargeDebris;
    pkt.objectIndex = 2;   // represents Phase2
    pkt.eventState = 1;    // Activate

    ownerRoom->BroadcastToMembers(
        PKT_S2C_MAPEVENT_TRIGGER_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::TriggerBuildingPhase3()
{
    MapEventPacket pkt;
    pkt.eventType = (int32_t)EMapEventType::LargeDebris;
    pkt.objectIndex = 3;   // represents Phase3
    pkt.eventState = 1;    // Activate

    ownerRoom->BroadcastToMembers(
        PKT_S2C_MAPEVENT_TRIGGER_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::StartBuildingMap()
{
    // Building map: no special bootstrap is required beyond resetting phase state.
    debrisSpawnAccumulator = 0.f;
    nextDebrisSpawnTime = debrisPhaseConfigs[0].min_Interval;
    bBuildingPhase2Trigger = false;
    bBuildingPhase3Trigger = false;

    ResetMapItemSpawner();
}

// ------------------------------------
// ---------   Map Control   ----------
// ---------    Ice Cave     ----------
// ------------------------------------
void GameLogic::UpdateIceCaveMap(float deltaTime)
{
    UpdateMapItemSpawner(deltaTime, EItemKind::Torch);

    // Enter phase 2 and start periodic icicle spawning.
    if (currentMapPhase >= 2 && !bIcecavePhase2Trigger) {
        bIcecavePhase2Trigger = true;
        EnterIcePhase2();
    }

    // Enter phase 3 and add floor destruction hazards.
    if (currentMapPhase >= 3 && !bIcecavePhase3Trigger) {
        bIcecavePhase3Trigger = true;
        EnterIcePhase3();
    }

    if (roundState == ERoundState::Playing && currentMapPhase >= 1)
    {
        UpdateIceChillSpawner(deltaTime);
        UpdateIceChillZones(deltaTime);
    }

    // Torch Test 
    if (bDebugTorchThawTestEnabled)
    {
        ApplyDebugFreezeOnceForTorchTest();
        UpdateTorchThaw(deltaTime);
    }

    UpdateFrozenPlayers(deltaTime);

    // Advance the icicle spawn timer after phase 2 begins.
    if (bIcecavePhase2Trigger) {
        icicleSpawnAccumulator += deltaTime;
        if (icicleSpawnAccumulator >= icicleSpawnInterval) {
            icicleSpawnAccumulator = 0.f;
            //TriggerRandomIcicle();
        }
    }

    // Advance the floor-break timer after phase 3 begins.
    if (bIcecavePhase3Trigger) {
        floorBreakAccumulator += deltaTime;
        if (floorBreakAccumulator >= floorBreakInterval) {
            floorBreakAccumulator = 0.f;
            //TriggerRandomFloorTile();
        }
    }

    // Update timers for icicles that are currently warning players.
    for (auto& icicle : icicles) {
        if (icicle.icicleState == EIcicleState::Warning) {
            icicle.warningTimer += deltaTime;
            if (icicle.warningTimer >= icicle.warningDuration) {
                StartIcicleFalling(icicle.icicleID);
            }
        }
    }

    // Update timers for floor tiles that are already breaking.
    for (auto& tile : floorTiles) {
        if (tile.tileState == EIceFloorState::Breaking) {
            tile.breakTimer += deltaTime;
            if (tile.breakTimer >= tile.breakDelay) {
                BreakFloor(tile.tileID);
            }
        }
    }

    UpdateIceFloorStanding(deltaTime);
}

void GameLogic::StartIceMap()
{
    // Counts must match the objects placed in the client map.
    int icicleCount = 20;    // matches client's IcicleActors array size
    int tileCount = 20;      // matches client's FloorTiles array size

    icicles.resize(icicleCount);
    for (int i = 0; i < icicleCount; ++i) {
        icicles[i].icicleID = i;
        icicles[i].icicleState = EIcicleState::Idle;
    }

    floorTiles.resize(tileCount);
    for (int i = 0; i < tileCount; ++i) {
        floorTiles[i].tileID = i;
        floorTiles[i].tileState = EIceFloorState::Normal;
    }

    ResetMapItemSpawner();
}


void GameLogic::EnterIcePhase2()
{
    icicleSpawnInterval = 3.0f;  // matches client IcicleSpawnIntervalPhase2
    icicleSpawnAccumulator = 0.f;
}

void GameLogic::EnterIcePhase3()
{
    icicleSpawnInterval = 1.5f;  // matches client IcicleSpawnIntervalPhase3
    floorBreakInterval = 4.0f;   // matches client FloorBreakIntervalPhase3
    floorBreakAccumulator = 0.f;
}

void GameLogic::SetFloorCracked(int tileID)
{
    if (tileID < 0 || tileID >= (int)floorTiles.size()) { return; }
    IceFloorTileData& tile = floorTiles[tileID];
    tile.tileState = EIceFloorState::Cracked;

    MapEventPacket pkt;
    pkt.eventType = (int32_t)EMapEventType::Floor;
    pkt.objectIndex = tileID;
    pkt.eventState = 1;  // Cracked
    ownerRoom->BroadcastToMembers(PKT_S2C_MAPEVENT_TRIGGER_BRD, (const char*)&pkt, sizeof(pkt));

    // Immediately move the tile into the Breaking state.
    StartFloorBreaking(tileID);
}

void GameLogic::StartFloorBreaking(int tileID)
{
    if (tileID < 0 || tileID >= (int)floorTiles.size()) { return; }
    IceFloorTileData& tile = floorTiles[tileID];
    tile.tileState = EIceFloorState::Breaking;
    tile.breakTimer = 0.f;  // UpdateIceCaveMap advances this timer and eventually calls BreakFloor.

    MapEventPacket pkt;
    pkt.eventType = (int32_t)EMapEventType::Floor;
    pkt.objectIndex = tileID;
    pkt.eventState = 2;  // Breaking
    ownerRoom->BroadcastToMembers(PKT_S2C_MAPEVENT_TRIGGER_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::BreakFloor(int tileID)
{
    if (tileID < 0 || tileID >= (int)floorTiles.size()) { return; }
    IceFloorTileData& tile = floorTiles[tileID];
    tile.tileState = EIceFloorState::Broken;

    MapEventPacket pkt;
    pkt.eventType = (int32_t)EMapEventType::Floor;
    pkt.objectIndex = tileID;
    pkt.eventState = 3;  // Broken
    ownerRoom->BroadcastToMembers(PKT_S2C_MAPEVENT_TRIGGER_BRD, (const char*)&pkt, sizeof(pkt));
}


void GameLogic::TriggerRandomFloorTile()
{
    std::vector<int> candidates;
    for (auto& tile : floorTiles) {
        if (tile.tileState == EIceFloorState::Normal) {
            candidates.push_back(tile.tileID);
        }
    }
    if (candidates.empty()) { return; }

    int chosen = candidates[rand() % candidates.size()];
    SetFloorCracked(chosen);
}

void GameLogic::StartIcicleWarning(int icicleID)
{
    if (icicleID < 0 || icicleID >= (int)icicles.size()) { return; }
    IcicleData& ic = icicles[icicleID];
    ic.icicleState = EIcicleState::Warning;
    ic.warningTimer = 0.f;

    MapEventPacket pkt;
    pkt.eventType = (int32_t)EMapEventType::Icicle;
    pkt.objectIndex = icicleID;
    pkt.eventState = 1;  // Warning
    ownerRoom->BroadcastToMembers(PKT_S2C_MAPEVENT_TRIGGER_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::StartIcicleFalling(int icicleID)
{
    if (icicleID < 0 || icicleID >= (int)icicles.size()) { return; }
    IcicleData& ic = icicles[icicleID];
    ic.icicleState = EIcicleState::Falling;

    MapEventPacket pkt;
    pkt.eventType = (int32_t)EMapEventType::Icicle;
    pkt.objectIndex = icicleID;
    pkt.eventState = 2;  // Falling
    ownerRoom->BroadcastToMembers(PKT_S2C_MAPEVENT_TRIGGER_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::BreakIcicle(int icicleID)
{
    if (icicleID < 0 || icicleID >= (int)icicles.size()) { return; }
    IcicleData& ic = icicles[icicleID];
    ic.icicleState = EIcicleState::Broken;

    MapEventPacket pkt;
    pkt.eventType = (int32_t)EMapEventType::Icicle;
    pkt.objectIndex = icicleID;
    pkt.eventState = 3;  // Broken
    ownerRoom->BroadcastToMembers(PKT_S2C_MAPEVENT_TRIGGER_BRD, (const char*)&pkt, sizeof(pkt));
}

void GameLogic::TriggerRandomIcicle()
{
    // Only idle icicles are eligible for a new warning cycle.
    std::vector<int> candidates;
    for (auto& ic : icicles) {
        if (ic.icicleState == EIcicleState::Idle) {
            candidates.push_back(ic.icicleID);
        }
    }
    if (candidates.empty()) { return; }

    int chosen = candidates[rand() % candidates.size()];
    StartIcicleWarning(chosen);
}

void GameLogic::UpdateIceChillSpawner(float deltaTime)
{
    iceChillSpawnAccumulator += deltaTime;

    if (iceChillSpawnAccumulator < iceChillNextSpawnTime)
    {
        return;
    }

    iceChillSpawnAccumulator = 0.f;
    SpawnIceChillZones();

    const float minInterval = currentMapPhase >= 3 ? phase3ChillMinSpawnInterval : phase2ChillMinSpawnInterval;
    const float maxInterval = currentMapPhase >= 3 ? phase3ChillMaxSpawnInterval : phase2ChillMaxSpawnInterval;

    iceChillNextSpawnTime = minInterval + static_cast<float>(rand()) / RAND_MAX * (maxInterval - minInterval);
}

void GameLogic::UpdateIceChillZones(float deltaTime)
{
    for (auto zoneIt = iceChillZones.begin(); zoneIt != iceChillZones.end(); )
    {
        IceChillZoneData& zone = *zoneIt;

        zone.lifeRemainTime -= deltaTime;
        if (zone.lifeRemainTime <= 0.f)
        {
            DespawnIceChillZone(zone.zoneID);
            zoneIt = iceChillZones.erase(zoneIt);
            continue;
        }

        for (const auto& pair : players)
        {
            Session* player = pair.second;
            if (!player) { continue; }

            GameData& gd = player->gameDatas;
            if (!gd.isConnected || gd.characterState != 0) { continue; }

            const float dx = gd.x - zone.x;
            const float dy = gd.y - zone.y;
            const float dist = GameMath::Length2D(dx, dy);

            const bool bInside = dist <= zone.radius;
            if (!bInside)
            {
                zone.stayTimesBySessionID.erase(player->sessionID);
                zone.triggeredSessionIDs.erase(player->sessionID);
                continue;
            }

            if (zone.triggeredSessionIDs.find(player->sessionID) != zone.triggeredSessionIDs.end())
            {
                continue;
            }

            float& stayTime = zone.stayTimesBySessionID[player->sessionID];
            stayTime += deltaTime;

            LOG_INFO("[IceChill] Inside zoneID=%d session=%d uid=%d dist=%.1f stay=%.2f/%.2f player=(%.1f, %.1f) zone=(%.1f, %.1f)",
                zone.zoneID,
                player->sessionID,
                player->playerUID,
                dist,
                stayTime,
                zone.freezeBuildUpTime,
                gd.x,
                gd.y,
                zone.x,
                zone.y);

            if (stayTime >= zone.freezeBuildUpTime)
            {
                ApplyFreezeToPlayer(player->sessionID, zone.freezeDuration);
                zone.stayTimesBySessionID.erase(player->sessionID);
                zone.triggeredSessionIDs.insert(player->sessionID);
            }
        }

        ++zoneIt;
    }
}

void GameLogic::SpawnIceChillZones()
{
    const int spawnCount = currentMapPhase >= 3 ? 2 : 1;

    for (int i = 0; i < spawnCount; ++i)
    {
        SpawnIceChillZone();
    }
}

void GameLogic::SpawnIceChillZone()
{
    IceChillZoneData zone{};
    zone.zoneID = nextIceChillZoneID++;

    zone.x = MapMinX + static_cast<float>(rand()) / RAND_MAX * (MapMaxX - MapMinX);
    zone.y = MapMinY + static_cast<float>(rand()) / RAND_MAX * (MapMaxY - MapMinY);
    zone.z = FixedGroundZ;

    iceChillZones.push_back(zone);

    if (!ownerRoom)
    {
        return;
    }

    LOG_INFO("[IceChill] Spawn zoneID=%d pos=(%.1f, %.1f, %.1f) radius=%.1f build=%.1f duration=%.1f",
        zone.zoneID, zone.x, zone.y, zone.z,
        zone.radius, zone.freezeBuildUpTime, zone.freezeDuration);

    // Broadcast Object Spawn
    SpawnObjectPacket pkt{};
    pkt.objectType = static_cast<int32_t>(EMapEventType::IceChillZone);
    pkt.objectID = zone.zoneID;
    pkt.x = zone.x;
    pkt.y = zone.y;
    pkt.z = zone.z;

    ownerRoom->BroadcastToMembers(
        PKT_S2C_SPAWN_OBJECT_BRD,
        reinterpret_cast<const char*>(&pkt),
        sizeof(pkt)
    );
}

void GameLogic::DespawnIceChillZone(int zoneID)
{
    if (!ownerRoom)
    {
        return;
    }

    MapEventPacket pkt{};
    pkt.eventType = static_cast<int32_t>(EMapEventType::IceChillZone);
    pkt.objectIndex = zoneID;
    pkt.eventState = 0; // 0 = Despawn

    ownerRoom->BroadcastToMembers(
        PKT_S2C_MAPEVENT_TRIGGER_BRD,
        reinterpret_cast<const char*>(&pkt),
        sizeof(pkt)
    );
}

void GameLogic::ApplyFreezeToPlayer(int sessionID, float duration)
{
    auto it = players.find(sessionID);
    if (it == players.end() || !it->second) { return; }

    Session* target = it->second;
    GameData& gd = target->gameDatas;

    if (!gd.isConnected || gd.characterState != 0) { return; }
    if (target->bFrozen) { return; }

    LOG_INFO("[Freeze] Apply session=%d uid=%d duration=%.2f",
        sessionID, target->playerUID, duration);

    target->bFrozen = true;
    target->FreezeRemainTime = duration;
    target->HorizontalVelocityX = 0.f;
    target->HorizontalVelocityY = 0.f;
    gd.animationNum = 0;

    BroadcastFreezeState(target->playerUID, true, duration);
}

void GameLogic::EndFreezeOnPlayer(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end() || !it->second) { return; }

    Session* target = it->second;
    if (!target->bFrozen) { return; }

    LOG_INFO("[Freeze] End session=%d uid=%d",
        sessionID, target->playerUID);

    target->bFrozen = false;
    target->FreezeRemainTime = 0.f;

    BroadcastFreezeState(target->playerUID, false, 0.f);
}

void GameLogic::UpdateFrozenPlayers(float deltaTime)
{
    for (auto& pair : players)
    {
        Session* player = pair.second;
        if (!player || !player->bFrozen) { continue; }

        player->FreezeRemainTime -= deltaTime;

        if (player->FreezeRemainTime <= 0.f)
        {
            EndFreezeOnPlayer(player->sessionID);
        }
    }
}

void GameLogic::BroadcastFreezeState(int targetUID, bool bFrozen, float duration)
{
    StatusEffectPacket pkt{};
    pkt.targetID = targetUID;
    pkt.effectType = 0; // Freeze
    pkt.active = bFrozen ? 1 : 0;
    pkt.duration = duration;

    ownerRoom->BroadcastToMembers(
        PKT_S2C_STATUS_EFFECT_BRD,
        (const char*)&pkt,
        sizeof(pkt)
    );
}

static long long MakeTorchThawPairKey(int torchSessionID, int targetSessionID)
{
    return (static_cast<long long>(torchSessionID) << 32) |
        static_cast<unsigned int>(targetSessionID);
}

void GameLogic::ApplyDebugFreezeOnceForTorchTest()
{
    if (bDebugFreezeAppliedForTorchTest)
    {
        return;
    }

    for (auto& pair : players)
    {
        Session* player = pair.second;
        if (!player)
        {
            continue;
        }

        GameData& gd = player->gameDatas;
        if (!gd.isConnected || gd.characterState != Alive)
        {
            continue;
        }

        //ApplyFreezeToPlayer(player->sessionID, 30.f);
        bDebugFreezeAppliedForTorchTest = true;

        LOG_INFO("[TorchThawTest] Debug freeze target session=%d uid=%d",
            player->sessionID,
            player->playerUID);

        return;
    }
}

bool GameLogic::IsTorchEquipped(Session* player) const
{
    if (!bDebugTorchThawTestEnabled)
    {
        return false;
    }

    if (!player)
    {
        return false;
    }

    const GameData& gd = player->gameDatas;
    // Test Code :: All player has Torch
    //return gd.isConnected && gd.characterState == Alive && !player->bFrozen;

    if (!gd.isConnected || gd.characterState != Alive || player->bFrozen)
    {
        return false;
    }

    if (gd.equippedItemID < 0)
    {
        return false;
    }

    ItemData* item = ownerRoom->GetItemData(gd.equippedItemID);
    if (!item)
    {
        return false;
    }

    return item->bEquipped &&
        item->ownerUID == player->playerUID &&
        item->ObjectType == e_ObjectType::WEAPON_ITEM &&
        item->ItemKind == EItemKind::Torch;
}

bool GameLogic::IsInTorchThawRange(Session* torchOwner, Session* frozenTarget) const
{
    if (!torchOwner || !frozenTarget)
    {
        return false;
    }

    const GameData& ownerData = torchOwner->gameDatas;
    const GameData& targetData = frozenTarget->gameDatas;

    const float dx = targetData.x - ownerData.x;
    const float dy = targetData.y - ownerData.y;
    const float distance = GameMath::Length2D(dx, dy);

    return distance <= TorchThawRadius;
}

void GameLogic::UpdateTorchThaw(float deltaTime)
{
    if (deltaTime <= 0.f)
    {
        return;
    }

    std::unordered_set<long long> activePairs;

    for (const auto& ownerPair : players)
    {
        Session* torchOwner = ownerPair.second;
        // Torch Test for end Freezen state
        if (!IsTorchEquipped(torchOwner))
        {
            continue;
        }

        for (const auto& targetPair : players)
        {
            Session* target = targetPair.second;
            if (!target || target == torchOwner)
            {
                continue;
            }

            const GameData& targetData = target->gameDatas;
            if (!targetData.isConnected || targetData.characterState != Alive || !target->bFrozen)
            {
                continue;
            }

            if (!IsInTorchThawRange(torchOwner, target))
            {
                continue;
            }

            const long long key = MakeTorchThawPairKey(torchOwner->sessionID, target->sessionID);
            activePairs.insert(key);

            float& progress = torchThawProgressByPair[key];
            progress += deltaTime;

            LOG_INFO("[TorchThaw] owner=%d target=%d progress=%.2f/%.2f",
                torchOwner->playerUID,
                target->playerUID,
                progress,
                TorchThawRequiredTime);

            if (progress >= TorchThawRequiredTime)
            {
                EndFreezeOnPlayer(target->sessionID);
                torchThawProgressByPair.erase(key);
            }
        }
    }

    for (auto it = torchThawProgressByPair.begin(); it != torchThawProgressByPair.end(); )
    {
        if (activePairs.find(it->first) == activePairs.end())
        {
            it = torchThawProgressByPair.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameLogic::HandleIceFloorStanding(int sessionID, int floorID, int pieceIndex)
{
    if (roundState != ERoundState::Playing)
    {
        return;
    }

    if (sessionID < 0)
    {
        return;
    }

    auto PlayerIt = players.find(sessionID);
    if (PlayerIt == players.end() || PlayerIt->second == nullptr)
    {
        return;
    }

    Session* Player = PlayerIt->second;
    
    {
        std::lock_guard<std::mutex> moveLock(Player->MoveIntentLock);
        Player->bOnIce = true;
        Player->IceContactRemainTime = 0.20f;
    }

    if (currentMapPhase < 2)
    {
        return;
    }

    const int tileID = pieceIndex;

    std::lock_guard<std::mutex> lock(iceFloorMutex);

    if (tileID < 0 || tileID >= static_cast<int>(floorTiles.size()))
    {
        return;
    }

    if (Player->gameDatas.characterState == 1) // 0=Alive, 1=Dead
    {
        return;
    }

    IceFloorTileData& tile = floorTiles[tileID];

    if (tile.tileState == EIceFloorState::Broken ||
        tile.tileState == EIceFloorState::Breaking)
    {
        return;
    }

    tile.standingSessionIDs.insert(sessionID);
}

void GameLogic::UpdateIceFloorStanding(float deltaTime)
{
    if (deltaTime <= 0.f)
    {
        return;
    }

    if (roundState != ERoundState::Playing || currentMapPhase < 2)
    {
        return;
    }

    const float standingBreakTime =
        (currentMapPhase >= 3) ? 9.f : 18.f;

    if (standingBreakTime <= 0.f)
    {
        return;
    }

    std::vector<std::pair<int, int>> pendingEvents;

    {
        std::lock_guard<std::mutex> lock(iceFloorMutex);

        for (IceFloorTileData& tile : floorTiles)
        {
            if (tile.tileState == EIceFloorState::Broken ||
                tile.tileState == EIceFloorState::Breaking)
            {
                tile.standingSessionIDs.clear();
                continue;
            }

            const int standingCount = static_cast<int>(tile.standingSessionIDs.size());
            if (standingCount <= 0)
            {
                continue;
            }

            tile.standingProgress += (deltaTime / standingBreakTime) * standingCount;

            if (!tile.bCrackBroadcastedByStanding && tile.standingProgress >= 0.6f)
            {
                tile.bCrackBroadcastedByStanding = true;
                tile.tileState = EIceFloorState::Cracked;
                pendingEvents.push_back({ tile.tileID, 1 }); // Cracked
            }

            if (tile.standingProgress >= 1.f)
            {
                tile.tileState = EIceFloorState::Broken;
                pendingEvents.push_back({ tile.tileID, 3 }); // Broken
            }

            tile.standingSessionIDs.clear();
        }
    }

    for (const auto& Event : pendingEvents)
    {
        BroadcastFloorEvent(Event.first, Event.second);
    }
}

void GameLogic::BroadcastFloorEvent(int pieceIndex, int eventState)
{
    if (!ownerRoom)
    {
        return;
    }

    MapEventPacket pkt{};
    pkt.eventType = static_cast<int32_t>(EMapEventType::Floor);
    pkt.objectIndex = pieceIndex;
    pkt.eventState = eventState;

    ownerRoom->BroadcastToMembers(
        PKT_S2C_MAPEVENT_TRIGGER_BRD,
        reinterpret_cast<const char*>(&pkt),
        sizeof(pkt)
    );
}


// ------------------------------------
// ---------   Map Control   ----------
// ---------  Space Station  ----------
// ------------------------------------
void GameLogic::UpdateSpaceStation(float deltaTime)
{
    UpdateMapItemSpawner(deltaTime, EItemKind::Grenade);

    if (currentMapPhase >= 2 && !bSpaceStationPhase2Trigger)
    {
        bSpaceStationPhase2Trigger = true;
        EnterSpaceStationPhase2();
    }

    if (currentMapPhase >= 3 && !bSpaceStationPhase3Trigger)
    {
        bSpaceStationPhase3Trigger = true;
        EnterSpaceStationPhase3();
    }

    if (currentMapPhase == 2 || currentMapPhase == 3)
    {
        ApplyBlackHolePull(deltaTime);
    }
}

void GameLogic::StartSpaceStation()
{
    bSpaceStationPhase2Trigger = false;
    bSpaceStationPhase3Trigger = false;
    SpaceBlackHoles.clear();

    ResetMapItemSpawner();
}

void GameLogic::EnterSpaceStationPhase2()
{
    AddSpaceBlackHole(1, Outside1_BlackHoleCenter);

    LOG_INFO("[SpaceStation] Enter Phase2 - BlackHole Pull Start");
}

void GameLogic::EnterSpaceStationPhase3()
{
    AddSpaceBlackHole(2, Outside2_BlackHoleCenter);
    AddSpaceBlackHole(3, Outside3_BlackHoleCenter);

    LOG_INFO("[SpaceStation] Enter Phase3 - Add BlackHole 2, 3");
}

void GameLogic::ApplyBlackHolePull(float deltaTime)
{
    for (auto& Pair : players)
    {
        Session* player = Pair.second;
        if (!player) { continue; }

        GameData& gd = player->gameDatas;

        if (!gd.isConnected) { continue; }
        if (gd.characterState != Alive) { continue; }

        for (const SpaceBlackHoleData& blackHole : SpaceBlackHoles)
        {
            if (!blackHole.bActive)
            {
                continue;
            }

            float toX = blackHole.center.x - gd.x;
            float toY = blackHole.center.y - gd.y;

            const float distance = GameMath::Length2D(toX, toY);

            if (distance > blackHole.pullRadius || distance < blackHole.minDistance)
            {
                continue;
            }

            GameMath::Normalize2D(toX, toY);

            const float distanceAlpha =
                1.0f - (std::min)(distance / blackHole.pullRadius, 1.0f);

            float basePullStrength = blackHole.pullStrength;

            if (currentMapPhase == 3 && distance <= 1000.0f)
            {
                basePullStrength = 3000.0f;
            }

            const float strengthAlpha = (std::max)(distanceAlpha, 0.25f);
            const float finalStrength = basePullStrength * strengthAlpha;

            float pullDistance = finalStrength * deltaTime;
            pullDistance = (std::min)(pullDistance, blackHole.maxPullSpeed * deltaTime);

            Vector3 currentPos{ gd.x, gd.y, gd.z };
            Vector3 desiredPos{
                gd.x + toX * pullDistance,
                gd.y + toY * pullDistance,
                gd.z
            };

            const float collisionRadius = GetCollisionRadius(gd.roleType);
            const Vector3 resolvedPos =
                ResolveMovementWithCollision(currentPos, desiredPos, collisionRadius);

            gd.x = resolvedPos.x;
            gd.y = resolvedPos.y;
            gd.z = resolvedPos.z;
        }
    }
}

void GameLogic::AddSpaceBlackHole(int objectID, const Vector3& center)
{
    SpaceBlackHoleData blackHole{};
    blackHole.objectID = objectID;
    blackHole.center = center;
    blackHole.pullRadius = SpaceBlackHolePullRadius;
    blackHole.minDistance = SpaceBlackHoleMinDistance;
    blackHole.pullStrength = SpaceBlackHolePullStrength;
    blackHole.maxPullSpeed = SpaceBlackHoleMaxPullSpeed;
    blackHole.bActive = true;

    SpaceBlackHoles.push_back(blackHole);

    BroadcastSpaceBlackHoleSpawn(blackHole);
}

void GameLogic::BroadcastSpaceBlackHoleSpawn(const SpaceBlackHoleData& blackHole)
{
    if (!ownerRoom) { return; }

    SpawnObjectPacket pkt{};
    pkt.objectType = static_cast<int32_t>(EMapEventType::BlackHole);
    pkt.objectID = blackHole.objectID;
    pkt.x = blackHole.center.x;
    pkt.y = blackHole.center.y;
    pkt.z = blackHole.center.z;

    ownerRoom->BroadcastToMembers(
        PKT_S2C_SPAWN_OBJECT_BRD,
        reinterpret_cast<const char*>(&pkt),
        sizeof(pkt)
    );
}


// ------------------------------------
// ---------   Map Control   ----------
// -------  Common Map Logics  --------
// ------------------------------------
static float RandomFloat(float minValue, float maxValue)
{
    static thread_local std::mt19937 gen{ std::random_device{}() };
    std::uniform_real_distribution<float> dist(minValue, maxValue);
    return dist(gen);
}

static int RandomInt(int minValue, int maxValue)
{
    static thread_local std::mt19937 gen{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(minValue, maxValue);
    return dist(gen);
}

void GameLogic::ResetMapItemSpawner()
{
    bPhase1ItemsSpawned = false;
    bPhase2ItemsScheduled = false;
    pendingItemSpawns.clear();
}

void GameLogic::UpdateMapItemSpawner(float deltaTime, EItemKind phase2SpecialItem)
{
    if (currentMapPhase >= 1 && !bPhase1ItemsSpawned)
    {
        bPhase1ItemsSpawned = true;
        SpawnPhase1BasicItems();
    }

    if (currentMapPhase >= 2 && !bPhase2ItemsScheduled)
    {
        bPhase2ItemsScheduled = true;
        SchedulePhase2Items(phase2SpecialItem);
    }

    UpdatePendingItemSpawns(deltaTime);
}

void GameLogic::SpawnPhase1BasicItems()
{
    for (int i = 0; i < 6; ++i)
    {
        SpawnMapItem(PickRandomBasicItemKind());
    }
}

void GameLogic::SchedulePhase2Items(EItemKind specialItem)
{
    for (int i = 0; i < 3; ++i)
    {
        PendingItemSpawn spawn{};
        spawn.ItemKind = specialItem;
        spawn.RemainTime = RandomFloat(0.0f, 25.0f);
        pendingItemSpawns.push_back(spawn);
    }

    for (int i = 0; i < 3; ++i)
    {
        PendingItemSpawn spawn{};
        spawn.ItemKind = PickRandomBasicItemKind();
        spawn.RemainTime = RandomFloat(0.0f, 25.0f);
        pendingItemSpawns.push_back(spawn);
    }
}

void GameLogic::UpdatePendingItemSpawns(float deltaTime)
{
    for (auto it = pendingItemSpawns.begin(); it != pendingItemSpawns.end(); )
    {
        it->RemainTime -= deltaTime;

        if (it->RemainTime <= 0.0f)
        {
            SpawnMapItem(it->ItemKind);
            it = pendingItemSpawns.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void GameLogic::SpawnMapItem(EItemKind itemKind)
{
    if (!ownerRoom) { return; }

    ItemSpawnRange range{};
    range.ObjectID = nextItemObjectID++;
    range.ItemKind = itemKind;
    range.MinX = MapMinX;
    range.MaxX = MapMaxX;
    range.MinY = MapMinY;
    range.MaxY = MapMaxY;
    range.Z = 2500.0f;

    ItemData item = ownerRoom->SpawnRandomItem(range);

    ItemPacket pkt{};
    pkt.itemID = item.ObjectID;
    pkt.itemKind = static_cast<int32_t>(item.ItemKind);
    pkt.ownerUID = -1;
    pkt.bEquipped = 0;
    pkt.x = item.x;
    pkt.y = item.y;
    pkt.z = item.z;

    ownerRoom->BroadcastToMembers(
        PKT_S2C_SPAWN_ITEM_BRD,
        reinterpret_cast<const char*>(&pkt),
        sizeof(pkt)
    );

    LOG_INFO("[ItemSpawn] id=%d kind=%d pos=(%.1f, %.1f, %.1f)",
        pkt.itemID,
        pkt.itemKind,
        pkt.x,
        pkt.y,
        pkt.z);
}

EItemKind GameLogic::PickRandomBasicItemKind()
{
    static const EItemKind basicItems[] =
    {
        EItemKind::Sword,
        EItemKind::Spear,
        EItemKind::Hammer
    };

    return basicItems[RandomInt(0, 2)];
}
