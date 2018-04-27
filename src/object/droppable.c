/*
 * DROPPABLE.C -VISIBLE COMPONENT- IMPLEMENTATION
 * @author leba39, mortonmann.
 */
#include "droppable.h"

//F U N C T I O N s

void createDrop(struct Droppable **droppables, int *number_of_droppables, struct position* dropPos){

	//VARs
	struct Droppable d;
	struct size dropSize = {16,16}; //CHANGE RELATIVE TO SCREEN DIM
	int totalPixel = dropSize.alto * dropSize.ancho;

	//setting empty droppable.
	d.type.drop_ammo = NONE;	//any drop_xxxx would do the trick
	d.currentType = 0;
        d.dropObj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel);
	setSize(&d.dropObj,dropSize);
	setPosition(&d.dropObj,dropPos);
	
	
	if(!*droppables){
		if(!(*droppables = (struct Droppable*)malloc(sizeof(struct Droppable)))) printf("Memory allocation failed.");
	}else if(!(*droppables = (struct Droppable*)realloc(*droppables, sizeof(struct Droppable)*(*number_of_droppables+1)))){
		printf("Memory reallocation failed.");		
	}

	*(*droppables+*number_of_droppables) = d;
	(*number_of_droppables)++;
		
}

void deleteDroppable(struct Droppable **droppables, int *number_of_droppables, int drop_number){
	if(drop_number > *number_of_droppables) return; // If the droppable to be deleted does not exist
	(*number_of_droppables)--;
	for(int i = drop_number; i < (*number_of_droppables); i++){
		*(*droppables+i) = *(*droppables+i+1);
		*((*droppables+i)->dropObj.textureObj) = *((*droppables+i+1)->dropObj.textureObj); //texture can't be reassigned like the rest of the object variables because it is a pointer.
	}
	if(*number_of_droppables > 0){
		if(!(*droppables = (struct Droppable*)realloc(*droppables, sizeof(struct Droppable)*(*number_of_droppables)))){
			printf("Memory reallocation failed.");
		}
	}else{
		free(*droppables);
		*droppables = NULL;
	}
}

void setCurrentType(struct Droppable* drop,char newType[]){

	char tipo = newType[0];
	char modo = newType[1];

	switch (tipo){
		case 'A':
			drop->currentType = tipo;
			drop->type.drop_ammo   = (modo=='N') ? NORMAL :((modo=='I') ? INCENDIARY : EXPLOSIVE);
			break;
		case 'P':
			drop->currentType = tipo;
			drop->type.drop_potion = (modo=='S') ? SIMPLE : FULL;
			break;
		case 'W':
			drop->currentType = tipo;
			drop->type.drop_weapon = (modo=='P') ? PISTOL :((modo=='S') ? SHOTGUN : ((modo=='M') ? MACHINEGUN: RIFLE));
			break;
		default:
			drop->currentType = 0;		//check
			drop->type.drop_ammo = NONE;	//every drop_xxx would do the trick
			return;
	}	

}

void plotDrop(struct Droppable* drop,SDL_Plotter* plot){

	//WE UPDATE TEXTURE STRUCTS TO USE BE CAPABLE OF RECYCLING SAME DROPPABLE.
	
	//VARs
	struct texture blackClr;
	struct texture brownClr;
	struct texture   redClr;
	struct texture creamClr;
	struct texture   greenClr;
	int ancho,alto;

	blackClr.red   = 5;
	blackClr.green = 5;
	blackClr.blue  = 5;

	brownClr.red   = 165;
	brownClr.green = 70;
	brownClr.blue  = 5;

	redClr.red   = 250;
	redClr.green = 10;
	redClr.blue  = 10;

	creamClr.red   = 245;
	creamClr.green = 240;
	creamClr.blue  = 190;

	greenClr.red   = 10;
	greenClr.green = 240;
	greenClr.blue  = 10;

	//DEF
	ancho = drop->dropObj.sizeObj.ancho;
	alto  = drop->dropObj.sizeObj.alto;

	//TEXTURE
	int count;
	switch (drop->currentType){
		case 'P': //POTION
			count = 0;
			for(int i = 0;i<ancho;i++){
				for(int j = 0;j<alto;j++){
					setTexture(&(drop->dropObj),(abs(i-alto/2)<4||abs(j-ancho/2)<4) ? greenClr : creamClr,count);
					count++;
				}
			}
			break;
		case 'W': //WEAPON
			count = 0;
			for(int i = 0;i<ancho;i++){
				for(int j = 0;j<alto;j++){
					setTexture(&(drop->dropObj),(j%3==0) ? blackClr : brownClr,count);
					count++;
				}
			}
			break;
		case 'A': //AMMO
			count = 0;
			for(int i = 0;i<ancho;i++){
				for(int j = 0;j<alto;j++){
					setTexture(&(drop->dropObj),abs(i-j)<4 ? blackClr : redClr,count);
					count++;
				}
			}
			break;
		default:
			return;

	}
	
	plotObject(&(drop->dropObj),plot);
}
