/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "common.h"

typedef enum {
  BOAT, PERSON
} objectType;


typedef struct Object object;

struct Object
{
    /* pos eh em coordenadas cartesianas, enquanto 
    vel e acc sao em coordenadas polares. */
	acceleration acc;
	velocity vel; 
	point pos;
    unsigned int id;
    objectType type;
};

void updateObject( object o );
double objectGetDistFrom( point p );

#endif /* _OBJECT_H_ */
