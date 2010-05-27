/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSON_H_
#define _PERSON_H_

#include "../lib/common.h"
#include "../lib/objecttable.h"
typedef struct Object *person;

/* Serve para a colisao de passageiro com passageiro.
	aceleracao nao e'  utilizada com passageiros, tornando-a uma
	variavel temporaria perfeita. */
#define prevSpeed acc

void personInitializeClass();

/*Cria uma pessoa em uma das bordas, com a textura dada*/
person personNew(texture tex, double speed);

/*Cria uma pessoa na posicao e com a velocidade especificadas, com a textura dada*/
/*person personCreate(texture tex, point pos, velocity speed);*/

/*Nuka uma pessoa*/
void personRemove(person p);

/*Atualiza status da pessoa*/
void personUpdate(person p, int keepDir, double timedif);

/* Move a person dada para uma borda qualquer da tela e muda a velocidade para ficar de acordo. */
void personMoveToRandomBorder(person p, objectTable table);

/*Imprime posicao, velocidade e aceleracao de todos os passageiros*/
void personDump(person p);

/* Funcoes para criar novas pessoas e adicionar automaticamente na objectTable. */
person personAddNewToTable(objectTable table, double speed);
/*person personCreateToTable(objectTable table, point pos, velocity vel);*/

void personCollide(person per, object other);

#endif                          /* _PERSON_H_ */
