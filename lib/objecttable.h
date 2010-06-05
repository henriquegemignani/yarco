/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _OBJECTTABLE_H_
#define _OBJECTTABLE_H_

#include "object.h"

typedef struct ObjectTable *objectTable;

/* Devolve a instancia de objectTable, criando-a se necessario. */
objectTable objectTableGet();

/*Tenta adicionar o objeto OBJ na tabela, devolvendo 0 em caso de sucesso ou algum erro:
	ERROR_OBJECT_LIMIT_EXCEEDED
	ERROR_OBJECT_IS_COLLIDING */
int objectTableAddObject(object obj);

/* Devolve o objeto com o id dado, ou NULL caso nao exista. */
object objectTableSearchObject(unsigned int id);

/* Remove o objeto dado da tabela. Devolve 0 em sucesso e 
	WARNING_OBJECT_NOT_FOUND se o objeto nao existe na tabela. */
int objectTableRemoveObject(object obj);

/* Remove o objeto com o ID dado da tabela. Devolve 0 em sucesso e 
	WARNING_OBJECT_NOT_FOUND se o objeto nao existe na tabela. */
int objectTableRemoveObjectByID(unsigned int id);

/* Ordena a tabela. */
void objectTableSort();

/* Realiza colisoes, chama o OBJECT_UPDATE de cada objeto e OBJECT_BOUNDS caso esteja fora da tela. */
void objectTableUpdate(double timedif, int newIteraction);

/* Chama FUNC para cada objeto da tabela, passando tal objeto como parametro. */
void objectTableExecute(void (*func) (object p));

/* Devolve 1 caso OBJ esteja colidindo com algum objeto da tabela, 0 caso contrario. 
	OBJ nao precisa estar na tabela. */
int objectTableIsObjectColliding(object obj);

/* Devolve 1 caso a tabela tenha atingido o limite de objetos, 0 caso contrario. */
int objectTableFilled();

/* Imprime na saida padrao informacoes de todos os objetos na tabela. */
void objectTableDump();

/* Chama OBJECT_REMOVE para cada objeto da tabela, e depois destroi a tabela. */
void objectTableFinish();

#endif                          /* _OBJECTTABLE_H_ */
