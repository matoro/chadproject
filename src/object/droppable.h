/*
 * DROPPABLE.H -VISIBLE COMPONENT-
 * @author leba39, mortonmann.
 */
#ifndef DROPPABLE_H_INCLUDED
#define DROPPABLE_H_INCLUDED

//I N C L U D E s
#include <stdbool.h>
#include "object.h"
#include "weapon.h"
#include "potion.h"
#include "ammo.h"
#include "../graphic/SDL_Plotter.h"
#include "../graphic/screen.h"


//U N I O N

/**	UNION: dropType
 *PURPOSE: Holds either an enum weapon or enum potion value.
 *@data	enum weapon, potion	Available weapon and potion types.
 *				Their value reflects hp/damage.
 */
union dropType{
	
	enum weapon drop_weapon;	//Defaults to NONE
	enum potion drop_potion;
	enum ammunition drop_ammo;
};

//S T R U C T

/**	STRUCT: Droppable 
 *PURPOSE: Holds all neccessary data for a  droppable object.
 *@data	struct object dropObj	Object struct for this component, containing size,
 *				position and texture.
 *	char currentType	Current type of enum being used.
 *	union dropType type	Union holding a valid enum weapon or potion value.
 *	bool taken		Boolean state to represent that it has been already taken
 *				by the player and therefore shouldn't have effect/be plotted.
 */
struct Droppable{

	char currentType;
	struct object dropObj;
	union dropType type;
	bool taken = false;
};

//F U N C T I O N s

/**	FUNCTION: createDrop
 *PURPOSE: Creates a new droppable in the game.
 *PRECONDITION: Valid size, position and texture structs. Union holding a non-NONE value.
 *		Char box needs to be 'W','A' or 'P'.
 *POSTCONDITION: Droppable is created, ready to be plotted and taken by the player. Texture
 *		 will be set upon the type of droppable. Brown-ish for guns and green-ish 
 *		 for potions. Returns null if not called properly.
 *@params struct Droppable **droppables A pointer to the array of droppable objects.
 *	  int * number_of_droppables	A pointer to the number of droppables.
 *	  struct size dropSize		The size of the droppable.
 *	  struct position* dropPos	The position of the droppable. Struct position pointer.
 */void createDrop(struct Droppable **droppables, int *number_of_droppables,struct position* dropPos);

/*	FUNCTION:deleteDrop
PURPOSE: Deletes a droppable  from the array of droppables.
PRECONDITION: A pointer to a valid array of droppables with at least 1 member, the number of a droppables that exists within the array.
POSTCONDITION: The specified droppable is removed. All droppables after that droppable are moved back one space in the array.
@params struct Droppable **droppables	A pointer to a pointer to the first Droppable.
	int *number_of_droppables		A pointer the the number of droppables.
	int drop_number			The position in the array of the droppable to be deleted, starts at 0.
*/
void deleteDroppable(struct Droppable **droppables, int *number_of_droppables, int drop_number);

/**
 *	FUNCTION: setCurrentType
 *PURPOSE: Sets the correct member of the union data. Could also be use to
 *	   set the value of the enum.
 *PRECONDITION: Droppable already initialized, char[] containing at least
 *		one letter, 'P','W' or 'A'.
 *POSTCONDITION: union dropType will be set to the correct enum constant.
 */void setCurrentType(struct Droppable* drop,char newType[]);

/**	FUNCTION: plotDrop
 *PURPOSE: Plots a droppable object to the screen.
 *PRECONDITION: Configurated Droppable and active non null SDL_Plotter.
 *POSTCONDITION: Droppable is plotted. Color depends on its type.
 *@params struct Droppable* drop	The pointer to the droppable object.
 *	  SDL_Plotter* plot		The current plotter onto which the object will be drawn.
 */void plotDrop(struct Droppable* drop,SDL_Plotter* plot);
#endif
