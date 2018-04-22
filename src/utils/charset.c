/*
 *  CHARSET IMPLEMENTATION
 *  @author leba39, mortonman.
 */
#include "charset.h"
struct sprite getSprite(char letra){

    //VARs
    struct sprite response;
    
    if(!letra){
        response.caracter[0][0] = -1;   //its a way of saying that we couldn't find appropiate sprite
        return response;
    }

    switch(letra){
        
        case 'a':
        case 'A':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_a[i][j];}}
            return response;
        case 'b':
        case 'B':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_b[i][j];}}
            return response;
        case 'c':
        case 'C':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_c[i][j];}}
            return response;
        case 'd':
        case 'D':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_d[i][j];}}
            return response;
        case 'e':
        case 'E':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_e[i][j];}}
            return response;
        case 'f':
        case 'F':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_f[i][j];}}
            return response;
        case 'g':
        case 'G':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_g[i][j];}}
            return response;
        case 'h':
        case 'H':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_h[i][j];}}
            return response;
        case 'i':
        case 'I':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_i[i][j];}}
            return response;
        case 'j':
        case 'J':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_j[i][j];}}
            return response;
        case 'k':
        case 'K':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_k[i][j];}}
            return response;
        case 'l':
        case 'L':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_l[i][j];}}
            return response;
        case 'm':
        case 'M':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_m[i][j];}}
            return response;
        case 'n':
        case 'N':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_n[i][j];}}
            return response;
        case 'o':
        case 'O':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_o[i][j];}}
            return response;
        case 'p':
        case 'P':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_p[i][j];}}
            return response;
        case 'q':
        case 'Q':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_q[i][j];}}
            return response;
        case 'r':
        case 'R':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_r[i][j];}}
            return response;
        case 's':
        case 'S':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_s[i][j];}}
            return response;
        case 't':
        case 'T':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_t[i][j];}}
            return response;
        case 'u':
        case 'U':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_u[i][j];}}
            return response;
        case 'v':
        case 'V':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_v[i][j];}}
            return response;
        case 'w':
        case 'W':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_w[i][j];}}
            return response;
        case 'x':
        case 'X':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_x[i][j];}}
            return response;
        case 'y':
        case 'Y':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_y[i][j];}}
            return response;
        case 'z':
        case 'Z':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = letra_z[i][j];}}
            return response;
        case '1':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_1[i][j];}}
            return response;
        case '2':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_2[i][j];}}
            return response;
        case '3':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_3[i][j];}}
            return response;
        case '4':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_4[i][j];}}
            return response;
        case '5':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_5[i][j];}}
            return response;
        case '6':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_6[i][j];}}
            return response;
        case '7':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_7[i][j];}}
            return response;
        case '8':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_8[i][j];}}
            return response;
        case '9':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_9[i][j];}}
            return response;
        case '0':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = numero_0[i][j];}}
            return response;
        case ',':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = signo_coma[i][j];}}
            return response;
        case '.':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = signo_punto[i][j];}}
            return response;
        case ';':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = signo_puntocoma[i][j];}}
            return response;
        case '!':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = signo_exclamacion[i][j];}}
            return response;
        case '?':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = signo_pregunta[i][j];}}
            return response;
        case ' ':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = signo_espacio[i][j];}}
            return response;
        case '+':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = signo_mas[i][j];}}
            return response;
        case '-':
            for(int i=0;i<SPRITE_DIM;i++){for(int j=0;j<SPRITE_DIM;j++){response.caracter[i][j] = signo_menos[i][j];}}
            return response;
        default:
            response.caracter[0][0] = -1;   //its a way of saying that we couldn't find appropiate sprite
            return response;
    }
}
