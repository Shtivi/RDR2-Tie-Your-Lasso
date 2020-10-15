#include "Main.h";

AttachedRope::AttachedRope(Vector3 mapPosition, Entity entity, const char* bone, float length) :
	AttachedRope(entity, createMapProp("p_shotGlass01x", mapPosition), bone, NULL, length)
{
	isAttachedToMap = true;
}

AttachedRope::AttachedRope(Entity entity1, Entity entity2, const char* bone1, const char* bone2, float length)
{
	Vector3 pos1 = ENTITY::GET_ENTITY_COORDS(entity1, true, 0);
	Vector3 pos2 = ENTITY::GET_ENTITY_COORDS(entity2, true, 0);

	if (length <= 0)
	{
		length = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, true);
	}

	this->entity1 = entity1;
	this->entity2 = entity2;
	this->ropeLength = length;
	this->bone1 = bone1;
	this->bone2 = bone2;
	this->ropeId = ROPE::ADD_ROPE(pos1.x, pos1.y, pos1.z, 0, 0, 0, length, 14, length, 0, 1.0f, 0, 1, true, 1.25f, true, 0, 0);
	ROPE::_0x462FF2A432733A44(ropeId, entity1, entity2, 0, 0, 0, 0, 0, 0, (Any*)bone1, (Any*)bone2);
	ROPE::ACTIVATE_PHYSICS(ropeId);
	ROPE::_0x3C6490D940FF5D0B(ropeId, 0, (Any*)"noose01x_Rope_03", length, 0);

	this->isAttachedToMap = false;
	this->isEntityHanging = false;
	this->isWinding = false;
}

bool AttachedRope::getIsAttachedToMap()
{
	return isAttachedToMap;
}

bool AttachedRope::getIsEntityHanging()
{
	return isEntityHanging;
}

Entity AttachedRope::getEntity1()
{
	return entity1;
}

Entity AttachedRope::getEntity2()
{
	return entity2;
}

bool AttachedRope::isExist()
{
	return ROPE::GET_ROPE_VERTEX_COUNT(ropeId) > 0;
}

void AttachedRope::startWinding() {
	if (!isWinding && canWind()) 
	{
		ROPE::START_ROPE_WINDING(this->ropeId);
		isWinding = true;

		if (ENTITY::IS_ENTITY_A_PED(entity1)) 
		{
			PED::SET_PED_TO_RAGDOLL(entity1, 10000, 10000, 0, false, false, false);
		}
	}
}

void AttachedRope::stopWinding() 
{
	ROPE::STOP_ROPE_WINDING(this->ropeId);
	isWinding = false;
}

void AttachedRope::startUnwinding() 
{
	ROPE::START_ROPE_UNWINDING_FRONT(this->ropeId);
}

void AttachedRope::stopUnwinding()
{
	ROPE::STOP_ROPE_UNWINDING_FRONT(this->ropeId);
}

bool AttachedRope::canWind() 
{
	return isExist() && distanceBetweenEntities(entity1, entity2) >= 2.0f;
}

int AttachedRope::update()
{
	if (!isExist()) 
	{
		return 0;
	}

	int wait = 100;
	float heightAboveGround;
	int currHealth;
	Ped ped;

	if (!isAttachedToMap || !entity1)
	{
		return 0;
	}

	if (ENTITY::DOES_ENTITY_EXIST(entity1) &&
		ENTITY::IS_ENTITY_A_PED(entity1))
	{
		ped = (Ped)entity1;

		if (ENTITY::IS_ENTITY_DEAD(ped) || !PED::IS_PED_HUMAN(ped))
		{
			return 0;
		}

		heightAboveGround = ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(ped);
		if (isEntityHanging && heightAboveGround < HANGING_TRESHOLD)
		{
			isEntityHanging = false;
			wait = 500;
		}

		if (!isEntityHanging && heightAboveGround >= HANGING_TRESHOLD)
		{
			isEntityHanging = true;
		}

		if (isEntityHanging)
		{
			currHealth = ENTITY::GET_ENTITY_HEALTH(ped);
			PED::SET_PED_TO_RAGDOLL(ped, 10000000, 10000000, 0, false, false, false);
			ENTITY::SET_ENTITY_HEALTH(ped, max(currHealth - 1, 0), 0);
		}
	}

	if (isWinding && !canWind()) {
		stopWinding();
	}

	return wait;
}

Object AttachedRope::createMapProp(char* model, Vector3 position)
{
	Object prop = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY(model), position.x, position.y, position.z, false, false, true, 0, 0);
	ENTITY::FREEZE_ENTITY_POSITION(prop, true);
	ENTITY::SET_ENTITY_VISIBLE(prop, true);

	return prop;
}