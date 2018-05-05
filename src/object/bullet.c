#include "bullet.h"



void createBullet(struct object *shooter, struct BulletObj **bullets, int *number_of_bullets){
	struct BulletObj newBullet;
	struct size bulletSize = {5,10}; 
	struct texture bulletBlack;

	bulletBlack.red   = 0;
	bulletBlack.green = 0;
	bulletBlack.blue  = 0;
	
	setPosition(&newBullet.obj, &(shooter->posObj));
	// changes the position so that the bullet doesn't start inside the player
	int a_x = (int) ceil((0-shooter->sizeObj.alto/2.0)*(cos(shooter->posObj.direction*M_PI/180.0))-(0-shooter->sizeObj.ancho/2.0)*(sin(shooter->posObj.direction*M_PI/180.0))+shooter->sizeObj.alto/2.0);
	int a_y = (int)  ceil((0-shooter->sizeObj.ancho/2.0)*(sin(shooter->posObj.direction*M_PI/180.0))+(0-shooter->sizeObj.alto/2.0)*(cos(shooter->posObj.direction*M_PI/180.0))+shooter->sizeObj.ancho/2.0);
	newBullet.obj.posObj.x += a_x;
	newBullet.obj.posObj.y += a_y;
	struct position updatedPos = changePosition(&(newBullet.obj), 'W', 10);
	newBullet.obj.posObj.x += updatedPos.x;
	newBullet.obj.posObj.y += updatedPos.y;
	setSize(&newBullet.obj,bulletSize);

	int totalPixel = bulletSize.alto * bulletSize.ancho;
	newBullet.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel);
	
	for(int i = 0;i<totalPixel;i++)	setTexture(&newBullet.obj, bulletBlack,i);





	if(!*bullets){
		if(!(*bullets = (struct BulletObj*)malloc(sizeof(struct BulletObj)))) printf("Memory allocation failed.");
	}else if(!(*bullets = (struct BulletObj*)realloc(*bullets, sizeof(struct BulletObj)*(*number_of_bullets+1)))){
		printf("Memory reallocation failed.");		
	}

	*(*bullets+*number_of_bullets) = newBullet;
	(*number_of_bullets)++;
}
void deleteBullet(struct BulletObj **bullets, int *number_of_bullets, int bullet_number){
	if(bullet_number > *number_of_bullets) return; // If the bullet to be deleted does not exist
	(*number_of_bullets)--;
	for(int i = bullet_number; i < (*number_of_bullets); i++){
		*(*bullets+i) = *(*bullets+i+1);
		*((*bullets+i)->obj.textureObj) = *((*bullets+i+1)->obj.textureObj); //texture can't be reassigned like the rest of the object variables because it is a pointer.
	}
	if(*number_of_bullets > 0){
		if(!(*bullets = (struct BulletObj*)realloc(*bullets, sizeof(struct BulletObj)*(*number_of_bullets)))){
			printf("Memory reallocation failed.");
		}
	}else{
		free(*bullets);
		*bullets = NULL;
	}

}

void updateBulletPos(struct BulletObj **bullets, int *number_of_bullets){
	//updates the positions of all bullets.
	for(int i = 0; i < *number_of_bullets; i++){
		struct position updatedPos = changePosition(&((*bullets+i)->obj), 'W', 5);
		(*bullets+i)->obj.posObj.x += updatedPos.x;
		(*bullets+i)->obj.posObj.y += updatedPos.y;
		//deletes bullet if it is too close to the edge of the screen, this prevents seg faults or looping bullets depending on the direction.
		if((*bullets+i)->obj.posObj.x < 10 || (*bullets+i)->obj.posObj.x > 590 || (*bullets+i)->obj.posObj.y < 10 || (*bullets+i)->obj.posObj.y > 590){
			deleteBullet(bullets, number_of_bullets, i);
		}
	}
}

void plotBullet(struct BulletObj *bullet, SDL_Plotter *plot){
	plotObject(&(bullet->obj), plot);
}
