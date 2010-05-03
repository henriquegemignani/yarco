/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "object.h"
#include "physics.h"
#include "person.h"

person personCreate( point pos, double speed ) {
    person p;
    double personDirection;
    AUTOMALLOC(p);
    p->id = 0;
    p->type = TYPE_PERSON;
    p->pos = pos;
    personDirection = (double)randInt( 0, 7 ) / 4;
    p->vel = vectorPolarToCartesian( vectorCreate(speed, personDirection * PI) );
    p->acc = vectorCreate(0,0);
    return p;
}
int personRemove( person p ) {
    free(p);
    return 0;
}

int personUpdate( person p ) {
    p->vel = newDirection( p->vel );
    updateObject(*p);
    return 0;
}

point personGetPos( person p ) {
    return p->pos;
}

unsigned int personGetID( person p ) {
    return p->id;
}

void personSetID( person p, unsigned int id ) {
    p->id = id;
}

int personCompare( person r, person s ) {
/* retorna < -1 se r<s, 0 se iguais, 1 se r>s */
	if( r.y < s.y ) return -1;
	else if ( r.y > s.y ) return 1;
	else
		if( r.x < s.x ) return -1;
		else if( r.x > s.x ) return 1;
		else return 0;
	
}
