/*
 * PLAYER.C FILE: INFO AND FUNCTIONS ABOUT THE PLAYERs OBJ.
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */

#include "player.h"

void setHealth(struct PlayerObj* player,int hp){
	
	player->health = hp;
}

int getHealth(struct PlayerObj* player){

	return player->health; 
}

void setAmmo(struct PlayerObj* player,int munition){
	
	player->health = munition;
}

int getAmmo(struct PlayerObj* player){

	return player->ammo; 
}

bool isAlive(struct PlayerObj* player){
	
	if ((player->health)>0)	return true;
	return false;
}

bool hasAmmo(struct PlayerObj* player){
	if ((player->ammo)>0) return true;
	return false;
}

void plotPlayer(struct PlayerObj player,SDL_Plotter* plot){
	 
	plotObject(&(player.obj),plot);
}


struct PlayerObj createPlayer(struct size dim, struct position pos){
	
	struct PlayerObj a;	
	setSize(&a.obj,dim);		//DIMENSION
	setPosition(&a.obj,pos);	//POSITION
	
	struct texture tomatoRed;
	tomatoRed.red   = 250;
	tomatoRed.green = 99;
	tomatoRed.blue  = 71;

	struct texture darkBlack; // TOMATO RED
	darkBlack.red   = 5;
	darkBlack.green = 5; 
	darkBlack.blue  = 5;

	int totalPixel = dim.alto * dim.ancho;
	a.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel); 	

	//HALF RED (FRONT) AND HALF BLACK (BACK)

	int count = 0;
	for(int i = 0;i<dim.ancho;i++){
		for(int j = 0;j<dim.alto;j++){
			/* OTHER CONFIGURATIONS
			 * Two colored stripes, condition:
  			 * (j<=(dim.alto/2)-1)?
			 * Red-Black chess squares, condition:
			 * (count%2==0)?
			 * ... We should find other patterns to style our objects.
			 */	
			setTexture(&a.obj,(count<=(totalPixel/2)-1) ? tomatoRed:darkBlack,count);
			count++;
		}
	}

	return a;
}
