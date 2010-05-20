/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "class.h"

/* TODO: mover esse define para common.h */
#define NUM_CLASS 2

static Class classList[NUM_CLASS];

/*void classAdd(objectType type, void (*updateFunc)(object), void (*removeFunc)(object), 
	int (*compareFunc)(object, object), void (*collideFunc)(object, object), void (*dumpFunc)(object)) { */
void classAdd(objectType type, void (*updateFunc)(object), void (*removeFunc)(object), 
	void (*collideFunc)(object, object), void (*dumpFunc)(object)) {
    int i;
    for( i = 0; i < NUM_CLASS; i++ )
        if( classList[i] == NULL )
            break;
    if( i == NUM_CLASS )
        genError("Erro interno: classAdd chamado mas nao ha mais espaco em classList.");
    AUTOMALLOC(classList[i]);
    classList[i]->type = type;
    classList[i]->updateFunc = updateFunc;
    classList[i]->removeFunc = removeFunc;
    //classList[i]->compareFunc = compareFunc;
    classList[i]->collideFunc = collideFunc;
    classList[i]->dumpFunc = dumpFunc;
}

Class getClass(objectType type) {
    for( int i = 0; i < NUM_CLASS; i++ )
        if( classList[i] == NULL || classList[i]->type == type )
            return classList[i];
    return NULL;
}

void classInitialize() {
    for( int i = 0; i < NUM_CLASS; i++ )
        classList[i] = NULL;
}
void classFinish() {
    for( int i = 0; i < NUM_CLASS; i++ )
        free( classList[i] );
}
