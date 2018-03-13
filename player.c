/*
 * PLAYER.C FILE: INFO AND FUNCTIONS ABOUT THE PLAYERs OBJ.
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */

#include "player.h"

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
	struct texture playertexture; // TOMATO RED
	playertexture.green = 99; 
	playertexture.blue = 71;
	setTexture(&a.obj, playertexture);
	setSize(&a.obj,dim);		//DIMENSION
	setPosition(&a.obj,pos);	//POSITION

	return a;
}
