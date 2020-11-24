#include "Main.h"

PullGallowLeverController::PullGallowLeverController() : BaseActionsController() 
{
	gallows = NULL;
}

Prompt* PullGallowLeverController::createActionPrompt()
{
	return new Prompt("Push Lever", GAMEPLAY::GET_HASH_KEY("INPUT_RELOAD"), PromptMode::SemiHold);
}

bool PullGallowLeverController::isAbleToExecute()
{
	Hash pedWeapon;
	if (WEAPON::GET_CURRENT_PED_WEAPON(player, &pedWeapon, 0, 0, 0) && pedWeapon != WeaponHash::WEAPON_UNARMED || findCarriedPedBy(player))
	{
		return false;
	}

	Vector3 playerPos = entityPos(player);
	gallows = Gallows::fromPosition(playerPos);

	return gallows != NULL && distance(gallows->getPosition(), playerPos) < 1.5f;
}

void PullGallowLeverController::preparePrompt(Prompt* prompt)
{
	if (gallows->isLeverPulled())
	{
		prompt->setText(gallows->getLeverMode() == Push ? "Pull Back" : "Push back");
	}
	else
	{
		prompt->setText(gallows->getLeverMode() == Push ? "Push Lever" : "Pull Lever");
	}
}

void PullGallowLeverController::execute()
{
	if (gallows->isLeverPulled())
	{
		gallows->reset(player);
	}
	else 
	{
		gallows->pullLever(player);
	}
}