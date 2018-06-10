/*
 *  -USER INTERFACE IMPLEMENTATION-
 *  @author leba39, mortonman.
 */
#include "ui.h"


void printUserInterface(struct PlayerObj* player, struct BarObj** bars, int* numBars, SDL_Plotter* plot){

    if(!player || !plot) return;

    //VARs
    int UI_height, UI_width;
    struct texture uiColor,fontColor, terrainColor, sandColor, waterColor;
    char* gun_type  = getGunMsg(player);
    char* ammo_type = getAmmoMsg(player);
    int fontSize = 3;
    int thinSize = 0;

    UI_height = 9*HEIGHT/10;   
    UI_width  = WIDTH;
    
    //TERRAIN DESIGN AUX VARs
    int waterLimit      = 20;
    int sandRadius      = UI_height/2;
    int waterRadius     = WIDTH/2;
    int circleY         = UI_height/2;
    int circleX         = WIDTH/2;


    fontColor.red    = 0;
    fontColor.green  = 0;
    fontColor.blue   = 145;

    uiColor.red    = 75;
    uiColor.green  = 75;
    uiColor.blue   = 75;
    
    terrainColor.red    = 50;
    terrainColor.green  = 100;
    terrainColor.blue   = 0;

    sandColor.red    = 235;
    sandColor.green  = 200;
    sandColor.blue   = 175;

    waterColor.red    = 100;
    waterColor.green  = 175;
    waterColor.blue   = 255;

    if(*bars==NULL||*numBars==0){
        //createBar holds the barSize at {100,20}px
        struct position healthBarPos    = {UI_width/12,UI_height+60,0};
        struct position ammoBarPos      = {3*UI_width/4,UI_height+60,0};
        enum bartype health = HEALTH;
        enum bartype ammo   = AMMO;
        
        createBar(bars, numBars, player, health, healthBarPos);
        createBar(bars, numBars, player, ammo, ammoBarPos);

    }
    //update
    setCurrentValue((*bars),player->health);
    setCurrentValue(((*bars)+1),player->ammo);
    
    int i,j;
    //plot terrain
    for(i=0; i<UI_height;i++){
        for(j=0; j<WIDTH;j++){
            
            double distance;                
            distance = sqrt((j-circleX)*(j-circleX)+(i-circleY)*(i-circleY));       //int -> double. no loss in precision. no warns.
            if(distance>waterRadius){
                //water
                plot->plotPixel(j,i,waterColor.red,waterColor.green,waterColor.blue);
            }else if(distance>sandRadius){
                //sand
                plot->plotPixel(j,i,sandColor.red,sandColor.green,sandColor.blue);
            }else{
                //grass
                plot->plotPixel(j,i,terrainColor.red,terrainColor.green,terrainColor.blue);
            }
       }
    }   

    //plot base layer UIBar
    for(i=UI_height; i<HEIGHT;i++){
        for(j=0;j<WIDTH;j++){
            plot->plotPixel(j,i,uiColor.red,uiColor.green,uiColor.blue);
        }
        uiColor.red++;
        uiColor.blue++;
    }
    //plot text
    struct position textGunPos  = {4*UI_width/12,UI_height+14,0};
    struct position textAmmoPos = {4*UI_width/12,UI_height+34,0};
    plotText(gun_type,textGunPos,fontColor,fontSize,thinSize,plot);
    plotText(ammo_type,textAmmoPos,fontColor,fontSize,thinSize,plot);
    
    return;
}


char printMenu(SDL_Plotter* plot){

    if(!plot)   return 0;

    //VARs
    char title[] = "CHADPROJECT v1";
    char opt1[]  = "1. Play the game!";
    char opt2[]  = "2. Top 10 scoreboard.";
    char opt3[]  = "3. Exit.";
    struct texture backgroundClr,stripeClr;
    struct texture titleClr;                            //white default value
    struct texture fontClr;    
    struct position textPos = {WIDTH/4,HEIGHT/4,0};

    backgroundClr.red   = 110;
    backgroundClr.green = 50;
    backgroundClr.blue  = 100;
    
    stripeClr.red   = 225;
    stripeClr.green = 225;
    stripeClr.blue  = 50;
    
    fontClr.red   = 1;
    fontClr.green = 1;
    fontClr.blue  = 110;

    //plot background
    plot->clear();
    int count = 0;
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            struct texture bgClr = ((j<100||j>500)||(i<100||i>500)&&count%4==0) ? stripeClr : backgroundClr;    //design purposes
            plot->plotPixel(j,i,bgClr.red,bgClr.green,bgClr.blue);
        }
        //design purposes - degradation
        count++;
        if(count>5){
            //if you want to change colors be careful with their rgb values. if your ++ goes beyond 255 color will go black.
            backgroundClr.red++;
            backgroundClr.green++;
            backgroundClr.blue++;
            stripeClr.green--;
            stripeClr.blue++;
            count = 0;
        }
    }
    //plot title and menu options
    plotText(title,textPos,titleClr,5,1,plot);
    textPos.y += 50;
    textPos.x += 50;
    plotText(opt1,textPos,fontClr,3,0,plot);
    textPos.y += 20;
    plotText(opt2,textPos,fontClr,3,0,plot);
    textPos.y += 20;
    plotText(opt3,textPos,fontClr,3,0,plot);
    //check for key pressed
    bool response = false;
    char letra;
    do{
        bool keyhit = plot->kbhit();
        if(keyhit){
            letra = plot->getKey();
            if(letra == '1' || letra == '2' || letra == '3')    response = true;
        }
        plot->update();
    }while(!response);

    return letra;
}

char* getGunMsg(struct PlayerObj* player){  
    //added casting otherwise C++ would throw. ISO c++ forbids converting a string constant into char*. Valid in C though.
    
    if(!player){
        return (char*)"player not found";   
    }else{
        switch(player->player_weapon){
            case NO_WEAPON:
                return (char*)"no gun!";
            case PISTOL:
                return (char*)"holding a pistol";
            case SHOTGUN:
                return (char*)"packing a 12 gauge";
            case MACHINEGUN:
                return (char*)"grabbing tommy gun";
            case RIFLE:
                return (char*)"sniping a rifle";
            default:
                return (char*)"not found";
        }
    }
}

char* getAmmoMsg(struct PlayerObj* player){
    //added casting otherwise C++ would throw. ISO c++ forbids converting a string constant into char*. Valid in C though.
    
    if(!player){
        return (char*)"player not found!";
    }else{
        switch(player->ammo_type){
            case NONE:
                return (char*)"no ammo!";
            case NORMAL:
                return (char*)"normal ammo";
            case INCENDIARY:
                return (char*)"incendiary ammo";
            case EXPLOSIVE:
                return (char*)"explosive ammo";
            default:
                return (char*)"not found";
        }
    }
}

FILE* openFile(char* mode){

    FILE* fp = NULL;

    fp = fopen("scores.txt",mode);
    if(!fp){
        fprintf(stderr,"Error, couldnt open file. Error num: %d\n",errno);
        perror("Description:");
    }    

    return fp;
}

int readScoreBoard(char* strings[]){

    if(!strings||TOP_TEN!=20)   return -1;

    //VARs      
    FILE* file = NULL;
    char* mode  = NULL;
    char* name;
    char* score;
    int number;   
    int returns;

    mode = (char*)"r";
    file = openFile(mode);
    if(!file)  return -2;

    int i;
    for(i=0; i<TOP_TEN; i++){
        
        returns = fscanf(file,"%s %s",name,score);
        if(returns==-1){
            break;
        }
        strings[i]   = name;
    }
    for(;i<TOP_TEN;i++){
        strings[i]   = (char*)"";
    }
    
    fclose(file);
}

int writeScoreBoard(){}


bool printScoreBoard(SDL_Plotter* plot){

    if(!plot)   return false;

    //VARs
    char title[]    = "TOP 10 SCOREBOARD";
    char header[]   = "NAME--------SCORE";
    char *scores[TOP_TEN];
    int error = 0;

    struct position textPos;
    struct texture bgColor1, bgColor2, titleColor, textColor1, textColor2;

    //DEFINITION
    textPos = {WIDTH/4,HEIGHT/4,0};

    bgColor1.red   = 110;
    bgColor1.green = 50;
    bgColor1.blue  = 100;
    
    bgColor2.red   = 225;
    bgColor2.green = 225;
    bgColor2.blue  = 50;
    
    titleColor.red   = 0;
    titleColor.green = 0;
    titleColor.blue  = 10;

    textColor1.red   = 150;
    textColor1.green = 0;
    textColor1.blue  = 150;

    textColor2.red   = 64;
    textColor2.green = 64;
    textColor2.blue  = 64;


    error = readScoreBoard(scores);
    if(error<0){
        fprintf(stderr,"Error reading scoreboard, code: %d\n",error);
        return false;
    }
    
    //plot background
    plot->clear();
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            struct texture bgClr = ((j<100||j>500)||(i<100||i>500)) ? bgColor1 : bgColor2;
            plot->plotPixel(j,i,bgClr.red,bgClr.green,bgClr.blue);
        }
        bgColor1.green++;
        bgColor2.blue++;   
        if(bgColor1.green>255)  bgColor1.green = bgColor1.green%255;
        if(bgColor2.green>255)  bgColor2.green = bgColor2.green%255;
    }

    //plot title and scores
    plotText(title,textPos,titleColor,5,1,plot);
    textPos.y += 50;
    textPos.x += 50;
    plotText(header,textPos,textColor1,3,0,plot);
/*
    for(int i=0; i<TOP_TEN/2; i++){
        textPos.y += 20;
        plotText(scores[i],textPos,textColor2,2,0,plot);
        textPos.x += 50;
        plotText(scores[i+1],textPos, textColor1,2,0,plot);
        textPos.x -= 50;
    }

*/
    //check for key pressed
    char letra;
    do{
        bool keyhit = plot->kbhit();
        if(keyhit){
            letra = plot->getKey();
            if(letra == '0'){
                return false;
            }else if(letra == 'B'){
                return true;
            }
        }
        plot->update();
    }while(true);
}
