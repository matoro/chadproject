/*
 * OBJECT.c FILE: BASIC STRUCT DATA COMMON FOR ALL OBJECTS.
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */
#include "object.h"

void setTexture(struct object *obj,struct texture clr,int index){
	
	obj->textureObj[index].red   = clr.red;
	obj->textureObj[index].green = clr.green;
	obj->textureObj[index].blue  = clr.blue;
}

struct texture getTexture(struct object *obj,int index){

	struct texture clr;

	clr.red   = obj->textureObj[index].red;
	clr.green = obj->textureObj[index].green;
	clr.blue  = obj->textureObj[index].blue;

	return clr;
}

void setSize(struct object *obj,struct size dimension){
	
	obj->sizeObj.alto   = dimension.alto;
	obj->sizeObj.ancho  = dimension.ancho;
}

struct size getSize(struct object *obj){

	struct size dim;

	dim.ancho = obj->sizeObj.ancho;
	dim.alto  = obj->sizeObj.alto;
	
	return dim;
}

void setPosition(struct object *obj,struct position pos){

	obj->posObj.x  = pos.x;
	obj->posObj.y  = pos.y;
	obj->posObj.direction = pos.direction;
}

struct position getPosition(struct object *obj){
	
	struct position pos;

	pos.x = obj->posObj.x;
	pos.y = obj->posObj.y;
	pos.direction = obj->posObj.direction;

	return pos;
}

struct position changePosition(struct object *obj,char movement, int rate){

	struct position response;

	struct position pos = getPosition(obj);
	int deltaX;
	int deltaY;
	int deltaDir;
	switch (movement){
		case 'W':
			deltaX = (int) round(rate*sin(pos.direction*M_PI/180.0));
			deltaY = (int) round(-rate*cos(pos.direction*M_PI/180.0));
			deltaDir = 0;
			fprintf(stdout,"You pressed W: %d %d\n",deltaX,deltaY);
			break;
		case 'S':
			deltaX = (int) round(-rate*sin(pos.direction*M_PI/180.0));
			deltaY = (int) round(rate*cos(pos.direction*M_PI/180.0));
			deltaDir = 0;
			fprintf(stdout,"You pressed S: %d %d\n",deltaX,deltaY);
			break;
		case 'A':
			deltaX = 0;
			deltaY = 0;
			deltaDir = -rate;
			fprintf(stdout,"You pressed A: %d\n",deltaDir);
			break;
		case 'D':
			deltaX = 0;
			deltaY = 0;
			deltaDir = rate;
			fprintf(stdout,"You pressed D: %d\n",deltaDir);
			break;
		case 'Q':
			//Same as going forward in (dir-90)º.Half the rate to simulate a slow hard movement.
			rate/=2;
			deltaX = (int) round(rate*sin((pos.direction-90)*M_PI/180.0));
			deltaY = (int) round(-rate*cos((pos.direction-90)*M_PI/180.0));
			deltaDir = 0;
			break;
		case 'E':
			rate/=2;
			deltaX = (int) round(rate*sin((pos.direction+90)*M_PI/180.0));
			deltaY = (int) round(-rate*cos((pos.direction+90)*M_PI/180.0));
			deltaDir = 0;
			break;
		default:
			deltaX = 0;
			deltaY = 0;
			deltaDir = 0;
			break;
	}

	response.x = deltaX;
	response.y = deltaY;
	response.direction = deltaDir;

	return response;
}
