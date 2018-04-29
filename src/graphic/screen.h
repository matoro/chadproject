/*
 * SCREEN.H -ALWAYS IN PLAY- COMPONENT
 * @author leba39, mortonman.
 */
#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

//I N C L U D E s
#include <string.h>
#include "SDL_Plotter.h"
#include "../object/object.h"
#include "../utils/charset.h"

//C O N S T A N T s
#define HEIGHT 600	//screen 
#define WIDTH 600	//dimensions

//F U N C T I O N s



/**	FUNCTION: plotObject
 *PURPOSE:          Plots object to the screen given an object and a SDL_Plotter.
 *PRECONDITION:     The object is not null. The plotter is already initialized.
 *POSTCONDITION:    The object is drawn taking into account current pos and dir.
 *@params struct object *obj	    The object in question.
 * 	      SLD_Plotter *plotter	    Active SDL plotter.
 */void plotObject(struct object *obj,SDL_Plotter* plotter); 



/**	FUNCTION: plotText
 *PURPOSE:          Prints information to the end-user through ingame texts.
 *PRECONDITION:	    Valid and well formed struct texture, non-negative fontSize int and char thinness smaller than fontsize.
 *                  Active non-null SDL_Plotter and a struct position within the window dimensions. 
 *POSTCONDITION:    Prints given string to  screen starting at initialPos, colored after fontColor,
 *                  with given fontSize and thinness characteristics. If msg is too long it is printed
 *                  until it goes out of bounds of the screen.
 *                  
 *@params   msg char[]                          The string containing the message.
 *          struct position initialPos          Struct position containing the position of the first letter of the string in the screen.
 *          struct texture fontColor            Struct texture with the desirable font-color.
 *          int fontSize                        Int with desirable font-size.
 *          char thinness                       Char with desirable thinnness of the string. Values smaller than font-size.
 *          SDL_Plotter* plotter                Active SDL plotter.
 */void plotText(char msg[],struct position initialPos,struct texture fontColor,int fontSize,char thinness,SDL_Plotter* plotter);

#endif
