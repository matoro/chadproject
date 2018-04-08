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
	if (enemy->active)	enemy->sight = true;	//if he's chasing he sure sees him.
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

void plotEnemy(struct EnemyObj enemy,SDL_Plotter* plot){
	 
	plotObject(&(enemy.obj),plot);
}


struct EnemyObj createEnemy(struct size dim, struct position pos){
	
	struct EnemyObj e;
	setSize(&e.obj,dim);            //DIMENSION
        setPosition(&e.obj,&pos);        //POSITION

        struct texture skinColor;
        skinColor.red   = 255;
        skinColor.green = 210;
        skinColor.blue  = 160;

        struct texture darkHair;	
        darkHair.red   = 5;
        darkHair.green = 5;
        darkHair.blue  = 5;

        struct texture eyeColor;	//RED for enemies.
        eyeColor.red   = 180;
        eyeColor.green = 5;
        eyeColor.blue  = 5;

	int totalPixel = dim.alto * dim.ancho;
        e.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel);
	
	//WE PAINT THE OBJECT


	int count = 0;
        for(int i = 0;i<dim.ancho;i++){
                for(int j = 0;j<dim.alto;j++){
                        setTexture(&e.obj,(i<=(dim.alto)&&j<=(dim.ancho/2)) ? skinColor:darkHair,count);        //IN-HALF
                        if(i<=(dim.alto)&&j==(dim.ancho/4)){                                                    //HORIZONTAL QUARTER
                                if(abs(dim.alto/2-i)>dim.alto/8)        setTexture(&e.obj,eyeColor,count);      //AVOID CENTER
                        }

                        count++;
                }
        }
	
	return e;
}
