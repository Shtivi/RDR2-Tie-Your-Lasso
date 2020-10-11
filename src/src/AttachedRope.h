#pragma once

class AttachedRope
{
private:
	int ropeId;
	Entity entity1;
	Entity entity2;
	const char* bone1;
	const char* bone2;
	float ropeLength;
	bool isAttachedToMap;
	bool isEntityHanging;
	bool isWinding;

public:
	AttachedRope(Vector3 mapPosition, Entity entity, const char* bone, float length);
	AttachedRope(Entity entity1, Entity entity2, const char* bone1, const char* bone2, float length);

	bool getIsAttachedToMap();
	bool getIsEntityHanging();
	bool isExist();
	Entity getEntity1();
	Entity getEntity2();
	
	void startWinding();
	void stopWinding();
	void startUnwinding();
	void stopUnwinding();
	int update();

private:
	Object createMapProp(char* model, Vector3 position);
};