/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "object.h"
#include "person.h"
#include "persontable.h"
#include <stdio.h>

/* BST de person. Se quiser da pra mudar, ainda. */
static struct PersonTable {
    person list[PERSON_LIMIT];
    unsigned int curMax, lastID;
} table;

void personTableInit() {
    table.curMax = table.lastID = 0;
}
unsigned int personTableAdd(person p) {
    if( table.curMax == PERSON_LIMIT )
        return ERROR_PERSON_LIMIT_EXCEEDED;
    table.list[table.curMax++] = p;
    return ++table.lastID;
}
person personTableSearch(unsigned int id) {
    int i;
    for( i = 0; i < table.curMax; i++ )
        if( personGetID( table.list[i] ) == id )
            return table.list[i];
    return NULL;
}
int personTableRemoveByID(unsigned int id) {
    int i;
    person pAux;
    for( i = 0; i < table.curMax; i++ )
        if( personGetID( table.list[i] ) == id ) {
            pAux = table.list[i];
            table.list[i] = NULL;
            return personRemove(pAux);
        }
    return WARNING_PERSON_NOT_FOUND;
}
int personTableRemoveByPerson(person p) {
    return personTableRemoveByID( personGetID(p) );
}

/* Management functions */
void personTableUpdate() {
    int i;
    for( i = 0; i < table.curMax; i++ )
        if( table.list[i] != NULL )
            personUpdate(table.list[i]);
    /* TODO: ordenar vetor table.list aqui, colocando todos 
      os NULL no fim e corrigindo table.curMax. */
}
void personTableExecute( void (*func)(person p) ) {
    int i;
    for( i = 0; i < table.curMax; i++ )
        if( table.list[i] != NULL )
            func(table.list[i]);
}
