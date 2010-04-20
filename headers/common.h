/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

struct Vector {
  double x, y;
};

typedef struct Vector vector;
typedef struct Vector velocity;
typedef struct Vector acceleration;

double VECTORlength(vector);

#endif
