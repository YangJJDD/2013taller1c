/*
 * MobileEntityUpdate.h
 *
 *  Created on: 08/05/2013
 *      Author: tomas
 */

#ifndef MobileEntityUPDATE_H_
#define MobileEntityUPDATE_H_

#include <sstream>
#include <list>

#include <model/map/Tile.h>
#include <model/Vector3.h>
#include <model/Chat.h>
#include <model/entityProperties/Speed.h>
#include <model/entityProperties/Coordinates.h>
#include <model/Chat.h>

using namespace std;

class MobileEntityUpdate {
public:
	MobileEntityUpdate();
	virtual ~MobileEntityUpdate();

	void setId(int id);
	int getId();

	void setName(string MobileEntityName);
	string getName();

	Vector3* getCurrentPos();
	void setCurrentPos(Vector3* currentPos);
	Vector3* getEndPos();
	void setEndPos(Vector3* endPos);
	Speed* getSpeed();
	void setSpeed(Speed* speed);
	bool isAttacking();
	void setAttacking(bool attacking);
	void setViewRange(int viewRange);
	void setFrozen(bool frozen);
	bool getFrozen();
	int getViewRange();
	float getLastAttackingDirection();
	void setLastAttackingDirection(float dir);
	Tile* getTile();
	void setTile(Tile* tile);
	void setNextTile(Tile* nextTile);
	Tile* getNextTile();
	//Operator to transform the object into a stream.
	friend ostream& operator <<(std::ostream&, const MobileEntityUpdate&);

	//Operator to load an object from a stream
	friend istream& operator >>(std::istream&, MobileEntityUpdate&);


	void setLife(int life);
	int getLife();

	void setMagic(int magic);
	int getMagic();

	void setCastingSpell(bool castingSpell);
	bool getCastingSpell();

	void setTeam(int team);
	int getTeam();
protected:
	int id;
	string name;

	Vector3* currentPos;
	Vector3* endPos;
	int life;
	int magic;
	Speed* speed;
	int team;
	bool attacking;
	float lastAttackingDirection;
	bool castingSpell;
	int viewRange;
	bool frozen;

	Coordinates* initCoords;

	Tile* currentTile;
	Tile* nextTile;


};

#endif /* MobileEntityUPDATE_H_ */
