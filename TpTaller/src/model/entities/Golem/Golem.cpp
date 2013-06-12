/*
 * Golem.cpp
 *
 *  Created on: 09/06/2013
 *      Author: damian
 */

#include <model/entities/Golem/Golem.h>

Golem::Golem() {
	this->life = 10 ;
	this->magic = 0;
	this->name = "Golem";
	this->owner = NULL;
	attackTimer.start();
}

int Golem::cost(){
	return GOLEM_COST;
}

void Golem::setOwner(Player* owner){
	this->owner = owner;
}

Player* Golem::getOwner(){
	return owner;
}

void Golem::collideTo(MobileEntity& entity) {
	// Casteo a puntero.
	MobileEntity* entityPtr = (MobileEntity*) &entity;
	entityPtr->applyDamage(1);
	if(entityPtr->isDead()) entityPtr->setKilledBy(team);
}

void Golem::attack(Entity& entity) {
	Entity* entityPtr = (Entity*) &entity;
	if (attackTimer.getTimeIntervalSinceStart() > ATTACK_TIMEOUT) {
		entityPtr->setLife(entityPtr->getLife() - 1);
		attackTimer.start();
	}
	if(entityPtr->isDead()) entityPtr->setKilledBy(team);
}

Golem::~Golem() {
}
