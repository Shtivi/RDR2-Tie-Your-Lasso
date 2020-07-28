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

void Initialize() 
{
	initActions();
}

//Ped ped = NULL;

void main()
{
	Initialize();

	while (true)
	{
		updateLasso();
		handleActions();
		UpdateRopes();

		if (IsKeyJustUp(VK_KEY_Z))
		{
			Ped player = PLAYER::PLAYER_PED_ID();
			//CASH::PLAYER_ADD_CASH(8000, 15000);
			//Vector3 pos = add(&ENTITY::GET_ENTITY_COORDS(player, 1, 0), &multiply(&ENTITY::GET_ENTITY_FORWARD_VECTOR(player), 8));
			//getGroundPos(pos, &pos);
			//createProp("s_ufo02x", pos);

			/*Ped ped = createPed("G_M_M_UniBanditos_01", pos);
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(ped, 1);
			DECORATOR::DECOR_SET_INT(ped, "honor_override", 0);*/
			//Vector3 propPos = PED::GET_PED_BONE_COORDS(ped, 14283, 0, 0, 0);
			//Vector3 propPos = pos;
			//Object prop = createProp("noose01x_Rope_03", propPos);
			//ENTITY::ATTACH_ENTITY_TO_ENTITY_PHYSICALLY(ped, prop, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 999999, 1, 0, 1, 1, 2, 0, 0, 0);
			//ENTITY::ATTACH_ENTITY_TO_ENTITY(ped, prop, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0);
		}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}