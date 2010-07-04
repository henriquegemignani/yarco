/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _LOGIC_H_
#define _LOGIC_H_

long timeInMicrosecond();
void loginAllegroCloseButtonHandler(void);

void logicSleep();
void logicInitialize(int argc, char* argv[]);
double logicLoop(double timeDifference);
void logicFinish();
int logicGameOver();

#endif                          /* _LOGIC_H_ */
