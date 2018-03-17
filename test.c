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

int main(){

	//VARs DECLARATION
	SDL_Plotter plotter(HEIGHT,WIDTH); 	//CONSTANTS DEFINED IN screen.h
	struct PlayerObj jugador;			//Typedef in player.h
	struct position playerPos = {WIDTH/2,HEIGHT/2,0};
	struct size playerDim	  = {16,16};	

	//DEFINITON
	jugador = createPlayer(playerDim,playerPos);//16X16@MIDDLE OF SCREEN

	//clear screen
	plotter.clear();

	//plot player box
	plotPlayer(jugador,&plotter);


	//GAME LOOP VARs
	playerPos	  = getPosition(&(jugador.obj));	//object.h function

	char letter = '\0';
	while(letter != '0')
	{

		struct position updatedPos = changePosition(&(jugador.obj),letter,6);

		playerPos.x 	    += updatedPos.x;
		playerPos.y 	    += updatedPos.y;
		playerPos.direction += updatedPos.direction;
		

		//we mend directions to keep them in range
		if (playerPos.direction > 359){
			playerPos.direction = playerPos.direction%360;
		}		
		if (playerPos.direction < 0){
			playerPos.direction = (playerPos.direction+360);
		}

		//update player new  position
		setPosition(&(jugador.obj),playerPos); 
		//plot new position
		plotter.clear();
		plotPlayer(jugador,&plotter);
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

	
	char final_msg[] = "See you soon!";
	plotText(final_msg);	//screen.h function
	plotter.setQuit(true);

	return 0;
}
