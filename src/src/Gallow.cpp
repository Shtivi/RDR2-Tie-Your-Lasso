#include "Main.h"

vector<Gallow*> gallows = {
	new StandardGallows( // Valentine
		toVector3(-315.075, 730.922, 119.411),
		vector<Vector3>{toVector3(-313.787, 728.843, 119.473), toVector3(-314.639, 733.692, 119.473f)},
		2371225963,
		"pull_lever_front_trapdoor_val"
	),
	new StandardGallows( // Blackwater
		toVector3(-766.644, -1260.87, 46.4626),
		vector<Vector3>{toVector3(-764.715, -1260.41, 46.3581)},
		-1923741333,
		"pull_lever_deputy_trapdoor_val"
	),
	new StDanisGallows()
};

//new StandardGallows( // Strawberry
//	toVector3(-1805.24, -337.156, 166.699), 
//	vector<Vector3>{ toVector3(-1806.2, -333.923, 166.623) }
//),

Gallow* Gallow::fromPosition(Vector3 pos) {
	for (vector<Gallow*>::iterator itr = gallows.begin(); itr != gallows.end(); itr++)
	{
		if (distance((*itr)->getPosition(), pos) <= 1.5f) {
			return *itr;
		}
	}

	return NULL;
}

Gallow::Gallow(Vector3 leverPos, vector<Vector3> trapdoorPositions, int trapdoorModel, char* trapdoorAnimation, GallowsLeverMode leverMode)
{
	this->leverPosition = leverPos;
	this->trapdoorPositions = trapdoorPositions;
	this->trapdoorModel = trapdoorModel;
	this->trapdoorAnimation = trapdoorAnimation;
	this->leverMode = leverMode;
}

Vector3 Gallow::getPosition()
{
	return this->leverPosition;
}

void Gallow::reset(Ped executioner)
{
	playAnimation(executioner, leverMode == Push ? "pull_unarmed_v1" : "push_behind_quick" , "script_re@public_hanging@lever", 4000);
	WAIT(1700);
	resetLever(getLever());

	WAIT(400);
	vector<Entity> trapdoors = getTrapdoors();
	for (vector<Entity>::iterator trapdoorItr = trapdoors.begin(); trapdoorItr != trapdoors.end(); trapdoorItr++)
	{
		resetTrapdoor(*trapdoorItr);
	}
}

bool Gallow::isLeverPulled()
{
	return ENTITY::IS_ENTITY_PLAYING_ANIM(getLever(), "script_re@public_hanging@lever", getLeverAnimationName(), 3);
}

void Gallow::pullLever(Ped executioner)
{
	WEAPON::SET_CURRENT_PED_WEAPON(executioner, WeaponHash::WEAPON_UNARMED, true, 0, 0, 0);
	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_GO_STRAIGHT_TO_COORD(0, leverPosition.x, leverPosition.y, leverPosition.z, 1, 5000, ENTITY::GET_ENTITY_HEADING(getLever()), 0, 0);
	//AI::TASK_TURN_PED_TO_FACE_COORD(0, leverPosition.x, leverPosition.y, leverPosition.z, 1000);
	AI::TASK_ACHIEVE_HEADING(0, ENTITY::GET_ENTITY_HEADING(getLever()), 1000);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(executioner, seq);

	vector<Entity> trapdoors = getTrapdoors();
	for (vector<Entity>::iterator trapdoorItr = trapdoors.begin(); trapdoorItr != trapdoors.end(); trapdoorItr++)
	{
		playTrapdoorAnimation(*trapdoorItr);
	}

	playLeverAnimation(getLever());
	WAIT(100);
	playLeverPullAnimation(executioner);
	//MAPREGION::_0x43F867EF5C463A53(MAPREGION::_0xF68485C7495D848E(leverPosition.x, leverPosition.y, leverPosition.z, 0, 0, 9.724f, 2.5f, 1.75f, 1.75f, (Any)"m_volGallowsLever"));
}

vector<Entity> Gallow::getTrapdoors()
{
	vector<Entity> trapdoors;

	for (vector<Vector3>::iterator trapdoorItr = trapdoorPositions.begin(); trapdoorItr != trapdoorPositions.end(); trapdoorItr++)
	{
		trapdoors.push_back(OBJECT::GET_CLOSEST_OBJECT_OF_TYPE((*trapdoorItr).x, (*trapdoorItr).y, (*trapdoorItr).z, 1, getTrapdoorModel(), false, 0, 0));
	}	
	return trapdoors;
}

Entity Gallow::getLever()
{
	return OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(leverPosition.x, leverPosition.y, leverPosition.z, 10, -1539465244, false, 0, 0);
}

void Gallow::playTrapdoorAnimation(Entity trapdoor)
{
	playEntityAnimation(trapdoor, trapdoorAnimation, "script_re@public_hanging@lever", 1000, false, true, 0.28f, 32768);
}

void Gallow::playLeverAnimation(Entity lever)
{
	playEntityAnimation(lever, getLeverAnimationName(), "script_re@public_hanging@lever", 1000.0f, false, true, 0.28f, 32768);
}

void Gallow::playLeverPullAnimation(Ped executioner)
{
	playAnimation(executioner, getLeverPulllAnimationName(), "script_re@public_hanging@lever", 4000);
}

void Gallow::resetLever(Entity lever)
{
	ENTITY::STOP_ENTITY_ANIM(lever, getLeverAnimationName(), "script_re@public_hanging@lever", 0);
}

void Gallow::resetTrapdoor(Entity trapdoor)
{
	ENTITY::STOP_ENTITY_ANIM(trapdoor, trapdoorAnimation, "script_re@public_hanging@lever", 0);
}

int Gallow::getTrapdoorModel()
{
	return trapdoorModel;
}

char* Gallow::getLeverAnimationName()
{
	return "push_lever_deputy_lever";
}

char* Gallow::getLeverPulllAnimationName()
{
	if (leverMode == Push)
	{
		return "push_behind_quick";
	}
	else
	{
		return "pull_unarmed_v1";
	}
}