/*
	THIS FILE IS A PART OF RDR 2 SCRIPT HOOK SDK
				http://dev-c.com
			(C) Alexander Blade 2019
*/

#include "Main.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Ped player;

void Initialize() 
{
	player = PLAYER::PLAYER_PED_ID();
	DECORATOR::DECOR_REGISTER("TYL_hanged", 3);

	initActions();
}

void main()
{
	Initialize();

	while (true)
	{
		player = PLAYER::PLAYER_PED_ID();

		handleActions();
		UpdateRopes();

		if (true && IsKeyJustUp(VK_F11)) 

		{
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(player, GAMEPLAY::GET_HASH_KEY("weapon_revolver_navy"), 30, 1, 1);
			showSubtitle("navy");
			//Vector3 pos = add(&ENTITY::GET_ENTITY_COORDS(player, 1, 0), &multiply(&ENTITY::GET_ENTITY_FORWARD_VECTOR(player), 5));
			//getGroundPos(pos, &pos);
			//Ped ped = createPed("CS_ColmODriscoll", pos);
			//DECORATOR::DECOR_SET_INT(ped, "honor_override", -10);
			//ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);

			//Vector3 pos2 = add(&ENTITY::GET_ENTITY_COORDS(player, 1, 0), &multiply(&ENTITY::GET_ENTITY_FORWARD_VECTOR(player), 5));
			//getGroundPos(pos2, &pos2);
			//Ped ped2 = createPed("CS_exconfedsleader_01", pos2);
			//DECORATOR::DECOR_SET_INT(ped2, "honor_override", -10);
			//ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped2, 1);
		}

		//if (!true) {
		//	Vector3 pos = entityPos(player);
		//	Hash weaponHash;
		//	WEAPON::GET_CURRENT_PED_WEAPON(player, &weaponHasbh, 0, 0, 0);
		//	if (weaponHash != WeaponHash::WEAPON_UNARMED) {
		//		Entity e;
		//		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &e) && distanceBetweenEntities(player, e) < 10) {
		//			if (IsKeyJustUp(VK_KEY_Z)) {
		//				//showSubtitle(to_string(ENTITY::GET_ENTITY_MODEL(e)).c_str());
		//				//playSoundFromEntity(e, "HIDEOUT_HDR_Sounds", "OPEN_BARN_DOORS");
		//			} 
		//			debug(entityPos(e));
		//		}
		//		else 
		//		{
		//			RaycastResult ray = raycastCrosshair(40, Map);
		//			debug(ray.hitPos);
		//		}
		//	}
		//	else {
		//		debug(pos);
		//	}
		//}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}

void debug(const char* text) {
	UI::DRAW_TEXT((char*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text), 0, 0);
}

void debug(string text) {
	debug(text.c_str());
}

void debug(Vector3 pos) {
	stringstream str;
	str << pos.x << ", " << pos.y << ", " << pos.z;
	debug(str.str());
}

void debug(float f) {
	debug(to_string(f));
}

void debug(int n) {
	debug(to_string(n));
}

void debug(bool b) {
	debug(to_string(b));
}

void showSubtitle(const char* text)
{
	UILOG::_0xFA233F8FE190514C((Any*)UI::_CREATE_VAR_STRING(10, "LITERAL_STRING", text)); // _UILOG_SET_CACHED_OBJECTIVE
	UILOG::_0xE9990552DEC71600(); // _UILOG_PRINT_CACHED_OBJECTIVE
	UILOG::_0xDFF0D417277B41F8(); // _UILOG_CLEAR_CACHED_OBJECTIVE
}

const char* to_string(Vector3 position)
{
	stringstream str;
	str << position.x << ", " << position.y << ", " << position.z;
	return str.str().c_str();
}