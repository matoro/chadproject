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
Under this directory we can find all the modelling our project uses. It presents structs and related object-functions to create what could be regarded as class objects by those familiar with OOP style programming.

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
