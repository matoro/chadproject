/*
 * OBJECT.c FILE: BASIC STRUCT DATA COMMON FOR ALL OBJECTS.
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */

void setTexture(struct object *obj,struct texture clr){
	
	obj->textureObj.red   = clr.red;
	obj->textureObj.green = clr.green;
	obj->textureObj.blue  = clr.blue;
}

struct texture getTexture(struct object *obj){

	struct texture clr;

	clr.red   = obj->textureObj.red;
	clr.green = obj->textureObj.green;
	clr.blue  = obj->textureObj.blue;

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
			deltaX = (int) round(-rate*sin(pos.direction*M_PI/180.0));
			deltaY = (int) round(-rate*cos(pos.direction*M_PI/180.0));
			deltaDir = 0;
			fprintf(stdout,"You pressed W: %d %d\n",deltaX,deltaY);
			break;
		case 'S':
			deltaX = (int) round(rate*sin(pos.direction*M_PI/180.0));
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