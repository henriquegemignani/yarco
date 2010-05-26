/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "class.h"

static Class classList[NUM_CLASS];
void classAdd(objectType type,
              void (*updateFunc) (object, int, double),
              void (*removeFunc) (object),
              void (*collideFunc) (object, object),
              void (*boundsFunc) (object), void (*dumpFunc) (object))
{
    int i;
    for (i = 0; i < NUM_CLASS; i++)
        if (classList[i] == NULL)
            break;
    if (i == NUM_CLASS)
        genError
            ("Erro interno: classAdd chamado mas nao ha mais espaco em classList.");
    AUTOMALLOC(classList[i]);
    classList[i]->type = type;
    classList[i]->updateFunc = updateFunc;
    classList[i]->removeFunc = removeFunc;
    classList[i]->collideFunc = collideFunc;
    classList[i]->boundsFunc = boundsFunc;
    classList[i]->dumpFunc = dumpFunc;
}

Class getClass(objectType type)
{
    int i;
    for (i = 0; i < NUM_CLASS; i++)
        if (classList[i] == NULL || classList[i]->type == type)
            return classList[i];
    return NULL;
}

void classInitialize()
{
    int i;
    for (i = 0; i < NUM_CLASS; i++)
        classList[i] = NULL;
}

void classFinish()
{
    int i;
    for (i = 0; i < NUM_CLASS; i++)
        free(classList[i]);
}
