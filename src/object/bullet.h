/*
 * BULLET.H FILE: BULLET STRUCT AND FUNCTIONS.
 * @author leba39, mortonman.
 */
#ifndef BULLET_H_
#define BULLET_H_


#include "player.h"


struct BulletObj{
	struct object obj;
    enum weapon shotBy;
    enum ammunition ammoUsed;
};

/**	FUNCTION: createBullet
 *PURPOSE: Adds a BulletObj to the array of BulletObjs. Position is in front of shooter.
 *PRECONDITION: The object is not null and has a valid position.
 *POSTCONDITION: A new bullet object is created.
 *@params struct object *shooter 	The object that is being shot.
 *	  struct BulletObj **bullets	A pointer to a pointer to the first bullet object.
 *	  int *number_of_bullets	    A pointer to an int representing the number of bullets
 *    enum weapon arms              Type of weapon that shot the bullet.
 *    enum ammunition ammo          Type of ammo used.
 */
void createBullet(struct object *shooter, struct BulletObj **bullets, int *number_of_bullets, enum weapon arms, enum ammunition ammo);

/**	FUNCTION: deleteBullet
 *PURPOSE: removes a BulletObj from the array of bulletObjs.
 *PRECONDITION: There is a BulletObj at the given bullet_number.
 *POSTCONDITION: The bullet is removed.
 *@params struct BulletObj **bullets	A pointer to a pointer to the first bullet object.
 *	  int *number_of_bullets	A pointer to an int representing the number of bullets
 *	  int bullet_number		The number of the bullet that is to be deleted, starts at 0.
 */
void deleteBullet(struct BulletObj **bullets, int *number_of_bullets, int bullet_number);

/**	FUNCTION: updateBulletPos
 *PURPOSE: Updates the positions of all bullets.
 *PRECONDITION: All bullets have valid positions. The given number of bullets is equal to or less that the current number of bullets.
 *POSTCONDITION: All bullets move forward.
 *@params struct BulletObj *bullets	A pointer to the first bullet object.
 *	  int *number_of_bullets	A pointer to an int representing the number of bullets
 */
void updateBulletPos(struct BulletObj **bullets, int *number_of_bullets);

/*	FUNCTION: plotBullet
 *PURPOSE: Plots a bullet on the screen.
 *PRECONDITION:Valid non-null BulletObj.
 *POSTCONDITION: The Bullet is plotted on the screen.
 * 
 *@params struct BulletObj *bullet	The bullet that is to be plotted.
 *	  SDL_Plotter *plot		The plotter onto which the bullet is being plottered
 */
void plotBullet(struct BulletObj *bullet, SDL_Plotter *plot);

#endif
