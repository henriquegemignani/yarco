/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _SHIP_H_
#define _SHIP_H_

#include "../lib/object.h"
typedef struct Object *ship;

void shipInitializeClass();

/*Cria um Navio */
ship shipNew( texture tex );

/*Nuka um navio*/
void shipRemove(ship s);

/*imprime os dados de um navio na saida padrao */
void shipDump( ship s );


#endif                          /* _SHIP_H_ */
