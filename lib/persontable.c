/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "object.h"
#include "person.h"
#include "persontable.h"
#include <stdio.h>

/* BST de person. Se quiser da pra mudar, ainda. */
struct PersonTable {
    int id;
    person val;
    persontable link[2];
};

static persontable root;

int personTableInit() {
    root = NULL;
    return 0;
}
int personTableAdd(person p) { /* devolve o id da pessoa */    
    return 0;
}
person personTableSearch(int id) {
    return NULL;
}
int personTableRemoveByID(int id) {
    return 0;
}
int personTableRemoveByPerson(person p) {
    return 0;
}

/* Management functions */
int personTableUpdate() {
    return 0;
}
void personTableExecute( void (*func)(person p) ) {
}
