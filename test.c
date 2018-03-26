/*
 *TESTING SDLLIB2
 *GAME TESTING
 */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>	//include math inside object/screen?
#include <stdbool.h>

#include "player.h" 	//Already contains object,SDL and stdbool
#include "screen.h"	//Contains SDL and plotting functions
#include "bar.h"

int main(){

	//VARs DECLARATION
	SDL_Plotter plotter(HEIGHT,WIDTH); 	//CONSTANTS DEFINED IN screen.h
	struct PlayerObj jugador;			
	struct BarObj healthBar;
	struct position playerPos    = {WIDTH/2,HEIGHT/2,0};
	struct size playerDim	     = {16,16};	
	struct position healthBarPos = {WIDTH/4,HEIGHT/4,0};
	enum bartype health          = HEALTH;


	//DEFINITON
	jugador   = createPlayer(playerDim,playerPos);//16X16@MIDDLE OF SCREEN
	healthBar = createBar(&jugador,health,healthBarPos);

	//clear screen
	plotter.clear();

	//plot player box
	plotPlayer(jugador,&plotter);
	plotBar(&healthBar,&plotter);

	//GAME LOOP VARs
	playerPos	  = getPosition(&(jugador.obj));	//object.h function

	char letter = '\0';
	while(letter != '0')
	{

		struct position updatedPos = changePosition(&(jugador.obj),letter,6);

		playerPos.x 	    += updatedPos.x;
		playerPos.y 	    += updatedPos.y;
		playerPos.direction += updatedPos.direction;
		

		//we mend directions to keep them in range. Move to player.c
		if (playerPos.direction > 359){
			playerPos.direction = playerPos.direction%360;
		}		
		if (playerPos.direction < 0){
			playerPos.direction = (playerPos.direction+360);
		}

		//simple test for bar.
		if (letter=='H'){
			jugador.health -= 5;
			fprintf(stdout,"PLAYER HEALTH: %d",jugador.health);
		}


		//update player new  position, health bar.
		setPosition(&(jugador.obj),playerPos); 
		setCurrentValue(&healthBar,jugador.health);
		//plot new position, health bar.
		//NOTE: plot first the base layer of our visible components 
		//and on top of those the ones who would overlap them.
		//In this case, the player gets overlapped by the healthBar.
		//Also, when players health goes below 0, something strange
		//happens as the player texture goes blue and eventually
		//hits a SEG FAULT. 

		//TODO: Implement checking and clean code!

		plotter.clear();
		plotPlayer(jugador,&plotter);
		plotBar(&healthBar,&plotter);
		plotter.update(); //neccessary? YES!
		
		bool keyhit = plotter.kbhit();
		if (keyhit){
			letter = plotter.getKey();
			//Debug traces
			fprintf(stdout,"PLAYER DIR: %d",playerPos.direction);
			fprintf(stdout,"PLAYER x: %d",playerPos.x);
			fprintf(stdout,"PLAYER y: %d",playerPos.y);
		}else{
			letter = '\0';
			//keeps the box from moving all the time in the last dir.
		}
	}

	free(jugador.obj.textureObj);
	char final_msg[] = "See you soon!";
	plotText(final_msg);	//screen.h function
	plotter.setQuit(true);

	return 0;
}
