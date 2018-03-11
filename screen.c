/*
 * SCREEN.c -ALWAYS IN PLAY- COMPONENT
 * CODE IMPLEMENTATION
 * @author leba39, mortonman.
 */

void plotObject(struct object *obj,SDL_Plotter* plotter){
	
	struct size dim     = getSize(obj);
	struct position pos = getPosition(obj);
	struct texture clr  = getTexture(obj);
	
	int adjustedx_f;
	int adjustedx_c;
	int adjustedy_f;
	int adjustedy_c;

	for(int i=0; i<*(size+0);i++){
		for(int j=0;j<*(size+1);j++){
		
			//Adjusted Coordenates.
			adjustedx_f = (int) floor((i-dim.alto/2.0)*(cos(pos.direction*M_PI/180.0))-(j-dim.ancho/2.0)*(sin(pos.direction*M_PI/180.0))+dim.alto/2.0);
			adjustedx_c = (int)  ceil((i-dim.alto/2.0)*(cos(pos.direction*M_PI/180.0))-(j-dim.ancho/2.0)*(sin(pos.direction*M_PI/180.0))+dim.alto/2.0); 
			adjustedy_f = (int) floor((i-dim.ancho/2.0)*(sin(pos.direction*M_PI/180.0))+(j-dim.alto/2.0)*(cos(pos.direction*M_PI/180.0))+dim.ancho/2.0);
			adjustedy_c = (int)  ceil((i-dim.ancho/2.0)*(sin(pos.direction*M_PI/180.0))+(j-dim.alto/2.0)*(cos(pos.direction*M_PI/180.0))+dim.ancho/2.0);

			//Plotting Coordenates.			
			plotter->plotPixel(adjustedx_c+pos.x,adjustedy_c+pos.y,clr.red,clr.green,clr.blue);
			plotter->plotPixel(adjustedx_f+pos.x,adjustedy_f+pos.y,clr.red,clr.green,clr.blue);
			plotter->plotPixel(adjustedx_c+pos.x,adjustedy_f+pos.y,clr.red,clr.green,clr.blue);
			plotter->plotPixel(adjustedx_f+pos.x,adjustedy_c+pos.y,clr.red,clr.green,clr.blue);
		}
	}
} 

void plotText(char msg[]){
	
	puts(msg,stdout);
}
