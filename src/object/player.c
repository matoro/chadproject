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
	
	player->ammo = munition;
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


struct PlayerObj createPlayer(struct size dim, struct position* pos){
	
	struct PlayerObj a;	
	setSize(&a.obj,dim);		//DIMENSION
	setPosition(&a.obj,pos);	//POSITION
	
	struct texture skinColor;
	skinColor.red   = 255;
	skinColor.green = 210;
	skinColor.blue  = 160;

	struct texture darkHair;
	darkHair.red   = 5;
	darkHair.green = 5; 
	darkHair.blue  = 5;

	struct texture eyeColor;
	eyeColor.red   = 5;
	eyeColor.green = 180; 
	eyeColor.blue  = 50;



	int totalPixel = dim.alto * dim.ancho;
	a.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel); 	


	//WE PAINT THE OBJECT. DOUBLE-COLORED HORIZONTAL SPLIT:
	
	printf("TOTAL PIXELS: %d\n",totalPixel);	//for debug purposes.

	
	/*
	 * OTHER CONFIGURATIONS.Doing a double 'for' loop (i&j<dim.alto):
	 *
	 * Two colored stripes, condition:
 	 * (j<(dim.alto/2)? strColor1:strColor2
	 *
	 * Red-Black chess squares, condition:
	 * (count%2==0) ? tomatoRed:darkBlack
 	 *
	 * Half red, half black. Vertical split. 
	 * count <= (totalPixel/2 -1) ? tomatoRed:DarkBlack
	 *
	 * We can also do degradations if we ++ some rgb values of our 
	 * struct texture on each iteration We can also do degradations if we ++ some rgb values of our 
	 *
	 * ... We should find other patterns to style our objects.
	 */
	
	//EXAMPLE FOR HORIZONTAL SPLIT:
	
	int count = 0;
	for(int i = 0;i<dim.ancho;i++){
		for(int j = 0;j<dim.alto;j++){
			setTexture(&a.obj,(i<=(dim.alto)&&j<=(dim.ancho/2)) ? skinColor:darkHair,count);	//IN-HALF
			if(i<=(dim.alto)&&j==(dim.ancho/4)){							//HORIZONTAL QUARTER
				if(abs(dim.alto/2-i)>dim.alto/8)	setTexture(&a.obj,eyeColor,count);	//AVOID CENTER
			}	
		
			count++;
		}
	}	
	return a;
}
