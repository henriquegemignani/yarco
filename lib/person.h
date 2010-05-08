/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSON_H_
#define _PERSON_H_

#include "common.h"
typedef struct Object *person;

/*Cria uma pessoa em uma das bordas*/
person personNew(double speed);

/*Cria uma pessoa na posicao e com a velocidade especificadas*/
person personCreate(point pos, velocity speed);

/*Nuka uma pessoa*/
void personRemove(person p);

/*Atualiza status da pessoa*/
void personUpdate(person p, int keepSpeed);

/*Retorna a posicao da pessoa*/
point personGetPos(person p);

/*Retorna a velocidade da pessoa*/
double personGetSpeed(person p);

/*Retorna o ID da pessoa*/
unsigned int personGetID(person p);

/*Seta o ID da pessoa*/
void personSetID(person p, unsigned int id);

/*Compara duas pessoas de acordo com sua posicao*/
int personCompare(person r, person s);

/*Imprime posicao, velocidade e aceleracao de todos os passageiros*/
void personDump(person p);

#endif                          /* _PERSON_H_ */
