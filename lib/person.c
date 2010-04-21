/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "object.h"
#include "person.h"

person personCreate( point pos ) {
    person p;
    AUTOMALLOC(p);
    p->id = 0; /* id invalido */
    p->type = PERSON;
    p->pos = pos;
    /* TODO: velocidade inicial precisa ser aleatoria. */
    p->vel = vectorCreate(0,0);
    p->pos = vectorCreate(0,0);
    return p;
}
int personRemove( person p ) {
    free(p);
    return 0;
}

int personUpdate( person p ) {
    updateObject(p->obj);
    return 0;
}

point personGetPos( person p ) {
    return p->pos;
}
