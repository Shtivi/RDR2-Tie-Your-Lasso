#include "Main.h"

Prompt* promptAttachToGround;
Prompt* promptAttachHogtied;
Prompt* promptKick;

void initActions()
{
	promptAttachToGround = new Prompt("Attach To Ground", GAMEPLAY::GET_HASH_KEY("INPUT_LOOK_BEHIND"), SemiHold);
	promptAttachHogtied = new Prompt("Attach To Ground", GAMEPLAY::GET_HASH_KEY("INPUT_LOOK_BEHIND"), SemiHold);
	promptKick = new Prompt("Kick", GAMEPLAY::GET_HASH_KEY("INPUT_NEXT_CAMERA"), Hold);
}

void handleActions()
{
	Ped player = PLAYER::PLAYER_PED_ID();
	Entity targetEntity;
	Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
	Vector3 playerGroundPos;
	Vector3 targetPos;

	getGroundPos(playerPos, &playerGroundPos);

	if (lassoTarget != 0 && ENTITY::IS_ENTITY_A_PED(lassoTarget) && !PED::IS_PED_ON_MOUNT(player))
	{
		promptAttachToGround->show();
		if (promptAttachToGround->isActivatedByPlayer())
		{
			AttachedRope* rope = new AttachedRope(playerGroundPos, lassoTarget, "SKEL_NECK0", 0);
			addRope(rope);
		}
	}
	else
	{
		promptAttachToGround->hide();
	}

	if (PLAYER::GET_PLAYER_TARGET_ENTITY(PLAYER::PLAYER_ID(), &targetEntity))
	{
		if (ENTITY::IS_ENTITY_A_PED(targetEntity) && PED::IS_PED_HUMAN(targetEntity) && AI::GET_IS_TASK_ACTIVE(targetEntity, 399))
		{
			promptAttachHogtied->setTargetEntity(targetEntity);
			promptAttachHogtied->show();
			
			targetPos = ENTITY::GET_ENTITY_COORDS(targetEntity, true, 0);
			Vector3 targetGroundPos;
			getGroundPos(targetPos, &targetGroundPos);

			if (promptAttachHogtied->isActivatedByPlayer())
			{
				addRope(new AttachedRope(targetGroundPos, targetEntity, "SKEL_NECK0", 2.0f));
			}

			if (distanceBetweenEntities(targetEntity, player) <= 2)
			{
				promptKick->setTargetEntity(targetEntity);
				promptKick->show();

				if (promptKick->isActivatedByPlayer())
				{
					const float FORCE_FACTOR = 2.5f;
				
					//Vector3 force = ENTITY::GET_ENTITY_FORWARD_VECTOR(player);
				
					float distance = max(distanceBetweenEntities(player, targetEntity), 1);
					Vector3 force;
					force.x = ((targetGroundPos.x - playerGroundPos.x) / distance) * FORCE_FACTOR;
					force.y = ((targetGroundPos.y - playerGroundPos.y) / distance) * FORCE_FACTOR;
					force.z = ((targetGroundPos.z - playerGroundPos.z) / distance) * FORCE_FACTOR;

					ENTITY::APPLY_FORCE_TO_ENTITY(targetEntity, 1, force.x, force.y, force.z, 0, 0, 0, 0, false, true, true, false, true);
				}
			}
			else
			{
				promptKick->hide();
			}
		}
		else
		{
			promptKick->hide();
			promptAttachHogtied->hide();
		}
	}
	else
	{
		promptAttachHogtied->hide();
		promptKick->hide();
	}
}