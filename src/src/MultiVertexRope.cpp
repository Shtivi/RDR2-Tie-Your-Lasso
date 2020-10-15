#include "Main.h";

MultiVertexRope::MultiVertexRope(AttachedRope* base)
{
	ropes.push_back(base);
	addRope(base);
}

MultiVertexRope* MultiVertexRope::pinTo(Vector3 pos)
{
	AttachedRope* lastRope = ropes.back();
	AttachedRope* rope = new AttachedRope(pos, lastRope->getBase(), NULL, 0);
	ropes.push_back(rope);
	return this;
}

void MultiVertexRope::startWinding()
{
	ropes.front()->startWinding();
}

void MultiVertexRope::stopWinding()
{
	ropes.front()->stopWinding();
}

void MultiVertexRope::update()
{

}