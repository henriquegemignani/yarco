/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _CLASS_H_
#define _CLASS_H_

#include "common.h"
#include "object.h"

typedef struct ClassStruct *Class;

struct ClassStruct {
	objectType type;
	void (*updateFunc)(object);
	void (*removeFunc)(object);
	int (*compareFunc)(object, object);
	void (*collideFunc)(object, object);
	void (*dumpFunc)(object);
};

/* Adiciona uma nova classe na lista. */
void classAdd(objectType type, void (*updateFunc)(object), void (*removeFunc)(object), 
	int (*compareFunc)(object, object), void (*collideFunc)(object, object), void (*dumpFunc)(object));

/* Devolve a classe correspondente ao tipo TYPE, ou NULL se nao existe. */
Class getClass(objectType type);

#define OBJECT_UPDATE(obj)          getClass((*obj).type)->updateFunc(obj)
#define OBJECT_COLLIDE(obj, tar)    getClass((*obj).type)->collideFunc((obj),(tar))
#define OBJECT_REMOVE(obj)          getClass((*obj).type)->removeFunc(obj)

/* Inicializa a lista de classes. */
void classInitialize();
/* Limpa a lista de classes. */
void classFinish();

#endif                          /* _CLASS_H_ */
