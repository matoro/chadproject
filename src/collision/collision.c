/*
 *  COLLISION IMPLEMENTATION
 *  @author leba39, mortonman.
 */
#include "collision.h"

int mapObject(struct object* obj, struct size** objMap){

    if(!obj)    return -1;

    //VARs
    int nPoints,index;
    struct size objDim;
    struct position objPos;

    objPos  = getPosition(obj);
    objDim  = getSize(obj);
    nPoints = (2*(objDim.alto+objDim.ancho))*2;     //floor&ceil border coordenates aka perimeter.

    //ALLOC
    if(*objMap != NULL){
        free(*objMap);      //we clean it
        *objMap = NULL;
    }
    *objMap = (struct size*)malloc(sizeof(struct size)*nPoints);

    //FILL MAP
    index = 0;    

    //HORIZONTAL BORDERS
    for(int i=0;i<objDim.alto;i++){
        int x_f,x_c,y_f,y_c;    
        int j = objDim.ancho;

        x_f = (int) floor((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        x_c = (int)  ceil((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        y_f = (int) floor((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);
        y_c = (int)  ceil((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);
    
        (*objMap)[index].ancho     = x_f + objPos.x;
        (*objMap)[index].alto      = y_f + objPos.y;
        (*objMap)[++index].ancho   = x_c + objPos.x;
        (*objMap)[index++].alto    = y_c + objPos.y;
    }

    for(int i=0;i<objDim.alto;i++){
        int x_f,x_c,y_f,y_c;    
        int j = 0;

        x_f = (int) floor((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        x_c = (int)  ceil((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        y_f = (int) floor((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);
        y_c = (int)  ceil((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);
    
        (*objMap)[index].ancho     = x_f + objPos.x;
        (*objMap)[index].alto      = y_f + objPos.y;
        (*objMap)[++index].ancho   = x_c + objPos.x;
        (*objMap)[index++].alto    = y_c + objPos.y;
    }

    //VERTICAL BORDERS
    for(int j=0;j<objDim.ancho;j++){
        int x_f,x_c,y_f,y_c;    
        int i = objDim.alto;

        x_f = (int) floor((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        x_c = (int)  ceil((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        y_f = (int) floor((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);
        y_c = (int)  ceil((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);

        (*objMap)[index].ancho     = x_f + objPos.x;
        (*objMap)[index].alto      = y_f + objPos.y;
        (*objMap)[++index].ancho   = x_c + objPos.x;
        (*objMap)[index++].alto    = y_c + objPos.y;
    }
    for(int j=0;j<objDim.ancho;j++){
        int x_f,x_c,y_f,y_c;    
        int i = 0;

        x_f = (int) floor((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        x_c = (int)  ceil((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        y_f = (int) floor((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);
        y_c = (int)  ceil((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);

        (*objMap)[index].ancho     = x_f + objPos.x;
        (*objMap)[index].alto      = y_f + objPos.y;
        (*objMap)[++index].ancho   = x_c + objPos.x;
        (*objMap)[index++].alto    = y_c + objPos.y;
    }

    return nPoints; //should be equal to index       
}

bool checkOverlap(struct object* firstObj,struct object* secondObj){

    if(!firstObj||!secondObj)   return false;

    //VARs
    bool collision = false;
    int firstMapLength, secondMapLength;
    struct size* firstMap  = NULL;
    struct size* secondMap = NULL;

    firstMapLength  = mapObject(firstObj,&firstMap); 
    secondMapLength = mapObject(secondObj,&secondMap);
    
    if (firstMapLength == -1 || secondMapLength == -1){
        fprintf(stderr,"Error mapping objects at checkOverlap()\n");
        return false;
    }

    for(int i=0;i<firstMapLength;i++){
        for(int j=0;j<secondMapLength;j++){
            if((firstMap[i].ancho == secondMap[j].ancho) && (firstMap[i].alto == secondMap[j].alto)){
                collision = true;
                return collision;
            }
        }
    }
    free(firstMap);
    free(secondMap);
    firstMap  = NULL;
    secondMap = NULL;
    
    return collision;
}

bool player_enemy_collision(struct PlayerObj* player, struct EnemyObj* enemy, char movement, int rate){
    //Function should be called only when the user wants to move the player.

    if(!player||!enemy)     return false;

    //VARs
    struct position playerPos, newPos;

    //FETCH POSITION
    playerPos = getPosition(&(player->obj));

    //GET FUTURE POSITION AND SET IT AS CURRENT IN PLAYER.
    newPos = changePosition(&(player->obj),movement,rate);
    newPos.x         += playerPos.x;
    newPos.y         += playerPos.y;
    newPos.direction += playerPos.direction;
    setPosition(&(player->obj),&newPos);
    
    //CHECK IF NEW-FUTURE POS OVERLAPS|COLLIDES WITH ENEMY AND SET OLD POSITION BACK IN THE PLAYER.
    if(checkOverlap(&(player->obj),&(enemy->obj))){
        setPosition(&(player->obj),&playerPos);
        return true;
    }else{
        setPosition(&(player->obj),&playerPos);
        return false;
    }
}

bool player_droppable_collision(struct PlayerObj* player, struct Droppable* drop, char movement, int rate){
    //Function should be called only when there are droppables on the game and when the player is moving.

    if(!player||!drop)     return false;

    //VARs
    struct position playerPos, newPos;

    //FETCH POSITIONS
    playerPos = getPosition(&(player->obj));

    //GET FUTURE POSITION AND SET IT AS CURRENT IN PLAYER.
    newPos = changePosition(&(player->obj),movement,rate);
    newPos.x         += playerPos.x;
    newPos.y         += playerPos.y;
    newPos.direction += playerPos.direction;
    setPosition(&(player->obj),&newPos);
    
    //CHECK IF NEWPOS OVERLAPS|COLLIDES WITH DROP AND SET OLD POSITION BACK IN THE PLAYER.
    if(checkOverlap(&(player->obj),&(drop->dropObj))){
        setPosition(&(player->obj),&playerPos);
        drop->taken = true;
        return true;
    }else{
        setPosition(&(player->obj),&playerPos);
        return false;
    }

}
