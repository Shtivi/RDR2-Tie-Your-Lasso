#include "Main.h"

StandardGallows::StandardGallows(Vector3 leverPosition, vector<Vector3> trapdoorPositions) : Gallow(leverPosition, trapdoorPositions)
{
}

char* StandardGallows::getLeverAnimationName()
{
	return "push_lever_deputy_lever";
}

char* StandardGallows::getLeverPulllAnimationName()
{
	return "push_behind_quick";
}

char* StandardGallows::getTrapdoorAnimationName()
{
	return "pull_lever_deputy_trapdoor_val";
}