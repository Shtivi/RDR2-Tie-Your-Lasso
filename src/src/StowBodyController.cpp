#include "Main.h"

StowBodyController::StowBodyController()
{
	wagon = NULL;
}

Prompt* StowBodyController::createActionPrompt()
{
	return new Prompt("Stow", GAMEPLAY::GET_HASH_KEY("INPUT_RELOAD"), PromptMode::SemiHold);
}

bool StowBodyController::isAbleToExecute()
{
	if (!findCarriedPedBy(player))
	{
		return false;
	}

	wagon = getClosestVehicle(player);
	if (wagon == NULL)
	{
		return false;
	}

	Vector3 edgePosition = getRelativeEntityCoords(wagon, -1);

	if (!VEHICLE::IS_VEHICLE_STOPPED(wagon) || distance(edgePosition, player) > 1.0f)
	{
		return false;
	}

	return true;
}

void StowBodyController::preparePrompt(Prompt* prompt)
{
	prompt->setTargetEntity(findCarriedPedBy(player));
}


void StowBodyController::execute()
{
	Ped body = findCarriedPedBy(player);
	CAM::DO_SCREEN_FADE_OUT(100);
	WAIT(100);
	ENTITY::DETACH_ENTITY(body, 0, 0);
	Vector3 wagonPos = ENTITY::GET_ENTITY_COORDS(wagon, 1, 0);
	ENTITY::SET_ENTITY_COORDS(body, wagonPos.x, wagonPos.y, wagonPos.z + 0.1, 0, 0, 0, 0);

	if (ENTITY::GET_ENTITY_HEALTH(body) > 0)
	{
		AI::_0x42AC6401ABB8C7E5(body, 0, 0);
	}

	WAIT(200);
	CAM::DO_SCREEN_FADE_IN(300);
}