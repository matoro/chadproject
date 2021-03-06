/*
 *  GAMELOGIC IMPLEMENTATION
 *  @author leba39, mortonman.
 */
#include "gamelogic.h"

void spawnDroppable(struct Droppable** droppables, int* num_droppables, int hp, int ammo){
 
    //VARs
    int index;
    unsigned char opt;
    bool probability;
    unsigned char base_limit = 20;
    char drop_type[2];
    struct position drop_pos;
    
    //PROBABILITY. 20% CHANCE OF SPAWNING DROPPABLE. INCREASES WITH LOW AMMO&HP
    if(ammo<20) base_limit += 10;
    if(hp<50)   base_limit += 10;
    probability = (1+rand()%100<base_limit);

    if(probability){
        //DEF
        opt      = (hp>80) ? (1+rand()%2) : (1+rand()%3);
        drop_pos = getRandomPos();
        switch(opt){

            case 1: //AMMO
                drop_type[0] = 'A';
                opt = (1+rand()%3);
                drop_type[1] = (opt==1) ? 'N' : ((opt==2) ? 'I': 'E');
                break;
            case 2: //WEAPON
                drop_type[0] = 'W';
                opt = (1+rand()%4);
                drop_type[1] = (opt==1) ? 'P' : ((opt==2) ? 'S': ((opt==3) ? 'M' : 'R'));
                break;
            case 3: //POTION
                drop_type[0] = 'P';
                opt = (1+rand()%2);
                drop_type[1] = (opt==1) ? 'S' : 'F';
                break;
            default:
                fprintf(stderr,"Something odd in spawnDroppable!\n");
                return;
        }
        createDrop(droppables,num_droppables,&drop_pos);
        index = *num_droppables-1;//droppables[0]
        setCurrentType((*droppables+index),drop_type);
    }else{
        fprintf(stdout,"Did not spawn any droppable this time!\n"); //debug
    }

    return;
}

void spawnEnemy(struct EnemyObj** enemies, int* num_enemies, struct object player_obj, int score){

    //VARs
    unsigned char digits = 0;
    unsigned char base_limit = 15;
    bool probability, overlap;
    struct object enemy_obj; 
    struct position enemy_pos;  //auxiliary
    struct size enemy_player_size = {16,16};    

    //PROBABILITY OF SPAWNING ENEMY. MORE SCORE, MORE DIGITS, MORE PROB.
    do{
        score /= 10;
        digits++;
    }while(score>0);
    probability = (((1+rand()%100)/digits)<base_limit);

    if(probability){
        //DEF
        overlap = true;
        enemy_obj.textureObj = NULL;    //dont need it
        enemy_obj.sizeObj    = enemy_player_size;
        do{
            enemy_obj.posObj = getRandomPos();
            overlap = checkOverlap(&enemy_obj,&player_obj);
        }while(overlap);    
        //once we have a valid position, we set its direction and create the enemy
        setEnemyDirection(&(enemy_obj.posObj),player_obj.posObj);
        createEnemy(enemies,num_enemies,enemy_player_size,&(enemy_obj.posObj));
    }else{
        fprintf(stdout,"Did not spawn any enemy this time!\n"); //debug
    }

    return;
}

struct position getRandomPos(){

    //VARs
    struct position pos;
    int offset_min, offset_max, border_x, border_y, x, y;

    //DEF
    offset_min    = 5;
    offset_max    = 15;
    border_x      = WIDTH-offset_max;
    border_y      = 9*HEIGHT/10-offset_max;

    //RAND
    //make sure from the get go to get a valid position within the game screen and not touching the borders (offsets). 
    x = rand()%border_x+offset_min; 
    y = rand()%border_y+offset_min;
    
    pos.x = x;
    pos.y = y;
    pos.direction = 0;

    return pos;
}

void setEnemyDirection(struct position* enemy_pos, struct position player_pos){

    //VARs
    int x, y, x_e, y_e, x_p, y_p, dir;
    double division, resultado, factor;

    //DEF
    factor = 180/PI;
    x_e = enemy_pos->x;
    y_e = enemy_pos->y;
    x_p = player_pos.x;
    y_p = player_pos.y;

    //OPER
    x = x_p-x_e;
    y = y_p-y_e;
    division  = (double)y/x;
    resultado = atan(division)*factor;
    
    //ADAPT DEGREES 0-360
    if((x<0&&y>0)||(x<0&&y<0))  resultado += 180;
    if(x>0&&y<0)                resultado += 360;
    //ADD POSITION.DIRECTION OFFSET
    resultado += 90;

    //SAVE
    dir = (int)floor(resultado);
    enemy_pos->direction = dir;

    return;
}

void updateScore(time_t* t_0, int* current_score){

    if(!t_0||!current_score||*t_0<0||*current_score<0)    return;

    //VARs
    time_t t_now;
    int sec_passed;

    //TIME
    t_now       = time(NULL);
    sec_passed  = t_now-*t_0;
    *t_0        = time(NULL);     
    if(sec_passed<=0)   return;

    //UPDATE
    *current_score += sec_passed;
    
    return;
}

bool onCooldown(struct timeval* t_last_shot, enum weapon player_weapon){

    if(!t_last_shot||player_weapon==NO_WEAPON)  return true;

    //VARs
    struct timeval t_current;
    double elapsed_time;

    //TIME
    gettimeofday(&t_current,NULL);
    elapsed_time  = (t_current.tv_sec - t_last_shot->tv_sec)*1000.0;      // sec to ms
    elapsed_time += (t_current.tv_usec - t_last_shot->tv_usec)/1000.0;   // us to ms
    
    switch(player_weapon){

        case PISTOL:
            if(elapsed_time>500){
                gettimeofday(t_last_shot,NULL); //update;
                return false;
            }
            break;
        case SHOTGUN:
            if(elapsed_time>1500){
                gettimeofday(t_last_shot,NULL); //update;
                return false;
            }
            break;
        case MACHINEGUN:
            if(elapsed_time>300){
                gettimeofday(t_last_shot,NULL); //update;
                return false;
            }
            break;
        case RIFLE:
            if(elapsed_time>2000){
                gettimeofday(t_last_shot,NULL); //update;
                return false;
            }
            break;
        default:
            break;
    }
    return true;
}

signed char bulletTimeStatus(struct timeval t_last_end){

    //VARs
    struct timeval t_current;
    double elapsed_time;

    //TIME
    gettimeofday(&t_current,NULL);
    elapsed_time  = (t_current.tv_sec - t_last_end.tv_sec)*1000.0;      // sec to ms
    elapsed_time += (t_current.tv_usec - t_last_end.tv_usec)/1000.0;   // us to ms

    if(elapsed_time < 0){
        return -1;
    }else if(elapsed_time > 25000){
        return 0;   //no cooldown
    }else if(elapsed_time < 5000){
        return 1;   //still running
    }else{
        return 2;   //in between
    }
}

void setBulletTime(struct timeval* t_last_end, bool mode, int* hp, bool* first_blood){

    if(!t_last_end||!hp||!first_blood)  return;

    /*  MODE:   true    -> set bullet time
     *          false   -> unset bullet time   
     */

    if(mode&&(*first_blood||*hp>10)){

        //PAY BULLET TIME PRICE
        if(*first_blood == true){
            *first_blood = false;
        }else{
            *hp -= 10;
        }

        //SET VALUES
        RATE_MVMT_PLAYER = 3;
        RATE_MVMT_ENEMY  = 1;
        RATE_MVMT_BULLET = 2;

        //UPDATE TIME
        gettimeofday(t_last_end,NULL);
    
    }else{

        //UNSET VALUES
        RATE_MVMT_PLAYER = 6;
        RATE_MVMT_ENEMY  = 6;
        RATE_MVMT_BULLET = 5;
    }

    return;
}
