#pragma once

const float HANGING_TRESHOLD = 1.1f;

void UpdateRopes();
void addRope(AttachedRope* rope);
bool doesEntityAttachedToRope(Entity entity);
AttachedRope* getClosestRopeWithin(Vector3 position, float radius);
