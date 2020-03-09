//#include "Main.h"
//bool forcegun = false;
//bool tpgun = false;
//bool Ammoexp = false;
//bool onehit = false;
//bool starwars = false;
//bool rapidfire = false;
//bool DeleteGun = false;
//bool Ammoinf = false;
//int ExplosionType = 1;
//
//float damageScale = 1000.0f;
//// too lazy to use the other math functions
//static  float dist(Vector3 p1, Vector3 p2)
//{
//	float x = p1.x - p2.x;
//	float y = p1.y - p2.y;
//	float z = p1.z - p2.z;
//	return SYSTEM::SQRT(x * x + y * y + z * z);
//}
//
//Vector3 addVector(Vector3 vector, Vector3 vector2) {
//	vector.x += vector2.x;
//	vector.y += vector2.y;
//	vector.z += vector2.z;
//	vector._paddingx += vector2._paddingx;
//	vector._paddingy += vector2._paddingy;
//	vector._paddingz += vector2._paddingz;
//	return vector;
//}
//double DegreeToRadian(double n) {
//	return n * 0.017453292519943295;
//}
//Vector3 RotationToDirection(Vector3 rot) {
//	double num = DegreeToRadian(rot.z);
//	double num2 = DegreeToRadian(rot.x);
//	double val = cos(num2);
//	double num3 = abs(val);
//	rot.x = (float)(-(float)sin(num) * num3);
//	rot.y = (float)(cos(num) * num3);
//	rot.z = (float)sin(num2);
//	return rot;
//
//}
//Vector3 multiplyVector(Vector3 vector, float inc) {
//	vector.x *= inc;
//	vector.y *= inc;
//	vector.z *= inc;
//	vector._paddingx *= inc;
//	vector._paddingy *= inc;
//	vector._paddingz *= inc;
//	return vector;
//}
//
//Vector3 rotDirection(Vector3* rot)
//{
//	float radianz = rot->z * 0.0174532924f;
//	float radianx = rot->x * 0.0174532924f;
//	float num = std::abs((float)std::cos((double)radianx));
//
//	Vector3 dir;
//
//	dir.x = (float)((double)((float)(-(float)std::sin((double)radianz))) * (double)num);
//	dir.y = (float)((double)((float)std::cos((double)radianz)) * (double)num);
//	dir.z = (float)std::sin((double)radianx);
//
//	return dir;
//}
//
//void weapons()
//{
//	Entity EntityTarget;
//	Ped playerPed = PLAYER::PLAYER_PED_ID();
//	Vector3 rot = CAM::GET_GAMEPLAY_CAM_ROT(0);
//	Vector3 dir = rot_to_direction(&rot);
//	Vector3 camPosition = CAM::GET_GAMEPLAY_CAM_COORD();
//	Vector3 playerPos = playerPosition();
//
//	if (tpgun)
//	{
//		if (PED::IS_PED_SHOOTING)
//		{
//			Vector3 iCoord;
//			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &iCoord))
//			{
//				ENTITY::SET_ENTITY_COORDS(playerPed, iCoord.x, iCoord.y, iCoord.z + 1, 0, 0, 1, 1);
//				WAIT(0);
//
//			}
//		}
//	}
//
//	if (onehit)
//	{
//		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &EntityTarget))
//		{
//			if (PED::IS_PED_SHOOTING(PLAYER::PLAYER_PED_ID()))
//			{
//				if (ENTITY::IS_ENTITY_A_PED(EntityTarget)
//					&& PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1)) {
//					EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
//				}
//				VEHICLE::EXPLODE_VEHICLE(EntityTarget, true, false, NULL);
//			}
//		}
//		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
//		PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
//		PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER(PLAYER::PLAYER_ID(), 9999999.9999f);
//	}
//	else
//	{
//		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 1.0f);
//		PLAYER::SET_PLAYER_MELEE_WEAPON_DAMAGE_MODIFIER(PLAYER::PLAYER_ID(), 1.0f);
//		PLAYER::SET_PLAYER_WEAPON_DEFENSE_MODIFIER(PLAYER::PLAYER_ID(), 1.0f);
//	}
//
//	if (Ammoexp)
//	{
//		//Imapct_Bull(VEHICLE_WEAPON_NOSE_TURRET_VALKYRIE);
//		Vector3 blowimpact;
//		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(playerPed, &blowimpact))
//		{
//			FIRE::ADD_EXPLOSION(blowimpact.x, blowimpact.y, blowimpact.z, ExplosionType, damageScale, true, false, NULL);
//		}
//	}
//
//	if (starwars)// oooooo
//	{
//		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(playerPed, &EntityTarget))
//		{
//			if (ENTITY::IS_ENTITY_A_PED(EntityTarget) && PED::IS_PED_IN_ANY_VEHICLE(EntityTarget, 1))
//			{
//				EntityTarget = PED::GET_VEHICLE_PED_IS_IN(EntityTarget, 0);
//			}
//			RequestControlOfEnt(EntityTarget);
//			ENTITY::SET_ENTITY_HAS_GRAVITY(EntityTarget, false);
//			if (IsKeyPressed(VK_LSHIFT))
//				ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * 10.0f, dir.y * 10.0f, dir.z * -50.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
//			else
//				ENTITY::APPLY_FORCE_TO_ENTITY(EntityTarget, 1, dir.x * -10.0f, dir.y * -10.0f, dir.z * +50.0f, 0.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
//		}
//	}
//
//	if (rapidfire)
//	{
//		if (!PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 1)) {
//			PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_PED_ID(), 1);
//			Vector3 gameplayCam = CAM::_GET_GAMEPLAY_CAM_COORDS();
//			Vector3 gameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(0);
//			Vector3 gameplayCamDirection = RotationToDirection(gameplayCamRot);
//			Vector3 startCoords = addVector(gameplayCam, (multiplyVector(gameplayCamDirection, 1.0f)));
//			Vector3 endCoords = addVector(startCoords, multiplyVector(gameplayCamDirection, 500.0f));
//			Hash weaponhash;
//			WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &weaponhash, 1, NULL, NULL);
//			if (CONTROLS::IS_CONTROL_PRESSED(2, 208) || (GetKeyState(VK_LBUTTON) & 0x8000)) {
//				GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(startCoords.x, startCoords.y, startCoords.z, endCoords.x, endCoords.y, endCoords.z, 50, 1, weaponhash, playerPed, 1, 1, 0xbf800000, NULL);
//			}
//		}
//	}
//
//
//	if (Ammoinf)
//	{
//		Ped playerPed = PLAYER::PLAYER_PED_ID();
//		Hash cur;
//		if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &cur, 0, 0, 0) && WEAPON::IS_WEAPON_VALID(cur))
//		{
//			int maxAmmo;
//			if (WEAPON::GET_MAX_AMMO(playerPed, &maxAmmo, cur))
//				WEAPON::SET_PED_AMMO(playerPed, cur, maxAmmo);
//			maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, cur, 1);
//			if (maxAmmo > 0)
//				WEAPON::SET_AMMO_IN_CLIP(playerPed, cur, maxAmmo);
//		}
//	}
//
//}
//
//bool givegun(char* weapon_option, char* weapon_name)
//{
//	Option(weapon_option);
//	if (Menu::Settings::currentOption == Menu::Settings::optionCount)
//	{
//		if (Menu::Settings::selectPressed)
//		{
//			std::string firsthash = ("WEAPON_");
//			std::string sechash = (weapon_name);
//			std::string fullhash = firsthash + sechash;
//			Hash hash = key(Menu::Tools::StringToChar(fullhash));
//			Ped playerPed = PLAYER::PLAYER_PED_ID();
//			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(playerPed, hash, 100, 1, 0x2cd419dc);
//			WEAPON::SET_PED_AMMO(playerPed, hash, 100);
//			WEAPON::SET_CURRENT_PED_WEAPON(playerPed, hash, 1, 0, 0, 0);
//			return true;
//		}
//	}
//	return false;
//}