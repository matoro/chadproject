/*
 *  -USER INTERFACE COMPONENT-
 *  @author leba39, mortonman.
 */
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

//I N C L U D E s
#include <stdbool.h>
#include "../graphic/screen.h"
#include "../object/bar.h"
#include "../object/player.h"

//F U N C T I O N s

/** FUNCTION:   printUserInterface
 *PURPOSE:      Should take care of creating the UserInterface bar at the bottom of the screen, create both health and ammo bars if they're not onplay
 *              and update them as well as plotting the current gun&ammo type the player posess.
 *PRECONDITION: Initialized game -that is, after user decides to play in menu-. Valid player and SDL_plotter pointers.
 *POSTCONDITION:User interface is created if it wasn't already and it is refreshed.
 *@params       struct PlayerObj* player        Pointer to the player struct.
 *              struct BarObj** bars            Pointer to struct of bars.
 *              int numBars                     Pointer to an int holding the number of active bars.
 *              SDL_Plotter* plot               Pointer to current SDL_Plotter.
 */void printUserInterface(struct PlayerObj* player, struct BarObj** bars, int* numBars, SDL_Plotter* plot);

/** FUNCTION:   printMenu
 *PURPOSE:      Takes care of presenting a menu right after the program executes and when the player wants to play again.
 *PRECONDITION: SDL_Plotter initialized at the start. End-of-game reached once the program is already running.
 *POSTCONDITION:Display menu options.
 *@params       SDL_Plotter* plot               Pointer to current SDL_plotter.   
 *@return       char                            Char representing the menu option chosen by the user.
 */char plotMenu(SDL_Plotter* plot);

//Auxiliary functions come next....

/** FUNCTION:   getGunMsg
 *PURPOSE:      Returns a particular string depending on the type of weapon the player is currently holding.
 *PRECONDITION: Initialized game and created player object.
 *POSTCONDITION:String is returned.
 *@params       struct PlayerObj* player        Pointer to valid player object.   
 *@return       char*                           String.
 */char* getGunMsg(struct PlayerObj* player);

/** FUNCTION:   getAmmoMsg
 *PURPOSE:      Returns a particular string depending on the type of ammo the player currently has.
 *PRECONDITION: Initialized game and valid player object.
 *POSTCONDITION:String is returned.
 *@params       struct PlayerObj* player        Pointer to valid player object.   
 *@return       char*                           String.
 */char* getAmmoMsg(struct PlayerObj* player);

#endif
