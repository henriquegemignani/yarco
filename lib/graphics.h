/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include "common.h"
#include "persontable.h"

typedef struct GraphicEngine *graphicEngine;

#define SCREEN_SIZE_X 800       //MAX_X     //800
#define SCREEN_SIZE_Y 600       //MAX_Y     //600

/*Inicializa parte grafica. uniquePerson define se deve usar um caracter diferente 
para cada pessoa desenhada.*/
void graphicInitialize(personTable table);
/*Atualiza os buffers*/
void graphicUpdate();
/*Mostra o que tem que ser mostrado*/
void graphicDraw();
/*Libera a memoria da parte grafica*/
void graphicFinish();

#endif                          /* _GRAPHICS_H_ */
