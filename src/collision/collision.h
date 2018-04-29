/*
 *  COLLISION.H
 *  @authors leba39, mortonman. 
 */
#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

//I N C L U D E s
#include <stdbool.h>

#include "../object/player.h"
#include "../object/enemy.h"

//F U N C T I O N s

/*      FUNCTION: mapObject
 *PURPOSE:          maps an entire object and save all of its (x,y) points in a struct size* (recycled from object.h)
 *PRECONDITION:     valid object pointer.
 *POSTCONDITION:    objMap will be allocated with all 'obj' points. An int is returned, who hold the length of the struct size[]
 *@params           struct object* obj          Pointer to an object.
 *                  struct size* objMap         Pointer to a struct size.
 *@return           int                         Lenght of objMap  
 */int mapObject(struct object* obj, struct size* objMap);

/*      FUNCTION: checkOverlap
 *PURPOSE:          checks if two object maps have some points in common;if so, returns true.
 *PRECONDITION:     valid object pointers.
 *POSTCONDITION:    Returns false if obj_1 and obj_2 are NOT colliding.
 *@params           struct object* obj_1        Pointer to the first object.
 *                  struct object* obj_2        Pointer to the second object.
 *@return           bool                        True if they collide.
 */bool checkOverlap(struct object* obj_1,struct object* objMap_2);

/*      FUNCTION: enemy_player_collision  
 *PURPOSE:          Handle if the next movement of a player collides with an enemy; if so, don't update player position.
 *PRECONDITION:     Valid player and enemy pointers.
 *POSTCONDITION:    Player gets its position updated in corcondance to the next user movement but it stays the same
 *                  otherwise.
 *@params           struct PlayerObj* player    Pointer to the player.
 *                  struct EnemyObj* enemy      Pointer to the enemy.
 *                  char movement               Char representing desired player movement. 
 */void player_enemy_collision(struct PlayerObj* player, struct EnemyObj* enemy,char movement);

//... rest of collision functions ...

#endif
