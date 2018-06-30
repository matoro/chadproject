/*
 *  -USER INTERFACE IMPLEMENTATION-
 *  @author leba39, mortonman.
 */
#include "ui.h"


void printUserInterface(struct PlayerObj* player, struct BarObj** bars, int* numBars, int score, SDL_Plotter* plot){

    if(!player || !plot) return;

    //VARs
    int UI_height, UI_width;
    struct texture uiColor,fontColor, terrainColor, sandColor, waterColor, scoreColor;
    struct position scorePos;
    char* gun_type  = getGunMsg(player);
    char* ammo_type = getAmmoMsg(player);
    char score_str[12] = "0";
    int fontSize  = 3;
    int thinSize  = 0;
    int scoreSize = 5;
 
    UI_height = 9*HEIGHT/10;   
    UI_width  = WIDTH;
    
    if(score>0) sprintf(score_str,"%d",score);    
    scorePos = {13*WIDTH/15,HEIGHT/30,0};

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

    scoreColor.red    = 70;
    scoreColor.green  = 10;
    scoreColor.blue   = 70;

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
    plotText(score_str,scorePos,scoreColor,scoreSize,thinSize,plot);

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

    fp = fopen(SCOREBOARD_FILE,mode);
    if(!fp){
        fprintf(stderr,"Error, couldnt open file. Error num: %d\n",errno);
        perror("Description:");
    }    

    return fp;
}

int readScoreBoard(struct file_data** data){

    if(!data)   return -1;      //Err:  we malloc NULL

    //VARs      
    FILE* file  = NULL;
    char* mode  = NULL;
    long int n_bytes;
    int n_data;
    
    mode = (char*)"r";
    file = openFile(mode);
    if(!file)  return -2;       //Err: couldnt open file 


    //FILE LENGTH
    fseek(file,0L,SEEK_END);
    n_bytes = ftell(file);
    n_data  = n_bytes/sizeof(struct file_data);
    rewind(file);               //equivalent to fseek(file,0L,SEEK_SET)
    if(n_data == 0){
        return 0;          
    }else if(n_data>TOP){
        return -3;              //Err: empty file or malformed.    
    }

    //MALLOC
    *data = (struct file_data*)malloc(sizeof(struct file_data)*n_data);

    //FILL STRUCTs
    for(int i=0; i<n_data;i++){
        fread(((*data)+i),sizeof(struct file_data),1,file);
    }
    
    fclose(file);
    return n_data;
}

int writeScoreBoard(struct file_data new_data){

    //VARs
    struct file_data* data;
    int num_data, name_length;
    FILE* file = NULL;
    char* mode = NULL;
    bool new_file = false;

    //VALIDATE INPUT
    name_length = strlen(new_data.name);
    if(new_data.score<0||name_length<3){
        fprintf(stderr,"Score must be positive and nickname length at least 3 characters long.\n");
        return -1;        //Invalid file_data struct input.
    }
    
    //READ FILE
    num_data = readScoreBoard(&data);
    if(num_data<0){
        fprintf(stderr,"Error reading scoreboard binary, code: %d\n",num_data);
        return -2;                                      //Error reading scoreboard.bin
    }else if(num_data>10){
        fprintf(stderr,"Scoreboard binary malformed, code: %d\n",num_data);
        return -3;                                      //Error reading scoreboard.bin
    }else if(num_data==0){
        new_file = true;        //no need to free data
    }
    
    //WRITE FILE
    mode = (char*)"w";
    file = openFile(mode);
    if(!file)  return -2;       //Err: couldnt open file 

    if(new_file){
        fwrite(&new_data, sizeof(struct file_data),1,file);
    }else{
        
        //INSERT POINT (SCOREBOARD KEEPS ITSELF SORTED)
        bool end = true;
        int index;
        for(index = 0; index<num_data; index++){
            if(new_data.score>data[index].score){
                end = false;
                break;
            }
        }
        if(end) index = num_data;

        int arr = 0;
        for(int i=0; i<TOP; i++){
            if(i==index){
                fwrite(&new_data, sizeof(struct file_data),1,file);
            }else{
                if(i>num_data)  break;
                fwrite((data+arr), sizeof(struct file_data),1,file);
                arr++;
            }
        }
    }

    //CLOSE AND FREE
    if(!new_file){ 
        free(data);     
        data = NULL;
    }
    fclose(file);
    
    return 0;
}


bool printScoreBoard(SDL_Plotter* plot){

    if(!plot)   return false;

    //VARs
    char title[]    = "TOP10 SCOREBOARD";
    char header[]   = "NAME-+-+-+-+-SCORE";
    char back[]     = "-b-ack";
    int num_data;
    struct file_data* data;
    struct position textPos, backPos;
    struct texture bgColor1, bgColor2, titleColor, textColor1, textColor2, textColor3;

    //DEFINITION
    textPos = {WIDTH/4,HEIGHT/4,0};
    backPos = {41*WIDTH/60,94*HEIGHT/120,0};

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

    textColor3.red   = 0;
    textColor3.green = 155;
    textColor3.blue  = 0;

    num_data = readScoreBoard(&data);
    if(num_data<0){
        fprintf(stderr,"Error reading scoreboard binary, code: %d\n",num_data);
        return false;
    }else{
        
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

        //plot title, back reference and scores
        plotText(back,backPos,textColor3,3,0,plot);
        plotText(title,textPos,titleColor,5,1,plot);
        textPos.y += HEIGHT/12;
        textPos.x += WIDTH/15;
        plotText(header,textPos,textColor1,3,0,plot);

        if(num_data>0){

            textPos.y+=HEIGHT/30;
            for(int i=0; i<num_data; i++){
                textPos.y += HEIGHT/30;
                plotText(data[i].name,textPos,textColor2,2,0,plot);
                textPos.x += 3*WIDTH/10;
                char score[12];
                sprintf(score,"%d",data[i].score);
                plotText(score,textPos,textColor2,2,0,plot);
                textPos.x -= 3*WIDTH/10;
            }

            free(data);
            data = NULL;
        }

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
}

bool printSaveScore(SDL_Plotter* plot, int score){

    if(!plot||score<0)   return false;

    //VARs
    char title[]    = "SAVE SCORE";
    char header[]   = "Enter your nickname";
    char rules[]    = "3-9 characters long";
    char save[]     = "SAVE";
    char back[]     = "EXIT";
    char clear[]    = "CLEAR";
    char score_str[12];
    char points[]   = " points";    
    int inputY, inputX, count;
    char nickname[10] = "";
    char letra;
    
    struct file_data data;
    struct position titlePos, textPos, savePos, backPos, clearPos, inputPos;
    struct texture bgColor1, bgColor2, bgColor3, bgColor4, titleColor, textColor1, textColor2, textColor3, textColor4;

    //DEFINITION

    bgColor1.red   = 80;
    bgColor1.green = 50;
    bgColor1.blue  = 40;
    
    bgColor2.red   = 50;
    bgColor2.green = 150;
    bgColor2.blue  = 150;
    
    bgColor3.red   = 150;
    bgColor3.green = 0;
    bgColor3.blue  = 75;

    bgColor4.red   = 235;
    bgColor4.green = 235;
    bgColor4.blue  = 235;

    titleColor.red   = 25;
    titleColor.green = 25;
    titleColor.blue  = 25;

    textColor1.red   = 150;
    textColor1.green = 0;
    textColor1.blue  = 150;

    textColor2.red   = 0;
    textColor2.green = 0;
    textColor2.blue  = 250;

    textColor3.red   = 250;
    textColor3.green = 250;
    textColor3.blue  = 50;

    textColor4.red   = 250;
    textColor4.green = 0;
    textColor4.blue  = 0;


    PLOT:
    titlePos = {WIDTH/3,HEIGHT/4,0};
    textPos = {19*WIDTH/60,HEIGHT/3,0};
    savePos = {2*WIDTH/3,94*HEIGHT/120,0};
    backPos = {WIDTH/4,94*HEIGHT/120,0};
    clearPos = {9*WIDTH/20,94*HEIGHT/120,0};

    //plot background
    plot->clear();
    for(int i=0;i<HEIGHT;i++){
        for(int j=0;j<WIDTH;j++){
            struct texture bgClr = ((j<100||j>500)||(i<100||i>500)) ? bgColor1 : bgColor2;
            bgClr = ((i+j)%8==0) ?  bgColor3 : bgClr;
            plot->plotPixel(j,i,bgClr.red,bgClr.green,bgClr.blue);
        }
    }

    //plot title, header and options
    plotText(back,backPos,textColor3,3,0,plot);
    plotText(clear,clearPos,textColor3,3,0,plot);
    plotText(save,savePos,textColor3,3,0,plot);
    plotText(title,titlePos,titleColor,5,0,plot);
    plotText(header,textPos,textColor1,3,0,plot);
    textPos.y += HEIGHT/30;
    textPos.x += WIDTH/20;
    plotText(rules,textPos,textColor4,2,0,plot);


    //plot input textbox and score
    inputPos    = {WIDTH/4,HEIGHT/2,0};
    inputX      = inputPos.x+WIDTH/2;
    inputY      = inputPos.y+HEIGHT/12;     

    for(int i=inputPos.y;i<inputY;i++){
        for(int j=inputPos.x;j<inputX;j++){
            plot->plotPixel(j,i,bgColor4.red,bgColor4.green,bgColor4.blue);
        }
    }
    inputPos.y += HEIGHT/30;
    inputPos.x += WIDTH/4;
    sprintf(score_str,"%d",score);
    strcat(score_str,points);
    plotText(score_str,inputPos,textColor2,3,1,plot);

    inputPos.x -= WIDTH/4;
    inputPos.x += HEIGHT/20;
    
    //check for key pressed
    count = 0;
    do{
        bool keyhit = plot->kbhit();
        if(keyhit){
            letra = plot->getKey();
            if(letra == '0'){
                //user press exit. player doesn't want to play anymore. return false.
                return false;
            }else if(letra == '1'){
                //user wants to clear input textbox                
                for(int i=0; i<MAX_NAME; i++)   nickname[i] = '\0';
                goto PLOT;
            }else if(letra == '3' || letra == '('){
                //user submits
                if(count<3||count>=MAX_NAME)    continue;                               
                
                memmove(data.name,nickname,count+1);
                data.score = score;
                int err = writeScoreBoard(data);
                if(err==0){
                    //Success saving scoreboard, sends user back to main menu.
                    fprintf(stdout,"SUCCESS SAVING SCORE!\n");
                    return true;
                }else{
                    //Something failed saving scoreboard, exits program.
                    fprintf(stderr,"SAVING SCORE ERROR. Numcode: %d\n",err);
                    return false;
                }
            }else{
                //add letter
                if(count<MAX_NAME-1)    nickname[count++] = letra;
            }
        }
        plotText(nickname,inputPos,textColor2,3,0,plot);
        plot->update();
    }while(true);
}
