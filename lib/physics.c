/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "physics.h"
#include "object.h"

vector newDirection( vector v ) {
  /* TODO: finish this! */
  return v;
}
acceleration newAcceleration( acceleration a ) {
  /* TODO: finish this! */
  return a;
}


void collision( object *a, object *b )
{
	/* TODO: adicionar alguma fisica de verdade aqui */
	velocity tmp = a->vel;
	a->vel = b->vel;
	b->vel = tmp;
}
