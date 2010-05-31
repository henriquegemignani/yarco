/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "objecttable.h"
#include "common.h"
#include "class.h"
#include "physics.h"

/*
    struct ObjectTable {
    object list[OBJECT_NUM_LIMIT];
    unsigned int curMax, lastID;
    configuration config;
};
*/

/*Algum motivo para a estrutura acime estar aqui e nao no .h? Eu mudei para usar no person.c ~Miojo*/

/* Funcoes privadas. */
int particao(object * vet, int ini, int fim)
{                               /* TODO: aqui fica o critério. MUST CHANGE */
    int i, j;
    object tmp;

    i = ini;
    for (j = ini + 1; j <= fim; ++j) {
        if (objectCompare(vet[j], vet[ini]) < 0) {      /*< */
            i++;
            tmp = vet[i];
            vet[i] = vet[j];
            vet[j] = tmp;
        }
    }
    tmp = vet[ini];
    vet[ini] = vet[i];
    vet[i] = tmp;

    return i;
}


void quicksort(object * vet, int ini, int fim)
{                               /*essa não muda nada !!! */
    int r;
    if (fim > ini) {
        r = particao(vet, ini, fim);
        quicksort(vet, ini, r - 1);
        quicksort(vet, r + 1, fim);
    }
}


/* Funcoes publicas. */

objectTable objectTableInit(configuration config)
{
    objectTable table;
    AUTOMALLOC(table);

    table->curMax = table->lastID = 0;
    table->config = config;

    return table;
}

int objectTableAddObject(objectTable table, object obj)
{
	obj->quadrante = quadSet(obj->pos.x/QUAD_SIZE_X, obj->pos.y/QUAD_SIZE_Y);
    if (objectTableFilled(table))
        return ERROR_OBJECT_LIMIT_EXCEEDED;
    if (objectTableIsObjectColliding(table, obj))
      return ERROR_OBJECT_IS_COLLIDING;
    obj->id = ++table->lastID;
    table->list[table->curMax++] = obj;
    return 0;
}

object objectTableSearchObject(objectTable table, unsigned int id)
{
    int i;
    for (i = 0; i < table->curMax; i++)
        if (objectGetID(table->list[i]) == id)
            return table->list[i];
    return NULL;
}

int objectTableRemoveObjectByObject(objectTable table, object obj)
{
    return objectTableRemoveObjectByID(table, objectGetID(obj));
}

int objectTableRemoveObjectByID(objectTable table, unsigned int id)
{
    int i;
    object pAux;
    for (i = 0; i < table->curMax; i++)
        if (objectGetID(table->list[i]) == id) {
            pAux = table->list[i];
            table->list[i] = NULL;
            removeObject(pAux);
            return 0;
        }
    return WARNING_OBJECT_NOT_FOUND;
}

void objectTableSort(objectTable table)
{
    quicksort(table->list, 0, table->curMax - 1);
}

void objectTableUpdate(objectTable table, double timedif,
                       int newIteraction)
{
    int i, j;
    point pos;
    /* Verificando colisoes. */
    for (i = 0; i < table->curMax; i++)
        for (j = i + 1; j < table->curMax; j++)
            if (quadNear
                (objectGetQuad(table->list[i]),
                 objectGetQuad(table->list[j])))
                if (objectIsColliding(table->list[i], table->list[j])) {
                    OBJECT_COLLIDE(table->list[i], table->list[j]);
					OBJECT_COLLIDE(table->list[j], table->list[i]);
				}

    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL) {
            /* Atualiza e... */
            OBJECT_UPDATE(table->list[i], table->config->keepSpeed
                          || !newIteraction, timedif);
            /* Verifica se saiu do mapa. */
            pos = objectGetPos(table->list[i]);
            if (pos.x > MAX_X || pos.y > MAX_Y || pos.x < 0 || pos.y < 0) {
                OBJECT_BOUNDS(table->list[i], table);
            }
        }

    objectTableSort(table);
    for (i = table->curMax - 1; i >= 0 && table->list[i] == NULL; i--)
        table->curMax--;
}

void objectTableExecute(objectTable table, void (*func) (object p))
{
    int i;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            func(table->list[i]);
}

int objectTableIsObjectColliding(objectTable table, object o)
{
  int i;
  for (i = 0; i < table->curMax; i++)
    if (table->list[i] != NULL && table->list[i] != o )
    	if(quadNear(objectGetQuad(o), objectGetQuad(table->list[i])))
    		if( objectIsColliding(table->list[i], o) )
    			return 1;
  return 0;
}

int objectTableFilled(objectTable table)
{
   if (table->curMax == OBJECT_NUM_LIMIT) {
        objectTableSort(table); /* TODO: como ordenar objetos? decidir em grupo */
        if (table->curMax == OBJECT_NUM_LIMIT)
            return 1;
   }
   return 0;
}

void objectTableDump(objectTable table)
{
    int i;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            objectDump(table->list[i]);
}

void objectTableRemove(objectTable table)
{
    int i;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            removeObject(table->list[i]);
    free(table);
}
