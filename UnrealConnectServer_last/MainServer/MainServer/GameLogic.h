#pragma once

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

class ObjectManager {
public:
	ObjectManager();

private:
	void Collision_Check();
	
private:
	ObjectData Data;
};