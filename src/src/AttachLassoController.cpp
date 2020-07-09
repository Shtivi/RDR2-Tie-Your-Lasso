#include "Main.h"

AttachLassoController::AttachLassoController()
	: BaseActionsController()
{
}

Prompt* AttachLassoController::createActionPrompt()
{
	return new Prompt("Attach To Ground", GAMEPLAY::GET_HASH_KEY("INPUT_LOOK_BEHIND"), SemiHold);
}

bool AttachLassoController::isAbleToExecute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 playerGroundPos;
	getGroundPos(playerPos, &playerGroundPos);

	return lassoTarget != 0 && ENTITY::IS_ENTITY_A_PED(lassoTarget) && !PED::IS_PED_ON_MOUNT(player);
}

void AttachLassoController::execute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 playerGroundPos;
	getGroundPos(playerPos, &playerGroundPos);

	AttachedRope* rope = new AttachedRope(playerGroundPos, lassoTarget, "SKEL_NECK0", 0);
	addRope(rope);

	PED::SET_ENABLE_HANDCUFFS(lassoTarget, 1, 0);
	AI::CLEAR_PED_TASKS(lassoTarget, 0, 0);
	WEAPON::REMOVE_ALL_PED_WEAPONS(lassoTarget, 0, 0);
	AI::TASK_STAND_STILL(lassoTarget, -1);
}