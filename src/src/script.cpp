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
	initActions();
}

void main()
{
	Initialize();

	while (true)
	{
		handleActions();
		UpdateRopes();

		//Entity temp;
		//PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &temp);
		//if (temp) {

		//debug(entityPos(temp));
		//}

		if (IsKeyJustUp(VK_KEY_Z))
		{
			//Entity lever;
			//PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &lever);
			//showSubtitle(to_string(ENTITY::GET_ENTITY_MODEL(lever)).c_str());
			//if (lever) {
			//	if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)"script_re@public_hanging@lever"))
			//	{
			//		STREAMING::REQUEST_ANIM_DICT((char*)"script_re@public_hanging@lever");
			//	}
			//	ENTITY::PLAY_ENTITY_ANIM(lever, "pull_lever_deputy_trapdoor_val", "script_re@public_hanging@lever", 1000.0f, false, true, true, 0.28f, 32768);
			//}
			//else {
			//	lever = NULL;
			//}
			//WAIT(2000);
			//PED::_0x7ABBD9E449E0DB00(ped, 0);
			//DECORATOR::DECOR_SET_INT(ped, "honor_override", 0);
			//DECORATOR::DECOR_SET_INT(ped, "loot_item_type1", -963759116);
			//DECORATOR::DECOR_SET_INT(ped, "loot_item_amt1", 1);
			//DECORATOR::DECOR_SET_INT(ped, "loot_item_model1", 0);

			//Vector3 propPos = PED::GET_PED_BONE_COORDS(ped, 14283, 0, 0, 0);
			//Vector3 boneOffset = entityPos(ped) - propPos;
			//Object prop = createProp("s_ropehogtiehands01x", propPos);
			//ENTITY::SET_ENTITY_ROTATION(prop, 0, 100, 1000, 2, 1);
			//ENTITY::ATTACH_ENTITY_TO_ENTITY(prop, ped, 0, 8, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0);
			//ENTITY::ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(ped, prop, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(ped, "SKEL_NECK0"), 0, 0, 0, 0, 0, 0, 0, 0, 100, 1000, 9999999, false, 0, 0, 0, 2, 0, 0, 0);
			// s_ropehogtiehandsmedium01x_a
			// p_ropewall01x
			// p_cs_fusespool01x

			//showSubtitle(to_string(entityPos(player)));

			//Vector3 pos = getGroundPos(entityPos(player) + getForwardVector(player));
			//ENTITY::SET_ENTITY_COORDS(player, pos.x, pos.y, pos.z, 1, 1, 1, 1);

			//showSubtitle(to_string(INTERIOR::GET_INTERIOR_FROM_ENTITY(player)).c_str());


			//playAnimation(player, "gen_shelf_r_b_player", "script_proc@robberies@coach@rhodes", 10000);
			//playAnimation(player, "gen_shelf_r_c_alden", "script_proc@robberies@coach@rhodes", 10000);

			//Vector3 pos1 = entityPos(player) + getForwardVector(player) * 5;
			//Vector3 pos2 = entityPos(player) + getForwardVector(player) * 7;
			//Ped ped = createPed("U_M_M_VhtStationClerk_01", pos1);
			//Ped ped2 = createPed("G_M_M_UniBanditos_01", pos2);
			//WAIT(1000);
			//AI::TASK_TURN_PED_TO_FACE_ENTITY(ped2, ped, 2000, 0, 0, 0);
			//WAIT(3000);
			//playAnimation(ped, "gen_shelf_r_c_alden", "script_proc@robberies@coach@rhodes", 20000);
			//playAnimation(ped2, "gen_shelf_r_b_player", "script_proc@robberies@coach@rhodes", 10000);
			//playAmbientSpeech(player, "VOCAL_FX_BUY_RESPONSE", "0507_U_M_M_VHTSTATIONCLERK_01");
			//showSubtitle(to_string(GAMEPLAY::GET_HASH_KEY("s_gallowlevernbx01x")).c_str());
			/*RaycastResult ray = raycast(entityPos(player), getForwardVector(player), 10, RaycastIntersectionOptions::Everything);
			if (ray.hitEntity && distance(entityPos(player), ray.hitPos) <= 10) {
				if (ENTITY::GET_ENTITY_MODEL(ray.hitEntity) == GAMEPLAY::GET_HASH_KEY("s_gallowlevernbx01x")) {
					showSubtitle("playing");
					if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)"script_re@public_hanging@lever"))
					{
						STREAMING::REQUEST_ANIM_DICT((char*)"script_re@public_hanging@lever");
					}
					ENTITY::PLAY_ENTITY_ANIM(ray.hitEntity, "push_lever_deputy_lever", "script_re@public_hanging@lever", 1000.0f, false, true, true, 0.28f, 32768);
				}
				else {
					showSubtitle(to_string(ENTITY::GET_ENTITY_MODEL(ray.hitEntity)).c_str());
				}
			}
			else {
				showSubtitle("no hit");
			}*/

			Entity lever;
			PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &lever);
			if (lever) {

				if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)"script_re@public_hanging@lever"))
				{
					STREAMING::REQUEST_ANIM_DICT((char*)"script_re@public_hanging@lever");
				}
				showSubtitle("playing");
				//playEntityAnimation(lever, "pull_lever_deputy_trapdoor_std", "script_re@public_hanging@lever", 1000, false, false, 0.28f, 32768);
				//WAIT(2500);
				//ENTITY::STOP_ENTITY_ANIM(lever, "pull_lever_front_trapdoor_std", "script_re@public_hanging@lever", 0);
				//ENTITY::SET_ENTITY_ROTATION(lever, 180, 180, 180, 2, 1);
				ENTITY::SET_ENTITY_COORDS(lever, 2688.43, -1113.97, 51.849, 1, 1, 1, 0);
			}
			//else {
			//	lever = NULL;
			//	showSubtitle("not a lever");
			//}


		}

		if (IsKeyJustUp(VK_KEY_X)) 

		{
			Vector3 pos = add(&ENTITY::GET_ENTITY_COORDS(player, 1, 0), &multiply(&ENTITY::GET_ENTITY_FORWARD_VECTOR(player), 5));
			getGroundPos(pos, &pos);
			Ped ped = createPed("G_M_M_UniBanditos_01", pos);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
			//Vector3 pos = add(&ENTITY::GET_ENTITY_COORDS(player, 1, 0), &multiply(&ENTITY::GET_ENTITY_FORWARD_VECTOR(player), 1));
			//getGroundPos(pos, &pos);
			//Object obj = createProp("s_gallowlevernbx01x", pos);
			//WAIT(1000);
			//playEntityAnimation(obj, "push_lever_deputy_lever", "script_re@public_hanging@lever", 4000.0f, false, false, 0.28f, 32768);
			//playAnimation(player, "push_behind_quick", "script_re@public_hanging@lever", 4000);
			//1666207837
			//vLocal_1051 = { 2688.435f, -1113.967f, 51.049f };
			//if (!STREAMING::HAS_MODEL_LOADED(-1923741333))
			//{
			//	STREAMING::REQUEST_MODEL(-1923741333, false);
			//}
			//RaycastResult ray = raycast(toVector3(-315.222f, 733.837f, 117.955f), toVector3(0, 0, 1), 10);
			//if (ray.hitEntity) {
			//	showSubtitle(to_string(ENTITY::GET_ENTITY_MODEL(ray.hitEntity)).c_str());
			//}
			//else {
			//	showSubtitle("no hit");
			//}
			//int obj = ENTITY::GET_OBJECT_INDEX_FROM_ENTITY_INDEX(ENTITY::_0x4735E2A4BB83D9DA(e));
			//showSubtitle(to_string(ENTITY::_0x4735E2A4BB83D9DA(e)).c_str());
			//if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)"script_re@public_hanging@lever"))
			//{
			//	STREAMING::REQUEST_ANIM_DICT((char*)"script_re@public_hanging@lever");
			//}
			//ENTITY::PLAY_ENTITY_ANIM(obj, "pull_lever_deputy_trapdoor_std", "script_re@public_hanging@lever", 1000.0f, false, true, true, 0.28f, 32768);
			//Vector3 pos = add(&ENTITY::GET_ENTITY_COORDS(player, 1, 0), &multiply(&ENTITY::GET_ENTITY_FORWARD_VECTOR(player), 13));
			//getGroundPos(pos, &pos);
			//createProp("p_trapdoor02x", pos);
			//playAnimation(player, "push_back_unarmed", "script_re@public_hanging@lever", 4000);

			//playAnimation(player, "enter_lever_pull_forward_john", "script_story@fin2@ig@ig4_hang_cleet", 3000);

			//createVehicle(VehicleHash::ChuckWagon002X, pos, ENTITY::GET_ENTITY_HEADING(player));
		}

		/*RaycastResult ray = raycast(entityPos(player) + getUpVector(player) * 0.2f, getForwardVector(player), 10);
		debug( (int)ENTITY::GET_ENTITY_MODEL(ray.hitEntity) );*/
		Entity lever;
		PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &lever);
		if (lever) {
			//debug((int)ENTITY::GET_ENTITY_MODEL(lever));
			debug(ENTITY::IS_ENTITY_PLAYING_ANIM(lever, "script_re@public_hanging@lever", "pull_lever_deputy_trapdoor_std", 2));
			//debug(entityPos(lever));
			//if (IsKeyJustUp(VK_KEY_Z)) {
			//	showSubtitle(to_string((int)ENTITY::GET_ENTITY_MODEL(lever)).c_str());
			//}
		}

		//debug(getForwardVector(player));

		//RaycastResult ray = raycast(entityPos(player), getUpVector(player) * -1, 10, Everything, player);
		//debug(ENTITY::GET_ENTITY_HEIGHT_ABOVE_GROUND(player));


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