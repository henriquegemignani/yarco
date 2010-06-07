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

/*Constante abaixo precalculada para economizar processamento. Serve para deixar o
 *circulo de colisao e o quadrado desenhado com a mesma area, para tentar reduzir a diferenca
 *entre o circulo de colisao e o desenho do quadrado*/
/*#define SQRT_PI 1.772453851 */


#define SQRT_2 1.414213562
#define SQRT_5 2.236067977

#define PERSON_NUM_LIMIT            100
#define PERSON_NUM_INIT             30
#define CORAL_NUM_INIT				12
#define OBJECT_NUM_LIMIT			150
#define PERSON_CREATE_RATE_DEFAULT  5
#define PERSON_SPEED_DEFAULT        10
#define PERSON_RADIUS               5
#define SHIP_RADIUS					50
#define CORAL_RADIUS                10
#define BOAT_RADIUS					10
#define MAX_X                       1023
#define MAX_Y                       767
#define DURATION_DEFAULT            50.0
#define STD_DIST                    0.5
#define NUM_CLASS                   4
#define QUAD_SIZE_X                 100
#define QUAD_SIZE_Y                 100
#define DEFAULT_FPS 				30

#define DEFAULT_TURNRATE   			(PI/2)
#define DEFAULT_ACCEL 				50
#define DEFAULT_FRICTION 			0.5
#define DEFAULT_TIME_STUCK 			5
#define DEFAULT_LIVES 				3

#include <stdio.h>              /* Agora nenhum arquivo precisa incluir essa biblioteca */
#include <stdlib.h>

struct Vector {
    double x, y;
};
/* Se em coordenadas polares, x representa o raio enquanto e y o angulo. */
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

quadrant quadSet(int x, int y);

int quadNear(quadrant a, quadrant b);

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

void generatePosInBorder(point * pos, double *dir);

/*Imprime mensagem de erro, sai do programa*/
void genError(char *msg);
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
