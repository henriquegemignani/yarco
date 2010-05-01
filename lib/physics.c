/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "physics.h"
#include "object.h"
#define PI 3.141592654

vector newDirection( vector v ) {
  /* TODO: finish this! */
  double length;
  int randNum;
  length = vectorLength ( v );
  if ( randNumber ( 1, 100 ) > 65)
    v = vectorRotate ( v, ( PI/4 * ( ( randNum - 61 )/5 ) ) );
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
