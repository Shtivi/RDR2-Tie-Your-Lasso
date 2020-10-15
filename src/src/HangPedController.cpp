#include "Main.h"

HangPedController::HangPedController() : 
	BaseActionsController() 
{
	victim = NULL;
	hangFrom = Vector3();
}

Prompt* HangPedController::createActionPrompt()
{
	return new Prompt("Hang", GAMEPLAY::GET_HASH_KEY("INPUT_NEXT_CAMERA"), PromptMode::SemiHold);
}

bool HangPedController::isAbleToExecute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Ped carriedPed = findCarriedPedBy(player);

	if (!carriedPed)
	{
		reset();
		return false;
	}


	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, 1, 0);
	RaycastResult ray = raycast(playerPos, getUpVector(player), 10, RaycastIntersectionOptions::Map);
	
	float dist = distance(playerPos, ray.hitPos);
	if (dist < 0.8f || dist > 3)
	{
		reset();
		return false;
	}

	victim = carriedPed;
	hangFrom = ray.hitPos;
	return true;
}

void HangPedController::preparePrompt(Prompt* prompt)
{
	prompt->setTargetEntity(victim);
}

void HangPedController::execute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, 1, 0);
	float length = distance(hangFrom, victim) - 0.15f;
	addRope(new AttachedRope(hangFrom, victim, "SKEL_NECK0", length));
}

void HangPedController::reset()
{
	victim = 0;
	hangFrom = Vector3();
}
