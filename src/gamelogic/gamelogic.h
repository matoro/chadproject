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
#include "../collision/collision.h"

//D E F I N E
#define PI 3.14

//F U N C T I O N s


/*      FUNCTION: spawnDroppable
 *PURPOSE:          Spawns a droppable on the map of a random type when the probability is matched (20% success).
 *                  This increases with low hp and ammo. 
 *PRECONDITION:     Valid droppable and num_droppables pointers.
 *POSTCONDITION:    Droppable will be located on a random yet valid position of the map.
 *@params           struct Droppable** droppables   Double pointer to droppables main array.
 *                  int* num_droppables             Pointer to the variable holding the number of droppables in-game.
 *                  int hp                          Current player health points.
 *                  int ammo                        Current player ammo.
 */void spawnDroppable(struct Droppable** droppables, int* num_droppables, int hp, int ammo);

/*      FUNCTION: spawnEnemy
 *PURPOSE:          Spawns an enemy on the map on a ramdon location pointing at the players current position. 
 *                  Probability base of 15% success, increases with score. Function checks that new enemy does not collide with the player.
 *PRECONDITION:     Valid enemies and num_enemies pointers.
 *POSTCONDITION:    Enemy will be spawned on a random yet valid position of the map looking at the player.
 *@params           struct EnemyObj** enemies       Double pointer to enemies main array.
 *                  int* num_enemies                Pointer to the variable holding the number of enemies in-game.
 *                  struct object player_obj        Value of the players object struct. It is used to properly set the new enemy direction.
 *                  int score                       Current player ammo.
 */void spawnEnemy(struct EnemyObj** enemies, int* num_enemies, struct object player_obj, int score);

/*      FUNCTION: getRandomPos
 *PURPOSE:          Returns a struct position with a random yet valid location of the map. It avoids locations near the borders.
 *POSTCONDITION:    Random struct position is returned.
 *@return           struct posotion                 Random struct position. Direction value set to 0.
 */struct position getRandomPos();

/*      FUNCTION: setEnemyDirection
 *PURPOSE:          Given an enemy and player position, sets the enemy position struct to point at the player.
 *PRECONDITION:     Valid enemy_pos pointer and well formed player_pos.
 *POSTCONDITION:    Enemy position direction will be set so it points directly at the players current location.
 *@params           struct position* enemy_pos      Pointer to the enemy position struct.
 *                  struct position player_pos      Value of the players position struct.
 */void setEnemyDirection(struct position* enemy_pos, struct position player_pos);

#endif
