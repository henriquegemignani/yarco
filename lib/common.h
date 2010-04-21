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
typedef struct Vector point;
typedef struct Vector velocity;
typedef struct Vector acceleration;

vector vectorCreate(double x, double y);

vector vectorFromVelocity( velocity v );
vector vectorFromAcceleration( acceleration a );

/* as duas ultimas eu achei que podem vir a ser usadas */

vector vectorSum(vector a, vector b);
vector vectorSub(vector a, vector b);
vector vectorMul(vector a, vector b);

double vectorLength(vector);
   int vectorPrint(vector);

int randNumber(int min, int max);

#endif /* _COMMON_H_ */
