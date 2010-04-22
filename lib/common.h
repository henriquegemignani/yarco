/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdlib.h>
struct Vector {
  double x, y;
};

typedef struct Vector vector;
typedef struct Vector point;
typedef struct Vector velocity;
typedef struct Vector acceleration;

vector vectorCreate(double x, double y);

vector vectorFromVelocity( velocity v );
vector vectorFromAcceleration( acceleration a );

/* as duas ultimas eu achei que podem vir a ser usadas */

vector vectorSum(vector a, vector b);
vector vectorSub(vector a, vector b);
vector vectorMulVet(vector a, vector b);
int vectorMulEsc(vector a, vector b);

double vectorLength(vector);
   int vectorPrint(vector);
   
double distanceBetweenPoints(point a, point b);
   
   
int randNumber(int min, int max);


/* EXIT CODES */
#define EXIT_MALLOCERROR 1

/* Defines para ajudar o desenvolvimento! */
#define AUTOMALLOC(p) p=malloc(sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCV(p,n) p=malloc((n)*sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCADV(p,s) p=malloc(s);if(!p)MALLOC_DIE()

/* Imprime um erro padrao para erro com malloc e encerra a execucao
 do programa, devolvendo o erro 1. */
void MALLOC_DIE();

#endif /* _COMMON_H_ */
