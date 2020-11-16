#pragma once

typedef struct RaycastResult
{
	bool didHit;
	Vector3 hitPos;
	Entity hitEntity;
	Vector3 normal;
};

enum RaycastIntersectionOptions
{
	Everything = -1,
	Map = 1,
	MissionEntities,
	Peds1 = 12,
	Objects = 16,
	Unk1 = 32,
	Unk2 = 64,
	Unk3 = 128,
	Vegetation = 256,
	Unk4 = 512
};

extern Ped player;

Vector3 entityPos(Entity entity);
void getGroundPos(Vector3 originalPos, Vector3* outPos);
float distanceBetweenEntities(Entity entity1, Entity entity2);
Ped createPed(const char* model, Vector3 pos);
Object createProp(char* model, Vector3 position, float heading = 0, bool isStatic = false, bool isVisible = true);
RaycastResult raycast(Vector3 source, Vector3 direction, float maxDist, RaycastIntersectionOptions intersectionOptions = Everything, Entity ignore = NULL);
RaycastResult raycastCrosshair(float maxDist, RaycastIntersectionOptions intersectionOptions = Everything, Entity ignore = NULL);
tm getGameTime();
Ped findCarriedPedBy(Ped carrier);
void getGroundPos(Vector3* position);
Vector3 getGroundPos(Vector3 originalPos);
Vector3 getRandomPositionInRange(Vector3 source, int radius);
Vector3 getRandomPedPositionInRange(Vector3 source, int radius);
Vector3 playerPos();
float getModelLength(Hash model);
Vector3 getRelativeEntityCoords(Entity entity, int offsetFromCenter = 0);
Ped getClosestPed(Ped around);
Vehicle getClosestVehicle(Ped around);
float calculateHeadingToPosition(Entity entity, Vector3 dest);
Ped findHogtiedTargetEntity();
Vector3* getSafeCoordForPed(Vector3 destination);
void playAnimation(Ped ped, const char* animName, const char* animDict, int duration = -1, float blendInSpeed = 8.0f, float blendOutSpeed = -8.0f, int flags = 0);
void loadImap(Hash imapHash);
void loadInteriorSet(Interior interior, const char* setName);
void playEntityAnimation(Entity entity, const char* animName, const char* animDict, float duration, bool loop = false, bool stayInAnim = false, float delta = 0, int bitset = 0);