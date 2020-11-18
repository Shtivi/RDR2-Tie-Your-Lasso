#include "Main.h"

StrawberryGallows::StrawberryGallows() : Gallows(
	toVector3(-1805.24, -337.156, 166.698),
	vector<Vector3>{toVector3(-1806.2, -333.923, 166.623)},
	3293336589,
	"pull_lever_deputy_trapdoor_std",
	270,
	270,
	vector<NooseSpot>{
		NooseSpot(toVector3(-1806.7, -334.425, 169.675), toVector3(-1806.7, -334.425, 169.675), toVector3(-1806.83, -334.213, 167.652))
	}
)
{}

void StrawberryGallows::resetTrapdoor(Entity trapdoor)
{
	ENTITY::SET_ENTITY_ROTATION(trapdoor, 0, 0, 80, 2, 1);
	ENTITY::SET_ENTITY_COORDS(trapdoor, -1806.2, -333.923, 166.623, 1, 1, 1, 1);
}

void StrawberryGallows::playTrapdoorAnimation(Entity trapdoor)
{
	ENTITY::SET_ENTITY_ROTATION(trapdoor, 270, 0, 80, 2, 1);
}