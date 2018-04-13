/*
 * VISIBLECOMPONENTS.H: Functions for easily plotting all visible objects
 * @author leba39, mortonman.
 */
#ifndef VISIBLECOMPONENTS_H_
#define VISIBLECOMPONENTS_H_

#include "../object/player.h"
#include "../object/bar.h"
#include "../object/bullet.h"
#include "../graphic/SDL_Plotter.h"

/**	FUNCTION: setSize
 *PURPOSE: Plots all visible objects.
 *PRECONDITION: Pointer to valid plotter, pointer to valide PlayerObj with a valid texture, size, and position
 *POSTCONDITION: Whole object gets a new size.
 *@params struct SDL_Plotter *plot	A pointer to the plotter that the objects will be plotted on.
 *	  struct PlayerObj player	The player to be plotted.
 *	  struct BarObj *bars		A pointer to the first bar object.
 * 	  int number_of_bars		The number of bar objects that exist.
 *			ADD MORE FOR EACH OBJECT TYPE
 */
void plotVisibleComponents(SDL_Plotter *plot, struct PlayerObj player, struct BarObj *bars, int number_of_bars, struct BulletObj *bullets, int number_of_bullets);

#endif
