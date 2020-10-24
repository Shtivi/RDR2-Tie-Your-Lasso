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

Ped findCarriedPedBy(Ped carrier)
{
	return PED::_0xD806CD2A4F2C2996(carrier);

	//int nearbyEntities[5 * 2 + 2];
	//Ped targetEntity = NULL;

	//nearbyEntities[0] = 5;
	//int n = PED::GET_PED_NEARBY_PEDS(carrier, (int*)&nearbyEntities, -1, -1);
	//for (int i = 0; i < n; i++)
	//{
	//	if (ENTITY::IS_ENTITY_A_PED(nearbyEntities[i]) &&
	//		ENTITY::DOES_ENTITY_EXIST(nearbyEntities[i]) &&
	//		ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(carrier, nearbyEntities[i]))
	//	{
	//		return nearbyEntities[i];
	//	}
	//}

	//return NULL;
}

void getGroundPos(Vector3* originalPos)
{
	getGroundPos(*originalPos, originalPos);
}

Vector3 getGroundPos(Vector3 originalPos)
{
	float groundZ;
	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(originalPos.x, originalPos.y, originalPos.z, &groundZ, false);
	return toVector3(originalPos.x, originalPos.y, groundZ);
}

Vector3 getRandomPositionInRange(Vector3 center, int radius)
{
	int x = rndInt((int)center.x - radius, (int)center.x + radius + 1);
	int topOrBottom = rndInt(0, 2) == 1 ? 1 : -1;
	double y = topOrBottom * sqrt(pow(radius, 2) - pow(x - center.x, 2)) + center.y;

	Vector3 output;
	output.x = x;
	output.y = (float)y;
	return getGroundPos(output);
}

Vector3 getRandomPedPositionInRange(Vector3 source, int radius)
{
	Vector3 position = getRandomPositionInRange(source, radius);
	PATHFIND::GET_SAFE_COORD_FOR_PED(position.x, position.y, position.z, true, &position, 16);
	return position;
}

Vector3 playerPos()
{
	return ENTITY::GET_ENTITY_COORDS(player, 1, 0);
}

float getModelLength(Hash model)
{
	Vector3 front, back;
	GAMEPLAY::GET_MODEL_DIMENSIONS(model, &front, &back);
	float length = get_vector_length(front - back);
	return length;
}

Vector3 getRelativeEntityCoords(Entity entity, int offsetFromCenter)
{
	float length = getModelLength(ENTITY::GET_ENTITY_MODEL(entity));
	Vector3 entityPos = ENTITY::GET_ENTITY_COORDS(entity, 1, 0);
	Vector3 forwardVec = ENTITY::GET_ENTITY_FORWARD_VECTOR(entity);
	
	return entityPos + forwardVec * offsetFromCenter * (length / 4);
}

Vehicle getClosestVehicle(Ped around)
{
	int nearbyEntities[5 * 2 + 2];
	nearbyEntities[0] = 5;
	int n = PED::GET_PED_NEARBY_VEHICLES(around, (int*)&nearbyEntities);

	if (n == 0)
	{
		return NULL;
	}

	Vehicle best = nearbyEntities[0];
	float bestDistance = distanceBetweenEntities(around, best);

	for (int i = 0; i < n; i++)
	{
		float dist = distanceBetweenEntities(around, nearbyEntities[i]);
		if (ENTITY::DOES_ENTITY_EXIST(nearbyEntities[i]) && dist < bestDistance)
		{
			best = nearbyEntities[i];
			bestDistance = dist;
		}
	}

	return best;
}

Vector3 entityPos(Entity entity)
{
	return ENTITY::GET_ENTITY_COORDS(entity, 1, 0);
}

float calculateHeadingToPosition(Entity entity, Vector3 dest)
{
	float entityHeading = ENTITY::GET_ENTITY_HEADING(entity);
	float angle = angleBetweenVectors(entityPos(entity), dest);
	return entityHeading - angle;
}

Ped findHogtiedTargetEntity()
{
	Entity targetEntity = NULL;
	Ped asPed;
	
	if (!PLAYER::GET_PLAYER_TARGET_ENTITY(PLAYER::PLAYER_ID(), &targetEntity))
	{
		return false;
	}

	if (ENTITY::IS_ENTITY_A_PED(targetEntity) &&
		PED::IS_PED_HUMAN(targetEntity) &&
		AI::GET_IS_TASK_ACTIVE(targetEntity, 400))
	{
		return (Ped)targetEntity;
	}

	return false;
}

Ped getClosestPed(Ped around)
{
	int nearbyEntities[5 * 2 + 2];
	Ped targetEntity = NULL;

	nearbyEntities[0] = 5;
	int n = PED::GET_PED_NEARBY_PEDS(around, (int*)&nearbyEntities, -1, -1);

	if (n == 0)
	{
		return NULL;
	}

	Ped best = nearbyEntities[0];
	float bestDistance = distanceBetweenEntities(around, best);

	for (int i = 0; i < n; i++)
	{
		float dist = distanceBetweenEntities(around, nearbyEntities[i]);
		if (ENTITY::DOES_ENTITY_EXIST(nearbyEntities[i]) && dist < bestDistance)
		{
			best = nearbyEntities[i];
			bestDistance = dist;
		}
	}

	return best;
}

Vector3* getSafeCoordForPed(Vector3 destination)
{
	Vector3* out = new Vector3();
	if (!PATHFIND::GET_SAFE_COORD_FOR_PED(destination.x, destination.y, destination.z, false, out, 16))
	{
		return NULL;
	}

	return out;
}

//void playAnimation(Entity entity, const char* animName, const char* animDict, bool loop, bool stayInAnim)
//{
//	if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)animDict))
//	{
//		STREAMING::REQUEST_ANIM_DICT((char*)animDict);
//	}
//	
//	Stopwatch stopwatch;
//	stopwatch.start();
//	while (!STREAMING::HAS_ANIM_DICT_LOADED((char*)animDict) && stopwatch.getElapsedSeconds() <= 1)
//	{
//		WAIT(25);
//	}
//
//	ENTITY::PLAY_ENTITY_ANIM(entity, (char*)animName, (char*)animDict, 1.f, loop, stayInAnim, 0, 0, 0);
//}

void playAnimation(Ped ped, const char* animName, const char* animDict, int duration, float blendInSpeed, float blendOutSpeed, int flags)
{
	if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)animDict))
	{
		STREAMING::REQUEST_ANIM_DICT((char*)animDict);
	}

	Stopwatch stopwatch;
	stopwatch.start();
	while (!STREAMING::HAS_ANIM_DICT_LOADED((char*)animDict) && stopwatch.getElapsedSeconds() <= 1)
	{
		STREAMING::REQUEST_ANIM_DICT((char*)animDict);
		WAIT(25);
	}

	AI::TASK_PLAY_ANIM(ped, (char*)animDict, (char*)animName, blendInSpeed, blendOutSpeed, duration, flags, 0, 0, 0, 0, 0, 0);
}

void loadImap(Hash imapHash)
{
	if (!STREAMING::_0xD779B9B910BD3B7C(imapHash))
	{
		STREAMING::_0x59767C5A7A9AE6DA(imapHash);
	}
}

void loadInteriorSet(Interior interior, const char* setName)
{
	if (!INTERIOR::_IS_INTERIOR_PROP_ENABLED(interior, (char*) setName)) {
		INTERIOR::_ENABLE_INTERIOR_PROP(interior, (char*) setName, 1);
	}
}