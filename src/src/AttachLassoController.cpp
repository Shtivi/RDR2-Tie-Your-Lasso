#include "Main.h"

AttachLassoController::AttachLassoController()
	: BaseActionsController()
{
	lassoTarget = NULL;
}

Prompt* AttachLassoController::createActionPrompt()
{
	return new Prompt("Attach To Ground", GAMEPLAY::GET_HASH_KEY("INPUT_LOOK_BEHIND"), SemiHold);
}

void AttachLassoController::preparePrompt(Prompt* prompt)
{
	if (distanceBetweenEntities(player, lassoTarget) < 3.1f)
	{
		prompt->setTargetEntity(lassoTarget);
	}
}

bool AttachLassoController::isAbleToExecute()
{
	Hash playerCurrWeapon;

	if (WEAPON::GET_CURRENT_PED_WEAPON(player, &playerCurrWeapon, true, 0, false) &&
		playerCurrWeapon == GAMEPLAY::GET_HASH_KEY("WEAPON_LASSO"))
	{
		lassoTarget = PED::_0xB65A4DAB460A19BD(PLAYER::PLAYER_PED_ID()); // _GET_LASSO_TARGET
	}
	else 
	{
		lassoTarget = NULL;
	}

	return lassoTarget != 0 && ENTITY::IS_ENTITY_A_PED(lassoTarget) && !PED::IS_PED_ON_MOUNT(player);
}

void AttachLassoController::execute()
{
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 playerGroundPos;
	getGroundPos(playerPos, &playerGroundPos);

	AttachedRope* rope = new AttachedRope(playerGroundPos, lassoTarget, "SKEL_NECK0", 0);
	addRope(rope);

	AI::CLEAR_PED_TASKS(lassoTarget, 0, 0);
	WEAPON::REMOVE_ALL_PED_WEAPONS(lassoTarget, 0, 0);
	AI::TASK_STAND_STILL(lassoTarget, -1);
}