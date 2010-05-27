/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "../lib/common.h"
#include "../lib/object.h"
#include "../lib/physics.h"
#include "ship.h"
#include "../lib/class.h"
#include "../lib/objecttable.h"

/* Funcoes privadas. */

ship shipCreate(point pos, texture tex)
{
    return objectCreate(TYPE_SHIP, 0, pos, vectorCreate(0,0), SHIP_RADIUS, tex);
}

/* Funcoes publicas. */

void shipInitializeClass()
{
    classAdd(TYPE_SHIP,
             NULL,
             removeObject,
             executeCollision, NULL, objectDump);
}

ship shipNew(texture tex)
{
    point pos = vectorCreate( MAX_X/4 * randInt(1,3), MAX_Y/4 * randInt(1,3) );
    return shipCreate(pos, tex);
}


void shipRemove(ship p)
{
    free(p);
}

