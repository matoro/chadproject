/*
 * OBJECT.H FILE: BASIC STRUCT DATA COMMON FOR ALL OBJECTS.
 * @author leba39, mortonman.
 */
#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

// S T R U C T s



/**	STRUCT: texture
 *PURPOSE: Data block that holds RGB values.
 *PRECONDITION: Defaults to white (255,255,255).
 *POSTCONDITION: RGB values ranging from 0-255.
 *@data		int red, green, blue.
 */
struct texture{
	
	int red = 255;
	int green = 255;
	int blue = 255;
};



/**	STRUCT: size
 *PURPOSE: Data block that holds size dimensions.
 *PRECONDITION: Defaults to zero. (0,0).
 *POSTCONDITION: Dimensions not greater that the actual SCREEN.
 *@data		int alto,ancho.
 */
struct size{	
	
	int alto = 0;
	int ancho = 0;
};



/**	STRUCT: position
 *PURPOSE: Data block that holds the object position.
 *PRECONDITION: x and y values lesser than screen dimensions.
 *POSTCONDITION: Valid x and y values and a direction ranging from 0-359.
 *@data 	int x, y, direction.
 */
struct position {
	
	int x;
	int y;
	int direction; 
};



/**	STRUCT: object
 *PURPOSE: Data block that holds size, position and texture values.
 *PRECONDITION: Existing non null structs.
 *POSTCONDITION: A proto-object ready to use.
 */
struct object{

	struct texture 	textureObj;
	struct size 	sizeObj;
	struct position posObj;
};

//F U N C T I O N s



/**	FUNCTION: setTexture
 *PURPOSE: Sets the given RGB values to an object texture struct.
 *PRECONDITION: Non null struct object* and valid texture values.
 *POSTCONDITION: Whole object gets a new RGB color.
 *@params struct object *obj	The object in question.
 *	  struct texture 	Data block containing RGB values.
 */void setTexture(struct object *obj,struct texture clr);



/**	FUNCTION: getTexture
 *PURPOSE: Returns the current texture of the given object.
 *PRECONDITION: Valid non null struct object*.
 *@params struct object *obj	The object in question.
 *@return struct texture	Data block containing RGB values.
 */struct texture getTexture(struct object *obj);



/**	FUNCTION: setSize
 *PURPOSE: Sets the given dimension values to an object size struct.
 *PRECONDITION: Non null struct object* and valid texture values.
 *POSTCONDITION: Whole object gets a new size.
 *@params struct object *obj	The object in question.
 *	  struct size dim	Data block containing dimension values.
 */void setSize(struct object *obj,struct size dimension);



/**	FUNCTION: getSize
 *PURPOSE: Returns the dimension of the object.
 *PRECONDITION: Non null struct object*.
 *@params struct object *obj	The object in question.
 *@return struct size		Data block containing dimension values.
 */struct size getSize(struct object *obj);



/**	FUNCTION: setPosition
 *PURPOSE: Sets the given dimension values to an object size struct.
 *PRECONDITION: Non null struct object* and valid texture values.
 *POSTCONDITION: Whole object gets a new size.
 *@params struct object *obj	The object in question.
 *	  struct position pos	Data block containing position values.
 */void setPosition(struct object *obj,struct position pos);



/**	FUNCTION: getPosition
 *PURPOSE: Returns the dimension values of an object.
 *PRECONDITION: Non null struct object*.
 *@params struct object *obj	The object in question.
 *@return struct position		Data block containing current position values.
 */struct position getPosition(struct object *obj);



/**	FUNCTION: changePosition
 *PURPOSE: Given an object, a movement key, and a rate, change the position of
 *	   an object at the appropriate rate.
 *PRECONDITION: The object is not null.  The movement key is an appropriate 
 *		directional key. The rate is nonnegative.
 *POSTCONDITION: The pos attribute of the object will be updated with its new 
 *		 coordinates. The object is not actually redrawn.
 *@params struct object *obj	The object in question
 *        char movement		The directional key input by the user
 *        int rate          	The rate at which to change movement speed
 *@return struct position       Data block containing adjusted position values.
 */struct position changePosition(struct object *obj,char movement, int rate);

#endif
