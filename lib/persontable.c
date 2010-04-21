/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "person.h"
#include "persontable.h"

/* BST de person. Se quiser da pra mudar, ainda. */
struct PersonTable {
    int id;
    person val;
    persontable link[2];
};

static persontable root;

int personTableInit() {
    root = NULL;
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
int personTableRemoveByPerson(person) {
    return 0;
}

/* Management functions */
int personTableUpdate() {
    return 0;
}
void personTableExecute( void (*func)(person) ) {
}

#endif /* _PERSONTABLE_H_ */
