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
