#pragma once

#include "Main.h"

class ValentineGallows : public Gallow 
{
public:
	ValentineGallows();

private:
	char* getLeverAnimationName();
	char* getLeverPulllAnimationName();
	char* getTrapdoorAnimationName();
	int getTrapdoorModel();
};