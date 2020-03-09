//#include "Main.h"
//
//bool godmode = false;
//bool allstamina = false;		
//bool allabilty = false;
//bool neverwanted = false;
//bool Invinciblehourse = false;
//bool UnlimStaminahourse = false;
//bool superjump = false;
//bool ragdoll = true;
//bool SuperRun = false;
//void SetPlayerHorseInvincible(bool set)
//{
//	Ped playerPed = PLAYER::PLAYER_PED_ID();
//	if (PED::IS_PED_ON_MOUNT(playerPed))
//	{
//		Ped horse = PED::GET_MOUNT(playerPed);
//		ENTITY::SET_ENTITY_INVINCIBLE(horse, set);
//	}
//}
//void setHorseUnlimStamina(bool set)
//{
//	if (set)
//	{
//		Ped playerPed = PLAYER::PLAYER_PED_ID();
//		if (PED::IS_PED_ON_MOUNT(playerPed))
//		{
//			Ped horse = PED::GET_MOUNT(playerPed);
//			PED::SET_PED_STAMINA(horse, 100.0);
//		}
//	}
//}
//void clear()
//{
//	Ped playerPed = PLAYER::PLAYER_PED_ID();
//	PURSUIT::CLEAR_CURRENT_PURSUIT();
//	PURSUIT::SET_PLAYER_WANTED_INTENSITY(playerPed, 0);
//	PURSUIT::SET_PLAYER_PRICE_ON_A_HEAD(playerPed, 0);
//}
//void Self() {
//	if(godmode)
//		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), godmode);
//	if(allstamina)
//		PLAYER::RESTORE_PLAYER_STAMINA(PLAYER::PLAYER_ID(), 100.0);
//	if(allabilty)
//		PLAYER::RESTORE_SPECIAL_ABILITY(PLAYER::PLAYER_ID(), -1, FALSE);
//	if(superjump)
//		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
//	
//	setHorseUnlimStamina(UnlimStaminahourse);
//	SetPlayerHorseInvincible(Invinciblehourse);
//	
//	if (neverwanted)
//	{
//		PURSUIT::CLEAR_CURRENT_PURSUIT();
//		PURSUIT::SET_PLAYER_PRICE_ON_A_HEAD(PLAYER::PLAYER_ID(), 0);
//		PURSUIT::SET_PLAYER_WANTED_INTENSITY(PLAYER::PLAYER_ID(), 0);
//		PLAYER::SET_WANTED_LEVEL_MULTIPLIER(0.0);
//	}	
//	
//	if (!ragdoll)
//	{
//		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), FALSE);
//		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), FALSE);
//	}
//	else
//	{
//		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), TRUE);
//		PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), TRUE);
//	}
//
//
//}
//void clone()
//{
//	PED::CLONE_PED(PLAYER::PLAYER_PED_ID(), ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID()), 0, 1);
//}
//void savebrowndoggy()
//{
//	Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
//	set_entity_as_mission(veh, TRUE);// makes the game things its needed
//}