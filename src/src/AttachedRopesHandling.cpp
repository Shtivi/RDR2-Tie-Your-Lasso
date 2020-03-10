#include "Main.h"

std::vector<AttachedRope*> attachedRopes;

void UpdateRopes() 
{
	int wait = 0;
	std::vector<AttachedRope*>::iterator it;

	for (it = attachedRopes.begin(); it != attachedRopes.end(); ++it) 
	{
		wait = max(wait, (*it)->update());
	}

	WAIT(wait);
}

void addRope(AttachedRope* rope)
{
	attachedRopes.push_back(rope);
}