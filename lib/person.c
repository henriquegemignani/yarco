/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"             /*Nem que seja so para deixar indicado que precisa do common.h */
#include "object.h"
#include "physics.h"
#include "person.h"
                       /*#include <stdio.h> *//*Dar um jeito de jogar isso pra outro lugar */

person personCreate(point pos, double speed)
{
    person p;
    double personDirection;
    AUTOMALLOC(p);
    p->id = 0;
    p->type = TYPE_PERSON;
    p->radius = PERSON_RADIUS;
    p->pos = pos;
    personDirection = (double) randInt(0, 7) / 4;
    p->vel =
        vectorPolarToCartesian(vectorCreate(speed, personDirection * PI));
    p->acc = vectorCreate(0, 0);
    return p;
}

person personNew(double speed)
{
    point pos;
    switch (randInt(1, 4)) {
    case 1:
        pos.x = 0;
        pos.y = randDouble(0, MAX_Y);
        break;
    case 2:
        pos.x = MAX_X;
        pos.y = randDouble(0, MAX_Y);
        break;
    case 3:
        pos.x = randDouble(0, MAX_X);
        pos.y = 0;
        break;
    case 4:
        pos.x = randDouble(0, MAX_X);
        pos.y = MAX_Y;
        break;
    default:
        genError
            ("Erro em personNew: numero aleatorio nao esta emtre 1 e 4\n");
    }
    return personCreate(pos, randomizeAround(speed, STD_DIST));
}


int personRemove(person p)
{
    free(p);
    return 0;                   /*wtf? por que nao void se sempre retorna 0? */
}

int personUpdate(person p)
{
    p->vel = newDirection(p->vel);
    updateObject(p);
    return 0;                   /*wtf? por que nao void entao? */
}

point personGetPos(person p)
{
    return p->pos;
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

    /*      if( r->pos.y < s->pos.y ) return -1;
       else if ( r->pos.y > s->pos.y ) return 1;
       else
       if( r->pos.x < s->pos.x ) return -1;
       else if( r->pos.x > s->pos.x ) return 1;
       else return 0;
     */
    if (r->pos.y == s->pos.y)
        return r->pos.x - s->pos.x;
    return r->pos.y - s->pos.y;
/*Mais elegante assim, non? De quebra, se precisar saber exatamente a diferenca no eixo relevante, la esta*/
}

void personDump(person p)
{
    printf("(ID%4d) P", p->id);
    vectorPrint(p->pos);
    printf(" V");
    vectorPrint(p->vel);
    printf(" A");
    vectorPrint(p->acc);
}
