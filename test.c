/*
 *TESTING SDLLIB2
 *GAME TESTING
 */

#include "screen.h"
#include "player.h"
#include "object.h"
#include "SDL_Plotter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	//VARs DECLARATION
	SDL_Plotter plotter(HEIGHT,WIDTH); 	//CONSTANTS DEFINED IN screen.h
	PlayerObj jugador;			//Typedef in player.h

	//DEFINITON
	jugador = createPlayer(16,16,WIDTH/2,HEIGHT/2,1);//16X16@MIDDLE OF SCREEN

	//clear screen
	plotter.clear();

	//plot player box
	plotPlayer(jugador,plotter);


	//GAME LOOP VARs
	char letter = "\0"; //whatever
	int[3] playerpos = getPosition(&jugador.obj);	//object.h function
	int playerposx = playerpos[0]; 
	int playerposy = playerpos[1];
	int playerdir  = playerpos[2];

	while(letter != 'q')
	{
    		letter = plotter.getKey();
		if (letter == 'w'){
			playerposy+=1;
		}
		if (letter == 's'){
			playerposy-=1;
		}
		if (letter == 'a'){
			playerposx-=1;
		}
		if (letter == 'd'){
			playerposx+=1;
		}
		
		//update player new  position
		setPosition(&jugador.obj,playerposx,playerposy,playerdir); 
		//plot new position
		plotPlayer(jugador,plotter);
		plotter.update(); //neccessary?
	}

	char[] final_msg = "See you soon!";
	plotText(final_msg);
	SDL_Quit();

	return 0;
}

void plotText(char[] msg){
	fprintf(stdin,"%s",&msg);
}

