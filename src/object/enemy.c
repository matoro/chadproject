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

void updateEnemyBehavior(struct EnemyObj **enemies, int number_of_enemies,struct PlayerObj player, struct BulletObj **bullets, int *number_of_bullets){
	if(!enemies||!bullets||number_of_enemies<0) return;
	
	for(int i = 0; i< number_of_enemies; i++){
			(*enemies+i)->line_of_sight = createSightLine(*(*enemies+i), 60);
			(*enemies+i)->cooldown++;
			if((*enemies+i)->cooldown > 100000) (*enemies+i)->cooldown = 0;
		if((*enemies+i)->cooldown%2 != 0) return;
		if((*enemies+i)->sight){
			attack(i,player,bullets,number_of_bullets,enemies,number_of_enemies);
		}else{
			search(i,player,enemies,number_of_enemies);
		}
	}
}

void search(int enemy_index, struct PlayerObj player, struct EnemyObj **enemies, int n_enemies){
	int y1 = (*enemies+enemy_index)->obj.posObj.y;
	int x1 = (*enemies+enemy_index)->obj.posObj.x;
	int y2 = player.obj.posObj.y;
	int x2 = player.obj.posObj.x;
	if(locIsSeen(*(*enemies+enemy_index), player.obj.posObj) || sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1))) < 50) (*enemies+enemy_index)->sight = true;
	for(int i = 0; i < n_enemies; i++){
		if(i == enemy_index) i++;
		if(i > n_enemies) break;
		y2 = (*enemies+i)->obj.posObj.y;	
		x2 = (*enemies+i)->obj.posObj.x;
		if(sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1))) < 20){
			if((*enemies+enemy_index)->cooldown%6 == 0
					&& !border_collision(&((*enemies+enemy_index)->obj), 'Q', 6)){
				struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'E', 6);
				(*enemies+enemy_index)->obj.posObj.x += updatedPos.x*dirToLoc(*(*enemies+enemy_index), (*enemies+i)->obj.posObj);
				(*enemies+enemy_index)->obj.posObj.y += updatedPos.y*dirToLoc(*(*enemies+enemy_index), (*enemies+i)->obj.posObj);
			}else if(!border_collision(&((*enemies+enemy_index)->obj), 'W', 6)){
				struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'W', 6);
				(*enemies+enemy_index)->obj.posObj.x += updatedPos.x;
				(*enemies+enemy_index)->obj.posObj.y += updatedPos.y;
			}
			return;
		}
	}
	struct position memoryPosition = (*enemies+enemy_index)->last_player_loc;
	if((*enemies+enemy_index)->cooldown%4 == 0){
		struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'A', 6);
		(*enemies+enemy_index)->obj.posObj.direction += updatedPos.direction*dirToLoc(*(*enemies+enemy_index), memoryPosition);
	}
	if((*enemies+enemy_index)->cooldown%12 == 0){// move toward last know player location, moves slower while searching.
		struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'W', 6); // will never lead enemy off screen
		(*enemies+enemy_index)->obj.posObj.x += updatedPos.x;
		(*enemies+enemy_index)->obj.posObj.y += updatedPos.y;
	}
	y2 = memoryPosition.y;
	x2 = memoryPosition.x;
	if(sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1))) > 12 && (*enemies+enemy_index)->cooldown%1000 == 0){ // looks around for the player if it isn't found
		(*enemies+enemy_index)->last_player_loc.x = rand()%400;
		(*enemies+enemy_index)->last_player_loc.y = rand()%400;
	}
}

void attack(int enemy_index,struct PlayerObj player, struct BulletObj **bullets, int *number_of_bullets, struct EnemyObj **enemies, int n_enemies){
	(*enemies+enemy_index)->last_player_loc= player.obj.posObj;
	int y1 = (*enemies+enemy_index)->obj.posObj.y;
	int x1 = (*enemies+enemy_index)->obj.posObj.x;
	int y2 = player.obj.posObj.y;
	int x2 = player.obj.posObj.y;
	if(!locIsSeen(*(*enemies+enemy_index), player.obj.posObj) && sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1))) < 50) (*enemies+enemy_index)->sight = false;
	for(int i = 0; i < n_enemies; i++){
		if(i == enemy_index) i++;
		if(i > n_enemies) break;
		y2 = (*enemies+i)->obj.posObj.y;	
		x2 = (*enemies+i)->obj.posObj.x;
		if(sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1))) < 50){
			if((*enemies+enemy_index)->cooldown%6 == 0 && !border_collision(&((*enemies+enemy_index)->obj), 'E', 6) 
					&& !border_collision(&((*enemies+enemy_index)->obj), 'Q', 6)){
				struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'E', 6);
				(*enemies+enemy_index)->obj.posObj.x += updatedPos.x*dirToLoc(*(*enemies+enemy_index), (*enemies+i)->obj.posObj);
				(*enemies+enemy_index)->obj.posObj.y += updatedPos.y*dirToLoc(*(*enemies+enemy_index), (*enemies+i)->obj.posObj);
			}else if(!border_collision(&((*enemies+enemy_index)->obj), 'W', 6)){
				struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'W', 6);
				(*enemies+enemy_index)->obj.posObj.x += updatedPos.x;
				(*enemies+enemy_index)->obj.posObj.y += updatedPos.y;
			}
			return;
		}
	}
	y2 = player.obj.posObj.y;
	x2 = player.obj.posObj.x;
	//shoot, enemy will always shoot if player is visible and time is right
	if((*enemies+enemy_index)->cooldown%300 == 0){
		createBullet(&((*enemies+enemy_index)->obj),bullets,number_of_bullets,PISTOL,NORMAL);
	}else if((*enemies+enemy_index)->cooldown%10 == 0){
		struct EnemyObj aimingE = *(*enemies+enemy_index);// enemy struct for purpose of aiming
		aimingE.line_of_sight = createSightLine(*(*enemies+enemy_index), -3);// smaller LOS for aiming.
		if(!locIsSeen(aimingE, player.obj.posObj)){
			struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'A', 6);
			(*enemies+enemy_index)->obj.posObj.direction += updatedPos.direction*dirToLoc(*(*enemies+enemy_index), player.obj.posObj);
		}
	}else if(sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1))) > 100 && (*enemies+enemy_index)->cooldown%6 == 0){//pursue player if too far
		struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'W', 6);
		(*enemies+enemy_index)->obj.posObj.x += updatedPos.x;
		(*enemies+enemy_index)->obj.posObj.y += updatedPos.y;
	}else if(sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1))) < 50 && (*enemies+enemy_index)->cooldown%6 == 0 
			&& !border_collision(&((*enemies+enemy_index)->obj), 'S', 6)){//move back from player if too close
		struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'S', 6);
		(*enemies+enemy_index)->obj.posObj.x += updatedPos.x;
		(*enemies+enemy_index)->obj.posObj.y += updatedPos.y;
	}else if(sqrt(((y2-y1)*(y2-y1))+((x2-x1)*(x2-x1))) < 50 && (*enemies+enemy_index)->cooldown%6 == 0 
			&& !border_collision(&((*enemies+enemy_index)->obj), 'E', 6)){
		struct position updatedPos = changePosition(&((*enemies+enemy_index)->obj), 'E', 6);
		(*enemies+enemy_index)->obj.posObj.x += updatedPos.x;
		(*enemies+enemy_index)->obj.posObj.y += updatedPos.y;
	}

	//avoid other enemies

	// save last known player location
	
}

bool locIsSeen(struct EnemyObj enemy, struct position playerPos){
	struct object p_obj;
	p_obj.posObj = playerPos;
	struct position updatedPos = changePosition(&(p_obj), 'E', 16);//player position for use in this function should be @ the center of the player, not the corner.
	playerPos.x += updatedPos.x;
	playerPos.y += updatedPos.y;
	updatedPos = changePosition(&(p_obj), 'S', 8);
	playerPos.x += updatedPos.x;
	playerPos.y += updatedPos.y;
	struct position points[5];//LOS points
	points[0] = enemy.line_of_sight.point1;
	points[1] = enemy.line_of_sight.point2;
	points[2] = enemy.line_of_sight.point3;
	points[3] = enemy.line_of_sight.point4;
	points[4] = enemy.line_of_sight.point1; // for the for loop later
	bool c = false;
	for (int i = 0; i < 4; i++) {
		if(!((points[i].y-points[i+1].y) + points[i+1].x)) return false;//can't divide by 0
		if (((points[i+1].y>playerPos.y)!=(points[i].y>playerPos.y))&&(playerPos.x<(points[i].x-points[i+1].x)*(playerPos.y-points[i+1].y)/(points[i].y-points[i+1].y) + points[i+1].x)) c = !c;
	  }
	  return c;
	}


struct LOS createSightLine(struct EnemyObj enemy, int end_width_offset){
	struct LOS line_of_sight;
	//4 corners of the quadrilateral.
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

int dirToLoc(struct EnemyObj enemy, struct position location){
	struct position updatedPos = changePosition(&(enemy.obj), 'E', 16);
	enemy.obj.posObj.x += updatedPos.x;
	enemy.obj.posObj.y += updatedPos.y;
	updatedPos = changePosition(&(enemy.obj), 'S', 8);
	enemy.obj.posObj.x += updatedPos.x;
	enemy.obj.posObj.y += updatedPos.y;
	struct position leftPos = enemy.obj.posObj;//a position to the left of the enemy
	struct position rightPos = enemy.obj.posObj;//a position to the right of the enemy opposite of leftPos
	updatedPos = changePosition(&(enemy.obj), 'E', 50);
	rightPos.x += updatedPos.x;
	rightPos.y += updatedPos.y;
	leftPos.x -= updatedPos.x;
	leftPos.y -= updatedPos.y; 
	// the distance  between the leftPos and the player position from the formula d=sqrt((y2-y1)^2+(x2-x1)^2)
	double dist_left = sqrt(((location.y-leftPos.y)*(location.y-leftPos.y))+((location.x-leftPos.x)*(location.x-leftPos.x)));
	double dist_right = sqrt(((location.y-rightPos.y)*(location.y-rightPos.y))+((location.x-rightPos.x)*(location.x-rightPos.x)));
	// because rightPos and leftPos are an equal distance from the enemy, with one on the left and the other on the right, the side of the enemy that the player is on can be determined by comparing the distance between each position and the player position
	return (dist_left > dist_right) ? -1 : 1;
}
