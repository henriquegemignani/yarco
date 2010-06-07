/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"

texture createTexture(int red, int blue, int green, texType type)
{
    texture tex;
    tex.color = (red << 16) + (blue << 8) + green;
    tex.type = type;
    return tex;
}

vector vectorCreate(double x, double y)
{
    vector v;
    v.x = x;
    v.y = y;
    return v;
}

quadrant quadSet(int x, int y)
{
    quadrant q;
    q.x = x;
    q.y = y;
    return q;
}

int quadNear(quadrant a, quadrant b)
{
    if (a.x - b.x > 1 || b.x - a.x > 1 || a.y - b.y > 1 || b.y - a.y > 1)
        return 0;
    return 1;
}

int signInt(int a)
{
    if (a < 0)
        return -1;
    if (a > 0)
        return 1;
    return 0;
}

int signDouble(double a)
{
    if (a < 0)
        return -1;
    if (a > 0)
        return 1;
    return 0;
}

int randInt(int min, int max)
{
    return (((max - min +
              1) * ((double) (1.0 * rand()) / (double) (1.0 * RAND_MAX +
                                                        1.0))) + min);
    /*Trecho de codigo oferecido pelo monitor de MAC122-08, levemente adaptado */
}

double randDouble(double min, double max)
{
    return (((double) rand() / RAND_MAX) * (max - min) + min);
}

double randomizeAround(double value, double distance)
{
    return (value + randDouble(-(value * distance), (value * distance)));
}

void generatePosInBorder(point * pos, double *dir)
{
    switch (randInt(1, 4)) {
    case 1:
        pos->x = 0;
        pos->y = randDouble(0, MAX_Y);
        *dir = -PI / 2;
        break;
    case 2:
        pos->x = MAX_X;
        pos->y = randDouble(0, MAX_Y);
        *dir = PI / 2;
        break;
    case 3:
        pos->x = randDouble(0, MAX_X);
        pos->y = 0;
        *dir = 0;
        break;
    case 4:
        pos->x = randDouble(0, MAX_X);
        pos->y = MAX_Y;
        *dir = PI;
        break;
    default:
        genError
            ("Erro em generatePosInBorder: numero aleatorio nao esta entre 1 e 4\n");
    }
}

void genError(char *msg)
{
    fprintf(stderr, "%s", msg);
    exit(EXIT_FAILURE);
}

void genWarning(char *msg)
{
    fprintf(stderr, "%s", msg);
}

void MALLOC_DIE()
{
    fprintf(stderr, "Erro de alocacao de memoria\n");
    exit(ERROR_MALLOC_FAILURE);
}
