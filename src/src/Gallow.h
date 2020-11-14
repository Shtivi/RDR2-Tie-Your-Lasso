#pragma once

class Gallow 
{
private:
	Vector3 leverPosition;
	vector<Vector3> trapdoorPositions;

public:
	static Gallow* fromPosition(Vector3 position);

	Gallow(Vector3 leverPosition, vector<Vector3> trapdoorPositions);
	void pullLever(Ped executioner);
	Vector3 getPosition();

protected:
	virtual vector<Entity> getTrapdoors();
	virtual Entity getLever();
	virtual void playTrapdoorAnimation(Entity trapdoor) = 0;
	virtual void playLeverAnimation(Entity lever) = 0;
	virtual void playLeverPullAnimation(Ped executioner) = 0;
};

#include "StandardGallows.h"
#include "ValentineGallows.h"