#include "Main.h"

KickPedController::KickPedController()
	: BaseActionsController()
{
	currentTarget = NULL;
}

Prompt* KickPedController::createActionPrompt()
{
	return new Prompt("Kick", GAMEPLAY::GET_HASH_KEY("INPUT_NEXT_CAMERA"), Hold);
}

bool KickPedController::isAbleToExecute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Entity targetEntity;

	if (PLAYER::GET_PLAYER_TARGET_ENTITY(PLAYER::PLAYER_ID(), &targetEntity) &&
		ENTITY::IS_ENTITY_A_PED(targetEntity) &&
		PED::IS_PED_HUMAN(targetEntity) &&
		AI::GET_IS_TASK_ACTIVE(targetEntity, 399) &&
		distanceBetweenEntities(player, targetEntity) <= KICK_MAX_DISTANCE)
	{
		currentTarget = targetEntity;
		return true;
	}
	else {
		currentTarget = NULL;
		return false;
	}
}

void KickPedController::preparePrompt(Prompt* prompt)
{
	prompt->setTargetEntity(currentTarget);
}

void KickPedController::execute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 playerGroundPos;
	getGroundPos(playerPos, &playerGroundPos);

	Vector3 targetPos = ENTITY::GET_ENTITY_COORDS(currentTarget, true, 0);
	Vector3 targetGroundPos;
	getGroundPos(targetPos, &targetGroundPos);

	const float FORCE_FACTOR = 2.5f;

	float distance = distanceBetweenEntities(player, currentTarget);
	float normalizedDistance = max(distance, 0.1f);

	Vector3 force;
	force.x = ((targetGroundPos.x - playerGroundPos.x) / distance) * FORCE_FACTOR;
	force.y = ((targetGroundPos.y - playerGroundPos.y) / distance) * FORCE_FACTOR;
	force.z = ((targetGroundPos.z - playerGroundPos.z) / distance) * FORCE_FACTOR;

	ENTITY::APPLY_FORCE_TO_ENTITY(currentTarget, 1, force.x, force.y, force.z, 0, 0, 0, 0, false, true, true, false, true);
}