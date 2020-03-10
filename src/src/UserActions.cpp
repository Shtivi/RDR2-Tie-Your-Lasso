#include "Main.h"

Prompt promptAttachToGround("Attach To Ground", GAMEPLAY::GET_HASH_KEY("INPUT_RELOAD"));
Prompt promptPushPed("Kick ped", GAMEPLAY::GET_HASH_KEY("INPUT_INSPECT"));

void handleActions()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Entity playerTargetEntity = 0;
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 groundPos;
	Vector3 targetPos;
	float groundZ;

	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(playerPos.x, playerPos.y, playerPos.z, &groundZ, false);
	groundPos.x = playerPos.x;
	groundPos.y = playerPos.y;
	groundPos.z = groundZ;

	if (lassoTarget != 0 && ENTITY::IS_ENTITY_A_PED(lassoTarget) && !PED::IS_PED_ON_MOUNT(player))
	{
		targetPos = ENTITY::GET_ENTITY_COORDS(lassoTarget, true, 0);

		/*if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerPos.x, playerPos.y, playerPos.z, targetPos.x, targetPos.y, targetPos.z, true) <= 3)
		{
			promptAttachToGround.setTargetEntity(lassoTarget);
			promptAttachToGround.setPriority(1);

		}
		else
		{
			promptAttachToGround.setTargetEntity(NULL);
			promptAttachToGround.setPriority(1);
		}*/

		promptAttachToGround.show();

		if (promptAttachToGround.isActivatedByPlayer())
		{
			AttachedRope* rope = new AttachedRope(groundPos, lassoTarget, "SKEL_NECK0", 0);
			addRope(rope);
		}
	}
	else
	{
		promptAttachToGround.hide();
	}

	Entity targetEntity;
	if (PLAYER::GET_PLAYER_TARGET_ENTITY(PLAYER::PLAYER_ID(), &targetEntity))
	{
		if (ENTITY::IS_ENTITY_A_PED(targetEntity) && PED::IS_PED_HUMAN(targetEntity) && AI::GET_IS_TASK_ACTIVE(targetEntity, 399))
		{
			promptPushPed.setTargetEntity(targetEntity);
			promptPushPed.setPriority(1);
			promptPushPed.show();
		}
		else
		{
			promptPushPed.hide();
		}
	}
	else
	{
		promptPushPed.hide();
	}
}