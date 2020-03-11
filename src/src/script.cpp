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
			Hash model = GAMEPLAY::GET_HASH_KEY("A_F_M_LowerSDTownfolk_01");
			STREAMING::REQUEST_MODEL(model, false);
			while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
			Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
			Ped ped = PED::CREATE_PED(model, playerPos.x + 2, playerPos.y + 2, playerPos.z, 0, false, false, false, false);
			PED::SET_PED_VISIBLE(ped, true);

			ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
		}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}