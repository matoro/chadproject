/*
 * ENEMY.C FILE: INFO AND FUNCTIONS ABOUT THE ENEMY OBJ.
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */

#include "enemy.h"

void setHealth(struct EnemyObj* enemy,int hp){
	
	enemy->health = hp;
}

int getHealth(struct EnemyObj* enemy){

	return enemy->health; 
}

void setAmmo(struct EnemyObj* enemy,int munition){
	
	enemy->health = munition;
}

void setFOV(struct EnemyObj* enemy,int fieldofview){
	
	enemy->fov = fieldofview;
}

int getFOV(struct EnemyObj* enemy){
	
	return enemy->fov;
}

void setBehaviour(struct EnemyObj* enemy, bool mode,bool seesPlayer){
	
	enemy->active = mode;
	enemy->sight  = seesPlayer;
	if (enemy->active)	enemy->sight = true;	//if he's chasing he sure sees him.
}

bool isActive(struct EnemyObj* enemy){

	return enemy->active;
}

bool seesPlayer(struct EnemyObj* enemy){

	return enemy->sight;
}

int getAmmo(struct EnemyObj* enemy){

	return enemy->ammo; 
}

bool isAlive(struct EnemyObj* enemy){
	
	if ((enemy->health)>0)	return true;
	return false;
}

bool hasAmmo(struct EnemyObj* enemy){
	if ((enemy->ammo)>0) return true;
	return false;
}

void plotEnemy(struct EnemyObj enemy,SDL_Plotter* plot){
	 
	plotObject(&(enemy.obj),plot);
}

void createEnemy(struct EnemyObj ** enemies, int *number_of_enemies,struct size dim, struct position* pos){
	
	struct EnemyObj e;
	setSize(&e.obj,dim);            //DIMENSION
        setPosition(&e.obj,pos);        //POSITION

        struct texture skinColor;
        skinColor.red   = 255;
        skinColor.green = 210;
        skinColor.blue  = 160;

        struct texture darkHair;	
        darkHair.red   = 5;
        darkHair.green = 5;
        darkHair.blue  = 5;

        struct texture eyeColor;	//RED for enemies.
        eyeColor.red   = 180;
        eyeColor.green = 5;
        eyeColor.blue  = 5;

	int totalPixel = dim.alto * dim.ancho;
        e.obj.textureObj = (struct texture*)malloc(sizeof(struct texture)*totalPixel);
	
	//WE PAINT THE OBJECT


	int count = 0;
        for(int i = 0;i<dim.ancho;i++){
                for(int j = 0;j<dim.alto;j++){
                        setTexture(&e.obj,(i<=(dim.alto)&&j<=(dim.ancho/2)) ? skinColor:darkHair,count);        //IN-HALF
                        if(i<=(dim.alto)&&j==(dim.ancho/4)){                                                    //HORIZONTAL QUARTER
                                if(abs(dim.alto/2-i)>dim.alto/8)        setTexture(&e.obj,eyeColor,count);      //AVOID CENTER
                        }

                        count++;
                }
        }
	
	if(!*enemies){
		if(!(*enemies = (struct EnemyObj*)malloc(sizeof(struct EnemyObj)))) printf("Memory allocation failed.");
	}else if(!(*enemies = (struct EnemyObj*)realloc(*enemies, sizeof(struct EnemyObj)*(*number_of_enemies+1)))){
		printf("Memory reallocation failed.");		
	}

	*(*enemies+*number_of_enemies) = e;
	(*number_of_enemies)++;
}

void deleteEnemy(struct EnemyObj ** enemies, int *number_of_enemies, int enemy_number){
	if(enemy_number > *number_of_enemies) return; // If the enemy to be deleted does not exist
	(*number_of_enemies)--;
	for(int i = enemy_number; i < (*number_of_enemies); i++){
		*(*enemies+i) = *(*enemies+i+1);
		*((*enemies+i)->obj.textureObj) = *((*enemies+i+1)->obj.textureObj); //texture can't be reassigned like the rest of the object variables because it is a pointer.
	}
	if(*number_of_enemies > 0){
		if(!(*enemies = (struct EnemyObj*)realloc(*enemies, sizeof(struct EnemyObj)*(*number_of_enemies)))){
			printf("Memory reallocation failed.");
		}
	}else{
		free(*enemies);
		*enemies = NULL;
	}
}

void updateEnemyBehavior(struct EnemyObj **enemies, int number_of_enemies,struct PlayerObj player, SDL_Plotter *plot, struct BulletObj **bullets, int *number_of_bullets){
	if(!enemies||!bullets||!plot||number_of_enemies<0) return;

    for(int i = 0; i< number_of_enemies; i++){
		if((*enemies+i)->sight){
			attack(i,player,plot,bullets,number_of_bullets,enemies,number_of_enemies);
		}else{
			search(i,player,enemies,number_of_enemies);
		}
	}
}

void search(int enemy_index, struct PlayerObj player, struct EnemyObj **enemies, int n_enemies){
	
    if(!enemies||enemy_index<0||n_enemies<1||enemy_index>n_enemies) return;
    
    //VARs
    struct EnemyObj *enemy = ((*enemies)+enemy_index);



    if(loc_is_seen(*enemy, player.obj.posObj)){
		enemy->sight = true;
		printf("enemy can see player\n");
		return;		
	}
	if(!loc_is_ahead(*enemy, enemy->last_player_loc)){ // turn toward last know player location.
		
        bool collision = enemy_enemies_collision(enemy,'D',6,enemies,n_enemies);
        if(!collision){    
            struct position updatedPos = changePosition(&(enemy->obj), 'D', 6);
		    enemy->obj.posObj.direction += (updatedPos.direction*dirToLoc(*enemy, enemy->last_player_loc));
        }
		
	}/*else if(calcDistance(enemy->obj.posObj, enemy->last_player_loc) < 40){
		enemy->last_player_loc.x = (rand() % 400)+100; 
		enemy->last_player_loc.y = (rand() % 400)+100;
	}*/ else{
		
        bool collision = enemy_enemies_collision(enemy,'W',6,enemies,n_enemies);
        if(!collision){
            struct position updatedPos = changePosition(&(enemy->obj), 'W', 6); 
		    enemy->obj.posObj.x += updatedPos.x;
		    enemy->obj.posObj.y += updatedPos.y;
        }

	}
}

void attack(int enemy_index,struct PlayerObj player, SDL_Plotter *plot, struct BulletObj **bullets, int *number_of_bullets, struct EnemyObj **enemies, int n_enemies){
	
    if(!enemies||enemy_index<0||n_enemies<1||enemy_index>n_enemies) return;

    //VARs
    struct EnemyObj *enemy = ((*enemies)+enemy_index);



    if(!loc_is_seen(*enemy, player.obj.posObj)){
		enemy->sight = false;
		printf("enemy can't see player\n");
		return;		
	}
	if(!loc_is_ahead(*enemy, player.obj.posObj)){ // turn toward player location.
		
        bool collision = enemy_enemies_collision(enemy,'D',6,enemies,n_enemies);
        if(!collision){
            struct position updatedPos = changePosition(&(enemy->obj), 'D', 6);
		    enemy->obj.posObj.direction += (updatedPos.direction*dirToLoc(*enemy, player.obj.posObj));
        }

	}/*else{
		createBullet(&(enemy->obj), bullets, number_of_bullets, PISTOL, NORMAL);
	}*/
	enemy->last_player_loc = player.obj.posObj;
	
}

bool loc_is_seen(struct EnemyObj enemy, struct position playerPos){
	struct position **lines = (struct position **)malloc(sizeof(struct position *)*5);
	*lines = createSightLine(enemy, 0);
	*(lines+1) = createSightLine(enemy, -10);
	*(lines+2) = createSightLine(enemy, 10);
	*(lines+3) = createSightLine(enemy, 30);
	*(lines+4) = createSightLine(enemy, -30);
	for(int x = 0; x < 5; x++){
		for(int y = 0; y < 12; y++){
			struct position *currentline = *(lines+x); //the compiler doesn't like it when I try to dereference twice in an if statement.
			if((currentline+y)->x < playerPos.x+10 && (currentline+y)->x > playerPos.x-10 && (currentline+y)->y < playerPos.y+10 && (currentline+y)->y > playerPos.y-10) {
				return true;

				printf("There is a match between the vision point located at %i %i and the player ate %i %i\n", (currentline+y)->x, (currentline+y)->y, playerPos.x, playerPos.y);
			}
		} 
	
	}
	return false;
	printf("there was no match, location not seen");
	for(int x = 0; x < 5; x++){
		free(*(lines+x));
	}
	free(lines);
}

bool loc_is_ahead(struct EnemyObj enemy, struct position playerPos){
	struct position currentPosition = enemy.obj.posObj;
	struct position updatedPos = changePosition(&(enemy.obj), 'E', 16);
	currentPosition.x += updatedPos.x;
	currentPosition.y += updatedPos.y;
	/*
	updatedPos = changePosition(&(enemy.obj), 'S', 8);
	currentPosition.x += updatedPos.x;
	currentPosition.y += updatedPos.y;
	*/
	while(currentPosition.x < 600 && currentPosition.x > 0 && currentPosition.y < 600 && currentPosition.y > 0){
		updatedPos = changePosition(&(enemy.obj), 'W', 5);
		currentPosition.x += updatedPos.x;
		currentPosition.y += updatedPos.y;
		if(currentPosition.x < playerPos.x+20 && currentPosition.x > playerPos.x-20 && currentPosition.y < playerPos.y+20 && currentPosition.y > playerPos.y-20) return true;
	}	
	return false;

}

struct position *createSightLine(struct EnemyObj enemy, int degree_offset){
	struct position *sightLine = (struct position *)malloc(sizeof(struct position)* 12);	//vision distance is constant
	struct position currentPosition = enemy.obj.posObj;
	struct position updatedPos = changePosition(&(enemy.obj), 'E', 16);
	currentPosition.x += updatedPos.x;
	currentPosition.y += updatedPos.y;
	enemy.obj.posObj.direction += degree_offset;
	for(int i = 0; i <12; i++){
		updatedPos = changePosition(&(enemy.obj), 'W', 16); //16 * 12 = 192 pixel vision distance.
		currentPosition.x += updatedPos.x;
		currentPosition.y += updatedPos.y;
		*(sightLine+i) = currentPosition;
	}
	return sightLine;
}	

int dirToLoc(struct EnemyObj enemy, struct position playerPos){
	int dir1 =  enemy.obj.posObj.direction;
	int dir2 = -1;
	struct position testposition;
	int distance = calcDistance(enemy.obj.posObj, playerPos);
	for(int i = 0; i < 60; i++){
		enemy.obj.posObj.direction = i*6;
		testposition = enemy.obj.posObj;
		struct position updatedPos = changePosition(&(enemy.obj), 'W', distance); //16 * 12 = 192 pixel vision distance.
		testposition.x += updatedPos.x;
		testposition.y += updatedPos.y;
		if(testposition.x < playerPos.x+10 && testposition.x > playerPos.x-10 && testposition.y < playerPos.y+10 && testposition.y > playerPos.y-10){
			dir2 = i * 6;
			break;
		}
	}
	if(dir2 = -1) return 1;
	if(abs(dir1-dir2) > 180 && dir1 < dir2){
		dir1 +=360;
	}else{
		dir2 +=360;
	}
	if(dir1-dir2 > 0) return -1;
	return 1;
}
