/*
 *TESTING SDLLIB2
 *GAME TESTING
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graphic/visiblecomponents.h"
#include "graphic/screen.h"	            //Contains SDL and plotting functions
#include "collision/collision.h"
#include "userinterface/ui.h"

int main(){

	//VARs DECLARATION
	SDL_Plotter plotter(HEIGHT,WIDTH); 	//CONSTANTS DEFINED IN screen.h

	struct PlayerObj jugador;
			
	struct BarObj    *bars = NULL;
	int number_of_bars = 0;
	
    struct BulletObj *bullets = NULL;
	int number_of_bullets = 0;
	
    struct EnemyObj  *enemies = NULL;
	int number_of_enemies = 0;
	
    struct Droppable *droppables = NULL;
	int number_of_droppables = 0;

	struct position playerPos    = {WIDTH/2,HEIGHT/2,0};
	struct position enemyPos     = {WIDTH/4,HEIGHT/2,90};
	struct position enemyPos1    = {WIDTH/2,HEIGHT/4,180};
	struct position enemyPos2    = {3*WIDTH/4,HEIGHT/2,270};
	struct size playerDim	     = {16,16};	//same for enemies
	
/*
	struct position healthBarPos = {WIDTH/6,7*HEIGHT/8,0};
	struct position ammoBarPos   = {3*WIDTH/4,7*HEIGHT/8,0};
	enum bartype health          = HEALTH;
	enum bartype ammo 	         = AMMO;
*/

	struct position dropPosP     = {WIDTH/8,HEIGHT/8,0};
	struct position dropPosW     = {7*WIDTH/8,HEIGHT/8,0};
	struct position dropPosA     = {WIDTH/2,HEIGHT/8,0};
		
	//AUXILIARY
	char dropType_1[2] = {'P','S'}; 	//POTION-SIMPLE
	char dropType_2[2] = {'W','P'};		//WEAPON-PISTOL
	char dropType_3[2] = {'A','N'};		//AMMO-NORMAL

/*
	char test_msg[]              = "+-1234567890";
    char test_string[]           = "matoro, mortonman and leba! How are you doing?";
    int fontSize                 = 4;
    char thinSize                = 1;
    struct position textPos      = {WIDTH/2,7*HEIGHT/8,0};
    struct texture fontColor; 
    fontColor.red   = 10;
    fontColor.green = 40;
    fontColor.blue  = 215;
    
    struct position stringPos   = {WIDTH/4,3*HEIGHT/8};
    struct texture colorString;
    colorString.red   = 105;
    colorString.green = 0;
    colorString.blue  = 110;
*/

	//DEFINITON
	jugador	  = createPlayer(playerDim,&playerPos);//16X16@MIDDLE OF SCREEN
	createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos);
	createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos1);
	createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos2);
	
//  createBar(&bars, &number_of_bars, &jugador,health,healthBarPos);
//  createBar(&bars, &number_of_bars, &jugador,ammo, ammoBarPos);
	
    createDrop(&droppables, &number_of_droppables,&dropPosP);	//taken==false by default
	createDrop(&droppables, &number_of_droppables,&dropPosW);
	createDrop(&droppables, &number_of_droppables,&dropPosA);
		//FURTHER SETTINGS
	setCurrentType(droppables,dropType_1);
	setCurrentType((droppables+1),dropType_2);
	setCurrentType((droppables+2),dropType_3);


	//CLEAR SCREEN AND INITIAL PLOTS
	plotter.clear();
    printUserInterface(&jugador, &bars, &number_of_bars, &plotter);
	plotVisibleComponents(&plotter, jugador, bars, number_of_bars, bullets, number_of_bullets, enemies, number_of_enemies, droppables, number_of_droppables);


	//GAME LOOP VARs
	playerPos = getPosition(&(jugador.obj));	//object.h function
	char letter = '\0';

	while(letter != '0')
	{
		if (letter=='H'){
		//simple test for bar.
			jugador.health -= 5;
			fprintf(stdout,"PLAYER HEALTH: %d",jugador.health);
		}else if (letter=='G'){
		//simple test for bar.
            jugador.ammo -= 5;
			fprintf(stdout,"PLAYER AMMO: %d",jugador.ammo);
		}else if (letter==' '){
		//testing shooting
			if(hasAmmo(&jugador)&&(jugador.player_weapon!=NO_WEAPON)){  
                //if player has ammo and a weapon.
                createBullet(&(jugador.obj), &bullets, &number_of_bullets, jugador.player_weapon, jugador.ammo_type);
                jugador.ammo--;
            }
		}else{
            //MOVEMENT:

            //TODO: Try collision logic for droppables. player_droppable_collision()
            if(number_of_droppables>0){
                  
                for(int i=0;i<number_of_droppables;i++){
                    if(player_droppable_collision(&jugador,(droppables+i),letter,6)){
                        
                        switch((droppables+i)->currentType){
                            case 'A':
                                jugador.ammo_type = (droppables+i)->type.drop_ammo;                 
                                jugador.ammo      = (jugador.ammo+20 > 50) ? 50 : jugador.ammo+20;
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


            //TODO: Try collision logic implementation. player_enemy_collision()
        
            bool playerEnemyCol = false;
            for(int i=0;i<number_of_enemies;i++){
                if(player_enemy_collision(&jugador,(enemies+i),letter,6)){
                    playerEnemyCol = true;
                    break;
                }
            }
            if(!playerEnemyCol){ //if there is no collision we can update player position safely.
                struct position updatedPos = changePosition(&(jugador.obj),letter,6);
		        playerPos.x 	    += updatedPos.x;
		        playerPos.y 	    += updatedPos.y;
		        playerPos.direction += updatedPos.direction;
		    }
        
        }


        //TODO: Try bullet collision logic. bullet_player_collision() and bullet_enemy_collision()
        if(number_of_bullets > 0){
            for(int i=0;i<number_of_bullets;i++){
                if(bullet_player_collision((bullets+i),&jugador)){
                    deleteBullet(&bullets,&number_of_bullets,i);
                    break;
                }
            }
            if(!isAlive(&jugador)){
            //END GAME
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
                    break;
                }
            }
        }
  
		//update player new  position, health and ammo bar.

        setPosition(&(jugador.obj),&playerPos); 
/*
		setCurrentValue(bars,jugador.health);			
		setCurrentValue((bars+1),jugador.ammo);			
*/
        //clears, updates bars and prints user interface and rest of components again.
		plotter.clear();
		printUserInterface(&jugador, &bars, &number_of_bars, &plotter);
		plotVisibleComponents(&plotter, jugador, bars, number_of_bars, bullets, number_of_bullets, enemies, number_of_enemies, droppables, number_of_droppables);

		//updates the position of all bullets
		updateBulletPos(&bullets,&number_of_bullets);

/*
        //plotText test
    	plotText(test_msg,textPos,fontColor,fontSize,thinSize,&plotter);     //screen.h function
        plotText(test_string,stringPos,colorString,2,0,&plotter);        
*/
		plotter.update(); //neccessary? YES!
		
		bool keyhit = plotter.kbhit();
		if (keyhit){
			letter = plotter.getKey();
			//Debug traces
			fprintf(stdout,"PLAYER DIR: %d\n",playerPos.direction);
			fprintf(stdout,"PLAYER x: %d\n",playerPos.x);
			fprintf(stdout,"PLAYER y: %d\n",playerPos.y);
		}else{
			letter = '\0';
			//keeps the box from moving all the time in the last dir.
		}

	}
	//free all visible components dyn allocated struct texture[]
	free(jugador.obj.textureObj);
	//free object textures
	for(int i = 0; i < number_of_bars; i ++) free((bars+i)->obj.textureObj);
	for(int i = 0; i < number_of_enemies; i ++) free((enemies+i)->obj.textureObj);
	for(int i = 0; i < number_of_droppables; i ++) free((droppables+i)->dropObj.textureObj);
	//free objects
	free(bars);
	free(enemies);
	free(droppables);

	plotter.setQuit(true);

	return 0;
}
