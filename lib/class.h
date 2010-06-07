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

    /* Funcao update do objeto. */
    void (*updateFunc) (object, int, double);

    /* Funcao de remocao do objeto. */
    void (*removeFunc) (object);

    /* Funcao de colisao do objeto. */
    void (*collideFunc) (object, object, double timedif);

    /* Funcao chamada quando o objeto esta fora da tela. */
    void (*boundsFunc) (object);

    /* Funcao para imprimir na saida padrao informacoes sobre o objeto. */
    void (*dumpFunc) (object);
};

/* Adiciona uma nova classe na lista. */
void classAdd(objectType type,
              void (*updateFunc) (object, int, double),
              void (*removeFunc) (object),
              void (*collideFunc) (object, object, double timedif),
              void (*boundsFunc) (object), void (*dumpFunc) (object));

/* Devolve a classe correspondente ao tipo TYPE, ou NULL se nao existe. */
Class getClass(objectType type);

/* Devolve 1 se a classe correspondente ao tipo TYPE possui um valor NULL para a 
	funcao func, 0 caso contrario. */
int classMethodIsNull(objectType type, int func);
#define CLASS_METHOD_UPDATE  1
#define CLASS_METHOD_COLLIDE 2
#define CLASS_METHOD_REMOVE  3
#define CLASS_METHOD_BOUNDS  4
#define CLASS_METHOD_DUMP    5

#define OBJECT_UPDATE(obj, arg1, arg2)  do { if( !classMethodIsNull((*obj).type, CLASS_METHOD_UPDATE) ) \
		getClass((*obj).type)->updateFunc((obj),(arg1),(arg2)); } while(0)
#define OBJECT_COLLIDE(obj, tar, dif)        do { if( !classMethodIsNull((*obj).type, CLASS_METHOD_COLLIDE) ) \
		getClass((*obj).type)->collideFunc((obj),(tar),(dif)); } while(0)
#define OBJECT_REMOVE(obj)              do { if( !classMethodIsNull((*obj).type, CLASS_METHOD_REMOVE) ) \
		getClass((*obj).type)->removeFunc(obj); } while(0)
#define OBJECT_BOUNDS(obj)       do { if( !classMethodIsNull((*obj).type, CLASS_METHOD_BOUNDS) ) \
		getClass((*obj).type)->boundsFunc(obj); } while(0)
#define OBJECT_DUMP(obj)                do { if( !classMethodIsNull((*obj).type, CLASS_METHOD_DUMP) ) \
		getClass((*obj).type)->dumpFunc(obj); } while(0)

/* Inicializa a lista de classes. */
void classInitialize();

/* Limpa a lista de classes. */
void classFinish();

#endif                          /* _CLASS_H_ */
