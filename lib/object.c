/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "object.h"

void updateObject( object o ){
	o.pos = vectorSum( o.pos, o.vel );
	o.vel = vectorSum( o.vel, o.acc );
}
