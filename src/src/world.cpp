#include "Main.h"

void getGroundPos(Vector3 originalPos, Vector3* outPos)
{
	float groundZ;
	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(originalPos.x, originalPos.y, originalPos.z, &groundZ, false);

	outPos->x = originalPos.x;
	outPos->y = originalPos.y;
	outPos->z = groundZ;
}

float distanceBetweenEntities(Entity entity1, Entity entity2)
{
	Vector3 pos1 = ENTITY::GET_ENTITY_COORDS(entity1, 1, 0);
	Vector3 pos2 = ENTITY::GET_ENTITY_COORDS(entity2, 1, 0);

	return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(pos1.x, pos1.y, pos1.z, pos2.x, pos2.y, pos2.z, 1);
}

Ped createPed(const char* modelName, Vector3 pos)
{
	Hash model = GAMEPLAY::GET_HASH_KEY((char*)modelName);
	STREAMING::REQUEST_MODEL(model, false);
	while (!STREAMING::HAS_MODEL_LOADED(model))
	{
		WAIT(0);
	}

	Ped ped = PED::CREATE_PED(model, pos.x, pos.y, pos.z, 0, false, false, false, false);
	PED::SET_PED_VISIBLE(ped, true);

	return ped;
}


Object createProp(char* model, Vector3 position, float heading, bool isStatic, bool isVisible)
{
	Hash modelHash = GAMEPLAY::GET_HASH_KEY(model);

	if (!STREAMING::HAS_MODEL_LOADED(modelHash))
	{
		STREAMING::REQUEST_MODEL(modelHash, false);
	}

	while (!STREAMING::HAS_MODEL_LOADED(modelHash))
	{
		WAIT(0);
	}

	Object prop = OBJECT::CREATE_OBJECT(modelHash, position.x, position.y, position.z, false, false, !isStatic, 0, 0);
	ENTITY::SET_ENTITY_HEADING(prop, heading);
	ENTITY::FREEZE_ENTITY_POSITION(prop, isStatic);
	ENTITY::SET_ENTITY_VISIBLE(prop, isVisible);

	return prop;
}

tm getGameTime()
{
	tm gameTime;
	gameTime.tm_year = 70; // make problems only with years aroud 1970, not 1900.
	gameTime.tm_mon = TIME::GET_CLOCK_MONTH();
	gameTime.tm_mday = TIME::GET_CLOCK_DAY_OF_MONTH();
	gameTime.tm_wday = TIME::GET_CLOCK_DAY_OF_WEEK();
	gameTime.tm_hour = TIME::GET_CLOCK_HOURS();
	gameTime.tm_min = TIME::GET_CLOCK_MINUTES();
	gameTime.tm_sec = TIME::GET_CLOCK_SECONDS();

	return gameTime;
}

RaycastResult raycast(Vector3 source, Vector3 direction, float maxDist, RaycastIntersectionOptions intersectionOptions)
{
	RaycastResult result;
	Vector3 target = add(&source, &multiply(&direction, maxDist));
	int rayHandle = SHAPETEST::_START_SHAPE_TEST_RAY(source.x, source.y, source.z, target.x, target.y, target.z, intersectionOptions, 0, 7);
	SHAPETEST::GET_SHAPE_TEST_RESULT(rayHandle, (BOOL*)&result.didHit, &result.hitPos, &result.normal, &result.hitEntity);
	return result;
}