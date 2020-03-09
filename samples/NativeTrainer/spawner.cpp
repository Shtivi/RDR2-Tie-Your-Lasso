//#include "Main.h"
//
//
//bool Sppwnin = true;
//bool deletecarbool = false;
//void deletecar()
//{
//	Ped playerPed = PLAYER::PLAYER_PED_ID();
//	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0))
//	{
//		Vehicle playerVeh = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
//		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(playerVeh);
//		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(playerVeh))
//		{
//			if (ENTITY::DOES_ENTITY_EXIST(playerVeh))
//			{
//				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(playerVeh, 1, 1);
//				VEHICLE::DELETE_VEHICLE(&playerVeh);
//			}
//		}
//	}
//}
//void SpawnVeh2(char* toSpawn)
//{
//	Hash model = GAMEPLAY::GET_HASH_KEY(toSpawn);
//	if (STREAMING::IS_MODEL_VALID(model))
//	{
//		STREAMING::REQUEST_MODEL(model, true);
//		while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
//		Vector3 ourCoords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false, true);
//		float forward = 5.f;
//		float heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
//		float xVector = forward * sin(degToRad(heading)) * -1.f;
//		float yVector = forward * cos(degToRad(heading));
//		if (deletecarbool) deletecar();
//		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, ourCoords.x + xVector, ourCoords.y + yVector, ourCoords.z, heading, true, true, true, true);
//		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(veh);
//		VEHICLE::SET_VEHICLE_ENGINE_ON(veh, true, true);
//		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, true);
//		DECORATOR::DECOR_SET_INT(veh, "MPBitset", 0);
//		auto networkId = NETWORK::VEH_TO_NET(veh);
//		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(veh))
//			NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(networkId, true);
//		if (Sppwnin) PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
//		WAIT(150);
//		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
//	}
//}
//bool driveonwater, karmode, carjump = false;
//void vehoption()
//{
//	if (driveonwater)
//	{
//		Player player = PLAYER::PLAYER_ID();
//		Ped playerPed = PLAYER::PLAYER_PED_ID();
//		Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
//		//drive_on_water(playerPed, drive_water_obj);
//		DWORD model = ENTITY::GET_ENTITY_MODEL(veh);
//		Vector3 pos = ENTITY::GET_ENTITY_COORDS(playerPed, 0, 1);
//		float height = 0;
//		//WATER::_SET_CURRENT_INTENSITY(height);
//		if ((WATER::GET_WATER_HEIGHT_NO_WAVES(pos.x, pos.y, pos.z, &height))) {
//			Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, GAMEPLAY::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
//			if (ENTITY::DOES_ENTITY_EXIST(container) && height > -50.0f) {
//				Vector3 pRot = ENTITY::GET_ENTITY_ROTATION(playerPed, 0);
//				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1)) pRot = ENTITY::GET_ENTITY_ROTATION(veh, 0);
//				RequestControlOfEnt(container);
//				ENTITY::SET_ENTITY_COORDS(container, pos.x, pos.y, height - 1.5f, 0, 0, 0, 1);
//				ENTITY::SET_ENTITY_ROTATION(container, 0, 0, pRot.z, 0, 1);
//				Vector3 containerCoords = ENTITY::GET_ENTITY_COORDS(container, 1, 1);
//				if (pos.z < containerCoords.z) {
//					if (!PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
//						ENTITY::SET_ENTITY_COORDS(playerPed, pos.x, pos.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
//					}
//					else {
//						RequestControlOfEnt(veh);
//						Vector3 vehc = ENTITY::GET_ENTITY_COORDS(veh, 1, 1);
//						ENTITY::SET_ENTITY_COORDS(veh, vehc.x, vehc.y, containerCoords.z + 2.0f, 0, 0, 0, 1);
//					}
//				}
//			}
//			else {
//				Hash model = GAMEPLAY::GET_HASH_KEY("prop_container_ld2");
//				STREAMING::REQUEST_MODEL(model, 1);
//				while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);
//				container = OBJECT::CREATE_OBJECT(model, pos.x, pos.y, pos.z, 1, 1, 0, 1, 1);
//				RequestControlOfEnt(container);
//				ENTITY::FREEZE_ENTITY_POSITION(container, 1);
//				ENTITY::SET_ENTITY_ALPHA(container, 0, 1);
//				ENTITY::SET_ENTITY_VISIBLE(container, false);
//			}
//		}
//		else {
//			Object container = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(pos.x, pos.y, pos.z, 4.0, GAMEPLAY::GET_HASH_KEY("prop_container_ld2"), 0, 0, 1);
//			if (ENTITY::DOES_ENTITY_EXIST(container)) {
//				RequestControlOfEnt(container);
//				ENTITY::SET_ENTITY_COORDS(container, 0, 0, -1000.0f, 0, 0, 0, 1);
//				WAIT(10);
//				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&container);
//				ENTITY::DELETE_ENTITY(&container);
//			}
//		}
//	}
//
//	if (karmode)
//	{
//		Ped playerPed = PLAYER::PLAYER_PED_ID();
//		Vehicle veh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
//		if (VEHICLE::IS_VEHICLE_ON_ALL_WHEELS(veh))
//		{
//			if (CONTROLS::IS_CONTROL_PRESSED(2, INPUT_VEH_ACCELERATE))
//			{
//
//				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, ENTITY::GET_ENTITY_SPEED_VECTOR(veh, true).y + 0.46f);
//				//_START_SCREEN_EFFECT("RaceTurbo", 0, 0);
//			}
//			if (CONTROLS::IS_CONTROL_JUST_PRESSED(2, INPUT_VEH_BRAKE))
//			{
//				VEHICLE::SET_VEHICLE_FORWARD_SPEED(veh, 0.0f);
//			}
//			else if (CONTROLS::IS_CONTROL_PRESSED(2, INPUT_VEH_BRAKE))
//			{
//				ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0.0, -0.4, 0.0, 0.0, 0.0, 0.0, 0, 1, 1, 1, 0, 1);
//				//SET_VEHICLE_FORWARD_SPEED(g_myVeh, GET_ENTITY_SPEED(g_myVeh) - 0.46f);
//				//_START_SCREEN_EFFECT("FocusOut", 0, 0);
//			}
//		}
//	}
//	if (carjump)
//	{
//		if (GetAsyncKeyState(VK_SPACE) || (CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, INPUT_FRONTEND_ACCEPT)))
//		{
//			int ped = PLAYER::PLAYER_PED_ID();
//			int veh = PED::GET_VEHICLE_PED_IS_IN(ped, true);
//			if (PED::IS_PED_IN_VEHICLE(ped, veh, true))
//			{
//				ENTITY::APPLY_FORCE_TO_ENTITY(veh, 1, 0, 0, 3, 0, 0, 0, 1, false, true, true, true, true);
//			}
//		}
//	}
//}
//
//
