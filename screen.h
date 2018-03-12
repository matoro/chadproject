/*
 * SCREEN.H -ALWAYS IN PLAY- COMPONENT
 * @author leba39, mortonman.
 */
#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

//I N C L U D E s
#include "SDL_Plotter.h"
#include "object.h"

//C O N S T A N T s
#define HEIGHT 600	//screen 
#define WIDTH 600	//dimensions

//F U N C T I O N s



/**	FUNCTION: plotObject
 *PURPOSE: Plots object to the screen given an object and a SDL_Plotter.
 *PRECONDITION: The object is not null. The plotter is already initialized.
 *POSTCONDITION: The object is drawn taking into account current pos and dir.
 *@params struct object *obj	 The object in question.
 * 	  SLD_Plotter *plotter	 Active SDL plotter.
 */void plotObject(struct object *obj,SDL_Plotter* plotter); 



/**	FUNCTION: plotText
 *PURPOSE: Prints useful information to the end-user. We'll use console and 
 *	   printfs for starters to later implement ingame window texts.
 *@params msg char[]. The string containing the message.
 *PRECONDITION:	A valid pointer to a char array.
 *POSTCONDITION: Prints given string to stdout.
 */void plotText(char msg[]);

#endif
