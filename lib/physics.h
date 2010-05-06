/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include "common.h"

/*Retorna a nova direcao do passageiro*/
vector newDirection( vector v );
/*Retorna a nova aceleracao de um objeto*/
acceleration newAcceleration( acceleration a );

#endif /* _PHYSICS_H_ */
