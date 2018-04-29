/*
 *TESTING SDLLIB2
 *GAME TESTING
 */


#include <stdio.h>
#include <stdlib.h>
//#include <math.h>	//include math inside object/screen?
#include <stdbool.h>

#include "graphic/visiblecomponents.h"
#include "graphic/screen.h"	//Contains SDL and plotting functions
#include "collision/collision.h"

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
	

	struct position healthBarPos = {WIDTH/6,7*HEIGHT/8,0};
	struct position ammoBarPos   = {3*WIDTH/4,7*HEIGHT/8,0};
	enum bartype health          = HEALTH;
	enum bartype ammo 	         = AMMO;

	struct position dropPosP     = {WIDTH/8,HEIGHT/8,0};
	struct position dropPosW     = {7*WIDTH/8,HEIGHT/8,0};
	struct position dropPosA     = {WIDTH/2,HEIGHT/8,0};
		
	//AUXILIARY
	char dropType_1[2] = {'P','S'}; 	//POTION-SIMPLE
	char dropType_2[2] = {'W','P'};		//WEAPON-PISTOL
	char dropType_3[2] = {'A','N'};		//AMMO-NORMAL

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


	//DEFINITON
	jugador	  = createPlayer(playerDim,&playerPos);//16X16@MIDDLE OF SCREEN
	createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos);
	createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos1);
	createEnemy(&enemies,&number_of_enemies,playerDim,&enemyPos2);
	createBar(&bars, &number_of_bars, &jugador,health,healthBarPos);
	createBar(&bars, &number_of_bars, &jugador,ammo, ammoBarPos);
	createDrop(&droppables, &number_of_droppables,&dropPosP);	//taken==false by default
	createDrop(&droppables, &number_of_droppables,&dropPosW);
	createDrop(&droppables, &number_of_droppables,&dropPosA);
		//FURTHER SETTINGS
	setCurrentType(droppables,dropType_1);
	setCurrentType((droppables+1),dropType_2);
	setCurrentType((droppables+2),dropType_3);


	//CLEAR SCREEN
	plotter.clear();
	//PLOTS
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
			createBullet(&(jugador.obj), &bullets, &number_of_bullets);
		}else{
        //TODO: Try collision logic implementation. player_enemy_collision()
        
            bool playerEnemyCol = false;
            for(int i=0;i<number_of_enemies;i++){
                if(player_enemy_collision(&jugador,(enemies+i),letter,6)){
                    playerEnemyCol = true;
                    break;
                }
            }
            if(!playerEnemyCol){ //if there is no collision we can update safely.
                struct position updatedPos = changePosition(&(jugador.obj),letter,6);
		        playerPos.x 	    += updatedPos.x;
		        playerPos.y 	    += updatedPos.y;
		        playerPos.direction += updatedPos.direction;
		    }
        
        }

		//update player new  position, health bar.
		setPosition(&(jugador.obj),&playerPos); 
		setCurrentValue(bars,jugador.health);			
		setCurrentValue((bars+1),jugador.ammo);			

		//TODO: Implement checking and clean code!

		plotter.clear();
		plotVisibleComponents(&plotter, jugador, bars, number_of_bars, bullets, number_of_bullets, enemies, number_of_enemies, droppables, number_of_droppables);

		//updates the position of all bullets
		updateBulletPos(&bullets,&number_of_bullets);

        //plotText test
    	plotText(test_msg,textPos,fontColor,fontSize,thinSize,&plotter);     //screen.h function
        plotText(test_string,stringPos,colorString,2,0,&plotter);        

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
