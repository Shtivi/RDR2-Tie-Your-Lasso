#include "Main.h"

WindRopeController::WindRopeController()
	: BaseActionsController(ActivationType::HOLD)
{
	rope = NULL;
}

Prompt* WindRopeController::createActionPrompt()
{
	return new Prompt("Wind rope", GAMEPLAY::GET_HASH_KEY("INPUT_SURRENDER"), Hold);
}

bool WindRopeController::isAbleToExecute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, 1, 0);

	if (findCarriedPedBy(player) || PED::IS_PED_ON_MOUNT(player)) 
	{
		return false;
	}

	rope = getClosestRopeWithin(playerPos, 1.5f);
	return rope != NULL && rope->canWind();
}

void WindRopeController::execute()
{
	if (rope)
	{
		rope->startWinding();
	}
}

void WindRopeController::stop() 
{
	if (rope)
	{
		rope->stopWinding();
	}
}