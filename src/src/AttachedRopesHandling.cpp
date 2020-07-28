#include "Main.h"

std::vector<AttachedRope*> attachedRopes;

Stopwatch ropesUpdateStopwatch;
double nextTickIn = 0;

void UpdateRopes() 
{
	if (ropesUpdateStopwatch.isStarted())
	{
		if (ropesUpdateStopwatch.getElapsedSeconds() < nextTickIn)
		{
			return;
		}
		else 
		{
			ropesUpdateStopwatch.stop();
		}
	}

	std::vector<AttachedRope*>::iterator it;
	for (it = attachedRopes.begin(); it != attachedRopes.end(); ++it) 
	{
		if (!(*it)->isExist())
		{
			attachedRopes.erase(it);
			continue;
		}

		nextTickIn = max(nextTickIn, (*it)->update());
	}

	nextTickIn = nextTickIn / 1000;
	ropesUpdateStopwatch.start();
}

void addRope(AttachedRope* rope)
{
	attachedRopes.push_back(rope);
}

bool doesEntityAttachedToRope(Entity entity)
{
	std::vector<AttachedRope*>::iterator it;
	AttachedRope* curr;

	for (it = attachedRopes.begin(); it != attachedRopes.end(); ++it)
	{
		curr = *it;
		
		if (!curr->isExist())
		{
			return false;
		}

		return curr->getEntity1() == entity || curr->getEntity2() == entity;
	}
}