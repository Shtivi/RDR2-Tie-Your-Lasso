#pragma once

using namespace std;

class MultiVertexRope
{
private:
	vector<AttachedRope*> ropes;

public:
	MultiVertexRope(AttachedRope* base);

	MultiVertexRope* pinTo(Vector3 position);
	void startWinding();
	void stopWinding();
	void update();
};