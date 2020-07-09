#include "Main.h"

AttachHogtiedController::AttachHogtiedController()
	: BaseActionsController()
{
	currentTarget = NULL;
}

Prompt* AttachHogtiedController::createActionPrompt()
{
	return new Prompt("Attach To Ground", GAMEPLAY::GET_HASH_KEY("INPUT_LOOK_BEHIND"), SemiHold);
}

bool AttachHogtiedController::isAbleToExecute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Entity targetEntity;

	if (PLAYER::GET_PLAYER_TARGET_ENTITY(PLAYER::PLAYER_ID(), &targetEntity) &&
		ENTITY::IS_ENTITY_A_PED(targetEntity) && 
		PED::IS_PED_HUMAN(targetEntity) && 
		AI::GET_IS_TASK_ACTIVE(targetEntity, 399))
	{
		currentTarget = targetEntity;
		return true;
	}
	else {
		currentTarget = NULL;
		return false;
	}
}

void AttachHogtiedController::preparePrompt(Prompt* prompt)
{
	prompt->setTargetEntity(currentTarget);
}

void AttachHogtiedController::execute()
{
	Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(currentTarget, true, 0);
	Vector3 targetGroundPos;
	getGroundPos(targetPos, &targetGroundPos);

	addRope(new AttachedRope(targetGroundPos, currentTarget, "SKEL_NECK0", 3.0f));
	PED::SET_ENABLE_HANDCUFFS(lassoTarget, 1, 0);
	WEAPON::REMOVE_ALL_PED_WEAPONS(lassoTarget, 0, 0);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(lassoTarget, 1);
}