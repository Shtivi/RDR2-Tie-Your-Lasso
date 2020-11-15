#include "Main.h"

HangPedController::HangPedController() : 
	BaseActionsController(ActivationType::TAP, 1) 
{
	victim = NULL;
	hangFrom = Vector3();
	shouldDrop = false;
}

Prompt* HangPedController::createActionPrompt()
{
	return new Prompt("Hang", GAMEPLAY::GET_HASH_KEY("INPUT_NEXT_CAMERA"), PromptMode::SemiHold);
}

bool HangPedController::isAbleToExecute()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Ped carriedPed = findCarriedPedBy(player);
	Ped targetEntity = findHogtiedTargetEntity();

	if (!carriedPed)
	{
		if (!targetEntity)
		{
			reset();
			return false;
		} 
		else
		{
			shouldDrop = false;
			victim = targetEntity;
		}
	}
	else
	{
		shouldDrop = true;
		victim = carriedPed;
	}

	if (!PED::IS_PED_HUMAN(victim))
	{
		return false;
	}

	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, 1, 0);
	RaycastResult ray = raycast(playerPos, getUpVector(player), 100, RaycastIntersectionOptions::Map);
	
	float dist = distance(playerPos, ray.hitPos) + 0.1f;
	if (dist < 0.8f || dist > 5)
	{
		reset();
		return false;
	}
	hangFrom = ray.hitPos;

	return true;
}

void HangPedController::preparePrompt(Prompt* prompt)
{
	prompt->setTargetEntity(victim);
}

void HangPedController::execute()
{
	Vector3* pinTo = getSafeCoordForPed(playerPos() + (ENTITY::GET_ENTITY_FORWARD_VECTOR(player) * 4));
	Vector3 placeOn = playerPos();
	if (!pinTo)
	{
		pinTo = &placeOn;
	}

	AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(victim, 1);
	WEAPON::REMOVE_ALL_PED_WEAPONS(victim, 0, 0);

	Vector3 goTo = playerPos() + getForwardVector(player) * 2;
	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	if (shouldDrop)
	{
		AI::_0xC7F0B43DCDC57E3D(0, victim, placeOn.x, placeOn.y, placeOn.z, 10.0f, 1);
	}
	AI::TASK_GO_STRAIGHT_TO_COORD(0, goTo.x, goTo.y, goTo.z, 1, 2500, ENTITY::GET_ENTITY_HEADING(player), 0, 0);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(player, seq);

	if (shouldDrop)
	{
		WAIT(2000);
	} 
	else
	{
		WAIT(500);
	}

	CAM::DO_SCREEN_FADE_OUT(300);
	WAIT(2000);
	AI::CLEAR_PED_TASKS_IMMEDIATELY(victim, 0, 0);

	float length = distance(hangFrom, victim) + 0.75f;
	MultiVertexRope* rope = new MultiVertexRope(new AttachedRope(hangFrom, victim, "SKEL_NECK0", length));
	rope->pinTo(*pinTo);
	addRope(rope);
	AI::TASK_STAND_STILL(victim, -1);
	ENTITY::SET_ENTITY_COORDS(victim, placeOn.x, placeOn.y, placeOn.z, 1, 1, 1, false);
	PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(victim, true);
	PED::SET_ENABLE_HANDCUFFS(victim, true, 0);

	CAM::DO_SCREEN_FADE_IN(300);
	WAIT(1000);
}

void HangPedController::reset()
{
	victim = 0;
	hangFrom = Vector3();
	shouldDrop = false;
}
