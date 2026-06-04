#pragma once

#include <map>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <mutex>
#include <cstdint>

class Room;
struct Session;
struct AttackHitReportPacket;
struct RoundChangePacket;
struct GrenadeBlackHolePacket;
struct GameData;

enum ERecCharacterState { Alive, Dead };
enum ERecRoleType { Striker, Guardian, Manipulator };
enum ERoundState { Waiting, Playing, Finished };
enum EMatchFlow { Robby, MapSelecting, MapSelectedWait, RoundPlaying, RoundFinish, MatchFinish };
enum class EDamageType : int32_t;

namespace GameMath {
	constexpr float PI = 3.141592f;

	inline float DegreesToRadians(float degrees)
	{
		return degrees * (PI / 180.0f);
	}

	inline float Length2D(float x, float y)
	{
		return std::sqrt(x * x + y * y);
	}

	inline void Normalize2D(float& x, float& y)
	{
		const float len = Length2D(x, y);
		if (len > 0.0001f)
		{
			x /= len;
			y /= len;
		}
	}
}


//struct PlayerData {
//	int maxHP = 100;			// 100 = Striker, 200 = Guardian, 120 = Manipulator
//	int currentHP = 100;
//	int characterState = 0;		// 0 = Alive, 1 = Dead
//	
//	int roleType = 0;			// 0 = Striker, 1 = Guardian, 2 = Manipulator
//	float baseWalkSpeed = 500.f;
//	int equippedItemID = -1;
//	
//	float x = 0, y = 0, z = 0;
//	float rotate = 0;
//};


enum class EItemKind {
	None = 0,
	Sword = 1,
	Spear = 2,
	Hammer = 3,
	Umbrella = 4,
	Torch = 5,
	Grenade = 6,
};

enum class e_ObjectType {
	WEAPON_ITEM = 1,
	DESTROYALBE_OBJECT = 2,
	MAP_INTERACT_OBJ = 3,
};

struct ObjectData {
	int ObjectID;
	e_ObjectType ObjectType;
	float x, y, z;
};

struct ItemData {
	int ObjectID;
	e_ObjectType ObjectType;
	EItemKind ItemKind = EItemKind::None;
	float x, y, z;

	int ownerUID = -1;
	bool bEquipped = false;
};

struct ItemSpawnRange
{
	int ObjectID;
	EItemKind ItemKind;
	float MinX;
	float MaxX;
	float MinY;
	float MaxY;
	float Z;
};



class ObjectManager {
public:
	ObjectManager();

private:
	void Collision_Check();
	void Damage_Calculation();
	
	// Placeholder for future client-side collision and damage logic porting.
	
private:
	ObjectData Data;
};


enum class EIcicleState { Idle, Warning, Falling, Broken };
enum class EIceFloorState { Normal, Cracked, Breaking, Broken };
enum class EMapEventType { 
	Icicle = 0, 
	Floor = 1, 
	SmallDebris = 2, 
	LargeDebris = 3,
	IceChillZone = 4,
	BlackHole = 5
};

struct IcicleData {
	int icicleID = -1;
	EIcicleState icicleState = EIcicleState::Idle;

	float warningTimer = 0.f;
	float warningDuration = 0.8f;
	float damage = 20.f;
};

struct IceFloorTileData {
	int tileID = -1;
	EIceFloorState tileState = EIceFloorState::Normal;

	float breakTimer = 0.f;
	float breakDelay = 1.5f;

	float standingProgress = 0.f;
	bool bCrackBroadcastedByStanding = false;
	std::unordered_set<int> standingSessionIDs;
};

struct IceChillZoneData {
	int zoneID = -1;
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float radius = 1500.f;
	float lifeRemainTime = 10.f;
	float freezeBuildUpTime = 0.5f;
	float freezeDuration = 3.f;

	std::unordered_map<int, float> stayTimesBySessionID;
	std::unordered_set<int> triggeredSessionIDs;
};

struct JunglePoisonFogData {
	bool bActive = false;

	float x = 0.f;
	float y = 0.f;
	float z = 500.f;
	float radius = 3000.f;

	float activationDelay = 20.0f;
	float activationTimer = 0.0f;

	float damageInterval = 1.0f;
	float damageAccumulator = 0.0f;
	int damageAmount = 10;
};

struct DebrisSpawnConfig {
	float min_Interval, max_Interval;
	int min_Count, max_Count;
};

struct Vector3 { float x = 0.f, y = 0.f, z = 0.f; };

struct SpaceBlackHoleData
{
	int objectID;
	Vector3 center;
	float pullRadius;
	float minDistance;
	float pullStrength;
	float maxPullSpeed;
	bool bActive;
	float lifeRemainTime = -1.0f;
};


struct CollisionBox {
	float MinX = 0.f, MinY = 0.f, MaxX = 0.f, MaxY = 0.f;
};

class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	Room* ownerRoom;
	std::map<int, Session*> players;


public:
	// ------------------------------------
	// ---------   Round State   ----------
	// ------------------------------------
	void SetMapType(int type) { mapType = type; }

	// Advances the current round timer and updates map-specific hazards.
	void Update(float deltaTime);
	// Resets state for the pre-round ready phase.
	void StartGameReady();
	// Starts the live round and initializes the selected map logic.
	void StartGameRound();
	// Ends the active round and broadcasts the final state.
	void EndGameRound();

	// Broadcasts the authoritative remaining game time.
	void BroadcastGameTime(float currentTime);
	// Broadcasts damage and remaining HP for a target.
	void BroadcastDamageApply(int targetID, int damage, int remainHP, EDamageType damageType);
	// Broadcasts a status-only update such as HP recovery.
	void BroadcastStatusUpdate(int targetID, int currentHP);
	// Broadcasts a life-state change such as Alive or Dead.
	void BroadcastStateChange(int targetID, int newState);
	// Broadcasts respawn position and HP for the target.
	void BroadcastRespawn(int targetID, float x, float y, float z, int hp);
	// Broadcasts a role change to every room member.
	void BroadcastRoleChange(int targetID, int newRoleType); 

	void BroadcastRoundResult(const RoundChangePacket& packet);

	void CountdownTick();                                  // Advances the server-side one-second round timer.
	void HandlePhaseChanged(int newPhase);                 // Triggers and broadcasts a map phase transition.
	int CalculateWinnerTeam();

private:
	int roundState = 0;            // 0=Waiting, 1=Playing, 2=Finished
	int readyTime = 10;
	int gameTime = 180;
	int currentReadyTime = 0;
	int currentGameTime = 0;
	

	// ------------------------------------
	// ---------   Match State   ----------
	// ------------------------------------
public:
	void StartMatch();
	void BeginRoundPrepare();
	void SetAvailableMaps(const std::vector<int>& maps);
	bool TrySelectMap();
	void FinishMapSelection();
	void BeginNextRoundOrEndMatch();
	void EndMatch();

private:
	int maxRound = 3;
	int currentRound = 0;

	std::vector<int> availableMaps;
	std::vector<int> remainingMaps;

	int team1Score = 0;
	int team2Score = 0;
	int requiredWinScore = (maxRound / 2) + 1;

	EMatchFlow matchFlowState = EMatchFlow::Robby;

	int selectedMapType = 0;

	float matchFlowRemainTime = 0.0f;
	float mapSelectTime = 10.0f;

	std::mt19937 MapRandomEngine{ std::random_device{}() };

private:
	// ------------------------------------
	// --------   InGame State   ----------
	// ------------------------------------
	float roundStartDelay = 1.0f;
	float resultRemainTime = 5.0f;

	float elapsedTime = 0.f;
	float timeAccumlator = 0.f;
	int currentMapPhase = 0;

public:
	// ------------------------------------
	// -------   Player Character   -------
	// ------------------------------------
	// HP System
	void ApplyDamage(int sessionID, int damageAmount, EDamageType damageType);		// Applies damage, triggers death at zero HP, and broadcasts the result.
	void Heal(int sessionID, int healAmount);				// Restores HP up to max HP and broadcasts the result.
	void ResetHP(int sessionID);							// Restores HP to max HP and broadcasts the updated status.
	void SetCurrentHP(int sessionID, int newHP);			// Sets the internal HP value after clamping it to the valid range.

	// State System
	void EndGameRoundByElimination(int eliminatedTeamID);
	void EndGameRoundWithResult(int winnerTeamID, int endReason);
	void SetCharacterState(int sessionID, int newState);	// Changes the life state and broadcasts the update.
	void HandleDeath(int sessionID);						// Marks the character as dead and starts respawn handling.
	void HandleRespawn(int sessionID);						// Restores HP, revives the player, resets position, and broadcasts the respawn.
	bool IsTeamEliminated(int teamID) const;

	// Role System
	void SetRole(int sessionID);							// Assigns a role and broadcasts the change.
	void ApplyRoleStats(int sessionID);						// Applies movement speed and max HP rules for the current role.
	float GetRoleSpeedMultiplier(int roleType);				// Returns the movement speed multiplier for the given role.

	// Item System
	// Handles item pickup requests for the given player.
	void HandleItemPickup(int sessionID, int itemID);
	// Equips the currently held item on the server side.
	void EquipItem();
	// Drops the currently equipped item back into the world.
	void DropCurrentItem(int sessionID, int itemID);

	// Combat System
	// Applies server-authoritative knockback between two players.
	void ApplyKnockback(int attackerID, int targetID, float power);
	// Processes the attack hit frame once the animation reaches it.
	void AnimNotify_AttackHit();
	// Character Movement Update
	void UpdatePlayerMovement(Session* player, float DeltaTime);
	void UpdatePlayerVertical(Session* player, float deltaTime, bool bJumpRequested);
	// Check Collision with Other Player and Objects
	float GetCollisionRadius(int roleType) const;
	bool CanOccupyPosition(const Vector3& pos, float radius) const;
	Vector3 ResolveMovementWithCollision(const Vector3& currentPos, const Vector3& desiredPos, float radius) const;
	float GetGroundActorZ() const { return FixedGroundZ + ServerCapsuleHalfHeight; }
	float GetCurrentServerGravityZ() const
	{
		return mapType == 3 ? SpaceServerGravityZ : ServerGravityZ;
	}

	float GetCurrentServerJumpZVelocity() const
	{
		return mapType == 3 ? SpaceServerJumpZVelocity : ServerJumpZVelocity;
	}

private:
	int MaxHP = 100;
	int CurrentHP = 100;
	int CharacterState = 0;			// 0 = Alive, 1 = Dead
	float RespawnTime = 3.0f;

	int RoleType = 0;				// 0 = Striker, 1 = Guardian, 2 = Manipulator
	float BaseWalkSpeed = 500.f;	// Striker: 1.2x, Guardian: 0.8x, Manipulator: 1.0x

	float ServerGravityZ = -1200.f;
	float ServerJumpZVelocity = 1000.0f;
	float SpaceServerGravityZ = -735.0f;      // -980 * 0.5
	float SpaceServerJumpZVelocity = 1200.0f;
	float ServerCapsuleHalfHeight = 475.0f;
	float GroundSnapTolerance = 2.0f;

	float AirMoveAcceleration = 6000.0f;
	float AirBrakingDeceleration = 800.0f;

	// =============================================
	// =============	Need  Modify	============
	// =============	Set Map Size	============
	// =============================================
	float MapMinX = -10000.0f;
	float MapMaxX = 10000.0f;
	float MapMinY = -10000.0f;
	float MapMaxY = 10000.0f;
	float FixedGroundZ = 500.0f;
public:
	// ------------------------------------
	// -----------   BaseItem   -----------
	// ------------------------------------
	// Starts item use handling for the active item.
	void StartUse();
	// Executes the hit logic for the current attack or item use.
	void DoHit();
	// Validates and processes an attack input from the given player.
	void HandleAttackInput(int sessionID);
	void HandleAttackHitReport(int sessionID, const AttackHitReportPacket& pkt);
	// Broadcast Attack Calculation Result.
	void BroadcastAttackAction(int attackerUID, int attackType, uint32_t attackSeq);
	// Applies validated damage from one player to another target.
	void ApplyDamageToTarget(int attackerID, int targetID, float damage);
	// Selects the proper attack animation for the current role.
	void GetAttackMontageByRole(ERecRoleType InRole) const;

	void ResetMapItemSpawner();
	void UpdateMapItemSpawner(float deltaTime, EItemKind phase2SpecialItem);
	void SpawnPhase1BasicItems();
	void SchedulePhase2Items(EItemKind specialItem);
	void UpdatePendingItemSpawns(float deltaTime);
	void SpawnMapItem(EItemKind itemKind);
	EItemKind PickRandomBasicItemKind();

private:
	float Damage = 20.f;
	float KnockbackPower = 800.f;
	float Range = 200.f;
	float Radius = 80.f;
	int ownerSessionID = -1;

	struct PendingItemSpawn
	{
		EItemKind ItemKind = EItemKind::None;
		float RemainTime = 0.0f;
	};

	bool bPhase1ItemsSpawned = false;
	bool bPhase2ItemsScheduled = false;

	int nextItemObjectID = 10000;
	std::vector<PendingItemSpawn> pendingItemSpawns;


public:
	// ------------------------------------
	// ---------   Map Control   ----------
	// ---------   Building Map  ----------
	// ------------------------------------
	// Updates time-driven hazards for the building map.
	void UpdateBuildingMap(float deltaTime);

	void SpawnSmallDebris(int spawnerID);                   // Spawns small debris and broadcasts the event.
	void HandleDebrisHit(int debrisID, int targetID);       // Applies debris hit damage and broadcasts the result.
	void DestroyDebris(int debrisID);                       // Removes debris and broadcasts the destruction.

	// Phase 1: every 6-10 seconds, 1 spawn / Phase 2: every 3-6 seconds, 1-2 spawns / Phase 3: every 2-4 seconds, 2 spawns
	// Advances the small debris spawn timer for the current phase.
	void UpdateDebrisSpawner(float deltaTime);
	void SpawnDebrisByPhase();								// Broadcasts the resulting event to all room members.

	void ActivateLargeDebris(int debrisID, float impulse);  // Starts a large debris fall and broadcasts the activation.
	// Updates the fall simulation for a large debris object.
	void UpdateLargeDebrisFall(int debrisID, float deltaTime);
	void LandAndFracture(int debrisID);                     // Handles impact, fractures chunks, and broadcasts the event.
	void BreakChunk(int debrisID, int chunkIndex);          // Breaks a single chunk and broadcasts the update.
	void ApplyDamageToChunk(int debrisID, int chunkIndex, float damage); // Applies damage to a chunk and evaluates chain breaks.
	void DropUnsupportedChunks(int debrisID);               // Drops unsupported chunks and broadcasts the result.

	void StartBuildingMap();
	void TriggerBuildingPhase2();                           // Broadcasts the resulting event to all room members.
	void TriggerBuildingPhase3();                           // Broadcasts the resulting event to all room members.

	void ActivateBreakable(int objectID);                   // Broadcasts the resulting event to all room members.
	void ApplyBreakableDamage(int objectID, float damage);  // Reduces durability on a breakable object.
	void BreakActor(int objectID);                          // Broadcasts the resulting event to all room members.
	// Resets a breakable object back to its initial state.
	void ResetBreakable(int objectID);


	// ------------------------------------
	// ---------   Map Control   ----------
	// ---------    Ice Cave     ----------
	// ------------------------------------
	// Updates timers and hazard state for the ice cave map.
	void UpdateIceCaveMap(float deltaTime);

	// Initializes icicle and floor-tile state for the ice cave.
	void StartIceMap();
	void EnterIcePhase2();                                  // Starts periodic icicle hazard spawns.
	void EnterIcePhase3();                                  // Adds floor-breaking hazards to the rotation.

	void SetFloorCracked(int tileID);                       // Changes a floor tile from Normal to Cracked and broadcasts the state.
	void StartFloorBreaking(int tileID);                    // Changes a tile from Cracked to Breaking and broadcasts the warning.
	void BreakFloor(int tileID);                            // Marks the tile as Broken, drops it, and broadcasts the event.
	void TriggerRandomFloorTile();                          // Selects a random eligible floor tile and starts its break sequence.

	void StartIcicleWarning(int icicleID);                  // Changes an icicle from Idle to Warning and broadcasts the alert.
	void StartIcicleFalling(int icicleID);                  // Changes an icicle to Falling and broadcasts the drop.
	void HandleIcicleHit(int icicleID, int targetID);       // Applies icicle hit damage and broadcasts the result.
	void BreakIcicle(int icicleID);                         // Marks the object as Broken and broadcasts the event.
	void TriggerRandomIcicle();                             // Selects a random idle icicle and starts its warning state.

	void UpdateIceChillSpawner(float deltaTime);
	void UpdateIceChillZones(float deltaTime);
	void SpawnIceChillZones();
	void SpawnIceChillZone();
	void DespawnIceChillZone(int zoneID);

	void ApplyFreezeToPlayer(int sessionID, float duration);
	void EndFreezeOnPlayer(int sessionID);
	void UpdateFrozenPlayers(float deltaTime);
	void BroadcastFreezeState(int targetUID, bool bFrozen, float duration);

	void HandleIceFloorStanding(int sessionID, int floorID, int pieceIndex);

	void UpdateTorchThaw(float deltaTime);
	bool IsTorchEquipped(Session* player) const;
	bool IsInTorchThawRange(Session* torchOwner, Session* frozenTarget) const;

	// Torch Test Function
	void ApplyDebugFreezeOnceForTorchTest();

private:
	void UpdateIceFloorStanding(float deltaTime);
	void BroadcastFloorEvent(int pieceIndex, int eventState);

	int mapType = 0;	// 1 = Building, 2 = Ice Cave
	int roundCount = 0;

	int phase1Time = 40;
	int phase2Time = 80;
	int phase3Time = 30;

	std::mutex iceFloorMutex;

	std::vector<IceChillZoneData> iceChillZones;

	int nextIceChillZoneID = 1;
	float iceChillSpawnAccumulator = 0.f;
	float iceChillNextSpawnTime = 5.f;

	float phase2ChillMinSpawnInterval = 6.f;
	float phase2ChillMaxSpawnInterval = 10.f;
	float phase3ChillMinSpawnInterval = 3.f;
	float phase3ChillMaxSpawnInterval = 6.f;

	// Torch Progress Data
	std::unordered_map<long long, float> torchThawProgressByPair;

	bool bDebugTorchThawTestEnabled = false;
	bool bDebugFreezeAppliedForTorchTest = false;

	float TorchThawRequiredTime = 1.5f;
	float TorchThawRadius = 350.f;

public:
	// ------------------------------------
	// ---------   Map Control   ----------
	// ---------  Space Station  ----------
	// ------------------------------------
	void UpdateSpaceStation(float deltaTime);

	void StartSpaceStation();

	void EnterSpaceStationPhase2();
	void EnterSpaceStationPhase3();

	void ApplyBlackHolePull(float deltaTime);
	void AddSpaceBlackHole(int objectID, const Vector3& center);
	void BroadcastSpaceBlackHoleSpawn(const SpaceBlackHoleData& blackHole);

public:
	// ------------------------------------
	// ---------   Map Control   ----------
	// --------  Jungle  Station  ---------
	// ------------------------------------
	void StartJungleMap();
	void UpdateJungleMap(float deltaTime);

	void UpdateJunglePoisonFog(float deltaTime);
	void ApplyJunglePoisonDamage();
	bool IsInsideJunglePoisonFog(const GameData& gd) const;

	void HandleGrenadeBlackHoleSpawn(int sessionID, const GrenadeBlackHolePacket& pkt);

private:
	// ------------ Building Map Statement ------------
	DebrisSpawnConfig debrisPhaseConfigs[3] = {
		{6.f, 10.f, 1, 1},
		{3.f,  6.f, 1, 2},
		{2.f,  4.f, 2, 2},
	};

	float debrisSpawnAccumulator = 0.f;
	float nextDebrisSpawnTime = 0.f;

	int nextObjectID = 1;

	bool bBuildingPhase2Trigger = false;
	bool bBuildingPhase3Trigger = false;


	// ------------ IceCave Map Statement ------------
	std::vector<IcicleData> icicles;
	std::vector<IceFloorTileData> floorTiles;

	float icicleSpawnAccumulator = 0.f;
	float icicleSpawnInterval = 3.f;

	float floorBreakAccumulator = 0.f;
	float floorBreakInterval = 4.f;

	bool bIcecavePhase2Trigger = false;
	bool bIcecavePhase3Trigger = false;

	float NormalMoveAcceleration = 16000.0f;
	float IceMoveAcceleration = 4500.0f;

	float NormalBrakingDeceleration = 18000.0f;
	float IceBrakingDeceleration = 700.0f;

	float IceMaxSpeedMultiplier = 1.05f;
	float StopVelocityThreshold = 5.0f;

	// ------------ SpaceStation Map Statement ------------
	bool bSpaceStationPhase2Trigger = false;
	bool bSpaceStationPhase3Trigger = false;

	std::vector<SpaceBlackHoleData> SpaceBlackHoles;

	Vector3 SpaceBlackHoleCenter = { 0.f, 0.f, 500.f };
	Vector3 Outside1_BlackHoleCenter = {  11000.f,      0.f, 1000.f };
	Vector3 Outside2_BlackHoleCenter = { -11000.f,      0.f, 1000.f };
	Vector3 Outside3_BlackHoleCenter = {      0.f, -11000.f, 1000.f };

	float SpaceBlackHolePullRadius   = 12000.f;
	float SpaceBlackHoleMinDistance  =  150.f;
	float SpaceBlackHolePullStrength = 1600.f;
	float SpaceBlackHoleMaxPullSpeed = 1400.f;

	int nextGrenadeBlackHoleObjectID = 1000;


	// ------------ Jungle Map Statement ------------
	JunglePoisonFogData junglePoisonFog;
};