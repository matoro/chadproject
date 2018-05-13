/*
 *  -USER INTERFACE IMPLEMENTATION-
 *  @author leba39, mortonman.
 */
#include "ui.h"


void printUserInterface(struct PlayerObj* player, struct BarObj** bars, int* numBars, SDL_Plotter* plot){

    if(!player || !plot) return;

    //VARs
    int UI_height, UI_width;
    struct texture uiColor,fontColor;
    char* gun_type  = getGunMsg(player);
    char* ammo_type = getAmmoMsg(player);
    int fontSize = 3;
    int thinSize = 0;

    fontColor.red    = 0;
    fontColor.green  = 0;
    fontColor.blue   = 145;

    uiColor.red    = 75;
    uiColor.green  = 75;
    uiColor.blue   = 75;
    
    UI_height = 9*HEIGHT/10;   
    UI_width  = WIDTH;

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
    //plot base layer
    for(int i=UI_height; i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
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

