#include "Main.h"

Prompt promptAttachToGround("AttachToGround", GAMEPLAY::GET_HASH_KEY("INPUT_RELOAD"));

void handleActions()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Entity playerTargetEntity = 0;
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 groundPos;
	float groundZ;

	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerPos.x, playerPos.y, playerPos.z, &groundZ, false);
	groundPos.x = playerPos.x;
	groundPos.y = playerPos.y;
	groundPos.z = groundZ;

	if (lassoTarget != 0 && ENTITY::IS_ENTITY_A_PED(lassoTarget) && !PED::IS_PED_ON_MOUNT(player)) 
	{
		if (PLAYER::IS_PLAYER_TARGETTING_ENTITY(PLAYER::PLAYER_ID(), lassoTarget, 0))
		{
			promptAttachToGround.setTargetEntity(lassoTarget);
		}

		promptAttachToGround.isEnabled = false;

		if (promptAttachToGround.isActivatedByPlayer())
		{
			createAttachedRope(groundPos, lassoTarget, "SKEL_NECK0", 0);
		}
	}
	else
	{
		promptAttachToGround.isEnabled = false;
	}

	promptAttachToGround.update();
}