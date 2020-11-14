#include "Main.h"

ValentineGallows::ValentineGallows() : Gallow(
	toVector3(-315.075, 730.922, 119.411),
	vector<Vector3>{toVector3(-315.222f, 733.837f, 117.955f), toVector3(-313.989, 729.185, 117.951f)} )
{
}

void ValentineGallows::playTrapdoorAnimation(Entity trapdoor)
{
	playEntityAnimation(trapdoor, "pull_lever_front_trapdoor_val", "script_re@public_hanging@lever", 1000, false, true, 0.28f, 32768);
}

void ValentineGallows::playLeverAnimation(Entity lever)
{
	playEntityAnimation(lever, "push_lever_deputy_lever", "script_re@public_hanging@lever", 1000.0f, false, true, 0.28f, 32768);
}

void ValentineGallows::playLeverPullAnimation(Ped executioner)
{
	playAnimation(player, "push_behind_quick", "script_re@public_hanging@lever", 4000);
}
