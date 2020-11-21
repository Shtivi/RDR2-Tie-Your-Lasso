#include "Main.h"

vector<Gallows*> gallows = {
	new Gallows( // Valentine
		toVector3(-315.075, 730.922, 119.411),
		vector<Vector3>{toVector3(-313.787, 728.843, 119.473), toVector3(-314.639, 733.692, 119.473f)},
		2371225963,
		"pull_lever_front_trapdoor_val",
		270,
		90,
		vector<NooseSpot>{
			NooseSpot(toVector3(-314.166, 727.714, 122.854), toVector3(-313.907, 726.881, 121.285), toVector3(-314.543, 728.321, 120.608)),
			NooseSpot(toVector3(-314.487, 729.75, 122.897), toVector3(-314.697, 731.494, 121.753), toVector3(-314.735, 729.307, 120.615)),
			NooseSpot(toVector3(-315.338, 734.837, 122.885), toVector3(-315.492, 735.995, 121.696), toVector3(-315.63, 734.277, 120.617)),
			NooseSpot(toVector3(-315.04, 732.948, 122.899), toVector3(-314.741, 731.737, 121.504), toVector3(-315.383, 732.747, 120.61))
		}
	),
	new Gallows( // Blackwater
		toVector3(-766.644, -1260.87, 46.4626),
		vector<Vector3>{toVector3(-764.715, -1260.41, 46.3581)},
		-1923741333,
		"pull_lever_deputy_trapdoor_val",
		90,
		360,
		vector<NooseSpot>{
			NooseSpot(toVector3(-764.132, -1259.81, 49.5529), toVector3(-764.132, -1259.81, 49.5529), toVector3(-763.769, -1259.63, 47.3899)),
			NooseSpot(toVector3(-765.368, -1259.89, 49.5529), toVector3(-765.368, -1259.89, 49.5529), toVector3(-765.381, -1259.48, 47.3899))
		}
	),
	new StDanisGallows(),
	new Gallows( // Rhodes
		toVector3(1373.52, -1216.83, 83.2595),
		vector<Vector3>{toVector3(1375.53, -1215.3, 83.1936)},
		-1923741333,
		"pull_lever_front_trapdoor_val",
		270,
		90,
		vector<NooseSpot>{
			NooseSpot(toVector3(1374.76, -1216.23, 86.4909), toVector3(1373.4, -1217.74, 84.161), toVector3(1374.63, -1215.9, 84.2286)),
			NooseSpot(toVector3(1374.95, -1214.53, 86.6254), toVector3(1373.89, -1212.46, 85.8205), toVector3(1374.84, -1214.49, 84.2374))
		}
	),
	new StrawberryGallows()
};

Gallows* Gallows::fromPosition(Vector3 pos) {
	for (vector<Gallows*>::iterator itr = gallows.begin(); itr != gallows.end(); itr++)
	{
		if (distance((*itr)->getPosition(), pos) <= 8) {
			return *itr;
		}
	}

	return NULL;
}

Gallows::Gallows(
	Vector3 leverPos, 
	vector<Vector3> trapdoorPositions, 
	int trapdoorModel, 
	char* trapdoorAnimation, 
	float leverHeading, 
	float noosedPedHeading, 
	vector<NooseSpot> nooseSpots, 
	GallowsLeverMode leverMode
)
{
	this->leverPosition = leverPos;
	this->trapdoorPositions = trapdoorPositions;
	this->trapdoorModel = trapdoorModel;
	this->trapdoorAnimation = trapdoorAnimation;
	this->leverMode = leverMode;
	this->leverHeading = leverHeading;
	this->nooseSpots = nooseSpots;
	this->noosedPedHeading = noosedPedHeading;
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

	for (vector<NooseSpot>::iterator itr = nooseSpots.begin(); itr != nooseSpots.end(); itr++)
	{
		if (!itr->isAvailable()) {
			Rope* rope = getRopeAttachedTo(itr->getOccupant());
			if (rope) {
				rope->detach();
			}
			itr->clear();
		}
	}

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

	if (isLeverPulled()) 
	{
		WAIT(2000);
		for (vector<NooseSpot>::iterator itr = nooseSpots.begin(); itr != nooseSpots.end(); itr++)
		{
			if (!itr->isAvailable())
			{
				PED::EXPLODE_PED_HEAD(itr->getOccupant(), GAMEPLAY::GET_HASH_KEY("WEAPON_LASSO"));
				//ENTITY::SET_ENTITY_HEALTH(itr->getOccupant(), 4, 0);
			}
		}
	}
}

bool Gallows::canNooseAtPosition(Vector3 position)
{
	if (isLeverPulled()) {
		return false;
	}

	NooseSpot* nooseSpot = findClosestAvailableNooseSlot(position);
	return nooseSpot != NULL;
}

void Gallows::noose(Ped victim, Vector3 position)
{
	NooseSpot* nooseSpot = findClosestAvailableNooseSlot(position);
	
	if (!nooseSpot) {
		return;
	}

	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(victim, true);
	ENTITY::SET_ENTITY_COORDS(victim, nooseSpot->getTrapdoorPosition().x, nooseSpot->getTrapdoorPosition().y, nooseSpot->getTrapdoorPosition().z, 1, 1, 0, false);
	WAIT(500);
	AI::CLEAR_PED_TASKS_IMMEDIATELY(victim, 0, 0);
	AI::TASK_STAND_STILL(victim, -1);
	PED::SET_ENABLE_HANDCUFFS(victim, true, 0);
	float length = distance(nooseSpot->getTrapdoorPosition(), nooseSpot->getAnchorPosition()) + 0.75;
	MultiVertexRope* rope = new MultiVertexRope(new AttachedRope(nooseSpot->getAnchorPosition(), victim, "SKEL_NECK0", length));
	rope->pinTo(nooseSpot->getVerticalAnchorPosition());
	addRope(rope);
	WAIT(500);
	ENTITY::SET_ENTITY_HEADING(victim, noosedPedHeading);
	nooseSpot->setOccupant(victim);

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
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(executioner, seq);
	WAIT(500);

	int i = 0;
	while (AI::GET_SEQUENCE_PROGRESS(executioner) != -1 && i < 50)
	{
		WAIT(100);
	}
	i++;
}

Vector3 Gallows::getLeverPullingPosition()
{
	return leverPosition + getRightVector(getLever()) * -0.7f;
}

float Gallows::getLeverHeading()
{
	return leverHeading - ENTITY::GET_ENTITY_HEADING(getLever());
}

NooseSpot* Gallows::findClosestAvailableNooseSlot(Vector3 position)
{
	NooseSpot* closest = &(*nooseSpots.begin());
	if (!closest) {
		return NULL;
	}

	float bestDistance = distance(closest->getTrapdoorPosition(), position);

	for (vector<NooseSpot>::iterator itr = nooseSpots.begin(); itr != nooseSpots.end(); itr++)
	{
		float currentDistance = distance((*itr).getTrapdoorPosition(), position);
		if (currentDistance <= bestDistance && itr->isAvailable()) {
			closest = &(*itr);
			bestDistance = currentDistance;
		}
	}

	if (bestDistance > 2 || !closest->isAvailable()) {
		return NULL;
	}

	return closest;
}
