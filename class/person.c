/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "../lib/common.h"
#include "../lib/object.h"
#include "../lib/physics.h"
#include "person.h"
#include "../lib/class.h"
#include "../lib/objecttable.h"

/* Funcoes privadas. */

person personCreate(texture tex, point pos, velocity vel)
{
    return objectCreate(TYPE_PERSON, 0, pos, vel, PERSON_RADIUS, tex);
}

void generatePosAndVelInBorder(double speed, point * pos, velocity * vel)
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
             executeCollision, personMoveToRandomBorder, objectDump);
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

void personUpdate(person p, int keepDir, double timedif)
{
    if (!keepDir)
        p->vel = newDirection(p->vel);
    updateObject(p, timedif);
}

void personMoveToRandomBorder(person p, objectTable table)
{
	do{
		generatePosAndVelInBorder(vectorLength(p->vel), &p->pos, &p->vel);
	} while( objectTableIsObjectColliding(table, p) );
}

void personDump(person p)
{
    printf("(ID%4d) P", p->id);
    vectorPrint(p->pos);
    printf(" V");
    vectorPrint(p->vel);
    printf("\n");
}

person personAddNewToTable(objectTable table, double speed)
{
  person p = personNew(createTexture(randInt(40,200), randInt(40,200), randInt(40,200), TEX_CIRCLE), speed);
  int err;
  do {
    err = objectTableAddObject(table, p);
    if (err == ERROR_OBJECT_LIMIT_EXCEEDED) {
      personRemove(p);
      return NULL;
    } else if (err == ERROR_OBJECT_IS_COLLIDING) {
      generatePosAndVelInBorder(speed, &p->pos, &p->vel);
    }
    if( err != 0 ) {
      printf("Tentando criar pessoa. Err = %d", err );
      vectorPrint(p->pos);
      vectorPrint(p->vel);
      printf("\n");
    }
  } while( err != 0 );
  return p;
}


/*person personCreateToTable(objectTable table, point pos, velocity vel)
{
  person aux, p;
  aux = 
    personCreate(createTexture(randInt(40,200), randInt(40,200), randInt(40,200), TEX_CIRCLE), pos, vel);
  p = objectTableAddObject(table, aux);
  if (p == ERROR_OBJECT_LIMIT_EXCEEDED)
    personRemove(aux);
  return p;
  }*/
