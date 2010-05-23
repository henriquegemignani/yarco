/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "object.h"
#include "physics.h"
#include "person.h"
#include "class.h"

/* Funcoes privadas. */

void generatePosAndVelInBorder(double speed, point *pos, velocity *vel)
{
    double dir;
    /*Dir determina a primeira direcao do passageiro de modo que ele nao saia imediatamente da tela */
    
    switch (randInt(1, 4)) {
    case 1:
        pos->x = 0;
        pos->y = randDouble(0, MAX_Y);
        dir = -PI / 2;
        break;
    case 2:
        pos->x = MAX_X;
        pos->y = randDouble(0, MAX_Y);
        dir = PI / 2;
        break;
    case 3:
        pos->x = randDouble(0, MAX_X);
        pos->y = 0;
        dir = 0;
        break;
    case 4:
        pos->x = randDouble(0, MAX_X);
        pos->y = MAX_Y;
        dir = PI;
        break;
    default:
        genError
            ("Erro em personNew: numero aleatorio nao esta entre 1 e 4\n");
    }
    *vel =
        vectorPolarToCartesian(vectorCreate
                               (randomizeAround(speed, STD_DIST),
                                dir + PI / 4 * randInt(0, 4)));
}


/* Funcoes publicas. */

void personInitializeClass()
{
    classAdd(TYPE_PERSON,
             personUpdate,
             removeObject, 
             executeCollision, 
             personMoveToRandomBorder,
             objectDump);
}

person personCreate(texture tex, point pos, velocity vel)
{
    return objectCreate(TYPE_PERSON, 0, pos, vel, PERSON_RADIUS, tex);
}

person personNew(texture tex, double speed)
{
    point pos;
    velocity vel;
    generatePosAndVelInBorder(speed, &pos, &vel);
    return personCreate(tex, pos, vel);
}


void personRemove(person p)
{
    free(p);
}

void personUpdate(person p, int keepDir, int fps)
{
    if(!keepDir)
    	p->vel = newDirection(p->vel);
    updateObject(p, fps);
}

void personMoveToRandomBorder(person p)
{
    generatePosAndVelInBorder(vectorLength(p->vel), &p->pos, &p->vel);
}

void personDump(person p)
{
    printf("(ID%4d) P", p->id);
    vectorPrint(p->pos);
    printf(" V");
    vectorPrint(p->vel);
}
