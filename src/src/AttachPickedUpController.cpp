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
	Ped targetEntity = findCarriedPedBy(player);

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

	addRope(new AttachedRope(targetGroundPos, currentTarget, "SKEL_NECK0", 4.0f));
}