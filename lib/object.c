/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "object.h"
#include "vector.h"

object objectCreate(objectType type, unsigned int id, point pos,
                    velocity vel, double radius, texture tex)
{
    object o;
    AUTOMALLOC(o);
    o->id = id;
    o->type = type;
    o->radius = radius;
    o->pos = pos;
    o->vel = vel;
    o->tex = tex;
    o->acc = vectorCreate(0, 0);
    o->quad =
        quadSet((int) (pos.x / QUAD_SIZE_X), (int) (pos.y / QUAD_SIZE_Y));
    o->extra = NULL;
    o->toBeRemoved = 0;
    return o;
}

texture objectGetTexture(object a)
{
    return a->tex;
}

point objectGetPos(object a)
{
    return a->pos;
}

quadrant objectGetQuad(object a)
{
    return a->quad;
}

void objectQuadUpdate(object a)
{
    a->quad =
        quadSet((int) (a->pos.x / QUAD_SIZE_X),
                (int) (a->pos.y / QUAD_SIZE_Y));
}

double objectGetSpeed(object a)
{
    return vectorLength(a->vel);
}

unsigned int objectGetID(object a)
{
    return a->id;
}

void objectSetID(object a, unsigned int id)
{
    a->id = id;
}

void updateObject(object o, double timedif)
{
    o->pos = vectorSum(o->pos, vectorMulDouble(o->vel, timedif));
    objectQuadUpdate(o);
}

int objectCompare(object r, object s)
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


double objectGetDistFrom(object o, point p)
{
    return distanceBetweenPoints(o->pos, p);
}

int objectIsColliding(object a, object b)
{
    return (distanceBetweenPoints(a->pos, b->pos) <
            (a->radius + b->radius));
}

void objectDump(object a)
{
    printf("(ID%4d) P", a->id);
    vectorPrint(a->pos);
    printf(" V");
    vectorPrint(a->vel);
    printf(" A");
    vectorPrint(a->acc);
    printf("\n");
}

void removeObject(object a)
{
    free(a);
}
