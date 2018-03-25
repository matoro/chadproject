/*
 * DROPPABLE.C -VISIBLE COMPONENT- IMPLEMENTATION
 * @author leba39, mortonmann.
 */
#include "droppable.h"

//F U N C T I O N s

struct Droppable createDrop(struct size dropSize,struct position dropPos, union dropType tipo,char box){

	struct Droppable d;

	d.type = tipo;
	setSize(&d.dropObj,dropSize);
	setPosition(&d.dropObj,dropPos);
	struct texture dropClr;
	switch (box){
		case 'P': //GREEN
			dropClr.red   = 0;
			dropClr.green = 180;
			dropClr.blue  = 6;
			break;
		case 'W': //BROWN
			dropClr.red   = 140;
			dropClr.green = 70;
			dropClr.blue  = 0;
			break;
		case 'A': //YELLOW
			dropClr.red   = 255;
			dropClr.green =255;
			dropClr.blue  = 64;
			break;
		default:
			return d;
	}
	setTexture(&d.dropObj,dropClr);
	
	return d;	
}

void plotDrop(struct Droppable drop,SDL_Plotter* plot){

	plotObject(&(drop.dropObj),plot);
}
