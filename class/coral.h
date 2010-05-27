/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _CORAL_H_
#define _CORAL_H_

#include "../lib/common.h"
#include "../lib/objecttable.h"
typedef struct Object *coral;

void coralInitializeClass();

/*Nuka um coral*/
void coralRemove(coral c);

/* Funcoes para criar novas pessoas e adicionar automaticamente na objectTable. */
coral coralAddNewToTable(objectTable table);

#endif                          /* _CORAL_H_ */
