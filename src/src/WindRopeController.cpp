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

	if (findCarriedPedBy(player)) 
	{
		return false;
	}

	rope = getClosestRopeWithin(playerPos, 1.5f);
	return rope != NULL && rope->canWind();
}

void WindRopeController::preparePrompt(Prompt* prompt)
{
	//debug(distanceBetweenEntities(rope->getBase(), rope->getAttached()));
	//if (distanceBetweenEntities(rope->getBase(), rope->getAttached()) < 3)
	//{
	//	debug("prompt");
	//	prompt->setTargetEntity(rope->getAttached());
	//	prompt->setControl(GAMEPLAY::GET_HASH_KEY("INPUT_NEXT_CAMERA"));
	//}
	//else
	//{
	//	prompt->setTargetEntity(NULL);
	//	prompt->setControl(GAMEPLAY::GET_HASH_KEY("INPUT_SURRENDER"));
	//}
}

void WindRopeController::execute()
{
	rope->startWinding();
}

void WindRopeController::stop() 
{
	rope->stopWinding();
}