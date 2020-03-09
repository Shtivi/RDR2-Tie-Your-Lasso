#pragma once

const float HANGING_TRESHOLD = 1.1f;

typedef struct AttachedRope
{
	Entity entity1;
	Entity entity2;
	int rope;
	float ropeLength;
	bool isAttachedToMap;
	bool isEntityHanging;
};

extern std::vector<AttachedRope*> attachedRopes;

AttachedRope* createAttachedRope(Entity entity1, Entity entity2, const char* bone1, const char* bone2, float length);
AttachedRope* createAttachedRope(Vector3 mapPosition, Entity entity, const char* bone, float length);
Object createMapProp(char* model, Vector3 position);
void UpdateRopes();