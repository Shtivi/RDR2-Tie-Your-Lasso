#include "Main.h";

MultiVertexRope::MultiVertexRope(AttachedRope* base)
{
	ropes.push_back(base);
}

Entity MultiVertexRope::getBase()
{
	return ropes.back()->getBase();
}

Entity MultiVertexRope::getAttached()
{
	return ropes.front()->getAttached();
}

bool MultiVertexRope::isExist()
{
	return ropes.front()->isExist();
}

bool MultiVertexRope::canWind()
{
	return ropes.front()->canWind();
}

void MultiVertexRope::pinTo(Vector3 pos)
{
	AttachedRope* lastRope = ropes.back();
	AttachedRope* rope = new AttachedRope(pos, lastRope->getBase(), NULL, 0);
	ropes.push_back(rope);
}

void MultiVertexRope::startWinding()
{
	ropes.front()->startWinding();
}

void MultiVertexRope::stopWinding()
{
	ropes.front()->stopWinding();
}

int MultiVertexRope::update()
{
	return ropes.front()->update();
}