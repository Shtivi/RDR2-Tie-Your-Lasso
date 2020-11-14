#pragma once

#include "Main.h"

class StandardGallows : public Gallow
{
public:
	StandardGallows(Vector3 leverPosition, vector<Vector3> trapdoorPositions, int trapdoorModel, char* trapdoorAnimation, GallowsLeverMode leverMode = Push);
};