/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSONTABLE_H_
#define _PERSONTABLE_H_

#include "person.h"

/*Inicializa tabela de pessoas*/
        void personTableInit( double defaultSpeed, double createRate );
/*Uh... alguem que saiba o que isso faz exatamente, coloque aqui*/
	 int personTableAddNew();
/*Coloca uma pessoa na tabela*/
unsigned int personTableAdd(person p);
/*Procura a pessoa com ID id na tabela*/
      person personTableSearch(unsigned int id);
/*Remove a pessoa de ID id da tabela*/
         int personTableRemoveByID(unsigned int id);
/*Remove a pessa especificada da tabela*/
         int personTableRemoveByPerson(person p);

/*Ordena a tabela por posicao*/
        void personTableSort();
/*void quicksort( person *vet, int ini, int fim ); 
  int particao( person *vet, int ini, int fim );	*/
/*wtf, essas duas non son funcoes internas do .c?*/	

/*Atualiza a tabela*/
       void personTableUpdate();
/*Alguem que saiba, arrume esse comentario. >_>*/
       void personTableExecute( void (*func)(person p) );
		
/*Dumpa a tabela*/
       void personTableDump();

#endif /* _PERSONTABLE_H_ */
