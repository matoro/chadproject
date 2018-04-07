/*
 * ENEMY.H FILE: INFO AND FUNCTIONS ABOUT ENEMY OBJ.
 * @author leba39, mortonman.
 */
#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <stdbool.h>
#include "object.h"
#include "../graphic/screen.h"
#include "../graphic/SDL_Plotter.h"

//S T R U C T s

/**	STRUCT: EnemyObj
 *PURPOSE: Holds the health and ammo variables relavent to the enemy class,
 *	   as well as standard object variables.
 *@data int health, ammo	The enemy's health and ammo. Both default to 100.
 *	struct obj  	 	Object struct for the enemy, will contain texture, size, and position.
 *	bool active		Wether the behaviour of the enemy is active (true) or passive (false).
 *	bool seesPlyr		Boolean who represents if this component is prepared to shoot or not.
 *	int fov			The enemys fov. It will chase the player once on sight and shoot it 
 *				if it cans (ammo).
 */
struct EnemyObj{

	struct object obj;
	int health  = 100;
	int ammo    = 100;
	int fov     = 60;
	bool active = false;
	bool sight  = false;
	//enums for type of weapon and ammo go here. Dont forget the includes as well when this component merges into 'testing'
	//...	
};

//F U N C T I O N s

/**	FUNCTION: setHealth
 *PURPOSE: Sets the health of an enemy to a given int.
 *PRECONDITION: Valid non null EnemyObj* and valid int.
 *POSTCONDITION: The health variable of the enemy object is set to the given int.
 *@params EnemyObj* enemy	The enemy whos health is being modified.
 *	  int hp		The value for the enemy's health to be set to.
 */void setHealth(struct EnemyObj* enemy,int hp);

/**	FUNCTION: getHealth
 *PURPOSE: Returns the health of an enemy.
 *PRECONDITION: Valid non null EnemyObj*.
 *@params EnemyObj* enemy	The enemy whos health is being returned.
 *@return int			The health variable of the enemy object.
 */int getHealth(struct EnemyObj* enemy);

/**	FUNCTION: setAmmo
 *PURPOSE: Sets the ammo of an enemy to a given int.
 *PRECONDITION: Valid non null EnemyObj* and valid int.
 *POSTCONDITION: The ammo variable of the enemy object is set to the given int.
 *@params EnemyObj* enemy	The enemy whos ammo is being modified.
 *	  int munition		The value for the enemy's ammo to be set to.
 */void setAmmo(struct EnemyObj* enemy,int munition);

/**	FUNCTION: getAmmo
 *PURPOSE: Returns the Ammo of an enemy.
 *PRECONDITION: Valid non null EnemyObj*.
 *@params EnemyObj* enemy	The enemy whos  ammo is being returned.
 *@return int			The ammo variable of the enemy object.
 */int getAmmo(struct EnemyObj* enemy);

/**	FUNCTION: setFOV
 *PURPOSE: Sets the fov of an enemy to a given int.
 *PRECONDITION: Valid non null EnemyObj* and valid int.
 *POSTCONDITION: The fov variable of the enemy object is set to the given int.
 *@params EnemyObj* enemy	The enemy whos fov is being modified.
 *	  int fieldofview	The value for the enemy's fov to be set to.
 */void setFOV(struct EnemyObj* enemy,int fieldofview);

/**	FUNCTION: getFOV
 *PURPOSE: Returns the FOV of an enemy.
 *PRECONDITION: Valid non null EnemyObj*.
 *@params EnemyObj* enemy	The enemy whos  fov is being returned.
 *@return int			The fov variable of the enemy object.
 */int getFOV(struct EnemyObj* enemy);

/**	FUNCTION: setBehaviour
 *PURPOSE: Sets the behaviour of an enemy.
 *PRECONDITION: Valid non null EnemyObj* and valid int.
 *POSTCONDITION: The passive/active mode and sight is set accordingly.
 *@params EnemyObj* enemy	The enemy whos states are being modified.
 *	  bool active		The enemy mode. True active, false passive.
 *	  bool sight 		The enemy sight. True if the player is on sight.
 */void setBehaviour(struct EnemyObj* enemy,bool active,bool sight);

/**	FUNCTION: isAlive
 *PURPOSE: Returns a boolean value based on the health of an enemy. 
 *PRECONDITION: Valid non null EnemyObj*.
 *@params EnemyObj* enemy	The enemy whos ammo is being returned.
 *@return bool			True if health is < 0, false otherwise.
 */bool isAlive(struct EnemyObj* enemy);

/**	FUNCTION: hasAmmo
 *PURPOSE: Returns a boolean value based on the ammo of an enemy. 
 *PRECONDITION: Valid non null EnemyObj*.
 *@params EnemyObj* enemy	The enemy whos ammo is being returned.
 *@return bool			True if ammo is < 0, false otherwise.
 */bool hasAmmo(struct EnemyObj* enemy);

/**	FUNCTION: isActive
 *PURPOSE: Returns a boolean value based on current enemy mode. 
 *PRECONDITION: Valid non null EnemyObj*.
 *@params EnemyObj* enemy	The enemy whos active var is being returned.
 *@return bool			True if enemy is active and chasing, false otherwise.
 */bool isActive(struct EnemyObj* enemy);

/**	FUNCTION: seesPlayer
 *PURPOSE: Returns a boolean value based on the enemy current fov of the player. 
 *PRECONDITION: Valid non null EnemyObj*.
 *@params EnemyObj* enemy	The enemy object whos state is being returned.
 *@return bool			True if player is on sight, false otherwise.
 */bool seesPlayer(struct EnemyObj* enemy);

/**	FUNCTION: plotEnemy
 *PURPOSE: Plots an enemy object on the screen.
 *PRECONDITION: Valid non null EnemyObj* with valid object variables and a valid non null SDL_Plotter*.
 *@params EnemyObj* enemy	The enemy that is being plotted.
 *	  SDL_Plotter* plot	The plotter onto which the enemy object is being plotted.
 */void plotEnemy(struct EnemyObj enemy,SDL_Plotter* plot);

/**	FUNCTION: createPlayer
 *PURPOSE: Plots an enemy object on the screen.
 *PRECONDITION: valid ints, j and i must be within screen limits, dir must be between 0 and 359.
 *@params struct size		The height and width of an enemy object.
 *	  struct position	The position values of the enemy object.
 *@return EnemyObj	A enemy with the given size and postion variables. 
 */struct EnemyObj createEnemy(struct size dim, struct position pos);

#endif
