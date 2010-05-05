/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSON_H_
#define _PERSON_H_

#include "common.h"
typedef struct Object *person;

      person personNew( double speed );
    /*person personCreate( point pos, double speed );*//*Talvez non seja necessario com a existencia de personNew*/
         int personRemove( person p );
         int personUpdate( person p );
       point personGetPos( person p );
unsigned int personGetID( person p );
        void personSetID( person p, unsigned int id );
         int personCompare( person r, person s ); /* usa como crit√rio a ordem de impressao na tela */
		void personDump( person p );

#endif /* _PERSON_H_ */
