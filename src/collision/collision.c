/*
 *  COLLISION IMPLEMENTATION
 *  @author leba39, mortonman.
 */
#include "collision.h"

int mapObject(struct object* obj, struct size* objMap){

    if(!obj)    return;

    //VARs
    int nPoints,index;
    struct size objDim;
    struct position objPos;

    objPos  = getPosition(obj);
    objDim  = getSize(obj);
    nPoints = (objDim.alto+objDim.ancho)*2;     //floor&ceil border coordenates aka perimeter.

    //ALLOC
    if(objMap){
        free(objMap);
        objMap = NULL;
    }else{
        objMap = (struct size*)malloc(sizeof(struct size)*nPoints);
    }

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
    
        objMap[index].ancho     = x_f;
        objMap[index].alto      = y_f;
        objMap[++index].ancho   = x_c;
        objMap[index++].alto    = y_c;
    }

    //VERTICAL BORDERS
    for(int j=0;j<objDim.ancho;j++){
        int x_f,x_c,y_f,y_c;    
        int i = objDim.alto;

        x_f = (int) floor((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        x_c = (int)  ceil((i-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))-(j-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+objDim.alto/2.0);
        y_f = (int) floor((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);
        y_c = (int)  ceil((i-objDim.ancho/2.0)*(sin(objPos.direction*M_PI/180.0))+(j-objDim.alto/2.0)*(cos(objPos.direction*M_PI/180.0))+objDim.ancho/2.0);

        objMap[index].ancho     = x_f;
        objMap[index].alto      = y_f;
        objMap[++index].ancho   = x_c;
        objMap[index].alto      = y_c;
    }

    return nPoints; //should be equal to index       
}

bool checkOverlap(struct object* firstObj,struct object* secondObj){

    if(!firstObj||!secondObj)   return;

    //VARs
    bool collision = false;
    int firstMapLength, secondMapLength;
    struct size* firstMap  = NULL;
    struct size* secondMap = NULL;

    firstMapLength  = mapObject(firstObj,firstMap); 
    secondMapLength = mapObject(secondObj,secondMap);
    
    for(int i=0;i<firstMapLength;i++){
        for(int j=0;j<secondMapLength;j++){
            if((firstMap[i].ancho == secondMap[j].ancho) && (firstMap[i].alto == secondMap[j].alto)){
                collision = true;
                return collision;
            }
        }
    }
    return collision;
}

bool player_enemy_collision(struct PlayerObj* player, struct EnemyObj* enemy, char movement, int rate){
    //Function should be called only when the user wants to move the player.

    if(!player||!enemy)     return;

    //VARs
    struct position playerPos, newPos, enemyPos;

    //FETCH POSITIONS
    playerPos = getPosition(&(player->obj));
    enemyPos  = getPosition(&(player->obj));

    //GET FUTURE POSITION AND SET IT AS CURRENT IN PLAYER.
    newPos = changePosition(&(player->obj),movement,rate);
    newPos.x         += playerPos.x;
    newPos.y         += playerPos.y;
    newPos.direction += playerPos.direction;
    setPosition(&(player->obj),newPos);
    
    //CHECK IF NEWPOS OVERLAPS|COLLIDES WITH ENEMY AND SET OLD POSITION BACK IN THE PLAYER.
    if(checkOverlap(&(player->obj),&(enemy->obj))){
        setPosition(&(player->obj),playerPos);
        return true;
    }else{
        setPosition(&(player->obj),playerPos);
        return false;
    }
}
