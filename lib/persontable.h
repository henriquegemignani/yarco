/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSONTABLE_H_
#define _PERSONTABLE_H_

#include "person.h"

typedef struct PersonTable *personTable;

/*Inicializa tabela de pessoas*/
void personTableInit(double defaultSpeed, double createRate);

/*Cria uma nova pessoa e a adiciona na tabela. Devolve 1 para sucesso, 
    ERROR_PERSON_LIMIT_EXCEEDED em erro. */
int personTableAddNew();

/*Procura a pessoa com ID id na tabela*/
person personTableSearch(unsigned int id);

/*Remove a pessoa de ID id da tabela*/
int personTableRemoveByID(unsigned int id);

/*Remove a pessa especificada da tabela*/
int personTableRemoveByPerson(person p);

/*Ordena a tabela por posicao*/
void personTableSort();

/*Atualiza a tabela*/
void personTableUpdate();

/*Para cada pessoa na tabela, chama func passando tal pessoa como parametro.*/
void personTableExecute(void (*func) (person p));

/*Dumpa a tabela*/
void personTableDump();

#endif                          /* _PERSONTABLE_H_ */
