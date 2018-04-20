#include "visiblecomponents.h"



void plotVisibleComponents(SDL_Plotter *plot, struct PlayerObj player, struct BarObj *bars, int number_of_bars, struct BulletObj *bullets, int number_of_bullets, struct EnemyObj *enemies, int number_of_enemies, struct Droppable *droppables, int number_of_droppables){
	plotPlayer(player, plot);
	if(bars) for(int i = 0; i < number_of_bars; i++) plotBar(&(*(bars+i)), plot);
	if(bullets) for(int i = 0; i < number_of_bullets; i++) plotBullet(&(*(bullets+i)), plot);
	if(enemies) for(int i = 0; i < number_of_enemies; i++) plotEnemy(*(enemies+i), plot);
	if(droppables) for(int i = 0; i < number_of_droppables; i++) plotDrop(&(*(droppables+i)), plot);
	//add more for each object type
}	
