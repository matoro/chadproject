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
#include <sys/time.h>

#include "globals.h"
#include "../object/droppable.h"
#include "../object/enemy.h"
#include "../object/weapon.h"
#include "../graphic/screen.h"          //I only want the CONSTs, next time put them all in separate file
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

/*      FUNCTION: updateScore
 *PURPOSE:          Given the current score and the time since the game started, it will increment the score accordingly.
 *PRECONDITION:     Valid time_t and current_score pointers. Score must be positive.
 *POSTCONDITION:    Score gets updated every second.
 *@params           struct time_t*  time_t          Pointer to the time_t holding game start time.
 *                  int*            current_score   Pointer to variable holding the games score.
 */void updateScore(time_t* t_0, int* current_score);

/*      FUNCTION: onCooldown
 *PURPOSE:          Given the current players weapon and the last time he shot it, it will return wether
 *                  if its on cooldown or not.
 *PRECONDITION:     Valid timeval pointer.
 *POSTCONDITION:    Checks for cooldown on the players weapon.
 *@params           struct timeval* t_last_shot     Pointer to the timeval holding the last time it was shot.
 *                  enum weapon     player_weapon   Value of the players weapon.
 *@return           bool                            True if its on cooldown and therefore player can't shoot. False otherwise.
 */bool onCooldown(struct timeval* t_last_shot, enum weapon player_weapon);

/*      FUNCTION: bulletTimeStatus
 *PURPOSE:          Given the value of the last time bullet-time action was used, it will return wether if its on cooldown,
 *                  if its ready to use again or if it is currently being used/activated.
 *POSTCONDITION:    Value representing the actual state of the bullet-time functionality is returned.
 *@params           struct timeval  t_last_end      Value of the last time bullet-time was used by the player.
 *@return           signed char                     Range[-1, 2]. -1 If there is something odd, 0 if there is no cooldown,
 *                                                  1 if bullet-time is going on and 2 if it is on cooldown.
 */signed char bulletTimeStatus(struct timeval t_last_end);

/*      FUNCTION: setBulletTime
 *PURPOSE:          Changes the values of the global variables holding the movement rates in order to set/unset bullet-time.
 *PRECONDITION:     Valid t_last_end, hp and first_blood pointers.
 *POSTCONDITION:    Values for the global variables will be modified accordingly.
 *@params           struct timeval* t_last_end      Pointer to the timeval struct holding the last time bullet time was used.
 *                  bool mode                       For logic purposes. True to SET, false to UNSET.
 *                  int* hp                         Pointer to the players current health points.
 *                  bool* first_blood               Pointer to boolean. It will be true if the player has recently killed an enemy,
 *                                                  making the price of the bullet-time action free for him. Otherwise it will cost
 *                                                  him 10 hp. 
 */void setBulletTime(struct timeval* t_last_end, bool mode, int* hp, bool* first_blood);

#endif
