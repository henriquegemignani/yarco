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
              void (*collideFunc) (object, object, double timedif),
              void (*boundsFunc) (object), 
			  void (*dumpFunc) (object))
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

int classMethodIsNull(objectType type, int func ) {
	Class c = getClass(type);
	if(c == NULL) genError("classMethodIsNull chamado para classe inexistente.\n");
	switch( func ) {
		case CLASS_METHOD_UPDATE:	return c->updateFunc == NULL;
		case CLASS_METHOD_COLLIDE:	return c->collideFunc == NULL;
		case CLASS_METHOD_REMOVE:	return c->removeFunc == NULL;
		case CLASS_METHOD_BOUNDS:	return c->boundsFunc == NULL;
		case CLASS_METHOD_DUMP:		return c->dumpFunc == NULL;
	}
	return 1;
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
