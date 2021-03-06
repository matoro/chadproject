/*
 *TESTING SDLLIB2
 *GAME TESTING
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

#include "graphic/visiblecomponents.h"
#include "graphic/screen.h"	            //Contains SDL and plotting functions
#include "collision/collision.h"
#include "userinterface/ui.h"
#include "gamelogic/gamelogic.h"
#include "gamelogic/globals.h"

int main(){

	//VARs
	SDL_Plotter plotter(HEIGHT,WIDTH, false); 	//CONSTANTS DEFINED IN screen.h. false -> NO SOUND

	struct PlayerObj jugador;		
	struct BarObj    *bars          = NULL;
    struct BulletObj *bullets       = NULL;
    struct EnemyObj  *enemies       = NULL;
    struct Droppable *droppables    = NULL;
    
    int number_of_bars          = 0;
	int number_of_bullets       = 0;
	int number_of_enemies       = 0;
	int number_of_droppables    = 0;
    int score                   = 0;
    
    bool quit, cont, first_blood, spawn_time;
    
    time_t t_0;
    struct timeval t_cooldown;
    struct timeval bullet_time;

    struct position gameoverPos = {WIDTH/4,HEIGHT/3,0};
    struct position playerPos   = {WIDTH/2,HEIGHT/2,0};
	struct position enemyPos    = {WIDTH/4,HEIGHT/2,90};
	struct position enemyPos1   = {WIDTH/2,HEIGHT/4,180};
	struct position enemyPos2   = {3*WIDTH/4,HEIGHT/2,270};
	struct size playerDim	    = {16,16};	//same for enemies

	struct position dropPosP    = {WIDTH/8,HEIGHT/8,0};
	struct position dropPosW    = {7*WIDTH/8,HEIGHT/8,0};
	struct position dropPosA    = {WIDTH/2,HEIGHT/8,0};
		
    struct texture gameoverClr;  //defaults to white 

	    //auxiliary
	char dropType_1[2] = {'P','S'}; 	//(P)otion-(S)imple
	char dropType_2[2] = {'W','P'};		//(W)eapon-(P)istol
	char dropType_3[2] = {'A','N'};		//(A)mmo-(N)ormal
       
    char* gameover_str = (char*)"GAME OVER!";
    
    srand(time(NULL));

GAME:
    //MENU
    quit = false;
    cont = true;
    do{
        char option = printMenu(&plotter);
        if(option == '3'){
            plotter.setQuit(true);
	        return 0;
        }else if(option == '2'){
            cont = printScoreBoard(&plotter);
            if(!cont){
                plotter.setQuit(true);
	            return 0;
            }
        }else{break;}
    }while(cont);
    
    //RESET
    spawn_time  = true;
    first_blood = true;
    BT_STATUS   = 0;
    gettimeofday(&bullet_time,NULL);
    gettimeofday(&t_cooldown,NULL);
    t_0   = time(NULL);
    bullet_time.tv_sec -= 30;
    score = 0;
    number_of_enemies = 0;

    playerPos   = {WIDTH/2,HEIGHT/2,0};
	jugador	    = createPlayer(playerDim,&playerPos);//16X16@MIDDLE OF SCREEN
    
    createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos);
	createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos1);
	createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos2);
	
    createDrop(&droppables, &number_of_droppables,&dropPosP);	//taken==false by default
	createDrop(&droppables, &number_of_droppables,&dropPosW);
	createDrop(&droppables, &number_of_droppables,&dropPosA);
		//further settings
	setCurrentType(droppables,dropType_1);
	setCurrentType((droppables+1),dropType_2);
	setCurrentType((droppables+2),dropType_3);

    //CLEAR SCREEN AND INITIAL PLOTS
	plotter.clear();
    printUserInterface(&jugador, &bars, &number_of_bars, score, &plotter);
	plotVisibleComponents(&plotter, jugador, bars, number_of_bars, bullets, number_of_bullets, enemies, number_of_enemies, droppables, number_of_droppables);


	//GAME LOOP VARs
	playerPos = getPosition(&(jugador.obj));	//object.h function
	char letter = '\0';
	while(letter != '0')
	{
 
        //SPAWN ENEMIES AND DROPPABLES
        if(score%10!=0)  spawn_time = true;
        if(score%10==0&&spawn_time){
            spawnDroppable(&droppables, &number_of_droppables, jugador.health, jugador.ammo);
            spawnEnemy(&enemies, &number_of_enemies, jugador.obj, score);
            spawn_time = false;
        }
        if(number_of_enemies<1){
            while(number_of_enemies<3){
                spawnEnemy(&enemies, &number_of_enemies, jugador.obj, score);
            }
        }

        if((BT_STATUS=bulletTimeStatus(bullet_time)) == 2)  setBulletTime(&bullet_time, false, &(jugador.health), &first_blood);
        if(letter=='R'){
        //TEST BULLETIME
            BT_STATUS = bulletTimeStatus(bullet_time);
            if(BT_STATUS==1){
                fprintf(stdout,"Bullet time still active!\n");
            }else if(BT_STATUS==-1){
                fprintf(stderr,"Elapsed time inside bullet_time is negative!\n");
            }else{
                fprintf(stdout,"BULLET TIME: %s\n",(BT_STATUS==0) ? "SET" : "UNSET");
                setBulletTime(&bullet_time,(BT_STATUS==0), &(jugador.health), &first_blood);
            }

        }else if(letter=='L'){
        //DEBUG. LIST ALL VARIABLES.
            fprintf(stdout,"GLOBAL, RATE PLAYER: %d\n",RATE_MVMT_PLAYER);
            fprintf(stdout,"GLOBAL, RATE ENEMY: %d\n",RATE_MVMT_ENEMY);
            fprintf(stdout,"GLOBAL, RATE BULLET: %d\n",RATE_MVMT_BULLET);
            fprintf(stdout,"PLAYER AMMO: %d\n",jugador.ammo);
            fprintf(stdout,"PLAYER HEALTH: %d\n",jugador.health);
            fprintf(stdout,"PLAYER DIR: %d\n",playerPos.direction);
			fprintf(stdout,"PLAYER x: %d\n",playerPos.x);
			fprintf(stdout,"PLAYER y: %d\n",playerPos.y);
            fprintf(stdout,"FIRST BLOOD: %s\n",(first_blood) ? "TRUE": "FALSE");

		}else if (letter==' '){
		//SHOOT
            if(hasAmmo(&jugador)&&(!onCooldown(&t_cooldown, jugador.player_weapon))){  
                //if player has ammo and a weapon.
                createBullet(&(jugador.obj), &bullets, &number_of_bullets, jugador.player_weapon, jugador.ammo_type);
                jugador.ammo--;
            }
		}else{
            //MOVEMENT:
                //collision with droppables
            if(number_of_droppables>0){
                  
                for(int i=0;i<number_of_droppables;i++){
                    if(player_droppable_collision(&jugador,(droppables+i),letter,RATE_MVMT_PLAYER)){
                        
                        switch((droppables+i)->currentType){
                            case 'A':
                                jugador.ammo_type = (droppables+i)->type.drop_ammo;                 
                                jugador.ammo      = (jugador.ammo+30 > 50) ? 50 : jugador.ammo+30;
                                break;

                            case 'P':
                                if((droppables+i)->type.drop_potion == SIMPLE){
                                    jugador.health = (jugador.health+20 > 100) ? 100 : jugador.health+20;

                                }else{
                                    jugador.health = 100;                                          
                                }
                                break;
                        
                            case 'W':
                                jugador.player_weapon = (droppables+i)->type.drop_weapon;
                                break;

                            default:
                                break;
                        }                            
                        break;
                    }
                }
                for(int i=0;i<number_of_droppables;i++){
                    //cleaning and freeing droppables that have been taken.
                    if((droppables+i)->taken){
                        struct position removedPos = {0,0,0};
                        struct size removedSize    =  {0,0};                        

                        (droppables+i)->dropObj.posObj  = removedPos;
                        (droppables+i)->dropObj.sizeObj = removedSize;
                    
                        free((droppables+i)->dropObj.textureObj);
                        deleteDroppable(&droppables,&number_of_droppables,i);
                        break;
                    }
                }
                
            }
            //TODO: Try collision logic implementation. player_enemy_collision() and border_collision
        
            bool playerBorderCol = false;
            bool playerEnemyCol  = false;
            for(int i=0;i<number_of_enemies;i++){
                if(player_enemy_collision(&jugador,(enemies+i),letter,RATE_MVMT_PLAYER)){
                    playerEnemyCol = true;
                    break;
                }
            }
            playerBorderCol = border_collision(&(jugador.obj),letter,RATE_MVMT_PLAYER);

            if(!playerEnemyCol&&!playerBorderCol){ //if there is no collision we can update player position safely.
                struct position updatedPos = changePosition(&(jugador.obj),letter,RATE_MVMT_PLAYER);
		        playerPos.x 	    += updatedPos.x;
		        playerPos.y 	    += updatedPos.y;
		        playerPos.direction += updatedPos.direction;
		    }
        
        }
            //BULLET collision
        if(number_of_bullets > 0){
            for(int i=0;i<number_of_bullets;i++){
                if(bullet_player_collision((bullets+i),&jugador)){
                    deleteBullet(&bullets,&number_of_bullets,i);
                    break;
                }
            }
            if(!isAlive(&jugador)){
                
                //END GAME        
                plotText(gameover_str, gameoverPos, gameoverClr, 8, 1, &plotter);
                plotter.update();
                while((time(NULL)-t_0)<=5);

                if(!printSaveScore(&plotter, score))    quit = true;
                goto END;
            }
        }
        if(number_of_bullets > 0){
            for(int i=0;i<number_of_enemies;i++){            
                for(int j=0;j<number_of_bullets;j++){
                    if(bullet_enemy_collision((bullets+j),(enemies+i))){
                        deleteBullet(&bullets,&number_of_bullets,j);
                        break;
                    }                
                }
                if(!isAlive((enemies+i))){
                    deleteEnemy(&enemies,&number_of_enemies,i);
                    score += 10;
                    first_blood = true;
                    break;
                }
            }
        }
  
		//update player new  position, health, ammo bar and score.
        setPosition(&(jugador.obj),&playerPos); 
        updateScore(&t_0,&score);
        //clears, updates bars and prints user interface and rest of components again.
		plotter.clear();
		printUserInterface(&jugador, &bars, &number_of_bars, score, &plotter);
		plotVisibleComponents(&plotter, jugador, bars, number_of_bars, bullets, number_of_bullets, enemies, number_of_enemies, droppables, number_of_droppables);

		//updates the position of all bullets
		updateBulletPos(&bullets,&number_of_bullets);

		//updates the enemies
		updateEnemyBehavior(&enemies, number_of_enemies,jugador, &bullets, &number_of_bullets);

		
        //updates plotter, checks for key hit.
        plotter.update(); //neccessary? YES!
		bool keyhit = plotter.kbhit();
		if (keyhit){
			letter = plotter.getKey();
		}else{
			letter = '\0';  //keeps the box from moving all the time in the last dir.
		}
	}

END:
    
    int i;
	//free all visible components dyn allocated struct texture[]
	free(jugador.obj.textureObj);
	for(i=0; i<number_of_enemies; i++){
        free((enemies+i)->obj.textureObj);
    }
    for(i=0; number_of_bars>0;){
        deleteBar(&bars,&number_of_bars,i);
    }
	for(i=0; number_of_droppables>0;){
        deleteDroppable(&droppables,&number_of_droppables,i);
    }
	for(i=0; number_of_bullets>0;){
        deleteBullet(&bullets,&number_of_bullets,i);
    }

    if(!quit){
        goto GAME;
    }else{
	    plotter.setQuit(true);
	    return 0;
    }
}
