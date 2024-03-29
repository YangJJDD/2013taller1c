/*
 * Shield.cpp
 *
 *  Created on: Jun 8, 2013
 *      Author: gonchub
 */

#include <model/entities/Items/Shield.h>

Shield::Shield() : Item() {
}

Shield::Shield(Item* entity) : Item(entity) {
	Vector3* pos = entity->getCurrentPos();
	this->currentPos = new Vector3(pos->getX(), pos->getY(), pos->getZ());
	Coordinates coordin = entity->getCoordinates();
	this->coord = new Coordinates(coordin.getCol(), coordin.getRow());
	Base base = entity->getBase();
	Base* newBase = new Base(base);
	this->base = newBase;
	this->name = entity->getName();
	this->life = entity->getLife();
	this->currentTile = NULL;
	this->team = entity->getTeam();
	this->killedBy = entity->getKilledBy();
}

void Shield::applyEffects(Player& entity) {
	entity.setShield(20);
}

void Shield::collideTo(Player& entity) {
	applyEffects(entity);
	removeFromGame = true;
}

string Shield::getClassName() {
	return "Shield";
}

Shield::~Shield() {
}
