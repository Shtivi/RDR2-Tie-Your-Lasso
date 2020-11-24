#include "Main.h"

StDanisGallows::StDanisGallows() : Gallows(
	toVector3(2691, -1113.49, 51.8719),
	vector<Vector3>{toVector3(2688.43, -1113.97, 51.849)},
	-1666207837,
	"pull_lever_deputy_trapdoor_std",
	270,
	180,
	vector<NooseSpot>{
		NooseSpot(toVector3(2687.43, -1113.97, 54.2681), toVector3(2685.62, -1113.95, 53.536), toVector3(2687.47, -1114.05, 52.8697)),
		NooseSpot(toVector3(2689.2, -1113.92, 54.2681), toVector3(2691.29, -1113.95, 53.555), toVector3(2689.27, -1114.08, 52.8697))
	},
	GallowsLeverMode::Pull
)
{
}

void StDanisGallows::resetTrapdoor(Entity trapdoor)
{
	ENTITY::SET_ENTITY_ROTATION(trapdoor, 0, 0, 0, 2, 1);
	ENTITY::SET_ENTITY_COORDS(trapdoor, 2688.43, -1113.97, 51.849, 1, 1, 1, 1);
}

Vector3 StDanisGallows::getLeverPullingPosition()
{
	return getPosition() + getRightVector(getLever()) * 0.7f;
}

float StDanisGallows::getLeverHeading()
{
	return 90 - ENTITY::GET_ENTITY_HEADING(getLever());
}