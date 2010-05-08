/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "common.h"
#include "graphics.h"
typedef enum {
    TYPE_BOAT, TYPE_PERSON
} objectType;


typedef struct Object object;

struct Object {
    acceleration acc;
    velocity vel;
    point pos;
    unsigned int id;
    objectType type;
    double radius;
    texture tex;
};
/*Posicao e velocidade sao dados por coordenadas cartesianas, enquanto a aceleracao e dada por coordenadas polares*/

/*Atualiza o objeto*/
void updateObject(object * o);
/*Retorna a distancia entre o objeto e o ponto p*/
double objectGetDistFrom(object o, point p);
/*Verifica se dois objetos estao colidindo no mundo.*/
int objectIsColiding(object a, object b);

#endif                          /* _OBJECT_H_ */
