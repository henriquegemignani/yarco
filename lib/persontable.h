/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSONTABLE_H_
#define _PERSONTABLE_H_

#include "person.h"

typedef struct PersonTable *personTable;

/*Inicializa tabela de pessoas*/
personTable personTableInit(double defaultSpeed, double createRate);

/*Cria uma nova pessoa em alguma borda e a adiciona na tabela. 
Devolve a pessoa criada e ERROR_PERSON_LIMIT_EXCEEDED em erro. */
person personTableAddNew(personTable table);

/*Procura a pessoa com ID id na tabela*/
person personTableSearch(personTable table, unsigned int id);

/*Remove a pessoa de ID id da tabela*/
int personTableRemoveByID(personTable table, unsigned int id);

/*Remove a pessa especificada da tabela*/
int personTableRemoveByPerson(personTable table, person p);

/*Ordena a tabela por posicao*/
void personTableSort(personTable table);

/*Atualiza a tabela*/
void personTableUpdate(personTable table);

/*Para cada pessoa na tabela, chama func passando tal pessoa como parametro.*/
void personTableExecute(personTable table, void (*func) (person p));

/*Dumpa a tabela*/
void personTableDump(personTable table);

/*Remove a tabela*/
void personTableRemove(personTable table);

#endif                          /* _PERSONTABLE_H_ */
