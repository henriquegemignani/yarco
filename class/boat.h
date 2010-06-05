/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/
#ifndef _BOAT_H_
#define _BOAT_H_
#include "../lib/common.h"
#include "../lib/class.h"
typedef struct Object *boat;

void boatInitializeClass();

boat boatCreate(texture tex, point pos, velocity vel);
void boatUpdate(boat b, int keepDir, double timedif);
void boatRemove(boat b);
void boatOB(boat b);
void boatCollide(boat b, object o, double timedif);
boat boatAddNewToTable(int color);
#endif
