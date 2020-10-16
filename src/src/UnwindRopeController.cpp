#include "Main.h";

UnwindRopeController::UnwindRopeController()
{
	rope = NULL;
}

Prompt* UnwindRopeController::createActionPrompt()
{
	return new Prompt("Unwind rope", GAMEPLAY::GET_HASH_KEY("INPUT_RELOAD"), Hold);
}

bool UnwindRopeController::isAbleToExecute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, 1, 0);

	if (findCarriedPedBy(player) || PED::IS_PED_ON_MOUNT(player))
	{
		return false;
	}

	rope = getClosestRopeWithin(playerPos, 1.5f);
	return rope != NULL && rope->canUnwind();
}

void UnwindRopeController::execute()
{
	rope->startUnwinding();
}

void UnwindRopeController::stop()
{
	rope->stopUnwinding();
}