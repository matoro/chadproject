/*
 *  CHARACTER SET SPRITES.
 *  @author leba39, mortonman.
 */
#ifndef CHARSET_H_INCLUDED
#define CHARSET_H_INCLUDED

//I N C L U D E s
#include <stdbool.h>
#define SPRITE_DIM 4

//F U N C T I O N s
struct sprite getSprite(char letra);

//C O N S T A N T s  &  S T R U C T s  
//ENCAPSULATE
struct sprite{
    bool caracter[SPRITE_DIM][SPRITE_DIM];
};
/*  Character SPRITES.
 *  charSet dictionary: "abcdefghijklmnopqrstuvwxyz0123SPRITE_DIM56789,.;+-!? ";
 */
const bool letra_a[SPRITE_DIM][SPRITE_DIM]={
    {0,1,0,0},
    {1,0,1,0},
    {1,1,1,0},
    {1,0,1,0},
};
const bool letra_b[SPRITE_DIM][SPRITE_DIM]={
    {1,0,0,0},
    {1,1,1,0},
    {1,0,1,0},
    {1,1,1,0},
};
const bool letra_c[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,1,1,0},
    {1,0,0,0},
    {1,1,1,0},
};
const bool letra_d[SPRITE_DIM][SPRITE_DIM]={
    {0,0,1,0},
    {1,1,1,0},
    {1,0,1,0},
    {1,1,1,0},
};
const bool letra_e[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {1,1,1,0},
    {1,0,0,0},
    {1,1,1,0},
};
const bool letra_f[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {1,0,0,0},
    {1,1,0,0},
    {1,0,0,0},
};
const bool letra_g[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {1,1,1,0},
    {0,0,1,0},
    {1,1,1,0},
};
const bool letra_h[SPRITE_DIM][SPRITE_DIM]={
    {1,0,0,0},
    {1,1,1,0},
    {1,0,1,0},
    {1,0,1,0},
};
const bool letra_i[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {0,1,0,0},
    {0,1,0,0},
    {0,1,0,0},
};
const bool letra_j[SPRITE_DIM][SPRITE_DIM]={
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {1,1,1,0},
};
const bool letra_k[SPRITE_DIM][SPRITE_DIM]={
    {1,0,1,0},
    {1,1,0,0},
    {1,1,0,0},
    {1,0,1,0},
};
const bool letra_l[SPRITE_DIM][SPRITE_DIM]={
    {1,0,0,0},
    {1,0,0,0},
    {1,0,0,0},
    {1,1,1,0},
};
const bool letra_m[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,0,1,0},
    {1,1,1,0},
    {1,0,1,0},
};
const bool letra_n[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,1,1,0},
    {1,0,1,0},
    {1,0,1,0},
};
const bool letra_o[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,1,1,0},
    {1,0,1,0},
    {1,1,1,0},
};
const bool letra_p[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {1,0,1,0},
    {1,1,1,0},
    {1,0,0,0},
};
const bool letra_q[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {1,0,1,0},
    {1,0,1,0},
    {1,1,1,1},
};
const bool letra_r[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {1,0,1,0},
    {1,1,0,0},
    {1,0,1,0},
};
const bool letra_s[SPRITE_DIM][SPRITE_DIM]={
    {0,1,0,0},
    {1,0,0,0},
    {0,1,0,0},
    {1,0,0,0},
};
const bool letra_t[SPRITE_DIM][SPRITE_DIM]={
    {0,1,0,0},
    {1,1,1,0},
    {0,1,0,0},
    {0,1,0,0},
};
const bool letra_u[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,0,1,0},
    {1,0,1,0},
    {1,1,1,0},
};
const bool letra_v[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,0,1,0},
    {1,0,1,0},
    {0,1,0,0},
};
const bool letra_w[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,0,1,0},
    {1,1,1,0},
    {1,1,1,0},
};
const bool letra_x[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,0,1,0},
    {0,1,0,0},
    {1,0,1,0},
};
const bool letra_y[SPRITE_DIM][SPRITE_DIM]={
    {1,0,1,0},
    {1,0,1,0},
    {0,1,0,0},
    {0,1,0,0},
};
const bool letra_z[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {1,1,1,0},
    {0,1,0,0},
    {1,1,1,0},
};
const bool numero_1[SPRITE_DIM][SPRITE_DIM]={
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {0,0,1,0},
};
const bool numero_2[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {0,0,1,0},
    {0,1,0,0},
    {1,1,1,0},
};
const bool numero_3[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {0,0,1,0},
    {0,0,1,0},
    {1,1,1,0},
};
const bool numero_4[SPRITE_DIM][SPRITE_DIM]={
    {1,0,1,0},
    {1,0,1,0},
    {1,1,1,0},
    {0,0,1,0},
};
const bool numero_5[SPRITE_DIM][SPRITE_DIM]={
    {1,0,0,0},
    {1,1,1,0},
    {0,0,1,0},
    {1,1,1,0},
};
const bool numero_6[SPRITE_DIM][SPRITE_DIM]={
    {1,0,0,0},
    {1,1,1,0},
    {1,0,1,0},
    {1,1,1,0},
};
const bool numero_7[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {0,0,1,0},
    {0,1,0,0},
    {0,1,0,0},
};
const bool numero_8[SPRITE_DIM][SPRITE_DIM]={
    {1,0,1,0},
    {0,1,0,0},
    {1,0,1,0},
    {0,1,0,0},
};
const bool numero_9[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {1,0,1,0},
    {1,1,1,0},
    {0,0,1,0},
};
const bool numero_0[SPRITE_DIM][SPRITE_DIM]={
    {1,1,1,0},
    {1,0,1,0},
    {1,0,1,0},
    {1,1,1,0},
};
const bool signo_coma[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {0,0,0,0},
    {0,1,0,0},
    {1,0,0,0},
};
const bool signo_punto[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {0,0,0,0},
    {1,1,0,0},
    {1,1,0,0},
};
const bool signo_puntocoma[SPRITE_DIM][SPRITE_DIM]={
    {1,1,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {1,0,0,0},
};
const bool signo_mas[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {0,1,0,0},
    {1,1,1,0},
    {0,1,0,0},
};
const bool signo_menos[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {0,0,0,0},
    {1,1,1,0},
    {0,0,0,0},
};
const bool signo_exclamacion[SPRITE_DIM][SPRITE_DIM]={
    {0,1,0,0},
    {0,1,0,0},
    {0,0,0,0},
    {0,1,0,0},
};
const bool signo_pregunta[SPRITE_DIM][SPRITE_DIM]={
    {0,1,1,0},
    {0,0,1,0},
    {0,1,0,0},
    {0,1,0,0},
};
const bool signo_espacio[SPRITE_DIM][SPRITE_DIM]={
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
};
#endif
