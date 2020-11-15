#pragma once

#include "Main.h"

class ValentineGallows : public Gallows
{
public:
	ValentineGallows();

private:
	char* getLeverAnimationName();
	char* getLeverPulllAnimationName();
	char* getTrapdoorAnimationName();
	int getTrapdoorModel();
};