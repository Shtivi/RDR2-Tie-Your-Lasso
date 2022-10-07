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

	return lassoTarget != 0 && ENTITY::IS_ENTITY_A_PED(lassoTarget) && PED::IS_PED_ON_FOOT(player) && PED::IS_PED_HUMAN(lassoTarget);
}

void AttachLassoController::execute()
{
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	AttachedRope* rope;
	Vector3 hitchingCoords;
	getGroundPos(playerPos, &hitchingCoords);

	int hitchingScenarioPoint = AI::_0xF533D68FF970D190(playerPos.x, playerPos.y, playerPos.z, GAMEPLAY::GET_HASH_KEY("PROP_HITCHINGPOST"), 3, 1, 1);
	if (hitchingScenarioPoint)
	{
		Entity hitchingPostObject = invoke<Entity>(0x7467165EE97D3C68, hitchingScenarioPoint);
		if (hitchingPostObject) 
		{
			hitchingCoords = entityPos(hitchingPostObject);
			hitchingCoords.z += 0.8;
		}
	}
	
	rope = new AttachedRope(hitchingCoords, lassoTarget, "SKEL_NECK0", 0);
	addRope(rope);

	AI::CLEAR_PED_TASKS(lassoTarget, 0, 0);
	WEAPON::REMOVE_ALL_PED_WEAPONS(lassoTarget, 0, 0);
	AI::TASK_STAND_STILL(lassoTarget, -1);

	if (PED::IS_PED_HUMAN(lassoTarget))
	{
		PED::SET_ENABLE_HANDCUFFS(lassoTarget, 1, 0);
		//PED::_0x1902C4CFCC5BE57C(lassoTarget, 0x222D41E5);
		//PED::_0xCC8CA3E88256E58F(lassoTarget, false, true, true, true, false);
		PED::SET_PED_COMBAT_MOVEMENT(lassoTarget, 0);
	}
}