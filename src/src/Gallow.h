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
	void reset(Ped executioner);
	bool isLeverPulled();
	Vector3 getPosition();

protected:
	virtual vector<Entity> getTrapdoors();
	virtual Entity getLever();
	virtual void playTrapdoorAnimation(Entity trapdoor);
	virtual void playLeverAnimation(Entity lever);
	virtual void playLeverPullAnimation(Ped executioner);
	virtual void resetLever(Entity lever);
	virtual void resetTrapdoor(Entity trapdoor);
	virtual char* getLeverAnimationName() = 0;
	virtual char* getLeverPulllAnimationName() = 0;
	virtual char* getTrapdoorAnimationName() = 0;
	virtual int getTrapdoorModel();
};

#include "StandardGallows.h"
#include "ValentineGallows.h"