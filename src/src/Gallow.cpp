#include "Main.h"

Gallow* Gallow::fromPosition(Vector3 pos) {
	return NULL;
}

Gallow::Gallow(Vector3 leverPos, vector<Vector3> trapdoorPositions)
{
	this->leverPosition = leverPos;
	this->trapdoorPositions = trapdoorPositions;
}

Vector3 Gallow::getPosition()
{
	return this->leverPosition;
}

void Gallow::pullLever(Ped executioner)
{
	WEAPON::SET_CURRENT_PED_WEAPON(executioner, WeaponHash::WEAPON_UNARMED, false, 0, 0, 0);
	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_GO_STRAIGHT_TO_COORD(0, leverPosition.x, leverPosition.y, leverPosition.z, 1, 5000, ENTITY::GET_ENTITY_HEADING(executioner), 0, 0);
	AI::TASK_TURN_PED_TO_FACE_COORD(0, leverPosition.x, leverPosition.y, leverPosition.z, 1000);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(executioner, seq);

	vector<Entity> trapdoors = getTrapdoors();
	for (vector<Entity>::iterator trapdoorItr = trapdoors.begin(); trapdoorItr != trapdoors.end(); trapdoorItr++)
	{
		playTrapdoorAnimation(*trapdoorItr);
	}

	WAIT(500);

	playLeverAnimation(getLever());
	playLeverPullAnimation(executioner);
}

vector<Entity> Gallow::getTrapdoors()
{
	vector<Entity> trapdoors;
	for (vector<Vector3>::iterator trapdoorItr = trapdoorPositions.begin(); trapdoorItr != trapdoorPositions.end(); trapdoorItr++)
	{
		RaycastResult ray = raycast(*trapdoorItr, toVector3(0, 0, 1), 10);
		if (ray.hitEntity && ENTITY::GET_ENTITY_MODEL(ray.hitEntity) == 2371225963) 
		{
			trapdoors.push_back(ray.hitEntity);
		}
	}
	
	return trapdoors;
}

Entity Gallow::getLever()
{
	RaycastResult ray = raycast(leverPosition, toVector3(0, 0, 1), 10);
	if (ray.hitEntity && ENTITY::GET_ENTITY_MODEL(ray.hitEntity) == -1539465244) {
		return ray.hitEntity;
	}

	return NULL;
}