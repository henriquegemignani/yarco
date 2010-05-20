/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "object.h"
#include "physics.h"
#include "person.h"
#include "class.h"

void personInitializeClass(int keepSpeed) {
    classAdd( TYPE_PERSON, 
        keepSpeed != 0 ? personUpdateKeepSpeed : personUpdateChangeSpeed, 
        removeObject, objectCompare, executeCollision, objectDump );
}

person personCreate(texture tex, point pos, velocity vel)
{
    return objectCreate(TYPE_PERSON, 0, pos, vel, PERSON_RADIUS, tex);
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

void personUpdateChangeSpeed(person p)
{
    p->vel = newDirection(p->vel);
    updateObject(p);
}
void personUpdateKeepSpeed(person p) {
    updateObject(p);
}

void personDump(person p)
{
    printf("(ID%4d) P", p->id);
    vectorPrint(p->pos);
    printf(" V");
    vectorPrint(p->vel);
}
