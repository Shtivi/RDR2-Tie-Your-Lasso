#include "Main.h"

StDanisGallows::StDanisGallows() : Gallows(
	toVector3(2691, -1113.49, 51.8719),
	vector<Vector3>{toVector3(2688.43, -1113.97, 51.849)},
	-1666207837,
	"pull_lever_deputy_trapdoor_std",
	GallowsLeverMode::Pull)
{

}

void StDanisGallows::resetTrapdoor(Entity trapdoor)
{
	ENTITY::SET_ENTITY_ROTATION(trapdoor, 180, 180, 180, 2, 1);
	ENTITY::SET_ENTITY_COORDS(trapdoor, 2688.43, -1113.97, 51.849, 1, 1, 1, 0);
}