#include "Main.h"

int promptAttachToGround;

void initializeActions()
{
	const char* text = UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", "Attach To Ground");
	promptAttachToGround = UI::_0x29FA7910726C3889(GAMEPLAY::GET_HASH_KEY("INPUT_RELOAD"), (Any*)text, 6, 1, 1, -1);
}

void handleActions()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 groundPos;
	float groundZ;

	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerPos.x, playerPos.y, playerPos.z, &groundZ, false);
	groundPos.x = playerPos.x;
	groundPos.y = playerPos.y;
	groundPos.z = groundZ;

	if (lassoTarget != 0 && ENTITY::IS_ENTITY_A_PED(lassoTarget) && !PED::IS_PED_ON_MOUNT(player)) 
	{
		// show prompt
		UI::_0x71215ACCFDE075EE(promptAttachToGround, 1);
		UI::_0x8A0FB4D03A630D21(promptAttachToGround, 1);
		UI::_0x2F11D3A254169EA4(promptAttachToGround, UI::_0xB796970BD125FCE8(lassoTarget), 0);

		if (CONTROLS::IS_DISABLED_CONTROL_JUST_RELEASED(0, GAMEPLAY::GET_HASH_KEY("INPUT_RELOAD")))
		{
			createAttachedRope(groundPos, lassoTarget, "SKEL_NECK0", 0);
		}
	}
	else
	{
		UI::_0x71215ACCFDE075EE(promptAttachToGround, 0);
		UI::_0x8A0FB4D03A630D21(promptAttachToGround, 0);
	}
}