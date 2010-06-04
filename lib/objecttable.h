/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _OBJECTTABLE_H_
#define _OBJECTTABLE_H_

#include "object.h"
#include "configuration.h"

typedef struct ObjectTable *objectTable;

struct ObjectTable {
    object list[OBJECT_NUM_LIMIT];
    unsigned int curMax, lastID;
    configuration config;
};

/* Devolve a instancia de objectTable, criando-a se necessario. */
objectTable objectTableGet();

/*Inicializa tabela de objetos*/
objectTable objectTableInit();

/*Tenta adicionar o objeto OBJ na tabela, devolvendo 0 em caso de sucesso ou algum erro:
	ERROR_OBJECT_LIMIT_EXCEEDED
	ERROR_OBJECT_IS_COLLIDING */
int objectTableAddObject(objectTable table, object obj);

/* Devolve o objeto com o id dado, ou NULL caso nao exista. */
object objectTableSearchObject(objectTable table, unsigned int id);

/* Remove o objeto dado da tabela. Devolve 0 em sucesso e 
	WARNING_OBJECT_NOT_FOUND se o objeto nao existe na tabela. */
int objectTableRemoveObjectByObject(objectTable table, object obj);

/* Remove o objeto com o ID dado da tabela. Devolve 0 em sucesso e 
	WARNING_OBJECT_NOT_FOUND se o objeto nao existe na tabela. */
int objectTableRemoveObjectByID(objectTable table, unsigned int id);

/* Ordena a tabela. */
void objectTableSort(objectTable table);

/* Realiza colisoes, chama o OBJECT_UPDATE de cada objeto e OBJECT_BOUNDS caso esteja fora da tela. */
void objectTableUpdate(objectTable table, double timedif, int newIteraction);

/* Chama FUNC para cada objeto da tabela, passando tal objeto como parametro. */
void objectTableExecute(objectTable table, void (*func) (object p));

/* Devolve 1 caso OBJ esteja colidindo com algum objeto da tabela, 0 caso contrario. 
	OBJ nao precisa estar na tabela. */
int objectTableIsObjectColliding(objectTable table, object obj);

/* Devolve 1 caso a tabela tenha atingido o limite de objetos, 0 caso contrario. */
int objectTableFilled(objectTable table);

/* Imprime na saida padrao informacoes de todos os objetos na tabela. */
void objectTableDump(objectTable table);

/* Chama OBJECT_REMOVE para cada objeto da tabela, e depois destroi a tabela. */
void objectTableRemove(objectTable table);

#endif                          /* _OBJECTTABLE_H_ */
