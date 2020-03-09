#include "Main.h"

Entity lassoTarget = 0;
bool isLassoEquiped = false;

void updateLasso() 
{
	Player playerId = PLAYER::PLAYER_ID();
	Ped player = PLAYER::PLAYER_PED_ID();
	Entity target;
	Hash playerCurrWeapon;
	Hash aimControlHash = GAMEPLAY::GET_HASH_KEY("INPUT_AIM");

	if (WEAPON::GET_CURRENT_PED_WEAPON(player, &playerCurrWeapon, true, 0, false) && 
		playerCurrWeapon == GAMEPLAY::GET_HASH_KEY("WEAPON_LASSO"))
	{
		isLassoEquiped = true;

		// Finish if already holding someone on lasso.
		if (CONTROLS::IS_CONTROL_PRESSED(0, aimControlHash) && lassoTarget != 0)
		{
			return;
		}

		// Reset target when releasing the aim button.
		if (CONTROLS::IS_DISABLED_CONTROL_JUST_RELEASED(0, aimControlHash))
		{
			lassoTarget = 0;
			return;
		}

		// Identify when the player shoots his lasso, and keep the target till released.
		if (PED::IS_PED_SHOOTING(player))
		{
			if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(playerId, &target)) 
			{
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