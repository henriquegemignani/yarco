/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _PERSONTABLE_H_
#define _PERSONTABLE_H_

typedef struct PersonTable *persontable;

   int personTableInit();
   int personTableAdd(person); /* devolve o id da pessoa */
person personTableSearch(int id);
   int personTableRemoveByID(int id);
   int personTableRemoveByPerson(person);
   
 int personTableUpdate();
void personTableExecute( void (*func)(person*) );

#endif /* _PERSONTABLE_H_ */
