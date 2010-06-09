/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _CORAL_H_
#define _CORAL_H_

#include "../lib/object.h"
typedef struct Object *coral;

void coralInitializeClass();

/* Funcoes para criar novos corais e adicionar automaticamente na objectTable. */
coral coralAddNewToTable(int verbose);

#endif                          /* _CORAL_H_ */
