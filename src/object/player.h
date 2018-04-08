/*
 * PLAYER.C FILE: INFO AND FUNCTIONS ABOUT THE PLAYERs OBJ.
 * @author leba39, mortonman.
 */
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>
#include "object.h"
#include "ammo.h"
#include "weapon.h"
#include "../graphic/screen.h"
#include "../graphic/SDL_Plotter.h"

//S T R U C T s

/**	STRUCT: PlayerObj
 *PURPOSE: Holds the health and ammo variables relavent to the player class,
 *	   as well as standard object variables.
 *@data int health, ammo	The player's health and ammo. Both default to 100.
 *	  struct obj  	 	Object struct for the player, will contain texture, size, and position.
 */
struct PlayerObj{

	struct object obj;
	int health = 100;
	int ammo   = 50;
	enum weapon player_weapon  = NO_WEAPON;
	enum ammunition ammo_type  = NORMAL;
	//...	
};

//F U N C T I O N s

/**	FUNCTION: setHealth
 *PURPOSE: Sets the health of a player to a given int.
 *PRECONDITION: Valid non null PlayerObj* and valid int.
 *POSTCONDITION: The health variable of the player object is set to the given int.
 *@params PlayerObj* player	The player that's health is being modified.
 *	  int hp		The value for the player's health to be set to.
 */void setHealth(struct PlayerObj* player,int hp);

/**	FUNCTION: getHealth
 *PURPOSE: Returns the health of a player.
 *PRECONDITION: Valid non null PlayerObj*.
 *@params PlayerObj* player	The player that's health is being returned.
 *@return int			The health variable of the player object.
 */int getHealth(struct PlayerObj* player);

/**	FUNCTION: setAmmo
 *PURPOSE: Sets the ammo of a player to a given int.
 *PRECONDITION: Valid non null PlayerObj* and valid int.
 *POSTCONDITION: The ammo variable of the player object is set to the given int.
 *@params PlayerObj* player	The player that's ammo is being modified.
 *	  int munition		The value for the player's ammo to be set to.
 */void setAmmo(struct PlayerObj* player,int munition);

/**	FUNCTION: getAmmo
 *PURPOSE: Returns the Ammo of a player.
 *PRECONDITION: Valid non null PlayerObj*.
 *@params PlayerObj* player	The player that's ammo is being returned.
 *@return int			The ammo variable of the player object.
 */int getAmmo(struct PlayerObj* player);

/**	FUNCTION: isAlive
 *PURPOSE: Returns a boolean value based on the health of a player. 
 *PRECONDITION: Valid non null PlayerObj*.
 *@params PlayerObj* player	The player that's ammo is being returned.
 *@return bool			True if health is < 0, false otherwise.
 */bool isAlive(struct PlayerObj* player);

/**	FUNCTION: hasAmmo
 *PURPOSE: Returns a boolean value based on the ammo of a player. 
 *PRECONDITION: Valid non null PlayerObj*.
 *@params PlayerObj* player	The player that's ammo is being returned.
 *@return bool			True if ammo is < 0, false otherwise.
 */bool hasAmmo(struct PlayerObj* player);

/**	FUNCTION: plotPlayer
 *PURPOSE: Plots a player object on the screen.
 *PRECONDITION: Valid non null PlayerObj with valid object variables and a valid non null SDL_Plotter*.
 *@params PlayerObj* player	The player that is being plotted.
 *	  SDL_Plotter* plot	The plotter onto which the player object is being plotted.
 */void plotPlayer(struct PlayerObj player,SDL_Plotter* plot);

/**	FUNCTION: createPlayer
 *PURPOSE: Plots a player object on the screen.
 *PRECONDITION: valid ints, j and i must be within screen limits, dir must be between 0 and 359.
 *@params struct size		The height and width of a player object.
 *	  struct position*	The position values of the player object. Struct position pointer.
 *@return PlayerObj	A player with the given size and postion variables. 
 */struct PlayerObj createPlayer(struct size dim, struct position* pos);

#endif
