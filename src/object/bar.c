//IMPLEMENTATION
#include "bar.h"

void createBar(struct BarObj **bars, int *number_of_bars, struct PlayerObj* player, enum bartype b_type, struct position pos){

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
	newBar.currentvalue = player->health;
	setPosition(&newBar.obj, &pos);
	setSize(&newBar.obj,barSize);

	int totalPixel = barSize.alto * barSize.ancho;
	newBar.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel);

	//APPLY COLOR ACCORDINGLY
	for(int i = 0;i<totalPixel;i++)	setTexture(&newBar.obj,(b_type == discriminator) ? greenHealth : brownAmmo,i);

	//Allocate memory for new bar
	if(!(*bars)){
		if(!(*bars = (struct BarObj*)malloc(sizeof(struct BarObj)))) printf("Memory allocation failed.");
	}else if(!(*bars = (struct BarObj*)realloc(*bars, sizeof(struct BarObj)*(*number_of_bars+1)))){
		printf("Memory reallocation failed.");		
	}

	*(*bars+*number_of_bars) = newBar;
	(*number_of_bars)++;
}

void deleteBar(struct BarObj **bars, int *number_of_bars, int bar_number){
	if(bar_number > *number_of_bars) return; // If the bar to be deleted does not exist
	(*number_of_bars)--;
	for(int i = bar_number; i < (*number_of_bars); i++){
		*(*bars+i) = *(*bars+i+1);
		*((*bars+i)->obj.textureObj) = *((*bars+i+1)->obj.textureObj); //texture can't be reassigned like the rest of the object variables because it is a pointer.
	}
	if(*number_of_bars > 0){
		if(!(*bars = (struct BarObj*)realloc(*bars, sizeof(struct BarObj)*(*number_of_bars)))){
			printf("Memory reallocation failed.");
		}
	}else{
		free(*bars);
		*bars = NULL;
	}
}

void setCurrentValue(struct BarObj* currentbar,int newvalue){

	currentbar->currentvalue = newvalue;
}

void plotBar(struct BarObj* bar,SDL_Plotter* plot){

	//VARs
	struct texture redHealth;
	struct texture blackAmmo;
    struct texture greenHealth;
	struct texture brownAmmo;
	enum bartype discriminator = HEALTH;
	enum bartype type = bar->type;

	int pixelsToDraw;
	int totalPixel;
	double deltaChange;

	greenHealth.red   = 5;
	greenHealth.green = 255;
	greenHealth.blue  = 5;

	brownAmmo.red   = 210;
	brownAmmo.green = 145;
	brownAmmo.blue  = 5;

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

    for(int i=0;i<totalPixel;i++){
        if(i>=pixelsToDraw){
            setTexture(&(bar->obj),(type == discriminator) ? redHealth   : blackAmmo,i);
        }else{
            setTexture(&(bar->obj),(type == discriminator) ? greenHealth : brownAmmo,i);
        }
    
    }

    plotObject(&(bar->obj),plot);	//If this doesn't work avoid using bar pointer.
}
