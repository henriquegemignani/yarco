/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "common.h"

#define SCREEN_SIZE_X MAX_X     //800
#define SCREEN_SIZE_Y MAX_Y     //600

/*Inicializa parte grafica*/
int graphicInitialize();
/*Atualiza os buffers*/
int graphicUpdate();
/*Mostra o que tem que ser mostrado*/
int graphicDraw();

#endif                          /* _GRAPHICS_H_ */
