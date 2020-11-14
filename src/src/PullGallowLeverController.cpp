#include "Main.h"

PullGallowLeverController::PullGallowLeverController() : BaseActionsController() 
{
	gallows = NULL;
}

Prompt* PullGallowLeverController::createActionPrompt()
{
	return new Prompt("Pull Lever", GAMEPLAY::GET_HASH_KEY("INPUT_RELOAD"), PromptMode::SemiHold);
}

bool PullGallowLeverController::isAbleToExecute()
{
	Vector3 playerPos = entityPos(player);
	gallows = Gallow::fromPosition(playerPos);

	return gallows != NULL;
}

void PullGallowLeverController::preparePrompt(Prompt* prompt)
{
	if (gallows->isLeverPulled())
	{
		prompt->setText("Reset");
	}
	else
	{
		prompt->setText("Pull Lever");
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
	//RaycastResult ray = raycast(toVector3(-315.222f, 733.837f, 117.955f), toVector3(0, 0, 1), 10);
	//Entity trapdoor = ray.hitEntity;

	//RaycastResult ray1 = raycast(toVector3(-313.989, 729.185, 117.951f), toVector3(0, 0, 1), 10);
	//Entity trapdoor2 = ray1.hitEntity;

	//RaycastResult ray2 = raycast(toVector3(-315.075, 730.922, 119.411), toVector3(0, 0, 1), 10);
	//Entity lever = ray2.hitEntity;

	//WEAPON::SET_CURRENT_PED_WEAPON(player, WeaponHash::WEAPON_UNARMED, false, 0, 0, 0);
	//Object seq;
	//AI::OPEN_SEQUENCE_TASK(&seq);
	//AI::TASK_GO_STRAIGHT_TO_COORD(0, -314.55, 730.943, 120.621, 1, 5000, ENTITY::GET_ENTITY_HEADING(player), 0, 0);
	//AI::TASK_TURN_PED_TO_FACE_ENTITY(0, lever, 1000, 0, 0, 0);
	//AI::CLOSE_SEQUENCE_TASK(seq);
	//AI::TASK_PERFORM_SEQUENCE(player, seq);

	//if (trapdoor && ENTITY::GET_ENTITY_MODEL(trapdoor) == 2371225963)
	//{
	//	playEntityAnimation(trapdoor, "pull_lever_front_trapdoor_val", "script_re@public_hanging@lever", 1000, false, true, 0.28f, 32768);
	//}

	//if (trapdoor2 && ENTITY::GET_ENTITY_MODEL(trapdoor2) == 2371225963)
	//{
	//	playEntityAnimation(trapdoor2, "pull_lever_front_trapdoor_val", "script_re@public_hanging@lever", 1000, false, true, 0.28f, 32768);
	//}

	//WAIT(500);
	//if (lever && ENTITY::GET_ENTITY_MODEL(lever) == -1539465244) {
	//	playEntityAnimation(lever, "push_lever_deputy_lever", "script_re@public_hanging@lever", 1000.0f, false, true, 0.28f, 32768);
	//}
	//WAIT(300);

	//playAnimation(player, "push_behind_quick", "script_re@public_hanging@lever", 4000);

}