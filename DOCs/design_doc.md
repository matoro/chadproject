# **CHAD PROJECT**
---
## DESIGN DOCUMENTATION
### *Architectural Overview:*
##### Index of contents
1. Layer organization.
2. Layer interaction.
3. Implementation process. Rights and wrongs.
4. Future development.
---
---
### 1. LAYER ORGANIZATION
The [***project***](https://github.com/matoro/chadproject), currently in *v0.1-alpha* is divided in seven different layers:
+ src/collision
+ src/gamelogic
+ src/graphic
+ src/objects
+ src/userinterface
+ src/utils
+ main `test.c`

All these seven layers could be classified in major groups if we were to focus on their end-purpose.  

| MODEL | PRESENTATION | LOGIC |
|:---:|:---:|:---:|
|objects|graphic|collision|
||userinterface|gamelogic|
||utils|main|

This approach will de discussed later in the layer interaction chapter.

### src/objects:
Under this directory we can find all the modelling our project uses. It presents structs and related object-functions to create what could be regarded as classes by those familiar with OOP style programming.

*Struct definitions*, *function declarations* and *enums* can be found inside *.h files meanwhile their implementations fall under their *.c counterparts.

Table of contents:

| H FILE | C FILE | DESCRIPTION |
|:---:|:---:|:---|
|object.h|object.c|Main attributte of every visual model. It comprehends size, texture and position on the screen. Plus auxiliary functions.|
|bar.h|bar.c|Holds type, max and current value of UI Bars and its functions.|
|bullet.h|bullet.c|Holds the type of weapon and ammo used and ballistic functions.|
|droppable.h|droppable.c|Conveys different types of droppables and whether they're taken.|
|enemy.h|enemy.c|Encompass health, fov, sight, active status, position and cooldown. Functions regarding enemy creation/deleting and behaviour/AI.|
|player.h|player.c|Similar to enemies, it includes health, ammo, weapon and ammo used. Auxiliary functions for creation/deleting/plotting such object.|
|potion.h||Enum containing different types of potions and their hp value.|
|weapon.h||Enum containing different types of weapons and their base damage value.|
|ammo.h||Enum containing different types of ammunition and their multiplier damage value.|

### src/graphic:
In this folder we can find all the neccessary functions that help us plot both text and object models into the screen.

*Function declarations* can be found inside *.h files meanwhile their implementations fall under their *.c counterparts.

Table of contents:

| H FILE | C FILE | DESCRIPTION |
|:---:|:---:|:---|
|screen.h|screen.c|Manages two key functions regarding screen-plotting; plotObject and plotText.|
|visiblecomponents.h|visiblecomponents.c|Contains the plotVisibleComponents auxiliary function that abstract us from calling plotObject on every component in-game. Wrapper of plotObject.|
|SDL_Plotter.h||Header file of the SDL library. plotPixel mainly.|

### src/userinterface:

All functionality regarding interaction with the user in every aspect of the game is contained here. During the game cycle, it interfaces through menus, in-game controls, scoreboard saving/writing etc.

*Struct definitions* and *function declarations* can be found inside *.h files meanwhile their implementations fall under their *.c counterparts.

Table of contents:

| H FILE | C FILE | DESCRIPTION |
|:---:|:---:|:---|
|ui.h|ui.c|Contains functions that plots the in-game UI, as well as the main menu and takes care of the scoreboard system maintenance.|

### src/utils:

This folder contains utils needed for other functions. In particular, it currently contains the sprite representation and functionality needed ir order to plotText (back in `/graphic`).

*Function declarations*, *structs* and *constants* can be found inside the .h file meanwhile its implementation fall under the .c counterpart.

Table of contents:

| H FILE | C FILE | DESCRIPTION |
|:---:|:---:|:---|
|charset.h|charset.c|Text sprites and its implementation feature getSprite go here.|

### src/collision:

Easy enough, all collision logic goes here. From bottom up auxiliary functions that maps objects to a bunch of `(x,y)` points to the more useful boolean collision functions (true/false response).

*Function declarations* can be found inside the .h file meanwhile its implementation fall under the .c counterpart.

Table of contents:

| H FILE | C FILE | DESCRIPTION |
|:---:|:---:|:---|
|collision.h|collision.c|Pretty self-explanatory. From mapObject and checkOverlap to boolean player_enemy_collision and more...|

### src/gamelogic:

This directory encapsulates game logic functionality that could've just been written inside the `main` file but was extracted for clarity purposes. It mainly handles spawn logic and bullet-time features. There is also present a global file that contains some extern variables that we manipulate inside `main`. This was only an effort meddling with this type of feature, as it is recognized as a bad practice.


*Function declarations* can be found inside *.h files meanwhile their implementations fall under their *.c counterparts.

Table of contents:

| H FILE | C FILE | DESCRIPTION |
|:---:|:---:|:---|
|gamelogic.h|gamelogic.c|Functions controlling the spawn of droppables and enemies, as well as bullet-time functionality.|
|globals.h|globals.c|Global variable definitions such as RATE_MVMT and so forth.|

### main:

Our entry point conveys all of these different layers into a simple enough classic game pattern. This could be divided in four different stages.
1. **Variable declaration**: all resources needed for it to run.
2. **Menu loop/Restart**: Presents the menu to the player and resets counters. Its output routes the rest of the execution.
3. **Main/Game loop**: Where the action happens. It leads to a save score screen (part of menu) and gives the player the chance to go back to ***(2)***.
4. **Exit**: The game prepares for exit. It frees allocated resources and returns with a normal (successful) exit.

It's not difficult to locate and differentiate these parts in the main code (currently `test.c`) in which the commentary makes the same assumptions.

---

### 2. LAYER INTERACTION

### MAIN

The main function is the core of the game and interacts directly with every other layer except utils.

##### Interactions with other layers:
+ **Objects:** Arrays of all game objects are declared at the beginning of *main()*. Objects are then added to or removed from these arrays with createX and DeleteX functions. Other than this, direct interaction with objects is limited to the player object (the central object of the game). The player's movement and status are handled directly in the main game loop.
+ **Graphic:** The SDL Plotter is declared in the beginning of *main()*. During gameplay, objects are plotted with *plotVisibleObjects()*.
+ **User Interface:** The user interface functions are used mainly for printing menus and game interface elements.
+ **Collision:** Collision for all objects other than enemies is handled in the main game loop using *X-X-collision()* functions.
+ **Game Logic:** Player movement references movement constants. Game logic functions are used for spawning enemies, spawning droppables, and managing time and score.

### MODEL

The model group handles the location, status, and behavior of game objects.

#### Objects

While the object layer is referenced by many others, it doesn't interact directly but with a few layers itself.

##### Interactions with other layers:
+ **Graphic:** Each object has a plotX function that uses *plotObject()* from *screen.c* in Graphic.
+ **Collision:** Enemy collision is handled in *enemy.c* using *X-X-collision()* functions.
+ **Gamelogic:** Enemy and bullet speed is determined from constants in *globals.c*.

### LOGIC

The logic group monitors and restricts other game elements. 

#### Collision Logic

The collision logic layer prevents objects from colliding or moving outside of the screen and therefore interacts exclusively with the object layer.

##### Interactions with other layers:
+ **Objects:** The locations of objects are used to determine if two objects will collide after a movement.

#### Game Logic

The game logic layer contains functions to spawn enemies and global variables, so it interacts exclusively with the object layer.

##### Interactions with other layers:
+ **Objects:** In the spawn fuctions, player status is used to determine if a droppable should spawn and avoid player-enemy overlap. *createDrop()* and *createEnemy()* are used to spawn new drops and enemies.

### PRESENTATION

The presentation group handles the game window and what is plotted in it.

#### Graphic

The graphic layer contains the SDL_Plotter class and functions to plot objects and text. It interacts with the object and util layers.

##### Interactions with other layers:
+ **Object:** *plotObject()* plots a pixel representation of an object struct.
+ **Utils:** *getSprite()* from *charset.c* is used in *plotText*.

#### User Interface

The user interface contains functions to plot menus, the scoreboard, and the game interface. It interacts with the object and  graphic layers.

##### Interactions with other layers:
+ **Object:** Updates bar objects. Information for bars is drawn from the player object.
+ **Graphic:** *plotObject()* and *plotText()* are used to create UIs.

#### Utils

The utils layer is referenced only by graphic and does not interact with any other layers itself.

---

### 3. IMPLEMENTATION PROCESS. RIGHTS AND WRONGS.
The implementation process will be discussed regarding the [*initial draft*](https://github.com/matoro/chadproject/blob/testing/DOCs/sigproject_game.html) of the game; considering which goals did we achieve, which ones we rejected in our way up and which ones we failed to implement or set aside for future releases.

###### OBJECTIVES

The primary goal was clear, make a **simple 2D shooter game with slow motion mechanics**. We agreed on this list of end-user objectives for our first release:

> **END USER OBJECTIVE**
>
> *Primary objective:*
> - [x] Survival mode -> Kill al enemies.
> - [ ] Level/career mode -> Reaching a certain point in the map.
>
> *Secondary objective:*
> - [x] High score:
>    + Survival mode -> Time record.
>    + Level/career mode -> Kill enemies and complete level faster.
>  - [x] Collect health potions/powerups/score items.

As of today, the current release hasn't achieved all the proposed objectives mentioned above. We did focus on the *survival mode* aspect of the game, including secondary goals like keeping the high score on a scoreboard ranked system and the implementation of droppables.

###### COMPONENTS

In relation with the **components** necessary for the actual game, we came up with these lists, one from a ***visible vs invisible perspective*** and the other one from a ***layering perspective***.

| VISIBLE COMP | INVISIBLE COMP |
|:---:|:---:|
|Player character|Loading level|
|Enemies|Bullets' trajectory|
|Weapons|Key listener|
|Bullets|Object movement|
|Timer/Score|Collision logic|
|Level map|Screen boundaries|
|Health/Ammo bar|Map design|
|Droppables|Time/Clock|

| ALWAYS IN PLAY | USUALLY IN PLAY | SOMETIMES IN PLAY |
|:---:|:---:|:---:|
|Screen|Time/Clock|Bullets|
|Key Listener|Player/NPCs|Droppables|
||Players' health/ammo bar|Bullets' trajectory|
||Collision logic|Load level|
||AI||
||Level map||
||Object movement||

Perhaps the greatest insight on how we ended up layering and organizing the groups shown in the tables back at chapter one comes from these two tables above.

On the first table, we can almost see how most of the **VISIBLE COMP** ended up being part of the **MODEL** -that is, src/objects- and how the **INVISIBLE COMP** ended up half as **LOGIC** (collision logic, AI, movement, game loops, timing etc) and the other half as **PRESENTATION** (screen/map design and UI).


##### RIGHTS AND WRONGS

It is hard to determine what you're doing wrong or right when it is your very first approach to this type of project. Either way, we think that we kept ourselves pretty much restrained to what we had planned and layed out back at our initial drafts -**and that that's a good thing**-; anyway, there are lots of things that we would **implement different if we were to do it again** (from a programming point of view). Here are but a few of them:

+ Reject the *global variables* that we used for MVMT_RATES in globals.c. It was a good exercise to get to know them (`extern`), but it is considered bad practice and there is really no point in having them (we could just pass them around).
+ Have some kind of *dump file of CONSTs and DEFINED variables* that are pretty common. In lots of cases, we found ourselves declaring and defining the same `struct`s over and over again. (For example: *struct textures* for a variety of colors, *struct position*s etc)
+ Working with *sprites* from the get-go. It wasn't until we implemented the plotText functions and with it the utils/charset that we discovered just how easy it was to just plot the array representation of a figure instead that with raw plotPixel(x,y) and math functions in order to draw squares, circles or make a simple face etc. (note that both our enemies and player characters, as well as the terrain and everything not-a-text is made using this type of procedure).
+ Let go of the *unnecessary OOP style programming*. At first, when we started modeling our `object`s, we made for them auxiliary functions and setters/getters but there is really no need for them in the imperative-referenced world of C. Most of them are kept unused in the current release.
+ [TODO: Add mortons]

---

### 4. FUTURE DEVELOPMENT

There are loads of things we can improve upon the current state of our game. There is no end to it, you could always expand it some more. Anyhow, we consider that **a final product may include these features**:
1. Finish our initial end-user objectives... that is, implement the *level/map* part of the game.
2. Improve *charset resolution* for better text readability.
3. Build the game in *different window-sizes* (chosen by the user). Most of the work on this part should be already done, as we tried to keep everything % relative to our WIDTH and HEIGHT screen dimensions but we are pretty sure as well that we left hard-coded some values here and there that will break stuff along the way.
4. Improve the *game AI* so that we have different types of enemies (more intelligent and deadly as the game goes on, without just incrementing their raw damage).
5. [TODO: Add mortons]
