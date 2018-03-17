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

//U N I O N

/**	UNION: dropType
 *PURPOSE: Holds either an enum weapon or enum potion value.
 *@data	enum weapon, potion	Available weapon and potion types.
 *				Their value reflects hp/damage.
 */
union dropType{
	
	enum weapon drop_weapon = NONE;	//Default to NONE
	enum potion drop_potion = NONE;	//Default to NONE
};

//S T R U C T

/**	STRUCT: Droppable 
 *PURPOSE: Holds all neccessary data for a  droppable object.
 *@data	struct object dropObj	Object struct for this component, containing size,
 *				position and texture.
 *	union dropType type	Union holding a valid enum weapon or potion value.
 *	bool taken		Boolean state to represent that it has been already taken
 *				by the player and therefore shouldn't have effect/be plotted.
 */
struct Droppable{

	struct object dropObj;
	union dropType type;
	bool taken = false;
};

//F U N C T I O N s

/**	FUNCTION: createDrop
 *PURPOSE: Creates a new droppable in the game.
 *PRECONDITION: Valid size, position and texture structs. Union holding a non-NONE value.
 *POSTCONDITION: Droppable is created, ready to be plotted and taken by the player. Texture
 *		 will be set upon the type of droppable. Brown-ish for guns and green-ish 
 *		 for potions.
 *@params struct size dropSize		The size of the droppable.
 *	  struct position dropPos	The position of the droppable.
 *	  union dropType tipo		A union type holding an enum weapon or potion value. 
 *@return struct Droppable	The struct Droppable configurated.         
 */struct Droppable createDrop(struct size dropSize,struct position dropPos, union dropType tipo);

/**	FUNCTION: plotDrop
 *PURPOSE: Plots a droppable object to the screen.
 *PRECONDITION: Configurated Droppable and active non null SDL_Plotter.
 *POSTCONDITION: Droppable is plotted. Color depends on its type.
 *@params struct Droppable drop		The droppable object.
 *	  SDL_Plotter* plot		The current plotter onto which the object will be drawn.
 */void plotDrop(struct Droppable drop,SDL_Plotter* plot);
#endif
