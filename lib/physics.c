/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "physics.h"
#include "object.h"
#include "vector.h"

vector newDirection(vector v)
{
    int randNum;
    if ((randNum = randInt(1, 20)) > 13)        /*13/20 = 0.65 de chance de nao mudar, 1/20 = 0.05 para cada outra direcao */
        v = vectorRotate(v, PI / 4 * (randNum - 13));
    return v;
}

void executeCollision(object a, object b)
{
    /*Lembre-se: Colisao inelastica e massas identicas... */
    velocity tmp = a->vel;
    a->vel = b->vel;
    b->vel = tmp;
}
