/*
 * SCREEN.H -ALWAYS IN PLAY- COMPONENT
 */

//SCREEN DIMESIONS
#define HEIGHT 420 
#define WIDTH 480

/**
 *Plots texture of object to the screen starting at given x and y coordinates.
 *@params X int. Left Horizontal position.
 *@params y int. Top Vertical position.
 *@params *obj struct object. Pointer to an object.
 */
void plotTexture(int x, int y, struct object *obj);

/**
 *Plots useful information to the player. We'll use console and printfs for 
 *starters to later implement ingame window texts.
 *@params msg char[]. The string containing the message.
 */
void plotText(char[] msg);
