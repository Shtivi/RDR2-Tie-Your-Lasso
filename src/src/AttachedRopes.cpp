#include "Main.h"

std::vector<AttachedRope*> attachedRopes;

int handleRope(AttachedRope* rope);

AttachedRope* createAttachedRope(Entity entity1, Entity entity2, const char* bone1, const char* bone2, float length)
{
	int ropeId;
	AttachedRope* rope = new AttachedRope;
	Vector3 pos1 = ENTITY::GET_ENTITY_COORDS(entity1, true, 0);
	Vector3 pos2 = ENTITY::GET_ENTITY_COORDS(entity2, true, 0);

	if (length <= 0) 
	{
		length = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, true);
	}

	rope->entity1 = entity1;
	rope->entity2 = entity2;
	rope->ropeLength = length;
	ropeId = ROPE::ADD_ROPE(pos1.x, pos1.y, pos1.z, 0, 0, 0, length, 14, length, 0, 1.0f, 0, 1, true, 1.25f, true, 0, 0);
	rope->rope = ropeId;

	ROPE::_0x462FF2A432733A44(ropeId, entity1, entity2, 0, 0, 0, 0, 0, 0, (Any*)bone1, (Any*)bone2);
	ROPE::ACTIVATE_PHYSICS(ropeId);
	ROPE::_0x3C6490D940FF5D0B(ropeId, 0, 0, length, 0);
	
	rope->isAttachedToMap = false;
	rope->isEntityHanging = false;

	attachedRopes.push_back(rope);

	return rope;
}

AttachedRope* createAttachedRope(Vector3 mapPosition, Entity entity, const char* bone, float length)
{
	Object mapProp = createMapProp("p_shotGlass01x", mapPosition);
	AttachedRope* rope = createAttachedRope(entity, mapProp, bone, NULL, 0);
	rope->isAttachedToMap = true;
	
	return rope;
}

Object createMapProp(char* model, Vector3 position)
{
	Object prop = OBJECT::CREATE_OBJECT(GAMEPLAY::GET_HASH_KEY(model), position.x, position.y, position.z, false, false, true, 0, 0);
	ENTITY::FREEZE_ENTITY_POSITION(prop, true);
	ENTITY::SET_ENTITY_VISIBLE(prop, true);
	
	return prop;
}

void UpdateRopes() 
{
	int wait = 0;
	std::vector<AttachedRope*>::iterator it;

	for (it = attachedRopes.begin(); it != attachedRopes.end(); ++it) 
	{
		wait = max(wait, handleRope(*it));
	}

	WAIT(wait);
}

int handleRope(AttachedRope* rope)
{
	int wait = 80;
	float heightAboveGround;
	int currHealth;
	Ped ped;

	if (!rope->isAttachedToMap || !rope->entity1)
	{
		return 0;
	}


	if (ENTITY::DOES_ENTITY_EXIST(rope->entity1) && 
		ENTITY::IS_ENTITY_A_PED(rope->entity1))
	{
		ped = (Ped)rope->entity1;

		if (ENTITY::IS_ENTITY_DEAD(ped) || !PED::IS_PED_HUMAN(ped))
		{
			return 0;
		}

		heightAboveGround = ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(ped);
		if (rope->isEntityHanging &&  heightAboveGround < HANGING_TRESHOLD)
		{
			rope->isEntityHanging = false;
			wait = 500;
		}

		if (!rope->isEntityHanging && heightAboveGround >= HANGING_TRESHOLD)
		{
			rope->isEntityHanging = true;
		}

		if (rope->isEntityHanging)
		{
			UI::_DRAW_TEXT("HANGED", 0, 0);
			currHealth = ENTITY::GET_ENTITY_HEALTH(ped);

			PED::SET_PED_TO_RAGDOLL(ped, 1000, 1000, 0, false, false, false);
			ENTITY::SET_ENTITY_HEALTH(ped, max(currHealth - 1, 0), 0);
		}
		else
		{
			UI::_DRAW_TEXT("NOT HANGED", 0, 0);
		}

		return wait;
	}
}