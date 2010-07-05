/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "ship.h"
#include "../lib/common.h"
#include "../lib/class.h"
#include "../lib/objecttable.h"
#include "../config/configuration.h"

void getShipPos(point p);

/* Funcoes privadas. */

ship shipCreate(point pos, texture tex)
{
    static double shipRadius = -1;
    if (shipRadius == -1)
        shipRadius = configGetValue("Radius", "Ship").real;
    return objectCreate(TYPE_SHIP, 0, pos, vectorCreate(0, 0), shipRadius,
                        tex);
}

/* Funcoes publicas. */

void shipInitializeClass()
{
    classAdd(TYPE_SHIP, NULL, removeObject, NULL, NULL, objectDump);
}

ship shipNew(texture tex)
{
    point pos = vectorCreate((double) MAX_X / 2, (double) MAX_Y / 2);
    getShipPos(pos);
    return shipCreate(pos, tex);
}
