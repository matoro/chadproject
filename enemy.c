/*
 * ENEMY.C FILE: INFO AND FUNCTIONS ABOUT THE ENEMY OBJ.
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */

#include "enemy.h"

void setHealth(struct EnemyObj* enemy,int hp){
	
	enemy->health = hp;
}

int getHealth(struct EnemyObj* enemy){

	return enemy->health; 
}

void setAmmo(struct EnemyObj* enemy,int munition){
	
	enemy->health = munition;
}

void setFOV(struct EnemyObj* enemy,int fieldofview){
	
	enemy->fov = fieldofview;
}

int getFOV(struct EnemyObj* enemy){
	
	return enemy->fov;
}

void setBehaviour(struct EnemyObj* enemy, bool mode,bool seesPlayer){
	
	enemy->active = mode;
	enemy->sight  = seesPlayer;
	if (active)	enemy->sight = true;	//if he's chasing he sure sees him.
}

bool isActive(struct EnemyObj* enemy){

	return enemy->active;
}

bool seesPlayer(struct EnemyObj* enemy){

	return enemy->sight;
}

int getAmmo(struct EnemyObj* enemy){

	return enemy->ammo; 
}

bool isAlive(struct EnemyObj* enemy){
	
	if ((enemy->health)>0)	return true;
	return false;
}

bool hasAmmo(struct EnemyObj* enemy){
	if ((enemy->ammo)>0) return true;
	return false;
}

void plotPlayer(struct EnemyObj enemy,SDL_Plotter* plot){
	 
	plotObject(&(enemy.obj),plot);
}


struct EnemyObj createPlayer(struct size dim, struct position pos){
	
	struct EnemyObj e;
	struct texture enemytexture; 	//BLACK
	
	enemy.texture.red  = 0
	enemytexture.green = 0; 
	enemytexture.blue  = 0;
	setTexture(&a.obj, enemytexture);
	setSize(&a.obj,dim);		//DIMENSION
	setPosition(&a.obj,pos);	//POSITION

	return e;
}
