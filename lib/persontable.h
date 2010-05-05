/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSONTABLE_H_
#define _PERSONTABLE_H_

#include "person.h"

        void personTableInit( double defaultSpeed, double createRate );
unsigned int personTableAdd(person p);
      person personTableSearch(unsigned int id);
         int personTableRemoveByID(unsigned int id);
         int personTableRemoveByPerson(person p);

		void personTableSort();
		void quicksort( person *vet, int ini, int fim );
		int particao( person *vet, int ini, int fim );		

        void personTableUpdate();
        void personTableExecute( void (*func)(person p) );
		
		void personTableDump();

#endif /* _PERSONTABLE_H_ */
