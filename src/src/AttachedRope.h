#pragma once

class AttachedRope : public Rope
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
	AttachedRope(Entity entity, Entity base, const char* bone1, const char* bone2, float length);

	bool getIsAttachedToMap();
	bool getIsEntityHanging();
	bool isExist();
	Entity getAttached();
	Entity getBase();
	
	void startWinding();
	void stopWinding();
	void startUnwinding();
	void stopUnwinding();
	bool canWind();
	int update();

private:
	Object createMapProp(char* model, Vector3 position);
};