/*
 *  -USER INTERFACE COMPONENT-
 *  @author leba39, mortonman.
 */
#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

//I N C L U D E s
#include <stdbool.h>
#include <stdio.h>
#include <errno.h>              //openFile error handling.
#include <stdlib.h>
#include <string.h>
#include "../graphic/screen.h"
#include "../object/bar.h"
#include "../object/player.h"

//D E F I N E

#define SCOREBOARD_FILE "scoreboard.bin"
#define TOP  10
#define MAX_NAME 10

//S T R U C T
struct file_data{
    char name[10];
    int score;
    //14bytes  
};

//F U N C T I O N s

/** FUNCTION:   printUserInterface
 *PURPOSE:      Should take care of creating the UserInterface bar at the bottom of the screen, create both health and ammo bars if they're not onplay
 *              and update them as well as plotting the current gun&ammo type the player posess and score.
 *PRECONDITION: Initialized game -that is, after user decides to play in menu-. Valid player and SDL_plotter pointers.
 *POSTCONDITION:User interface is created if it wasn't already and it is refreshed.
 *@params       struct PlayerObj* player        Pointer to the player struct.
 *              struct BarObj** bars            Pointer to struct of bars.
 *              int numBars                     Pointer to an int holding the number of active bars.
 *              int score                       Current score.
 *              SDL_Plotter* plot               Pointer to current SDL_Plotter.
 */void printUserInterface(struct PlayerObj* player, struct BarObj** bars, int* numBars, int score, SDL_Plotter* plot);

/** FUNCTION:   printMenu
 *PURPOSE:      Takes care of presenting a menu right after the program executes and when the player wants to play again.
 *PRECONDITION: SDL_Plotter initialized at the start. End-of-game reached once the program is already running.
 *POSTCONDITION:Display menu options.
 *@params       SDL_Plotter* plot               Pointer to current SDL_plotter.   
 *@return       char                            Char representing the menu option chosen by the user.
 */char printMenu(SDL_Plotter* plot);

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

/** FUNCTION:   openFile
 *PURPOSE:      Tries to open file called SCOREBOARD_FILE('scoreboard.bin') in given mode ("r","w"...).
 *PRECONDITION: File must be located in the same directory as the main program.
 *POSTCONDITION:File is opened and fd pointer is returned.
 *@params       char* mode                      Char* containing 'mode' option.   
 *@return       FILE*                           File descriptor pointer if everything goes ok. NULL otherwise.
 */FILE* openFile(char* mode);

/** FUNCTION:   readScoreBoard
 *PURPOSE:      Reads and mallocs every recorded name and score pair present in SCOREBOARD_FILE.
 *PRECONDITION: Non null file_data pointer parameter.
 *POSTCONDITION:SCOREBOARD_FILE is read and struct file_data array is filled containing those records.
 *@params       struct file_data** data         Double pointer to a struct file_data. For malloc purposes.   
 *@return       int                             Number of structs read (file_data size) if positive. Error codes if negative.
 */int readScoreBoard(struct file_data** data);

/** FUNCTION:   writeScoreBoard
 *PURPOSE:      Saves given record inside SCOREBOARD_FILE in a sorted manner, keeping the TOP 10 and discarding the rest.
 *PRECONDITION: Well formed file_data struct. Score must be positive and name at least 3 characters long.
 *POSTCONDITION:Given file_data struct is saved in SCOREBOARD_FILE in its corresponding position.
 *@params       struct file_data new_data       Struct containing the new record.
 *@return       int                             0 if everything went OK. Different error codes if negative.
 */int writeScoreBoard(struct file_data new_data);

/** FUNCTION:   printScoreBoard
 *PURPOSE:      Prints and presents a view for the user with the current TOP 10 records in SCOREBOARD_FILE.
 *PRECONDITION: SDL_Plotter must be valid and initiated.
 *POSTCONDITION:User can check the current scoreboard in a dedicated view within the program.
 *@params       SDL_Plotter* plot               SDL_Plotter pointer.
 *@return       bool                            False if there was an error or if the user wants to exit directly the program.
 *                                              True otherwise, that is, the user wants to go (b)ack to the menu.
 */bool printScoreBoard(SDL_Plotter* plot);

/** FUNCTION:   printSaveScore
 *PURPOSE:      Presents a view for the user to input its nickname to save his record into SCOREBOARD_FILE.
 *PRECONDITION: SDL_Plotter must be valid and initiated.
 *POSTCONDITION:User can input its nickname and save his score after the game is over.
 *@params       SDL_Plotter* plot               SDL_Plotter pointer.
 *              int score                       User's score. Must be positive.
 *@return       bool                            False if there was an error or if the user wants to exit directly the program.
 *                                              True otherwise.
 */bool printSaveScore(SDL_Plotter* plot, int score);

#endif
