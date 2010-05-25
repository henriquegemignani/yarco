/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _OBJECTTABLE_H_
#define _OBJECTTABLE_H_

#include "object.h"

typedef struct ObjectTable *objectTable;

objectTable objectTableInit(int fps);

void objectTableAddObject(objectTable table, object obj);

object objectTableSearchObject(objectTable table, unsigned int id);

int objectTableRemoveObjectByObject(objectTable table, object obj);

int objectTableRemoveObjectByID(objectTable table, unsigned int id);

void objectTableUpdate(objectTable table);

void objectTableExecute(objectTable table, void (*func) (object p));

void objectTableDump(objectTable table);

void objectTableRemove(objectTable table);

#endif                          /* _OBJECTTABLE_H_ */
