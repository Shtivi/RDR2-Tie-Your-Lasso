#include "Main.h"

TieGallowsNooseController::TieGallowsNooseController() : BaseActionsController()
{
	gallows = NULL;
	victim = NULL;
}


Prompt* TieGallowsNooseController::createActionPrompt()
{
	return new Prompt("Tie Noose", GAMEPLAY::GET_HASH_KEY("INPUT_NEXT_CAMERA"), PromptMode::SemiHold);
}

bool TieGallowsNooseController::isAbleToExecute()
{
	victim = findCarriedPedBy(player);
	if (!victim) {
		return false;
	}

	if (!PED::IS_PED_HUMAN(victim) || ENTITY::IS_ENTITY_DEAD(victim))
	{
		return false;
	}

	Vector3 playerPos = entityPos(player);
	gallows = Gallows::fromPosition(playerPos);
	return gallows && gallows->canNooseAtPosition(playerPos);
}

void TieGallowsNooseController::preparePrompt(Prompt* prompt)
{
	prompt->setTargetEntity(victim);
}

void TieGallowsNooseController::execute()
{
	Vector3 goTo = gallows->getPosition();
	Vector3 placeOn = playerPos();

	Object seq;
	AI::OPEN_SEQUENCE_TASK(&seq);
	AI::_0xC7F0B43DCDC57E3D(0, victim, placeOn.x, placeOn.y, placeOn.z, 10.0f, 1);
	AI::TASK_GO_STRAIGHT_TO_COORD(0, goTo.x, goTo.y, goTo.z, 1, 2500, ENTITY::GET_ENTITY_HEADING(player), 0, 0);
	AI::CLOSE_SEQUENCE_TASK(seq);
	AI::TASK_PERFORM_SEQUENCE(player, seq);

	WAIT(2500);
	CAM::DO_SCREEN_FADE_OUT(300);
	gallows->noose(victim, placeOn);
	WAIT(2500);
	CAM::DO_SCREEN_FADE_IN(300);
}