/*
 *TESTING SDLLIB2
 *GAME TESTING
 */

//#include "screen.h"
#include "player.h"
//#include "object.h"
//#include "SDL_Plotter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main(){

	//VARs DECLARATION
	SDL_Plotter plotter(HEIGHT,WIDTH); 	//CONSTANTS DEFINED IN screen.h
	PlayerObj jugador, *jugador_ptr;	//Typedef in player.h

	//DEFINITON
	jugador = createPlayer(16,16,WIDTH/2,HEIGHT/2,1);//16X16@MIDDLE OF SCREEN
	jugador_ptr = &jugador;

	//clear screen
	plotter.clear();

	//plot player box
	plotPlayer(jugador,&plotter);


	//GAME LOOP VARs
	int* playerpos = getPosition(&(jugador.obj));	//object.h function
	int playerposx = *(playerpos); 
	int playerposy = *(playerpos+1);
	int playerdir  = *(playerpos+2);

	char letter = '\0';
	while(letter != 'Q')
	{
		if (letter == 'W'){
			playerposy-=1;//It was += at first but it went down!
		}
		if (letter == 'S'){
			playerposy+=1; //It was  -= at first but it went up!
		}
		if (letter == 'A'){
			playerposx-=1;
		}
		if (letter == 'D'){
			playerposx+=1;
		}
		
		//update player new  position
		setPosition(&(jugador.obj),playerposx,playerposy,playerdir); 
		//plot new position
		plotter.clear();
		plotPlayer(jugador,&plotter);
		plotter.update(); //neccessary? YES!
		
		bool keyhit = plotter.kbhit();
		if (keyhit){
			letter = plotter.getKey();
		}else{
			letter = '\0';
		//keeps the box from moving all the time in the last dir.
		}
	}

	

	char final_msg[] = "See you soon!";
	plotText(final_msg);
	plotter.setQuit(true);

	return 0;
}

void plotText(char* msg){
	fprintf(stdin,"%s",msg);
}

