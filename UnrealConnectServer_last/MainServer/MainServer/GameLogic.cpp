#include "GameLogic.h"

#include "RoomManager.h"
#include "session.h"

GameLogic::GameLogic() { ownerRoom = nullptr; }

GameLogic::~GameLogic() { }

void GameLogic::Update(float deltaTime)
{
    if (roundState != ERoundState::Playing) { return; }

    elapsedTime += deltaTime;

    // Advance the shared one-second round timer.
    timeAccumlator += deltaTime;
    while (timeAccumlator >= 1.f) {
        timeAccumlator -= 1.f;
        CountdownTick();
    }

    // Update map-specific hazard logic.
    if (mapType == 1) { UpdateBuildingMap(deltaTime); }
    else if (mapType == 2) { UpdateIceCaveMap(deltaTime); }
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
    gameTime = phase1Time + phase2Time + phase3Time + 50;
    currentGameTime = 0;
    currentMapPhase = 0;

    // Initialize map gimmicks
    if (mapType == 1) {
        LOG_INFO("Building Map Select");
        // Building map: no special bootstrap is required beyond resetting phase state.
        debrisSpawnAccumulator = 0.f;
        nextDebrisSpawnTime = debrisPhaseConfigs[0].min_Interval;
        bBuildingPhase2Trigger = false;
        bBuildingPhase3Trigger = false;
    }
    else if (mapType == 2) {
        LOG_INFO("IceCave Map Select");
        StartIceMap();
    }
    else {
        LOG_ERROR("InValid Map Select");
        return;
    }

    PhaseChangePacket pkt;
    pkt.roundState = 1;
    pkt.mapPhase = 0;
    pkt.gameTime = (float)currentGameTime;

    ownerRoom->BroadcastToMembers(PKT_S2C_GAME_PHASE_CHANGE_BRD, (char*)&pkt, sizeof(pkt));
}

void GameLogic::EndGameRound()
{
    roundState = ERoundState::Finished;

    PhaseChangePacket pkt;
    pkt.roundState = 2;
    pkt.mapPhase = currentMapPhase;
    pkt.gameTime = 0.f;

    ownerRoom->BroadcastToMembers(PKT_S2C_GAME_PHASE_CHANGE_BRD, (char*)&pkt, sizeof(pkt));
}

void GameLogic::CountdownTick()
{
    if (roundState != ERoundState::Playing) { return; }
    else {
        currentGameTime--;

        BroadcastGameTime((float)currentGameTime);

        int elapsed = gameTime - currentGameTime;

        if (elapsed >= phase1Time && currentMapPhase == 0) {
            currentMapPhase = 1;
            HandlePhaseChanged(1);
        }
        else if (elapsed >= phase1Time + phase2Time && currentMapPhase == 1) {
            currentMapPhase = 2;
            HandlePhaseChanged(2);
        }
        else if (elapsed >= phase1Time + phase2Time + phase3Time && currentMapPhase == 2) {
            currentMapPhase = 3;
            HandlePhaseChanged(3);
        }

        if (currentGameTime <= 0) { EndGameRound(); }
    }
}

void GameLogic::HandlePhaseChanged(int newPhase)
{
    PhaseChangePacket pkt;
    pkt.roundState = 1;  // Playing
    pkt.mapPhase = newPhase;
    pkt.gameTime = (float)currentGameTime;

    ownerRoom->BroadcastToMembers(PKT_S2C_GAME_PHASE_CHANGE_BRD, (const char*)&pkt, sizeof(pkt));
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



void GameLogic::ApplyDamage(int sessionID, int damageAmount)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;
    if (damageAmount <= 0 || gd.characterState == 1) { return; } // non-positive damage or already dead

    SetCurrentHP(sessionID, gd.currentHP - damageAmount);

    // Broadcast the damage result to all clients in the room.
    // PKT_S2C_DAMAGE_APPLY_BRD: target session, damage, remaining HP
    BroadcastDamageApply(sessionID, damageAmount, gd.currentHP);
}

void GameLogic::Heal(int sessionID, int healAmount)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;
    if (healAmount <= 0) { return; }

    SetCurrentHP(sessionID, gd.currentHP + healAmount);

    // PKT_S2C_STATUS_UPDATE_BRD: target session and updated HP
    BroadcastStatusUpdate(sessionID, gd.currentHP);
}

void GameLogic::ResetHP(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;

    if (gd.characterState == 1) {  // Dead
        gd.currentHP = gd.maxHP;
        SetCharacterState(sessionID, 0);  // Alive
        HandleRespawn(sessionID);
    }
    else {
        SetCurrentHP(sessionID, gd.maxHP);
    }

    BroadcastStatusUpdate(sessionID, gd.currentHP);
}

void GameLogic::SetCurrentHP(int sessionID, int newHP)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;
    // Clamp the value to the valid HP range.
    if (newHP < 0) { newHP = 0; }
    if (newHP > gd.maxHP) { newHP = gd.maxHP; }
    gd.currentHP = newHP;

    // If HP reaches zero while the player is alive, trigger death handling.
    if (gd.characterState == 0 && gd.currentHP <= 0) {
        HandleDeath(sessionID);
    }
}

void GameLogic::SetCharacterState(int sessionID, int newState)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;
    if (gd.characterState == newState) { return; }

    gd.characterState = newState;

    // PKT_S2C_STATE_CHANGE_BRD: target session and new life state
    BroadcastStateChange(sessionID, newState);
}

void GameLogic::HandleDeath(int sessionID)
{
    SetCharacterState(sessionID, 1);  // Dead
}

void GameLogic::HandleRespawn(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;
    if (gd.characterState != 1) { return; } // ignore if not currently dead

    // Restore HP before sending the respawn update.
    gd.currentHP = gd.maxHP;

    // Mark the player as alive again.
    gd.characterState = 0;

    // Resolve a server-authoritative respawn position.
    // This will eventually use map-specific predefined spawn locations.
    // It currently falls back to the room-provided spawn helper.
    Vector3 spawnPoint = ownerRoom->GetRespwanLocation();
    gd.x = spawnPoint.x;
    gd.y = spawnPoint.y;
    gd.z = spawnPoint.z;

    // PKT_S2C_RESPAWN_BRD: target session, position, and HP
    BroadcastRespawn(sessionID, gd.x, gd.y, gd.z, gd.currentHP);
}

void GameLogic::SetRole(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;
    if (gd.characterState == 1) { return; }  // cannot change while Dead

    ApplyRoleStats(sessionID);

    BroadcastRoleChange(sessionID, gd.roleType);
}

void GameLogic::ApplyRoleStats(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    GameData& gd = it->second->gameDatas;
    gd.baseWalkSpeed = 500.f * GetRoleSpeedMultiplier(gd.roleType);

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

void GameLogic::HandleAttackInput(int sessionID)
{
    auto it = players.find(sessionID);
    if (it == players.end()) { return; }

    Session* attackerSession = it->second;
    if (!attackerSession) { return; }

    GameData& gd = attackerSession->gameDatas;

    // 연결 안 된 플레이어면 무시
    if (!gd.isConnected) { return; }

    // 죽은 상태면 공격 금지
    if (gd.characterState != 0) { return; }

    // 로그인 UID가 아직 없으면 무시
    if (attackerSession->playerUID <= 0) { return; }

    // 1차는 기본 공격만 보냄
    const int attackType = 0;

    BroadcastAttackAction(attackerSession->playerUID, attackType);
    LOG_INFO("[Attack] HandleAttackInput session=%d uid=%d room ok",
        sessionID, gd.userUID);

    // 2차에서 여기에 PendingAttack 등록
    // pendingAttacks.push_back({ sessionID, attackType, AttackWindupSec });
}

void GameLogic::BroadcastAttackAction(int attackerUID, int attackType)
{
    if (!ownerRoom) { return; }

    AttackActionPacket pkt{};
    pkt.attackerID = attackerUID;
    pkt.attackType = attackType;

    LOG_INFO("[Attack] BroadcastAttackAction attackerUID=%d type=%d",
        attackerUID, attackType);
    ownerRoom->BroadcastToMembers(
        PKT_S2C_ATTACK_ACTION_BRD,
        reinterpret_cast<const char*>(&pkt),
        sizeof(pkt));
}

void GameLogic::UpdateBuildingMap(float deltaTime)
{
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

void GameLogic::StartIceMap()
{
    // Counts must match the objects placed in the client map.
    int icicleCount = 20;    // matches client's IcicleActors array size
    int tileCount = 30;      // matches client's FloorTiles array size

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
}

void GameLogic::UpdateIceCaveMap(float deltaTime)
{
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

    // Advance the icicle spawn timer after phase 2 begins.
    if (bIcecavePhase2Trigger) {
        icicleSpawnAccumulator += deltaTime;
        if (icicleSpawnAccumulator >= icicleSpawnInterval) {
            icicleSpawnAccumulator = 0.f;
            TriggerRandomIcicle();
        }
    }

    // Advance the floor-break timer after phase 3 begins.
    if (bIcecavePhase3Trigger) {
        floorBreakAccumulator += deltaTime;
        if (floorBreakAccumulator >= floorBreakInterval) {
            floorBreakAccumulator = 0.f;
            TriggerRandomFloorTile();
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

