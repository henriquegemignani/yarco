/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "object.h"
#include "person.h"
#include "persontable.h"
/* #include <stdio.h> -- ta no common.h agora */



static struct PersonTable {
    person list[PERSON_NUM_LIMIT];
    unsigned int curMax, lastID;
    double defaultSpeed, createRate, createCounter;
} table;



int particao( person *vet, int ini, int fim )
{
	int i, j;
	person tmp;

	i = ini;
	for ( j=ini+1; j<=fim; ++j )
	{
		if( personCompare( vet[j], vet[ini] ) < 0 )  /*<*/
		{
			i++;
			tmp = vet[i];
			vet[i] = vet[j];
			vet[j] = tmp;
		}
	}
	tmp=vet[ini];
	vet[ini]=vet[i];
	vet[i]=tmp;

	return i;
}

void quicksort( person *vet, int ini, int fim )
{
	int r;
	if(fim > ini)
	{
		r=particao( vet, ini, fim );
		quicksort( vet, ini, r-1);
		quicksort( vet, r+1, fim );
	}
}



void personTableSort() {
	quicksort( table.list, 0, PERSON_NUM_LIMIT - 1 );
}



void personTableInit( double defaultSpeed, double createRate ) {
    table.curMax = table.lastID = 0;
    table.defaultSpeed = defaultSpeed;
    table.createRate = createRate;
    table.createCounter = randomizeAround( createRate, STD_DIST );
}



unsigned int personTableAdd(person p) {
    if( table.curMax == PERSON_NUM_LIMIT ) {
        personTableSort();
        if( table.curMax == PERSON_NUM_LIMIT )
            return ERROR_PERSON_LIMIT_EXCEEDED;
    }
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
void personTableUpdate( ) {
    int i;
    point pos;
    for( i = 0; i < table.curMax; i++ )
        if( table.list[i] != NULL ){
              personUpdate(table.list[i]);
	      pos = personGetPos( table.list[i] );
	      if( pos.x > MAX_X || pos.y > MAX_Y || pos.x < 0 || pos.y < 0 ){
	          personRemove( table.list[i] );
	          table.list[i] = personNew( table.defaultSpeed );
	    }
      }
      if(table.curMax < PERSON_NUM_LIMIT){
	  table.createCounter -= 1;
	  if(table.createCounter < 0){
	     personTableAdd( personNew( table.defaultSpeed ) ); 
	     table.createCounter += randomizeAround( table.createRate, STD_DIST );
	  }
      }
	personTableSort();
	for( i = table.curMax - 1; i >= 0 && table.list[i] == NULL; i-- )
		table.curMax--;
		
    /* TODO: Verificar se deve ou nao colocar mais passageiros */
}



void personTableExecute( void (*func)(person p) ) {
    int i;
    for( i = 0; i < table.curMax; i++ )
        if( table.list[i] != NULL )
            func(table.list[i]);
}




void personTableDump() {
	int i;
	for( i = 0; i < table.curMax; i++ ) {
		printf("Person[%2d]: ", i);
		if( table.list[i] != NULL )
			personDump( table.list[i] );
		else
			printf("NULL");
		printf("\n");
	}
	printf("\n");
}
