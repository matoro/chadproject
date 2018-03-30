//IMPLEMENTATION
#include "bar.h"

struct BarObj createBar(struct PlayerObj* player, enum bartype b_type, struct position pos){

	//VARs
	struct BarObj newBar;
	enum bartype discriminator = HEALTH;
	struct size barSize = {100,20}; //CHANGE. DIM RELATIVE TO SCREEN DIM
	struct texture greenHealth;
	struct texture brownAmmo;

	greenHealth.red   = 5;
	greenHealth.green = 255;
	greenHealth.blue  = 5;

	brownAmmo.red   = 210;
	brownAmmo.green = 145;
	brownAmmo.blue  = 5;

	newBar.type         = b_type;
	newBar.max	    = (b_type == discriminator) ? MAX_HEALTH : MAX_AMMO;
	newBar.currentvalue = (b_type == discriminator) ? player->health : player->ammo;
	setPosition(&newBar.obj,pos);
	setSize(&newBar.obj,barSize);

	int totalPixel = barSize.alto * barSize.ancho;
	newBar.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel);

	//APPLY COLOR ACCORDINGLY
	for(int i = 0;i<totalPixel;i++)	setTexture(&newBar.obj,(b_type == discriminator) ? greenHealth : brownAmmo,i);

	return newBar;
}

void setCurrentValue(struct BarObj* currentbar,int newvalue){

	currentbar->currentvalue = newvalue;
}

void plotBar(struct BarObj* bar,SDL_Plotter* plot){

	//VARs
	struct texture redHealth;
	struct texture blackAmmo;
	enum bartype discriminator = HEALTH;
	enum bartype type = bar->type;

	int pixelsToDraw;
	int totalPixel;
	double deltaChange;


	redHealth.red   = 255;
	redHealth.green = 5;
	redHealth.blue  = 5;
	
	blackAmmo.red   = 5;
	blackAmmo.green = 5;
	blackAmmo.blue  = 5;

	//UPDATE TEXTURE STRUCTS [] BEFORE PLOTTING AGAING.

	deltaChange  = (double)(bar->currentvalue)/(bar->max);	
	totalPixel   = (bar->obj.sizeObj.alto)*(bar->obj.sizeObj.ancho); //dots or ->?
	pixelsToDraw = round(deltaChange*totalPixel);


	for(int i = totalPixel-1;i >= pixelsToDraw;i--)	setTexture(&(bar->obj),(type == discriminator) ? redHealth : blackAmmo,i);

	
	plotObject(&(bar->obj),plot);	//If this doesn't work avoid using bar pointer.
}
