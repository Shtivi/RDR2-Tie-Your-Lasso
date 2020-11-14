#include "Main.h"

ValentineGallows::ValentineGallows() : Gallow(
	toVector3(-315.075, 730.922, 119.411),
	vector<Vector3>{toVector3(-313.787, 728.843, 119.473), toVector3(-314.639, 733.692, 119.473f)},
	2371225963,
	"pull_lever_front_trapdoor_val"
	)
{
}

char* ValentineGallows::getLeverAnimationName()
{
	return "push_lever_deputy_lever";
}

char* ValentineGallows::getLeverPulllAnimationName()
{
	return "push_behind_quick";
}

char* ValentineGallows::getTrapdoorAnimationName()
{
	return "pull_lever_front_trapdoor_val";
}

int ValentineGallows::getTrapdoorModel()
{
	return 2371225963;
}