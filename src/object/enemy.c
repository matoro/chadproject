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
			(*enemies+i)->line_of_sight = createSightLine(*(*enemies+i), 40);
			(*enemies+i)->cooldown++;
		if((*enemies+i)->cooldown%2 != 0) return;
			plot->plotPixel((*enemies+i)->line_of_sight.point3.x,(*enemies+i)->line_of_sight.point3.y,150,150,4);
			plot->plotPixel((*enemies+i)->line_of_sight.point4.x,(*enemies+i)->line_of_sight.point4.y,150,150,4);
		if((*enemies+i)->sight){
			attack(i,player,plot,bullets,number_of_bullets,enemies,number_of_enemies);
		}else{
			search(i,player,enemies,number_of_enemies);
		}
	}
}

void search(int enemy_index, struct PlayerObj player, struct EnemyObj **enemies, int n_enemies){
	if(loc_is_seen(*(*enemies+enemy_index), player.obj.posObj)){
		(*enemies+enemy_index)->sight = true;
	}
	if(dirToLoc(*(*enemies+enemy_index), player.obj.posObj) == -1){
		printf("Player is to the left of enemy.\n");
	}else{
		printf("Player is to the right of enemy.\n");
	}
}

void attack(int enemy_index,struct PlayerObj player, SDL_Plotter *plot, struct BulletObj **bullets, int *number_of_bullets, struct EnemyObj **enemies, int n_enemies){
	if(!loc_is_seen(*(*enemies+enemy_index), player.obj.posObj)){
		(*enemies+enemy_index)->sight = false;
	}
}

bool locIsSeen(struct EnemyObj enemy, struct position playerPos){
	struct object p_obj;
	p_obj.posObj = playerPos;
	struct position updatedPos = changePosition(&(p_obj), 'E', 16);
	playerPos.x += updatedPos.x;
	playerPos.y += updatedPos.y;
	updatedPos = changePosition(&(p_obj), 'S', 8);
	playerPos.x += updatedPos.x;
	playerPos.y += updatedPos.y;
	struct position points[4];
	points[0] = enemy.line_of_sight.point1;
	points[1] = enemy.line_of_sight.point2;
	points[2] = enemy.line_of_sight.point3;
	points[3] = enemy.line_of_sight.point4;
	double slope[4];
	if(enemy.line_of_sight.point2.x-enemy.line_of_sight.point1.x == 0){
		slope[0] = 2000; //value impossible on a 600*600 board.
		slope[2] = 2000;
	}else{
		slope[0] = ((enemy.line_of_sight.point2.y-enemy.line_of_sight.point1.y)/(enemy.line_of_sight.point2.x-enemy.line_of_sight.point1.x));
		slope[2] = ((enemy.line_of_sight.point4.y-enemy.line_of_sight.point3.y)/(enemy.line_of_sight.point4.x-enemy.line_of_sight.point3.x));
	}
	if(enemy.line_of_sight.point3.x-enemy.line_of_sight.point2.x == 0){
		slope[1] = 0;	
	}else{
		slope[1] = ((enemy.line_of_sight.point3.y-enemy.line_of_sight.point2.y)/(enemy.line_of_sight.point3.x-enemy.line_of_sight.point2.x));	
	}
	if(enemy.line_of_sight.point1.x-enemy.line_of_sight.point4.x == 0){
		slope[3] = 0;
	}else{
		slope[3] = ((enemy.line_of_sight.point1.y-enemy.line_of_sight.point4.y)/(enemy.line_of_sight.point1.x-enemy.line_of_sight.point4.x));
	}
	int hits = 0;
	while(playerPos.x < 600){
		for(int i = 0; i < 4; i++){
			if(slope[i] == 2000 && points[i].x==playerPos.x && ((points[i].y>playerPos.y && points[i+1].y<playerPos.y)||(points[i].y<playerPos.y && points[i+1].y>playerPos.y))){
			hits++;
			}else if(points[i].y+((playerPos.x-points[i].x)*slope[i]) ==  playerPos.y && ((points[i].x>playerPos.x && points[i+1].x<playerPos.x)||(points[i].x<playerPos.x && points[i+1].x>playerPos.x))) hits++;
		}
		playerPos.x++;
	}
	if(hits == 1) return true;
	return false;

}

struct LOS createSightLine(struct EnemyObj enemy, int end_width_offset){
	struct LOS line_of_sight;
	line_of_sight.point1 = enemy.obj.posObj;
	line_of_sight.point2 = enemy.obj.posObj;
	line_of_sight.point3 = enemy.obj.posObj;
	line_of_sight.point4 = enemy.obj.posObj;
	struct position updatedPos = changePosition(&(enemy.obj), 'E', 32);
	line_of_sight.point1.x += updatedPos.x;
	line_of_sight.point1.y += updatedPos.y;
	 updatedPos = changePosition(&(enemy.obj), 'W', 200);
	line_of_sight.point3.x += updatedPos.x;
	line_of_sight.point3.y += updatedPos.y;
	 updatedPos = changePosition(&(enemy.obj), 'Q', end_width_offset);
	line_of_sight.point3.x += updatedPos.x;
	line_of_sight.point3.y += updatedPos.y;
	 updatedPos = changePosition(&(enemy.obj), 'W', 200);
	line_of_sight.point4.x += updatedPos.x;
	line_of_sight.point4.y += updatedPos.y;
	 updatedPos = changePosition(&(enemy.obj), 'E', end_width_offset+32);
	line_of_sight.point4.x += updatedPos.x;
	line_of_sight.point4.y += updatedPos.y;
	return line_of_sight;
}

int dirToLoc(struct EnemyObj enemy, struct position playerPos){
		float dist_left = sqrt(abs(enemy.line_of_sight.point3.x-playerPos.x)+abs(enemy.line_of_sight.point3.y-playerPos.y));
		float dist_right = sqrt(abs(enemy.line_of_sight.point4.x-playerPos.x)+abs(enemy.line_of_sight.point4.y-playerPos.y));
		if(dist_left < dist_right) return -1;
		return 1;
}
