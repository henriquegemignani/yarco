/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSONTABLE_H_
#define _PERSONTABLE_H_

#include "person.h"
        void personTableInit();
unsigned int personTableAdd(person p);
      person personTableSearch(unsigned int id);
         int personTableRemoveByID(unsigned int id);
         int personTableRemoveByPerson(person p);

		void personTableSort();
		void quicksort( person *vet, int ini, int fim );
		void particao( person *vet, int ini, int fim );		

        void personTableUpdate();
        void personTableExecute( void (*func)(person p) );

#endif /* _PERSONTABLE_H_ */
