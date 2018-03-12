/*
 * PLAYER.C FILE: INFO AND FUNCTIONS ABOUT THE PLAYERs OBJ.
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */

#include <stdbool.h>
#include "player.h"
#include "object.h"
#include "SDL_Plotter.h"

void setHealth(PlayerObj* player,int hp){
	
	player->health = hp;
}

int getHealth(PlayerObj* player){

	return player->health; 
}

void setAmmo(PlayerObj* player,int munition){
	
	player->health = munition;
}

int getAmmo(PlayerObj* player){

	return player->ammo; 
}

bool isAlive(PlayerObj* player){
	
	if ((player->health)>0)	return true;
	return false;
}

bool hasAmmo(PlayerObj* player){
	if ((player->ammo)>0) return true;
	return false;
}

void plotPlayer(PlayerObj player,SDL_Plotter* plot){
	 
	plotObject(&(player.obj),plot);
}


PlayerObj createPlayer(struct size dim, struct position pos){
	
	PlayerObj a;

	setTexture(&a.obj,255,99,71); 			//TOMATO RED
	setSize(&a.obj,dim.alto,dim.ancho);		//DIMENSION
	setPosition(&a.obj,pos.x,pos.y,pos.direction);	//POSITION

	return a;
}
