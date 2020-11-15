#include "Main.h"

vector<Gallows*> gallows = {
	new Gallows( // Valentine
		toVector3(-315.075, 730.922, 119.411),
		vector<Vector3>{toVector3(-313.787, 728.843, 119.473), toVector3(-314.639, 733.692, 119.473f)},
		2371225963,
		"pull_lever_front_trapdoor_val"
	),
	new Gallows( // Blackwater
		toVector3(-766.644, -1260.87, 46.4626),
		vector<Vector3>{toVector3(-764.715, -1260.41, 46.3581)},
		-1923741333,
		"pull_lever_deputy_trapdoor_val"
	),
	new StDanisGallows(),
	new Gallows( // Rhodes
		toVector3(1373.52, -1216.83, 83.2595),
		vector<Vector3>{toVector3(1375.53, -1215.3, 83.1936)},
		-1923741333,
		"pull_lever_front_trapdoor_val"
	)
};

Gallows* Gallows::fromPosition(Vector3 pos) {
	for (vector<Gallows*>::iterator itr = gallows.begin(); itr != gallows.end(); itr++)
	{
		if (distance((*itr)->getPosition(), pos) <= 1.5f) {
			return *itr;
		}
	}

	return NULL;
}

Gallows::Gallows(Vector3 leverPos, vector<Vector3> trapdoorPositions, int trapdoorModel, char* trapdoorAnimation, GallowsLeverMode leverMode)
{
	this->leverPosition = leverPos;
	this->trapdoorPositions = trapdoorPositions;
	this->trapdoorModel = trapdoorModel;
	this->trapdoorAnimation = trapdoorAnimation;
	this->leverMode = leverMode;
}

Vector3 Gallows::getPosition()
{
	return this->leverPosition;
}

void Gallows::reset(Ped executioner)
{
	getToLever(executioner);
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

bool Gallows::isLeverPulled()
{
	return ENTITY::IS_ENTITY_PLAYING_ANIM(getLever(), "script_re@public_hanging@lever", getLeverAnimationName(), 3);
}

GallowsLeverMode Gallows::getLeverMode()
{
	return this->leverMode;
}


void Gallows::pullLever(Ped executioner)
{
	getToLever(executioner);

	vector<Entity> trapdoors = getTrapdoors();
	for (vector<Entity>::iterator trapdoorItr = trapdoors.begin(); trapdoorItr != trapdoors.end(); trapdoorItr++)
	{
		playTrapdoorAnimation(*trapdoorItr);
	}

	playLeverAnimation(getLever());
	WAIT(100);
	playLeverPullAnimation(executioner);
}

vector<Entity> Gallows::getTrapdoors()
{
	vector<Entity> trapdoors;

	for (vector<Vector3>::iterator trapdoorItr = trapdoorPositions.begin(); trapdoorItr != trapdoorPositions.end(); trapdoorItr++)
	{
		trapdoors.push_back(OBJECT::GET_CLOSEST_OBJECT_OF_TYPE((*trapdoorItr).x, (*trapdoorItr).y, (*trapdoorItr).z, 1, getTrapdoorModel(), false, 0, 0));
	}	
	return trapdoors;
}

Entity Gallows::getLever()
{
	return OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(leverPosition.x, leverPosition.y, leverPosition.z, 10, -1539465244, false, 0, 0);
}

void Gallows::playTrapdoorAnimation(Entity trapdoor)
{
	playEntityAnimation(trapdoor, trapdoorAnimation, "script_re@public_hanging@lever", 1000, false, true, 0.28f, 32768);
}

void Gallows::playLeverAnimation(Entity lever)
{
	playEntityAnimation(lever, getLeverAnimationName(), "script_re@public_hanging@lever", 1000.0f, false, true, 0.28f, 32768);
}

void Gallows::playLeverPullAnimation(Ped executioner)
{
	playAnimation(executioner, getLeverPulllAnimationName(), "script_re@public_hanging@lever", 4000);
}

void Gallows::resetLever(Entity lever)
{
	ENTITY::STOP_ENTITY_ANIM(lever, getLeverAnimationName(), "script_re@public_hanging@lever", 0);
}

void Gallows::resetTrapdoor(Entity trapdoor)
{
	ENTITY::STOP_ENTITY_ANIM(trapdoor, trapdoorAnimation, "script_re@public_hanging@lever", 0);
}

int Gallows::getTrapdoorModel()
{
	return trapdoorModel;
}

char* Gallows::getLeverAnimationName()
{
	return "push_lever_deputy_lever";
}

char* Gallows::getLeverPulllAnimationName()
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

void Gallows::getToLever(Ped executioner)
{
	Entity lever = getLever();
	Vector3 goTo = getLeverPullingPosition();

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::TASK_GO_STRAIGHT_TO_COORD(0, goTo.x, goTo.y, goTo.z, 1, 5000, getLeverHeading(), 0, 0);
	//AI::TASK_ACHIEVE_HEADING(0, getLeverHeading(), 1000);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(executioner, seq);
	WAIT(500);

	int i = 0;
	while (AI::GET_SEQUENCE_PROGRESS(executioner) != -1 && i < 50)
	{
		WAIT(100);
		i++;
	}
}

Vector3 Gallows::getLeverPullingPosition()
{
	return leverPosition + getRightVector(getLever()) * -0.7f;
}

float Gallows::getLeverHeading()
{
	return 270 - ENTITY::GET_ENTITY_HEADING(getLever());
}
