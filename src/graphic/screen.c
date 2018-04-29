/*
 * SCREEN.c -ALWAYS IN PLAY- COMPONENT
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */
#include "screen.h"

void plotObject(struct object *obj,SDL_Plotter* plotter){
	
	struct size dim     = getSize(obj);
	struct position pos = getPosition(obj);
	
	int adjustedx_f;
	int adjustedx_c;
	int adjustedy_f;
	int adjustedy_c;

	int totalIndex = 0;
	for(int i=0; i<dim.alto;i++){
		for(int j=0;j<dim.ancho;j++){		

			//Adjusted Coordenates.
			adjustedx_f = (int) floor((i-dim.alto/2.0)*(cos(pos.direction*M_PI/180.0))-(j-dim.ancho/2.0)*(sin(pos.direction*M_PI/180.0))+dim.alto/2.0);
			adjustedx_c = (int)  ceil((i-dim.alto/2.0)*(cos(pos.direction*M_PI/180.0))-(j-dim.ancho/2.0)*(sin(pos.direction*M_PI/180.0))+dim.alto/2.0); 
			adjustedy_f = (int) floor((i-dim.ancho/2.0)*(sin(pos.direction*M_PI/180.0))+(j-dim.alto/2.0)*(cos(pos.direction*M_PI/180.0))+dim.ancho/2.0);
			adjustedy_c = (int)  ceil((i-dim.ancho/2.0)*(sin(pos.direction*M_PI/180.0))+(j-dim.alto/2.0)*(cos(pos.direction*M_PI/180.0))+dim.ancho/2.0);

			//Getting this pixel color.
			struct texture clr  = getTexture(obj,totalIndex);

			//Plotting Coordenates.			
			plotter->plotPixel(adjustedx_c+pos.x,adjustedy_c+pos.y,clr.red,clr.green,clr.blue);
			plotter->plotPixel(adjustedx_f+pos.x,adjustedy_f+pos.y,clr.red,clr.green,clr.blue);
			plotter->plotPixel(adjustedx_c+pos.x,adjustedy_f+pos.y,clr.red,clr.green,clr.blue);
			plotter->plotPixel(adjustedx_f+pos.x,adjustedy_c+pos.y,clr.red,clr.green,clr.blue);
			
			totalIndex++;
		}
	}
} 

void plotText(char msg[],struct position initialPos,struct texture fontColor,int fontSize,char thinness,SDL_Plotter* plotter){
	
    if(!msg||fontSize<=0)    return;
    
    //VARs
    int msgLength;
    int initX;
    int initY;
    struct sprite nextSprite;

    //DEFINITION
    msgLength = strlen(msg);
    initX = initialPos.x;
    initY = initialPos.y;
    thinness = (thinness>=fontSize) ? 0 : thinness;


    for(int k=0;k<msgLength;k++){
        nextSprite = getSprite(msg[k]);
        if(nextSprite.caracter[0][0]!=-1){   //if we could find appropiate sprite
            //plot letter
            for(int i=0;i<SPRITE_DIM;i++){
                for(int j=0;j<SPRITE_DIM;j++){
                    if(nextSprite.caracter[i][j]==1){
                        //x-i&y-j doesn't correspond each other
                        int col = i*fontSize;
                        int row = j*fontSize;

                        for(int scale_col=0;scale_col<fontSize;scale_col++){
                            for(int scale_row=0;scale_row<fontSize;scale_row++){
                                if((fontSize-scale_row)>thinness&&(fontSize-scale_col)>thinness){
                                    plotter->plotPixel(initX+(row+scale_row),initY+(col+scale_col),fontColor.red,fontColor.green,fontColor.blue);
                                }
                            }
                        }
                    }                
                }
            }
        }else{
            fprintf(stderr,"Couldnt find sprite for: %c\n",msg[k]);
        }
        //update position.
        initX += SPRITE_DIM*fontSize;
        if((initX+SPRITE_DIM*fontSize)>WIDTH)     return;     //we return if the message is too long and we don't have WIDTH left for the next letter.
    }
}
