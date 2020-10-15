#pragma once

using namespace std;

class MultiVertexRope : public Rope
{
private:
	vector<AttachedRope*> ropes;

public:
	MultiVertexRope(AttachedRope* base);

	Entity getBase();
	Entity getAttached();
	bool isExist();
	bool canWind();
	void startWinding();
	void stopWinding();
	int update();

	void pinTo(Vector3 position);
};