/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _OBJECTTABLE_H_
#define _OBJECTTABLE_H_

#include "object.h"
#include "configuration.h"

typedef struct ObjectTable *objectTable;

objectTable objectTableInit(configuration config);

int objectTableAddObject(objectTable table, object obj);

object objectTableSearchObject(objectTable table, unsigned int id);

int objectTableRemoveObjectByObject(objectTable table, object obj);

int objectTableRemoveObjectByID(objectTable table, unsigned int id);

void objectTableSort(objectTable table);

void objectTableUpdate(objectTable table, double timedif,
                       int newIteraction);

void objectTableExecute(objectTable table, void (*func) (object p));

int objectTableIsObjectColliding(objectTable table, object o);

int objectTableFilled(objectTable table);

void objectTableDump(objectTable table);

void objectTableRemove(objectTable table);

#endif                          /* _OBJECTTABLE_H_ */
