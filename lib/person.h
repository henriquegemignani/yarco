/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSON_H_
#define _PERSON_H_

typedef struct Object *person;

person personCreate( point pos );
   int personRemove( person );
   int personUpdate( person );
 point personGetPos( person );

#endif /* _PERSON_H_ */
