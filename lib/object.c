/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "object.h"

void updateObject( object *o ) {
    vector aux = vectorPolarToCartesian( o->acc );
	o->pos = vectorSum( o->pos, o->vel );
	o->vel = vectorSum( o->vel, aux );
}

double objectGetDistFrom( object o, point p ) {
    return distanceBetweenPoints( o.pos, p );
}

int objectIsColiding( object a, object b ) {
    return (distanceBetweenPoints( a.pos, b.pos ) < (a.radius + b.radius));
}
