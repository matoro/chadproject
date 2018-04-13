/*
 * BARS.H FILE: HEALTH/AMMO BAR STRUCT AND FUNCTIONS.
 * @author leba39, mortonman.
 */
#ifndef BAR_H_
#define BAR_H_

#include "player.h"	//already includes screen and sdl_plotter?
#include "../graphic/screen.h"
#include "../graphic/SDL_Plotter.h"

//CONSTANTS
const int MAX_HEALTH = 100;
const int MAX_AMMO   =  50;

/*
*Enum:bartype 	the player statistic represented by the bar: health or ammo.
*/
enum bartype{
	HEALTH,
	AMMO
};

/*
*Struct:BarObj
*
*Variables: enum bartype type	The type of bar:health or ammo.
*	    int currentvalue	The current value of the player statistic the bar displays
*	    int max		The maximum value of the player statistic the bar displays
*	    struct object obj	The object struct common to all objects, contains position, texture, and size. 
*/
struct BarObj{
	enum bartype type;
	int currentvalue;
	int max;
	struct object obj;
};

/*	FUNCTION: createBar
 *PURPOSE: Creates health and ammo bar structs with based on the variables in a player struct.
 *PRECONDITION: A player struct with positive health and ammo integers, a valid bartype(Health or Ammo)
 *@params struct PlayerObj *player	The player from which the health or ammo value is taken.
 *        enum bartype type		The type of bar being created: Health or Ammo.
 *	  
 *@return struct BarObj		        A bar created based on the data in the player object and the position provided.
 */
void createBar(struct BarObj ** bars, int *number_of_bars, struct PlayerObj* player, enum bartype b_type, struct position pos);

/*	FUNCTION:deleteBar
PURPOSE: Deletes a bar from the array of bars.
PRECONDITION: A pointer to a valid array of bars with at least 1 member, the number of a bar that exists within the array.
POSTCONDITION: The specified bar is removed. All bars after that bar are moved back one space in the array.
@params struct BarObj **bars	A pointer to a pointer to the first BarObj.
	int *number_of_bars	A pointer the the number of bars.
	int bar_number		The position in the array of the bar to be deleted, starts at 0.
*/
void deleteBar(struct BarObj ** bars, int *number_of_bars, int bar_number);

/*	FUNCTION: updateBar
 *PURPOSE: Updates the currentvalue of health and ammo bars.
 *PRECONDITION: A valid non-null player struct with positive health and ammo integers less than the bar's max.  
 *POSTCONDITION: The currentvalue variable of the each bar is updated to relfect the current value of health and ammo in the player struct.
 *@params int newvalue			The value that the bar's currentvalue variable is set to.
 	  struct bar *currentbar	The bar that is currently being updated.
 */
void setCurrentValue(struct BarObj* currentbar, int newvalue);

/*	FUNCTION: plotBar
 *PURPOSE: Plots a bar on the screen.
 *PRECONDITION:Valid non-null BarObj.
 *POSTCONDITION: The Bar is plotted on the screen alongside its title.
 * 
 *@params struct BarObj *bar		The bar that is to be plotted.
 */
void plotBar(struct BarObj* bar,SDL_Plotter* plot);

#endif
