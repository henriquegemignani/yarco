/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _CORAL_H_
#define _CORAL_H_

#include "../lib/object.h"
typedef struct Object *coral;

void coralInitializeClass();

/*Nuka um coral*/
void coralRemove(coral c);

void coralCollide(coral c, object other);

/* Funcoes para criar novas pessoas e adicionar automaticamente na objectTable. */
coral coralAddNewToTable();

#endif                          /* _CORAL_H_ */
