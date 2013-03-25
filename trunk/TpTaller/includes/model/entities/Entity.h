/*
 * Entity.h
 *
 *  Created on: Mar 24, 2013
 *      Author: gonchub
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <model/entityProperties/Position.h>
#include <model/entityProperties/Speed.h>
#include <model/entityProperties/Power.h>

#include <string>
#include <vector>
#include <iostream>

class Entity {
public:
	Entity(std::string name, Position* position, Speed* speed,
			std::vector<Power*> powers);
	const Position* getPosition() const;
	void setPosition(Position* position);
	const Speed* getSpeed() const;
	void setSpeed(Speed* speed);
	const std::string getName() const;
	void setName(std::string name);
	std::vector<Power*> getPowers();
	void setPowers(std::vector<Power*> powers);
	virtual ~Entity();

private:
	Entity();
	Position* position;
	Speed* speed;
	std::vector<Power*> powers;
	std::string name;
};

#endif /* ENTITY_H_ */