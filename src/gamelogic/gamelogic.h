/*
 *  -GAMELOGIC COMPONENT DECLARATION-
 *  @author leba39, mortonman.
 */
#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

//I N C L U D E s
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "../object/droppable.h"
#include "../object/enemy.h"
#include "../graphic/screen.h"//I only want the CONSTs, next time put them all in separate file
//D E F I N E
#define PI 3.14

//D E C L A R A T I O N
void spawnDroppable(struct Droppable** droppables, int* num_droppables, int hp, int ammo);

void spawnEnemy(struct EnemyObj** enemies, int* num_enemies, struct object player_obj, int score);

struct position getRandomPos();

void setEnemyDirection(struct position* enemy_pos, struct position player_pos);

#endif
