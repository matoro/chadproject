/*
 * PLAYER.C FILE: INFO AND FUNCTIONS ABOUT THE PLAYERs OBJ.
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */

#include "object.h"
#include "SDL_Plotter.h"
#include <stdbool.h>


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


PlayerObj createPlayer(int h, int w, int j, int i, int dir){
	
	PlayerObj a;

	setTexture(&a.obj,255,99,71); 	//TOMATO RED
	setSize(&a.obj,h,w);		//DIMENSION
	setPosition(&a.obj,j,i,dir);	//POSITION

	return a;
}
