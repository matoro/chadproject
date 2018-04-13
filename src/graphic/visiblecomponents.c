#include "visiblecomponents.h"



void plotVisibleComponents(SDL_Plotter *plot, struct PlayerObj player, struct BarObj *bars, int number_of_bars, struct BulletObj *bullets, int number_of_bullets){
	plotPlayer(player, plot);
	if(bars != NULL) for(int i = 0; i < number_of_bars; i++) plotBar(&(*(bars+i)), plot);
	if(bullets != NULL) for(int i = 0; i < number_of_bullets; i++) plotBullet(&(*(bullets+i)), plot);
	//add more for each object type
}	
