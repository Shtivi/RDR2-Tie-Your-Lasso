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

		

		WAIT(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}