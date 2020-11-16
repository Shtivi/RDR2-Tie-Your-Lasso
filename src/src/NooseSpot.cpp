#include "Main.h"

NooseSpot::NooseSpot(Vector3 anchorPosition, Vector3 verticalAnchorPosition,  Vector3 trapdoorPosition)
{
	this->anchorPosition = anchorPosition;
	this->trapdoorPosition = trapdoorPosition;
	this->verticalAnchorPosition = verticalAnchorPosition;
	this->occupant = NULL;
}

Vector3 NooseSpot::getTrapdoorPosition() {
	return this->trapdoorPosition;
}

Vector3 NooseSpot::getAnchorPosition() {
	return this->anchorPosition;
}

Vector3 NooseSpot::getVerticalAnchorPosition() {
	return this->verticalAnchorPosition;
}

bool NooseSpot::isAvailable() {
	updateOccupant();
	return this->occupant == NULL;
}

Ped NooseSpot::getOccupant() {
	updateOccupant();
	return this->occupant;
}

void NooseSpot::setOccupant(Ped occupant) {
	this->occupant = occupant;
}

void NooseSpot::updateOccupant() {
	if (occupant && (!ENTITY::DOES_ENTITY_EXIST(occupant) || ENTITY::IS_ENTITY_DEAD(occupant) || !PED::IS_PED_HUMAN(occupant))) {
		this->clear();
	}
}

void NooseSpot::clear() {
	this->occupant = NULL;
}