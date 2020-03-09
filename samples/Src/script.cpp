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

void log(const char* msg);

void Initialize() 
{
	initializeActions();
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

				UI::DRAW_TEXT("should spawn", 0, 0);
				Hash model = GAMEPLAY::GET_HASH_KEY("A_F_M_LowerSDTownfolk_01");
				STREAMING::REQUEST_MODEL(model, false);
				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
				Vector3 playerPos = ENTITY::GET_ENTITY_COORDS(player, true, 0);
				int ped = PED::CREATE_PED(model, playerPos.x + 2, playerPos.y + 2, playerPos.z, 0, false, false, false, false);
				PED::SET_PED_VISIBLE(ped, true);
		}

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}

void log(const char* msg)
{
	ofstream file;
	file.open("D:\Program Files\Rockstar Games\Red Dead Redemption 2\TieYourLasso.log", ios::out | ios::app);
	if (file.is_open())
	{
		file << msg;
		file << "\n";
		file.close();
	}
}