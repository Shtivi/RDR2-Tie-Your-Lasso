#pragma once

#include "Main.h"

class StandardGallows : public Gallows
{
public:
	StandardGallows(Vector3 leverPosition, vector<Vector3> trapdoorPositions, int trapdoorModel, char* trapdoorAnimation, GallowsLeverMode leverMode = Push);
};