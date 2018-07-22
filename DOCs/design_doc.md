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
The [***project***](https://github.com/matoro/chadproject) , currently in *v0.1-alpha* is divided in seven different layers:
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
`[TODO]`
