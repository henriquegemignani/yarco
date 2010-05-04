/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

/* Constantes do programa */
#define PI 3.141592654

#define PERSON_NUM_LIMIT            100
#define PERSON_NUM_INIT             30
#define PERSON_CREATE_RATE_DEFAULT  5
#define PERSON_SPEED_DEFAULT        10
#define MAX_X                       800
#define MAX_Y                       600

#include <stdlib.h>
struct Vector {
  double x, y;
};
/* Se em coordenadas polares, x representa o raio enquanto e y o angulo. */

typedef struct Vector vector;
typedef struct Vector point;
typedef struct Vector velocity;
typedef struct Vector acceleration;

vector vectorCreate(double x, double y);

vector vectorSum(vector a, vector b);
vector vectorSub(vector a, vector b);
vector vectorMulVet(vector a, vector b);
double vectorMulEsc(vector a, vector b);

vector vectorPolarToCartesian(vector v);
vector vectorCartesianToPolar(vector v);

vector vectorRotate(vector v, double ang);
/*Funcao acima roatciona um vetor de acordo com o angulo dado, em radianos, no sentido horario*/
double vectorAngle( vector v );
vector vectorAngleSet( vector v, double ang );
vector vectorLengthSet(vector v, double length );
double vectorLength(vector);
   int vectorPrint(vector);
   
double distanceBetweenPoints(point a, point b);
   
   
   int randInt(int min, int max);
double randDouble(double min, double max);

  void genError(char *msg);


/* WARNING AND ERROR CODES */
#define ERROR_MALLOC_FAILURE            101
#define ERROR_PERSON_LIMIT_EXCEEDED     0
#define WARNING_PERSON_NOT_FOUND        202

/* Defines para ajudar o desenvolvimento! */
#define AUTOMALLOC(p) p=malloc(sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCV(p,n) p=malloc((n)*sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCADV(p,s) p=malloc(s);if(!p)MALLOC_DIE()
#define SWAP(a,b) a^=b,b^=a,a^=b

/* Imprime um erro padrao para erro com malloc e encerra a execucao
 do programa, devolvendo o erro 1. */
void MALLOC_DIE();

#endif /* _COMMON_H_ */
