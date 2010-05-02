/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSON_H_
#define _PERSON_H_

#include "common.h"
typedef struct Object *person;

person personCreate( point pos );
   int personRemove( person p );
   int personUpdate( person p );
 point personGetPos( person p );
unsigned int personGetID( person p );

#endif /* _PERSON_H_ */
