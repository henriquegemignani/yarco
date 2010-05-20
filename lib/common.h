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
#define PERSON_RADIUS               10
#define MAX_X                       1023
#define MAX_Y                       767
#define REPETITONS_DEFAULT          50
#define STD_DIST                    0.1

#include <stdio.h>              /* Agora nenhum arquivo precisa incluir essa biblioteca */
#include <stdlib.h>
#include <allegro.h>
struct Vector {
    double x, y;
};
/* Se em coordenadas polares, x representa o raio enquanto e y o angulo. */

typedef struct Vector vector;
typedef struct Vector point;
typedef struct Vector velocity;
typedef struct Vector acceleration;
/*Afinal, em fisica, posicao, aceleracao, e velocidade podem ser representados por vetores!*/

typedef char texture;           /* Afinal, em modo texto graficos eh uma letra! */

/*Cria um vetor*/
vector vectorCreate(double x, double y);

/*Soma dois vetores*/
vector vectorSum(vector a, vector b);
/*Subtrai vetores, primeiro vetor menos o segundo*/
vector vectorSub(vector a, vector b);
/*Multiplicacao escalar entre dois vetores*/
double vectorMulEsc(vector a, vector b);

/*Converte de coordenadas polares para coordenadas cartesianas*/
vector vectorPolarToCartesian(vector v);
/*Converte de coordenadas cartesianas para coordenadas polares*/
vector vectorCartesianToPolar(vector v);

/*Retorna o angulo do vetor*/
double vectorAngle(vector v);
/*Retorna o comprimento do vetor*/
double vectorLength(vector);
/*Seta o angulo do vetor*/
vector vectorAngleSet(vector v, double ang);
/*Seta o comprimento do vetor*/
vector vectorLengthSet(vector v, double length);
/*Rotaciona o vetor de acordo com o angulo dado, no sentido anti-horario*/
vector vectorRotate(vector v, double ang);
/*Imprime o vetor, retorna quantos caracteres foram impressos*/
int vectorPrint(vector);

/*Retorna a distancia entre dois pontos*/
double distanceBetweenPoints(point a, point b);

/*Gera um inteiro aleatorio de min a max*/
int randInt(int min, int max);
/*Gera um double aleatorio de min a max*/
double randDouble(double min, double max);
/*Aleatoriza o valor dado em no maximo value * +-distance*/
double randomizeAround(double value, double distance);

/*Imprime mensagem de erro, sai do programa*/
void genError(char *msg);


/* WARNING AND ERROR CODES */
#define ERROR_MALLOC_FAILURE            101
#define ERROR_PERSON_LIMIT_EXCEEDED     NULL
#define WARNING_PERSON_NOT_FOUND        202

/* Defines para ajudar o desenvolvimento! */
#define AUTOMALLOC(p) p=malloc(sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCV(p,n) p=malloc((n)*sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCADV(p,s) p=malloc(s);if(!p)MALLOC_DIE()
#define SWAP(a,b) a^=b,b^=a,a^=b

/* Imprime um erro padrao para erro com malloc e encerra a execucao
 do programa, devolvendo o erro 1. */
void MALLOC_DIE();

#endif                          /* _COMMON_H_ */
