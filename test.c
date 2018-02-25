/*
 *TESTING SDLLIB2
 *GAME TESTING
 */

#include "screen.h"
#include "SDL_Plotter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//FOR TESTING. THIS SHOULD BE PART OF PLAYER COMPONENT
struct player{
	struct texture = {255,99,71}; //tomato red.
	struct size = {16,16}; //16x16 pixel box size
	struct position;
	//...more info
};

struct texture{
	int red = 255;
	inr green = 255;
	int blue = 255;
	//DEFAULTS TO WHITE?
};

struct size{
	int altura;
	int ancho;
	//obligatory for every object
}

struct position{
	int x;
	int y;
};



int main(){

	
	//How can I change the window title?
	//if I use SDL_Window *window and 
	//then SDL_CreateWindow("title",pos,pos,row,col...) ? how can I access plotter
	//functions then??

	//VARs
	SDL_Plotter plotter(HEIGHT,WIDTH);
	struct player jugador1;

	player.position.x = WIDTH/2;
	player.position.y = HEIGHT/2;

	//clear screen
	plotter.clear();
	


	//plot player box, initial position at the center.
	plotTexture(player.position.x,player.position.y,&jugador1,plotter);

	//GAME LOOP VARs
	int playerposx = player.position.x; 
	int playerposy = player.position.y;
	char letter;
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
		
		//update player struct position. probably better within a call to
		//a player own function. like plotter's update.
		player.position.x = playerposx;
		player.position.y = playerposy; 
		
		plotTexture(playerposx,playerposy,&player,plotter);
		plotter.update(); //neccessary?
	}

	SDL_Quit();

	return 0;
}

void plotText(char[] msg){
	fprintf(stdin,"%s",&msg);
}

void plotTexture(int x, int y, struct object *obj,SDL_Plotter plotter){
	if((x<0)||(x>WIDTH)||(y<0)||(y>HEIGHT)){
		fprintf(stderr,"Wrong coordenates: %d %d",x,y);
	}else{
		//We extract info from the object
			//COLOR
		int r,g,b;
		r = obj->texture.red;
		g = obj->texture.green;
		b = obj->texture.blue;
			//SIZE
		int[2] size;
		size[0] = obj->size.heigth;
		size[1] = obj->size.width;

		for(int i = 0; i<size[0];i++){
			for(int j = 0; i<size[1];j++){
				//we paint every pixel of the object size
				//only those that appear on the screen.
				if !((x+i)>WIDTH||(y+j)>HEIGHT){
					plotter.plotPixel(x+i,y+j,r,g,b);
				}
			}
		}
	}
}	
