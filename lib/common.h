/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#define DEBUG
#ifdef DEBUG
#define debugMsg(msg) fprintf(stderr, "%s\n", msg);
#define debugDouble(msg,par) fprintf(stderr, "%s: %f\n", msg, (par));
#define debugOp(op) (op);
#else
#define debugMsg
#define debugDouble(msg,par)
#define debugOp(op)
#endif

/* Constantes do programa */
#define PI 3.141592654

/* Valores precalculados para economizar um pouco de processamento, ja que sao usados com certa frequencia*/
#define SQRT_2 1.414213562
#define SQRT_5 2.236067977

#define PERSON_SPEED_DEFAULT        10
#define MAX_X                       1023
#define MAX_Y                       767
#define DURATION_DEFAULT            50.0
#define STD_DIST                    0.5
#define NUM_CLASS                   4
#define QUAD_SIZE_X                 100
#define QUAD_SIZE_Y                 100

#include <stdio.h>              /* Agora nenhum arquivo precisa incluir essa biblioteca */
#include <stdlib.h>

struct Vector {
    double x, y;
};

struct Quad {
    int x, y;
};


typedef struct Vector vector;
typedef struct Vector point;
typedef struct Vector velocity;
typedef struct Vector acceleration;
/*Afinal, em fisica, posicao, aceleracao, e velocidade podem ser representados por vetores!*/

typedef struct Quad quadrant;

typedef enum {
    TEX_SQUARE,
    TEX_CIRCLE,
    TEX_TRIANGLE,
    TEX_HORIZONTAL_RETANGLE,
    TEX_VERTICAL_RETANGLE
} texType;

typedef struct Texture {
    int color;
    texType type;
} texture;

texture createTexture(int red, int blue, int green, texType type);


/*Cria um vetor*/
vector vectorCreate(double x, double y);
/* Todas as outras operacoes com vetores sao definidas em "lib/vector.h" */

/*Seta um quadrante*/
quadrant quadSet(int x, int y);

/*Verifica se o quadrante b esta num dos 8 quadrantes adjances ao quadrante a*/
int quadNear(quadrant a, quadrant b);

/*Funcoes que retornam o sinal de um numero*/
int signInt(int a);
int signDouble(double a);

/*Retorna a distancia entre dois pontos*/
double distanceBetweenPoints(point a, point b);

/*Gera um inteiro aleatorio de min a max*/
int randInt(int min, int max);
/*Gera um double aleatorio de min a max*/
double randDouble(double min, double max);
/*Aleatoriza o valor dado em no maximo value * +-distance*/
double randomizeAround(double value, double distance);
/*Gera um ponto na borda da tela*/
void generatePosInBorder(point * pos, double *dir);

/*Imprime mensagem de erro, sai do programa*/
void genError(char *msg);

/*Imprime uma mesngagem de aviso, continua no programa*/
void genWarning(char *msg);


/* WARNING AND ERROR CODES */
#define ERROR_MALLOC_FAILURE            101
#define ERROR_OBJECT_LIMIT_EXCEEDED		201
#define WARNING_OBJECT_NOT_FOUND		202
#define ERROR_OBJECT_IS_COLLIDING               203


/* Defines para ajudar o desenvolvimento! */
#define AUTOMALLOC(p) p=malloc(sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCV(p,n) p=malloc((n)*sizeof(*(p)));if(!p)MALLOC_DIE()
#define AUTOMALLOCADV(p,s) p=malloc(s);if(!p)MALLOC_DIE()
#define SWAP(a,b) a^=b,b^=a,a^=b

/* Imprime um erro padrao para erro com malloc e encerra a execucao
 do programa, devolvendo o erro 1. */
void MALLOC_DIE();

#endif                          /* _COMMON_H_ */
