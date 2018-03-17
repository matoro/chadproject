/*
 * BARS.H FILE: HEALTH/AMMO BAR STRUCT AND FUNCTIONS.
 * @author leba39, mortonman.
 */
#ifndef BAR_H_
#define BAR_H_

#include "player.h"

/*
*Enum:bartype 	the player statistic represented by the bar: health or ammo.
*/
enum bartype{
	health;
	ammo;
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
struct BarObj *createBar(struct PlayerObj *player, enum bartype type, struct position pos);

/*	FUNCTION: updateBar
 *PURPOSE: Updates the currentvalue of health and ammo bars.
 *PRECONDITION: A valid non-null player struct with positive health and ammo integers less than the bar's max.  
 *POSTCONDITION: The currentvalue variable of the each bar is updated to relfect the current value of health and ammo in the player struct.
 *@params int newvalue			The value that the bar's currentvalue variable is set to.
 	  struct bar *currentbar	The bar that is currently being updated.
 */
void setCurrentValue(struct BarObj *currentbar, int newvalue);

/*	FUNCTION: plotBar
 *PURPOSE: Plots a bar on the screen.
 *PRECONDITION:Valid non-null BarObj.
 *POSTCONDITION: The Bar is plotted on the screen alongside its title.
 * 
 *@params struct BarObj *bar		The bar that is to be plotted.
 */
void plotBar(struct BarObj *bar);

#endif
