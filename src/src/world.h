#pragma once

void getGroundPos(Vector3 originalPos, Vector3* outPos);
float distanceBetweenEntities(Entity entity1, Entity entity2);
Ped createPed(const char* model, Vector3 pos);
Object createProp(char* model, Vector3 position, float heading = 0, bool isStatic = false, bool isVisible = true);
tm getGameTime();