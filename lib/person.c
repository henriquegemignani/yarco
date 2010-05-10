/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "object.h"
#include "physics.h"
#include "person.h"

person personCreate(texture tex, point pos, velocity vel)
{
    person p;
    AUTOMALLOC(p);
    p->id = 0;
    p->type = TYPE_PERSON;
    p->radius = PERSON_RADIUS;
    p->pos = pos;
    p->vel = vel;
    p->tex = tex;
    p->acc = vectorCreate(0, 0);
    return p;
}

person personNew(texture tex, double speed)
{
    double dir;                 /*Dir determina a primeira direcao do passageiro de modo que ele nao saia imediatamente da tela */
    point pos;
    velocity vel;
    switch (randInt(1, 4)) {
    case 1:
        pos.x = 0;
        pos.y = randDouble(0, MAX_Y);
        dir = -PI / 2;
        break;
    case 2:
        pos.x = MAX_X;
        pos.y = randDouble(0, MAX_Y);
        dir = PI / 2;
        break;
    case 3:
        pos.x = randDouble(0, MAX_X);
        pos.y = 0;
        dir = 0;
        break;
    case 4:
        pos.x = randDouble(0, MAX_X);
        pos.y = MAX_Y;
        dir = PI;
        break;
    default:
        genError
            ("Erro em personNew: numero aleatorio nao esta entre 1 e 4\n");
    }
    vel =
        vectorPolarToCartesian(vectorCreate
                               (randomizeAround(speed, STD_DIST),
                                dir + PI / 4 * randInt(0, 4)));
    return personCreate(tex, pos, vel);
}


void personRemove(person p)
{
    free(p);
}

void personUpdate(person p, int keepSpeed)
{
    if (!keepSpeed)
        p->vel = newDirection(p->vel);
    updateObject(p);
}

texture personGetTexture(person p)
{
    return p->tex;
}

point personGetPos(person p)
{
    return p->pos;
}

double personGetSpeed(person p)
{
    return vectorLength(p->vel);
}

unsigned int personGetID(person p)
{
    return p->id;
}

void personSetID(person p, unsigned int id)
{
    p->id = id;
}

int personCompare(person r, person s)
{
    /* Considera NULL maior que qualquer outro elemento,
       exceto ele mesmo. */
    /* retorna <0 se r < s, 0 se iguais, >0 se r > s */
    if (r == NULL || s == NULL)
        return (r == NULL) - (s == NULL);
    /* Retorna: 1, se somente r == NULL
       0, se ambos sao NULL
       -1, se apenas s == NULL
       curti isso :)           
     */
    if (r->pos.y == s->pos.y)
        return r->pos.x - s->pos.x;
    return r->pos.y - s->pos.y;
}

void personDump(person p)
{
    printf("(ID%4d) P", p->id);
    vectorPrint(p->pos);
    printf(" V");
    vectorPrint(p->vel);
}
