#include "Main.h"

using namespace std;

AttachPickedUpController::AttachPickedUpController()
	: BaseActionsController()
{
	currentTarget = NULL;
}

Prompt* AttachPickedUpController::createActionPrompt()
{
	return new Prompt("Attach To Ground", GAMEPLAY::GET_HASH_KEY("INPUT_LOOK_BEHIND"), SemiHold);
}

bool AttachPickedUpController::isAbleToExecute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Ped targetEntity = findCarriedPed();

	if (!targetEntity)
	{
		return false;
	}

	if (PED::IS_PED_HUMAN(targetEntity))
	{
		currentTarget = targetEntity;
		return true;
	}
	else 
	{
		currentTarget = NULL;
		return false;
	}
}

void AttachPickedUpController::preparePrompt(Prompt* prompt)
{
	prompt->setTargetEntity(currentTarget);
}

void AttachPickedUpController::execute()
{
	Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(currentTarget, true, 0);
	Vector3 targetGroundPos;
	getGroundPos(targetPos, &targetGroundPos);

	addRope(new AttachedRope(targetGroundPos, currentTarget, "SKEL_NECK0", 3.0f));
	PED::SET_ENABLE_HANDCUFFS(lassoTarget, 1, 0);
	WEAPON::REMOVE_ALL_PED_WEAPONS(lassoTarget, 0, 0);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(lassoTarget, 1);
}

Ped AttachPickedUpController::findCarriedPed()
{
	int nearbyEntities[5 * 2 + 2];
	Ped player = PLAYER::PLAYER_PED_ID();
	Ped targetEntity = NULL;

	nearbyEntities[0] = 5;
	int n = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), (int*)&nearbyEntities, -1, -1);
	for (int i = 0; i < n; i++)
	{
		if (ENTITY::IS_ENTITY_A_PED(nearbyEntities[i]) && 
			ENTITY::DOES_ENTITY_EXIST(nearbyEntities[i]) && 
			ENTITY::IS_ENTITY_ATTACHED_TO_ENTITY(player, nearbyEntities[i]))
		{
			return nearbyEntities[i];

		}
	}

	return NULL;
}