/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "object.h"
#include "physics.h"
#include "person.h"

person personCreate( point pos, double speed ) {
    person p;
    int personDirection;
    AUTOMALLOC(p);
    p->id = 0;
    p->type = TYPE_PERSON;
    p->pos = pos;
    personDirection = randInt( 0, 7 );
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
