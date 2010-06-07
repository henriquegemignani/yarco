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
    /*vector aux = vectorPolarToCartesian(o->acc);*/
    o->pos = vectorSum(o->pos, vectorMulDouble(o->vel, timedif));
    /*o->vel = vectorSum(o->vel, vectorMulDouble(aux, timedif));*/
    o->quad =
        quadSet((int) (o->pos.x / QUAD_SIZE_X),
                (int) (o->pos.y / QUAD_SIZE_Y));
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
    /* point centerOfA, centerOfB;
	centerOfA = a->pos; vectorCreate(a->pos.x+a->radius,a->pos.y+a->radius);
	centerOfB = b->pos; vectorCreate(b->pos.x+b->radius,b->pos.y+b->radius);
	return (distanceBetweenPoints(centerOfA, centerOfB) <
            (a->radius + b->radius));
	Serio, wtf? o que estava acima podia estar errado de tantos jeitos diferentes que eu nem vou comentar. Se nao estava quebrado, e porque tudo tinha o mesmo raio
	if((a->tex.type == TEX_CIRCLE || a->tex.type == TEX_TRIANGLE) && (b->tex.type == TEX_CIRCLE || b->tex.type == TEX_TRIANGLE)) */
	/* TODO(objectIsColliding): limpar excesso de codigo comentado bizarro */
	return (distanceBetweenPoints(a->pos, b->pos) < (a->radius + b->radius));

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
