/*
 *  COLLISION.H
 *  @authors leba39, mortonman. 
 */
#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED

//I N C L U D E s
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "../object/player.h"
#include "../object/enemy.h"
#include "../object/droppable.h"
#include "../object/bullet.h"
#include "../graphic/screen.h" 

//F U N C T I O N s

/*      FUNCTION: mapObject
 *PURPOSE:          maps an entire object and save all of its (x,y) points in a struct size* (recycled from object.h)
 *PRECONDITION:     valid object pointer.
 *POSTCONDITION:    objMap will be allocated with all 'obj' points. An int is returned, who hold the length of the struct size[]
 *@params           struct object* obj          Pointer to an object.
 *                  struct size* objMap         Pointer to a struct size.
 *@return           int                         Lenght of objMap  
 */int mapObject(struct object* obj, struct size** objMap);

/*      FUNCTION: checkOverlap
 *PURPOSE:          checks if two object maps have some points in common;if so, returns true.
 *PRECONDITION:     valid object pointers.
 *POSTCONDITION:    Returns false if obj_1 and obj_2 are NOT colliding.
 *@params           struct object* firstObj     Pointer to the first object.
 *                  struct object* secondObj    Pointer to the second object.
 *@return           bool                        True if they collide.
 */bool checkOverlap(struct object* firstObj,struct object* secondObj);

/*      FUNCTION: player_enemy_collision  
 *PURPOSE:          Handle if the next movement of a player collides with an enemy; if so, don't update player position.
 *PRECONDITION:     Valid player and enemy pointers.
 *POSTCONDITION:    Player gets gets permission to update its position in corcondance to the next user movement but it stays the same
 *                  otherwise.
 *@params           struct PlayerObj* player    Pointer to the player.
 *                  struct EnemyObj* enemy      Pointer to the enemy.
 *                  char movement               Char representing desired player movement.
 *                  int rate                    Rate of movement.
 *@return           bool                        True if there is collision 
 */bool player_enemy_collision(struct PlayerObj* player, struct EnemyObj* enemy,char movement,int rate);

/*      FUNCTION: player_droppable_collision  
 *PURPOSE:          Handle if the next movement of a player collides with a droppable; if so, change droppable taken boolean to 'true'.
 *PRECONDITION:     Valid player and droppable pointers.
 *POSTCONDITION:    Droppable gets 'taken'.
 *@params           struct PlayerObj* player    Pointer to the player.
 *                  struct Droppable* drop      Pointer to the droppable.
 *                  char movement               Char representing next player movement.
 *                  int rate                    Rate of movement.
 *@return           bool                        True if there is collision 
 */bool player_droppable_collision(struct PlayerObj* player, struct Droppable* drop,char movement,int rate);

/*      FUNCTION: bullet_player_collision  
 *PURPOSE:          Handle if the passed bullet collides with the player; if so, reduce players health and returns true.
 *PRECONDITION:     Valid player and bullet pointers.
 *POSTCONDITION:    Players health gets cut.
 *@params           struct BulletObj* bullet    Pointer to the bullet.
 *                  struct PlayerObj* player    Pointer to the player.
 *@return           bool                        True if there is collision 
 */bool bullet_player_collision(struct BulletObj* bullet, struct PlayerObj* player);

/*      FUNCTION: bullet_enemy_collision  
 *PURPOSE:          Handle if the passed bullet collides with an enemy; if so, reduce enemys health and returns true.
 *PRECONDITION:     Valid enemy and bullet pointers.
 *POSTCONDITION:    Enemys health gets cut.
 *@params           struct BulletObj* bullet    Pointer to the bullet.
 *                  struct EnemyObj* enemy      Pointer to the player.
 *@return           bool                        True if there is collision 
 */bool bullet_enemy_collision(struct BulletObj* bullet, struct EnemyObj* enemy);

/*      FUNCTION:   enemy_enemies_collision  
 *PURPOSE:          Handles if the next movement of an enemy collides with another enemy; returns response as a boolean.
 *PRECONDITION:     Valid enemy(single) and enemies(array) pointers.
 *POSTCONDITION:    Enemy gets permission to update its position.
 *                  
 *@params           struct EnemyObj* enemy      Pointer to the enemy.
 *                  char movement               Char representing next movement
 *                  int rate                    Rate of movement.
 *                  struct EnemyObj** enemies   Pointer to the enemies array.
 *                  int number_enemies          Number of enemies onplay.
 *@return           bool                        True if there is collision 
 */bool enemy_enemies_collision(struct EnemyObj* enemy,char movement,int rate, struct EnemyObj** enemies, int number_enemies);


bool border_collision(struct object* obj, char movement, int rate);

//... rest of collision functions ...

#endif
