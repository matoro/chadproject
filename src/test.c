/*
 *TESTING SDLLIB2
 *GAME TESTING
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>	//include math inside object/screen?
#include <stdbool.h>

#include "object/player.h" 	//Already contains object,SDL and stdbool
#include "object/enemy.h"
#include "object/bar.h"
#include "object/droppable.h"
#include "object/bullet.h"
#include "graphic/visiblecomponents.h"
#include "graphic/screen.h"	//Contains SDL and plotting functions

int main(){

	//VARs DECLARATION
	SDL_Plotter plotter(HEIGHT,WIDTH); 	//CONSTANTS DEFINED IN screen.h

	struct PlayerObj jugador;			
	struct BarObj    *bars = NULL;
	int number_of_bars = 0;
	struct BulletObj *bullets = NULL;
	int number_of_bullets = 0;
	struct EnemyObj  enemigo;
	struct EnemyObj  enemigo1;
	struct EnemyObj  enemigo2;
	struct Droppable simplePotion;
	struct Droppable pistolWeapon;
	struct Droppable normalAmmo;

	struct position playerPos    = {WIDTH/2,HEIGHT/2,0};
	struct position enemyPos     = {WIDTH/4,HEIGHT/2,90};
	struct position enemyPos1    = {WIDTH/2,HEIGHT/4,180};
	struct position enemyPos2    = {3*WIDTH/4,HEIGHT/2,270};
	struct size playerDim	     = {16,16};	//same for enemies
	

	struct position healthBarPos = {WIDTH/6,7*HEIGHT/8,0};
	struct position ammoBarPos   = {3*WIDTH/4,7*HEIGHT/8,0};
	enum bartype health          = HEALTH;
	enum bartype ammo 	     = AMMO;

	struct position dropPosP     = {WIDTH/8,HEIGHT/8,0};
	struct position dropPosW     = {7*WIDTH/8,HEIGHT/8,0};
	struct position dropPosA     = {WIDTH/2,HEIGHT/8,0};
		
		//AUXILIARY
	char dropType_1[2] = {'P','S'}; 	//POTION-SIMPLE
	char dropType_2[2] = {'W','P'};		//WEAPON-PISTOL
	char dropType_3[2] = {'A','N'};		//AMMO-NORMAL


	//DEFINITON
	jugador	  = createPlayer(playerDim,&playerPos);//16X16@MIDDLE OF SCREEN
	enemigo   = createEnemy(playerDim,&enemyPos);
	enemigo1  = createEnemy(playerDim,&enemyPos1);
	enemigo2  = createEnemy(playerDim,&enemyPos2);
	createBar(&bars, &number_of_bars, &jugador,health,healthBarPos);
	createBar(&bars, &number_of_bars, &jugador,ammo, ammoBarPos);
	
	simplePotion = createDrop(&dropPosP);	//taken==false by default
	pistolWeapon = createDrop(&dropPosW);
	normalAmmo   = createDrop(&dropPosA);
		//FURTHER SETTINGS
	setCurrentType(&simplePotion,dropType_1);
	setCurrentType(&pistolWeapon,dropType_2);
	setCurrentType(&normalAmmo,dropType_3);


	//CLEAR SCREEN
	plotter.clear();
	//PLOTS
	plotEnemy(enemigo,&plotter);
	plotEnemy(enemigo1,&plotter);
	plotEnemy(enemigo2,&plotter);
	plotVisibleComponents(&plotter, jugador, bars, number_of_bars, bullets, number_of_bullets);

	plotDrop(&simplePotion,&plotter);
	plotDrop(&pistolWeapon,&plotter);
	plotDrop(&normalAmmo,&plotter);

	//GAME LOOP VARs
	playerPos = getPosition(&(jugador.obj));	//object.h function

	char letter = '\0';

	while(letter != '0')
	{

		struct position updatedPos = changePosition(&(jugador.obj),letter,6);

		playerPos.x 	    += updatedPos.x;
		playerPos.y 	    += updatedPos.y;
		playerPos.direction += updatedPos.direction;
		
		/*
		//we mend directions to keep them in range. Move to object.c
		if (playerPos.direction > 359){
			playerPos.direction = playerPos.direction%360;
		}		
		if (playerPos.direction < 0){
			playerPos.direction = (playerPos.direction+360);
		}
		*/
		//simple test for bar.
		if (letter=='H'){
			jugador.health -= 5;
			fprintf(stdout,"PLAYER HEALTH: %d",jugador.health);
		}
	
		if (letter=='G'){
			jugador.ammo -= 5;
			fprintf(stdout,"PLAYER AMMO: %d",jugador.ammo);
		}
		//testing shooting
		if (letter==' '){
			createBullet(&(jugador.obj), &bullets, &number_of_bullets);
		}

		//update player new  position, health bar.
		setPosition(&(jugador.obj),&playerPos); 
		setCurrentValue(bars,jugador.health);			
		setCurrentValue((bars+1),jugador.ammo);			
		//We should call only plotBar when we set a new current value. its not efficient to plot the same thing over and over.

		//plot new position, health bar.
		//NOTE: plot first the base layer of our visible components 
		//and on top of those the ones who would overlap them.
		//In this case, the player gets overlapped by the healthBar.
		//Also, when players health goes below 0, something strange
		//happens as the player texture goes blue and eventually
		//hits a SEG FAULT. 

		//TODO: Implement checking and clean code!

		plotter.clear();
		plotEnemy(enemigo,&plotter);
		plotEnemy(enemigo1,&plotter);
		plotEnemy(enemigo2,&plotter);
		plotVisibleComponents(&plotter, jugador, bars, number_of_bars, bullets, number_of_bullets);
		plotDrop(&simplePotion,&plotter);
		plotDrop(&pistolWeapon,&plotter);
		plotDrop(&normalAmmo,&plotter);

		//updates the position of all bullets
		updateBulletPos(&bullets,&number_of_bullets);

		plotter.update(); //neccessary? YES!
		
		bool keyhit = plotter.kbhit();
		if (keyhit){
			letter = plotter.getKey();
			//Debug traces
			fprintf(stdout,"PLAYER DIR: %d\n",playerPos.direction);
			fprintf(stdout,"PLAYER x: %d\n",playerPos.x);
			fprintf(stdout,"PLAYER y: %d\n",playerPos.y);
		}else{
			letter = '\0';
			//keeps the box from moving all the time in the last dir.
		}

	}
	//free all visible components dyn allocated struct texture[]
	free(jugador.obj.textureObj);
	free(enemigo.obj.textureObj);
	free(enemigo1.obj.textureObj);
	free(enemigo2.obj.textureObj);
	for(int i = 0; i < number_of_bars; i ++) free((bars+i)->obj.textureObj);
	free(bars);
	free(simplePotion.dropObj.textureObj);
	free(pistolWeapon.dropObj.textureObj);
	free(normalAmmo.dropObj.textureObj);

	//first valgrind runs outputs >2kb leaks. 120,000 allocs and 110000ish frees. Is this our thing or SDLs?


	char final_msg[] = "See you soon!";
	plotText(final_msg);	//screen.h function
	plotter.setQuit(true);

	return 0;
}
