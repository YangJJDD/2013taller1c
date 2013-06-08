/*
 * Flag.cpp
 *
 *  Created on: 06/06/2013
 *      Author: damian
 */

#include <model/entities/Flag.h>

Flag::Flag() {
	player="";
	name="Flag";
}
void Flag::attackedBy(string player)
{
	this->player=player;
}
string Flag::getClassName()
{
	return this->name;
}
void Flag::collideTo(MobileEntity& player) {
	        receiveDamage(player);
	        if ( life <= 0 ) {
	               killedBy = player.getTeam();
	      }
}

void Flag::receiveDamage(MobileEntity& player)
{
	life-=player.getDamageBuffer();
}
Flag::~Flag() {
}
