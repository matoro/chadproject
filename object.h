/*
 *OBJECT.H FILE: BASIC STRUCT DATA COMMON FOR ALL OBJECTS.
 */
#include "screen.h" //DO I NEED TO INCLUDE SDL_PLOTTER.h?

struct texture{
	//DEFAULTS TO WHITE.
	int red = 255;
	int green = 255;
	int blue = 255;
};

struct size{	
	
	int alto = 0;
	int ancho = 0;
};

struct position {
	
	int x;
	int y;
	int direction; //Pointing at. 1-360.
};

struct object{

	struct texture 	textureObj;
	struct size 	sizeObj;
	struct position posObj;
};


void setTexture(struct object *obj,int r, int g, int b){
	
	obj->textureObj.red   = r;
	obj->textureObj.green = g;
	obj->textureObj.blue  = b;
}


int* getTexture(struct object *obj){

	static int clr[3];
	clr[0] = obj->textureObj.red;
	clr[1] = obj->textureObj.green;
	clr[2] = obj->textureObj.blue;

	return clr;
}


void setSize(struct object *obj,int height, int width){
	
	obj->sizeObj.alto   = height;
	obj->sizeObj.ancho  = width;
}

int* getSize(struct object *obj){

	static int dim[2];
	dim[0] = obj->sizeObj.ancho;
	dim[1] = obj->sizeObj.alto;
	
	return dim;
}

void setPosition(struct object *obj,int i, int j,int dir){

	obj->posObj.x  = i;
	obj->posObj.y  = j;
	obj->posObj.direction = dir;
}

int* getPosition(struct object *obj){
	
	static int pos[3];
	pos[0] = obj->posObj.x;
	pos[1] = obj->posObj.y;
	pos[2] = obj->posObj.direction;

	return pos;
}

int* changePosition(struct object *obj,char movement, int rate){

	int* pos  = getPosition(obj);
	int deltaX;
	int deltaY;
	int deltaDir = 0;
	switch (movement){
		case 'W':
			deltaX = (int) -rate*sin(*(pos+2)*(M_PI/180.0));
			deltaY = (int) -rate*cos(*(pos+2)*(M_PI/180.0));
			break;
		case 'S':
			deltaX = (int) rate*sin(*(pos+2)*(M_PI/180.0));
			deltaY = (int) rate*cos(*(pos+2)*(M_PI/180.0));
			break;
		case 'A':
			deltaDir = -rate;
			break;
		case 'D':
			deltaDir = rate;
			break;
		default:
			deltaX = 0;
			deltaY = 0;
			deltaDir = 0;
			break;
	}

	static int response[3] = {deltaX,deltaY,deltaDir};
	return response;
}

void plotObject(struct object *obj,SDL_Plotter* plotter){
	
	int* size = getSize(obj);
	int* pos  = getPosition(obj);
	int* clr  = getTexture(obj);
	int adjustedx_f;
	int adjustedx_c;
	int adjustedy_f;
	int adjustedy_c;

	for(int i=0; i<*(size+0);i++){
		for(int j=0;j<*(size+1);j++){
		
			//Adjusted Coordenates.
			adjustedx_f = (int) floor((((i-((*size)/2.0)))*(cos((*(pos+2))*(M_PI/180.0)))-((j-((*(size+1))/2.0)))*(sin((*(pos+2))*(M_PI/180.0)))+(*size)/2.0));
			adjustedx_c = (int)  ceil((((i-((*size)/2.0)))*(cos((*(pos+2))*(M_PI/180.0)))-((j-((*(size+1))/2.0)))*(sin((*(pos+2))*(M_PI/180.0)))+(*size)/2.0)); 
			adjustedy_f = (int) floor((((i-((*(size+1))/2.0)))*(sin((*(pos+2))*(M_PI/180.0)))+((j-((*size)/2.0)))*(cos((*(pos+2))*(M_PI/180.0)))+(*(size+1))/2.0));
			adjustedy_c = (int) ceil((((i-((*(size+1))/2.0)))*(sin((*(pos+2))*(M_PI/180.0)))+((j-((*size)/2.0)))*(cos((*(pos+2))*(M_PI/180.0)))+(*(size+1))/2.0));

			//Plotting Coordenates.			
			plotter->plotPixel(adjustedx_c+*(pos+0),adjustedy_c+*(pos+1)
				,*(clr),*(clr+1),*(clr+2));

			plotter->plotPixel(adjustedx_f+*(pos+0),adjustedy_f+*(pos+1)
				,*(clr),*(clr+1),*(clr+2));

			plotter->plotPixel(adjustedx_c+*(pos+0),adjustedy_f+*(pos+1)
				,*(clr),*(clr+1),*(clr+2));

			plotter->plotPixel(adjustedx_f+*(pos+0),adjustedy_c+*(pos+1)
				,*(clr),*(clr+1),*(clr+2));
		}
	}
}
