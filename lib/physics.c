/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "physics.h"
#include "object.h"

vector newDirection( vector v ) {
  /* TODO: finish this! */
 
	/* por ora eu prefiro deixar isso aqui
  double length;
  int randNum;
  length = vectorLength ( v );
  if ( randInt ( 1, 100 ) > 65)
    v = vectorRotate ( v, ( PI/4 * ( ( randNum - 61 )/5 ) ) );
  return v;
  */

	int randNum;
	if ( ( randNum=randInt( 1 , 20 ) ) > 13  )
		v = vectorRotate ( v, PI/4 * (randNum-13) );		

	return v;
	/*Gracias por simplificar o codigo*/
}
acceleration newAcceleration( acceleration a ) {
  /* TODO: finish this! */
  return a;
}


void collision( object a, object b )
{
	/* TODO: adicionar alguma fisica de verdade aqui */
	velocity tmp = a.vel;
	a.vel = b.vel;
	b.vel = tmp;
	/*Perai, assumindo massas iguais, nao e isso que acontece?*/
}
