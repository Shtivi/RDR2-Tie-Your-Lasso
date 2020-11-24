#pragma once

class NooseSpot 
{
public:
	NooseSpot(Vector3 anchorPosition, Vector3 verticalAnchorPosition, Vector3 trapdoorPosition);
	Vector3 getAnchorPosition();
	Vector3 getTrapdoorPosition();
	Vector3 getVerticalAnchorPosition();
	bool isAvailable();
	Ped getOccupant();
	void clear();
	void setOccupant(Ped occupant);

private:
	Vector3 verticalAnchorPosition;
	Vector3 anchorPosition;
	Vector3 trapdoorPosition;
	Ped occupant;

	void updateOccupant();
};