#pragma once

class StDanisGallows : public Gallows
{
public:
	StDanisGallows();

private:
	void resetTrapdoor(Entity trapdoor);
	Vector3 getLeverPullingPosition();
	float getLeverHeading();
};