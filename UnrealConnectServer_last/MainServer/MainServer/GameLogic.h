#pragma once

#include <map>
#include <vector>

class Room;
struct Session;

enum ERecCharacterState { Alive, Dead };
enum ERecRoleType { Striker, Guardian, Manipulator };
enum ERoundState { Waiting, Playing, Finished };


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
	float x, y, z;
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
enum class EMapEventType { Icicle = 0, Floor = 1, SmallDebris = 2, LargeDebris = 3 };

struct IcicleData {
	int icicleID = -1;
	EIcicleState icicleState = EIcicleState::Idle;

	float warningTimer = 0.f;
	float warningDuration = 0.8f;
	float damage = 20.f;
};

struct  IceFloorTileData {
	int tileID = -1;
	EIceFloorState tileState = EIceFloorState::Normal;

	float breakTimer = 0.f;
	float breakDelay = 1.5f;
};

struct DebrisSpawnConfig {
	float min_Interval, max_Interval;
	int min_Count, max_Count;
};


class GameLogic
{
public:
	GameLogic();
	~GameLogic();

	Room* ownerRoom;
	std::map<int, Session*> players;

	void SetMapType(int type) {mapType = type;}

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
	void BroadcastDamageApply(int targetID, int damage, int remainHP);
	// Broadcasts a status-only update such as HP recovery.
	void BroadcastStatusUpdate(int targetID, int currentHP);
	// Broadcasts a life-state change such as Alive or Dead.
	void BroadcastStateChange(int targetID, int newState);
	// Broadcasts respawn position and HP for the target.
	void BroadcastRespawn(int targetID, float x, float y, float z, int hp);
	// Broadcasts a role change to every room member.
	void BroadcastRoleChange(int targetID, int newRoleType);

private:
	float elapsedTime = 0.f;
	float timeAccumlator = 0.f;
	int currentMapPhase = 0;

public:
	// ------------------------------------
	// -------   Player Character   -------
	// ------------------------------------
	// HP System
	void ApplyDamage(int sessionID, int damageAmount);		// Applies damage, triggers death at zero HP, and broadcasts the result.
	void Heal(int sessionID, int healAmount);				// Restores HP up to max HP and broadcasts the result.
	void ResetHP(int sessionID);							// Restores HP to max HP and broadcasts the updated status.
	void SetCurrentHP(int sessionID, int newHP);			// Sets the internal HP value after clamping it to the valid range.

	// State System
	void SetCharacterState(int sessionID, int newState);	// Changes the life state and broadcasts the update.
	void HandleDeath(int sessionID);						// Marks the character as dead and starts respawn handling.
	void HandleRespawn(int sessionID);						// Restores HP, revives the player, resets position, and broadcasts the respawn.

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
	void DropCurrentItem();

	// Combat System
	// Applies server-authoritative knockback between two players.
	void ApplyKnockback(int attackerID, int targetID, float power);
	// Processes the attack hit frame once the animation reaches it.
	void AnimNotify_AttackHit();

private:
	int MaxHP = 100;
	int CurrentHP = 100;
	int CharacterState = 0;			// 0 = Alive, 1 = Dead
	float RespawnTime = 3.0f;

	int RoleType = 0;				// 0 = Striker, 1 = Guardian, 2 = Manipulator
	float BaseWalkSpeed = 500.f;	// Striker: 1.2x, Guardian: 0.8x, Manipulator: 1.0x

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
	// Broadcast Attack Calculation Result.
	void BroadcastAttackAction(int attackerUID, int attackType);
	// Applies validated damage from one player to another target.
	void ApplyDamageToTarget(int attackerID, int targetID, float damage);
	// Selects the proper attack animation for the current role.
	void GetAttackMontageByRole(ERecRoleType InRole) const;

private:
	float Damage = 20.f;
	float KnockbackPower = 800.f;
	float Range = 200.f;
	float Radius = 80.f;
	int ownerSessionID = -1;

public:
	// ------------------------------------
	// ---------   Round State   ----------
	// ------------------------------------
	void StartReady();                                     // Starts the ready phase and broadcasts the new round state.
	void StartRound();                                     // Starts live gameplay and broadcasts the new round state.
	void CountdownTick();                                  // Advances the server-side one-second round timer.
	void HandlePhaseChanged(int newPhase);                 // Triggers and broadcasts a map phase transition.

private:
	int roundState = 0;            // 0=Waiting, 1=Playing, 2=Finished
	int readyTime = 10;
	int gameTime = 180;
	int currentReadyTime = 0;
	int currentGameTime = 0;


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

private:
	int mapType = 0;	// 1 = Building, 2 = Ice Cave

	int phase1Time = 120;
	int phase2Time = 60;
	int phase3Time = 20;

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
};