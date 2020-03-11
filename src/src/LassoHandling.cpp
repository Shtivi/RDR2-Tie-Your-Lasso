#include "Main.h"

Entity lassoTarget = 0;
bool isLassoEquiped = false;
bool wasHoldingLastFrame = true;

void updateLasso() 
{
	Player playerId = PLAYER::PLAYER_ID();
	Ped player = PLAYER::PLAYER_PED_ID();
	Entity target;
	Hash playerCurrWeapon;
	Hash aimControl = GAMEPLAY::GET_HASH_KEY("INPUT_AIM");

	if (WEAPON::GET_CURRENT_PED_WEAPON(player, &playerCurrWeapon, true, 0, false) && 
		playerCurrWeapon == GAMEPLAY::GET_HASH_KEY("WEAPON_LASSO"))
	{

		isLassoEquiped = true;

		// Finish if already holding someone on lasso.
		if (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, aimControl) && lassoTarget != 0)
		{
			UI::DRAW_TEXT((char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", "holding"), 0, 0);
			return;
		}

		// Reset target when releasing the aim button.
		if (CONTROLS::IS_CONTROL_RELEASED(0, aimControl) && wasHoldingLastFrame)
		{
			UI::DRAW_TEXT((char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", "just released"), 0, 0);
			wasHoldingLastFrame = false;
			lassoTarget = 0;
			return;
		}

		// Identify when the player shoots his lasso, and keep the target till released.
		if (PED::IS_PED_SHOOTING(player))
		{
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(playerId, &target)) 
			{
				UI::DRAW_TEXT((char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", "just holded"), 0, 0);
				wasHoldingLastFrame = true;
				lassoTarget = target;
			}
		}
	}
	else
	{
		isLassoEquiped = false;
		lassoTarget = 0;
	}
}