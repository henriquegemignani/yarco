/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "coral.h"
#include "../lib/common.h"
#include "../lib/object.h"
#include "../lib/objecttable.h"
#include "../lib/class.h"
#include "../lib/objecttable.h"

/* Funcoes privadas. */
point coralGeneratePosition()
{
    return vectorCreate(randDouble(0, MAX_X), randDouble(0, MAX_Y));
}

coral coralCreate(texture tex, point pos)
{
	static double coralRadius = -1;
	if(coralRadius == -1) coralRadius = configGetValue("Radius", "Coral").real;
    return objectCreate(TYPE_CORAL, 0, pos, vectorCreate(0, 0),
                        randomizeAround(coralRadius, STD_DIST), tex);
}

/* Funcoes publicas. */
void coralInitializeClass()
{
    classAdd(TYPE_CORAL, NULL, removeObject, NULL, NULL, objectDump);
}

/* Funcoes para criar novos corais e adicionar automaticamente na objectTable. */
coral coralAddNewToTable(int verbose)
{
    coral c =
        coralCreate(createTexture
                    (randInt(40, 200), randInt(40, 200), randInt(40, 200),
                     TEX_SQUARE),
                    coralGeneratePosition());
    int err;
    do {
        err = objectTableAddObject(c);
        if (err == ERROR_OBJECT_LIMIT_EXCEEDED) {
            removeObject(c);
            return NULL;
        } else if (err == ERROR_OBJECT_IS_COLLIDING) {
            c->pos = coralGeneratePosition();
        }
        if (err != 0 && verbose) {
            printf("Tentando criar coral. Err = %d ", err);
            objectDump(c);
        }
    } while (err != 0);
    return c;
}
