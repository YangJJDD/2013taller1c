/*
 * TileData.cpp
 *
 *  Created on: Apr 3, 2013
 *      Author: lucas
 */

#include <model/map/TileData.h>
#include <stdio.h>

using namespace std;

TileData::TileData() {
	mobileEntity = NULL;
	tileType = "neutral";
	iterator = entities.begin();
	wasVisible = false;
	isVisible = false;
	walkable = true;
}

std::string TileData::getType() {
	return tileType;
}

MobileEntity* TileData::getMobileEntity() {
	return mobileEntity;
}

Entity* TileData::getNextEntity() {
	if (iterator == entities.end() || getNumberOfEntitiesOnTile() <= 0)
		return NULL;
	Entity* entity = *iterator;
	++iterator;
	return entity;
}

int TileData::getNumberOfEntitiesOnTile() {
	return entities.size();
}

bool TileData::getWasVisible() {
	return wasVisible;
}

bool TileData::getIsVisible() {
	return isVisible;
}

bool TileData::isWalkable( bool ignoremobileEntity ) {
	if (!ignoremobileEntity && mobileEntity != NULL) return false;

	return walkable;
}

void TileData::setType(std::string type) {
	tileType = type;
}

void TileData::setMobileEntity(MobileEntity* newPersonaje) {
	mobileEntity = newPersonaje;
}

void TileData::cleanMobileEntity() {
	mobileEntity = NULL;
}

void TileData::setVisibility(bool value) {
	if (value) {
		wasVisible = true;
		isVisible = true;
	} else {
		isVisible = false;
	}
}

void TileData::setWalkable(bool _walkable) {
	this->walkable = _walkable;
}

void TileData::addEntity(Entity* entity) {
	//Se agrega la entidad al final del vector.
	entities.push_back(entity);
}

TileData::~TileData() {
	// TODO Auto-generated destructor stub
}
