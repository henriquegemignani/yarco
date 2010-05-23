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
    void (*updateFunc) (object, int, int);
    
    /* Funcao de remocao do objeto. */
    void (*removeFunc) (object);
    
    /* Funcao de colisao do objeto. */
    void (*collideFunc) (object, object);
    
    /* Funcao chamada quando o objeto esta fora da tela. */
    void (*boundsFunc) (object);
    
    /* Funcao para imprimir na saida padrao informacoes sobre o objeto. */ 
    void (*dumpFunc) (object);
};

/* Adiciona uma nova classe na lista. */ 
void classAdd(objectType type,
    void (*updateFunc) (object, int, int),
    void (*removeFunc) (object), 
    void (*collideFunc) (object, object),
    void (*boundsFunc) (object),
    void (*dumpFunc) (object));

/* Devolve a classe correspondente ao tipo TYPE, ou NULL se nao existe. */ 
    Class getClass(objectType type);

#define OBJECT_UPDATE(obj, arg1, arg2)  getClass((*obj).type)->updateFunc((obj),(arg1),(arg2))
#define OBJECT_COLLIDE(obj, tar)        getClass((*obj).type)->collideFunc((obj),(tar))
#define OBJECT_REMOVE(obj)              getClass((*obj).type)->removeFunc(obj)
#define OBJECT_BOUNDS(obj)              getClass((*obj).type)->boundsFunc(obj)
#define OBJECT_DUMP(obj)                getClass((*obj).type)->dumpFunc(obj)
    
/* Inicializa a lista de classes. */ 
void classInitialize();

/* Limpa a lista de classes. */ 
void classFinish();

#endif  /* _CLASS_H_ */
