/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _REPORT_H_
#define _REPORT_H_

#include "common.h"

typedef struct {
    char *name;
    int life;
    int score;
    int people;
} status;

void initReport(int players);
void statusReport(int player, char *name, int lives, int score, int peopleHeld);
status getStatus(int player);
void finishReport();

#endif                          /* _REPORT_H_ */
