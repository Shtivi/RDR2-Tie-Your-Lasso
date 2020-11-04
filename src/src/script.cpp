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

		if (IsKeyJustUp(VK_KEY_Z))
		{
			//Vector3 pos = add(&ENTITY::GET_ENTITY_COORDS(player, 1, 0), &multiply(&ENTITY::GET_ENTITY_FORWARD_VECTOR(player), 13));
			//getGroundPos(pos, &pos);
			//Ped ped = createPed("G_M_M_UniBanditos_01", pos);
			//PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
			//DECORATOR::DECOR_SET_INT(ped, "honor_override", 0);

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
		}

		if (IsKeyJustUp(VK_KEY_X)) 
		{
			//Vector3 pos = add(&ENTITY::GET_ENTITY_COORDS(player, 1, 0), &multiply(&ENTITY::GET_ENTITY_FORWARD_VECTOR(player), 13));
			//getGroundPos(pos, &pos);
			//createVehicle(VehicleHash::ChuckWagon002X, pos, ENTITY::GET_ENTITY_HEADING(player));
		}

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