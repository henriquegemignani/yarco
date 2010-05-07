/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "physics.h"
#include "object.h"

vector newDirection(vector v)
{
    int randNum;
    if ((randNum = randInt(1, 20)) > 13)
        v = vectorRotate(v, PI / 4 * (randNum - 13));
    return v;
}

acceleration newAcceleration(acceleration a)
{
    /* TODO: finish this! (newAcceleration) */
    /*Isso nem vai ser usado nessa etapa... */
    return a;
}


void executeCollision(object * a, object * b)
{
    /* TODO: adicionar alguma fisica de verdade aqui */
    velocity tmp = a->vel;
    a->vel = b->vel;
    b->vel = tmp;
    /*Perai, assumindo massas iguais, nao e isso que acontece? */
}
