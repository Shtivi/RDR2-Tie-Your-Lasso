#pragma once

class StrawberryGallows : public Gallows
{
public:
	StrawberryGallows();

private:
	void resetTrapdoor(Entity trapdoor);
	void playTrapdoorAnimation(Entity trapdoor);
};