/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "object.h"
#include "physics.h"
#include "person.h"

person personCreate( point pos ) {
    person p;
    double personSpeed;
    int personDirection;
    AUTOMALLOC(p);
    p->id = 0;
    p->type = PERSON;
    p->pos = pos;
    personSpeed = randDouble( PERSON_SPEED_MIN, PERSON_SPEED_MAX );
    personDirection = randInt( 0, 7 );
    p->vel = vectorPolarToCartesian( vectorCreate(personSpeed, personDirection * PI) );
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
