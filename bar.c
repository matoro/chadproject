//IMPLEMENTATION
#include "bar.h"

struct BarObj createBar(struct PlayerObj* player, enum bartype type, struct position pos){

	//VARs
	struct BarObj newBar;
	enum bartype discriminator = health;
	struct size barSize = {100,20};
	struct texture greenHealth;
	struct texture redHealth;
	struct texture brownAmmo;
	struct texture blackAmmo;

	greenHealth.red   = 5;
	greenHealth.green = 255;
	greenHealth.blue  = 5;
	
	redHealth.red   = 255;
	redHealth.green = 5;
	redHealth.blue  = 5;

	brownAmmo.red   = 210;
	brownAmmo.green = 145;
	brownAmmo.blue  = 5;

	blackAmmo.red   = 5;
	blackAmmo.green = 5;
	blackAmmo.blue  = 5;


	newBar.bartype  = type;
	newBar.max	= (type == discrimnator) ? MAX_HEALTH : MAX_AMMO;
	setPosition(&newBar.obj,pos);
	setSize(&newBar.obj,barSize);

	int totalPixel = barSize.alto * barSize.ancho;
	newBar.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel);

	//APPLY COLOR ACCORDINGLY
	//TODO
	

	return newBar;
}

void setCurrentValue(struct BarObj* currentbar,int newvalue){

	currentbar->currentvalue = newvalue;
}

void plotBar(struct BarObj* bar,SDL_Plotter* plot){

	//UPDATE TEXTURE STRUCTS [] BEFORE PLOTTING AGAING.
	
	plotObject(&(bar->obj),plot);	//If this doesn't work avoid using bar pointer.
}
