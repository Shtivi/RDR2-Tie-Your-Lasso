#pragma once

#include "Main.h"

class ValentineGallows : public Gallow 
{
public:
	ValentineGallows();

private:
	void playTrapdoorAnimation(Entity trapdoor);
	void playLeverAnimation(Entity lever);
	void playLeverPullAnimation(Ped executioner);
};