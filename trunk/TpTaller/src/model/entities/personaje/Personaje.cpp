/* 
 * File:   Personaje.cpp
 * Author: damian
 * 
 * Created on 23 de marzo de 2013, 12:13
 */

#include <model/entities/personaje/Personaje.h>
#include <model/entities/Entity.h>
#include <stdio.h>

Personaje::Personaje() {
	endPos = new Vector2(0, 0);
	velocity = 3;
	this->position = new Position(0, 0, 0);
	this->speed = new Speed(0, Vector2(0, 0));
	this->name = "";
	this->path = new list<Tile *>();
	this->currentTile = new Tile( new Coordinates(0, 0) );
}

void Personaje::setPos(float x, float y) {
	//Llamamos al super
	Entity::setPos(x, y);

	endPos->SetValues(currentPos->GetX(), currentPos->GetY());
}

void Personaje::MoveTo(int x, int y) {
	endPos = new Vector2(x, y);
}

void Personaje::Update() {
	if (IsMoving() == false)
	{
		if (path->size() == 0) return;
		else setNextPosition();
	}

	Vector2* moveDirection = new Vector2(endPos->GetX() - currentPos->GetX(),
			endPos->GetY() - currentPos->GetY());

	if (moveDirection->GetNorm() < velocity + 1) {
		// Close enough to the end position to move in one step.
		currentPos->SetValues(endPos->GetX(), endPos->GetY());
	} else {
		moveDirection->Normalize();
		moveDirection->MultiplyBy(velocity);
		currentPos->Add(moveDirection);
		if (path->size() == 0) return;
		else setNextPosition();
	}
}

void Personaje::setNextPosition() {
	Tile* tile = path->front();
	path->remove(tile);

	Position* tilePos = tile->getPosition();
	MoveTo(tilePos->getX(), tilePos->getY());

	delete currentTile;
	currentTile = tile;
}

Vector2* Personaje::GetCurrentPos() {
	return new Vector2(currentPos->GetX(), currentPos->GetY());
}

Vector2* Personaje::GetMovementDirection() {
	Vector2* moveDirection = new Vector2(endPos->GetX() - currentPos->GetX(),
			endPos->GetY() - currentPos->GetY());
	moveDirection->Normalize();

	return moveDirection;
}

Personaje::Personaje(std::string name, Position* position, Speed* speed,
		std::vector<Power*> powers) {
	this->position = position;
	this->speed = speed;
	this->name = name;
	this->powers = powers;
	this->currentTile = new Tile(new Coordinates(0, 0));
	endPos = new Vector2(0, 0);
	velocity = 3;
}

Personaje::~Personaje() {
	delete this->position;
	delete this->speed;
}

Position* Personaje::getPosition() {
	return position;
}

void Personaje::setPosition(Position* position) {
	this->position = position;
}

Speed* Personaje::getSpeed() {
	return speed;
}

void Personaje::setSpeed(Speed* speed) {
	this->speed = speed;
}

std::string Personaje::getName() {
	return name;
}

void Personaje::setName(std::string name) {
	this->name = name;
}

std::vector<Power*> Personaje::getPowers() {
	return powers;
}

void Personaje::setPowers(std::vector<Power*> powers) {
	this->powers = powers;
}

bool Personaje::IsMoving() {
	return !(currentPos->IsEqual(endPos));
}

void Personaje::assignPath(list<Tile *> *_path) {
	delete this->path;
	this->path = _path;
}

void Personaje::setTile( Tile* _tile ) {
	delete this->currentTile;
	this->currentTile = _tile;
}

Tile* Personaje::getTile() {
	return currentTile;
}
