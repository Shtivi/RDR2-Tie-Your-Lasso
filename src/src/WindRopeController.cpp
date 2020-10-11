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
	rope = getClosestRopeWithin(playerPos, 1.5f);
	return rope != NULL && rope->canWind();
}

void WindRopeController::execute()
{
	rope->startWinding();
}

void WindRopeController::stop() 
{
	rope->stopWinding();
}