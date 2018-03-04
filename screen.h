/*
 * SCREEN.H -ALWAYS IN PLAY- COMPONENT
 */

//INCLUDES
#include "SDL_Plotter.h"
//#include "object.h"

//CONSTANTS
#define HEIGHT 600	//screen 
#define WIDTH 600	//dimensions

/**
 *Plots object to the screen.
 *@params *obj struct object. Pointer to an object.
 *@params plotter SLD_Plotter. Graphics.
 */
void plotObject(struct object *obj,SDL_Plotter* plotter); 

/**
 *Plots useful information to the player. We'll use console and printfs for 
 *starters to later implement ingame window texts.
 *@params msg char[]. The string containing the message.
 */
void plotText(char msg[]);
