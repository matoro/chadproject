//IMPLEMENTATION
#include "bar.h"

struct BarObj createBar(struct PlayerObj* player, enum bartype type, struct position pos){

	//VARs
	struct BarObj newBar;
	enum bartype discriminator = health;
	struct size barSize = {100,20}; //CHANGE. DIM RELATIVE TO SCREEN DIM
	struct texture greenHealth;
	struct texture brownAmmo;

	greenHealth.red   = 5;
	greenHealth.green = 255;
	greenHealth.blue  = 5;

	brownAmmo.red   = 210;
	brownAmmo.green = 145;
	brownAmmo.blue  = 5;

	newBar.bartype  = type;
	newBar.max	= (type == discriminator) ? MAX_HEALTH : MAX_AMMO;
	setPosition(&newBar.obj,pos);
	setSize(&newBar.obj,barSize);

	int totalPixel = barSize.alto * barSize.ancho;
	newBar.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel);

	//APPLY COLOR ACCORDINGLY
	for(int i = 0;i<totalPixel;i++)	setTexture(&newBar.obj,(type == discrimator) ? greenHealth : brownAmmo,i);

	return newBar;
}

void setCurrentValue(struct BarObj* currentbar,int newvalue){

	currentbar->currentvalue = newvalue;
}

void plotBar(struct BarObj* bar,SDL_Plotter* plot){

	//VARs
	struct texture redHealth;
	struct texture blackAmmo;
	enum bartype discriminator = health;
	enum bartype type = bar->bartype;

	int pixelsToDraw;
	int totalPixel;
	int deltaChange;


	redHealth.red   = 255;
	redHealth.green = 5;
	redHealth.blue  = 5;
	
	blackAmmo.red   = 5;
	blackAmmo.green = 5;
	blackAmmo.blue  = 5;

	//UPDATE TEXTURE STRUCTS [] BEFORE PLOTTING AGAING.

	deltaChange  = (bar->currentvalue)/(bar->max);	
	totalPixel   = (bar->obj.size.alto)*(bar->obj.size.ancho); //dots or ->?
	pixelsToDraw = round(deltaChange*totalPixel);

	for(int i = 1;i <= pixelsToDraw;i++)	setTexture(&(bar->obj),(type == discrimator) ? redHealth : blackAmmo,totalPixel-i);

	
	plotObject(&(bar->obj),plot);	//If this doesn't work avoid using bar pointer.
}
