/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "objecttable.h"
#include "common.h"
#include "class.h"
#include "configuration.h"

struct ObjectTable {
    object* list;
    unsigned int size, curMax, lastID;
};
/* Funcoes privadas. */
int particao(object * vet, int ini, int fim)
{
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
{
    int r;
    if (fim > ini) {
        r = particao(vet, ini, fim);
        quicksort(vet, ini, r - 1);
        quicksort(vet, r + 1, fim);
    }
}

objectTable objectTableInit()
{
    objectTable table;
    AUTOMALLOC(table);
	table->size = configGetValue("General", "LimitObject").num;
	AUTOMALLOCV(table->list, table->size);
    table->curMax = table->lastID = 0;
    return table;
}

void objectTableRemovePending()
{
	objectTable table = objectTableGet();
    int i;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL && table->list[i]->toBeRemoved == 1) {
            OBJECT_REMOVE(table->list[i]);
            table->list[i] = NULL;
        }
}

/* Funcoes publicas. */

objectTable objectTableGet()
{
	static objectTable table = NULL;
    if (table == NULL)
        table = objectTableInit();
    return table;
}

int objectTableAddObject(object obj)
{
	objectTable table = objectTableGet();
    objectQuadUpdate(obj);
    if (objectTableFilled())
        return ERROR_OBJECT_LIMIT_EXCEEDED;
    if (objectTableIsObjectColliding(obj))
        return ERROR_OBJECT_IS_COLLIDING;
    obj->id = ++table->lastID;
    table->list[table->curMax++] = obj;
    return 0;
}

object objectTableSearchObject(unsigned int id)
{
    int i;
	objectTable table = objectTableGet();
    for (i = 0; i < table->curMax; i++)
        if (objectGetID(table->list[i]) == id)
            return table->list[i];
    return NULL;
}

int objectTableSearchPosition(unsigned int id)
{
    int i;
	objectTable table = objectTableGet();
    for (i = 0; i < table->curMax; i++)
        if (objectGetID(table->list[i]) == id)
            return i;
    return -1;
}

int objectTableRemoveObject(object obj)
{
    return objectTableRemoveObjectByID(objectGetID(obj));
}

int objectTableRemoveObjectByID(unsigned int id)
{
    int i;
	objectTable table = objectTableGet();
    for (i = 0; i < table->curMax; i++)
        if (objectGetID(table->list[i]) == id) {
            table->list[i]->toBeRemoved = 1;
            return 0;
        }
    return WARNING_OBJECT_NOT_FOUND;
}

void objectTableSort()
{
	objectTable table = objectTableGet();
    quicksort(table->list, 0, table->curMax - 1);
}

void objectTableUpdate(double timedif, int newIteraction)
{
	objectTable table = objectTableGet();
    int i, j;
    point pos;
    /* Verificando colisoes. */
    for (i = 0; i < table->curMax; i++)
        for (j = i + 1; j < table->curMax; j++)
            if (table->list[i] != NULL && table->list[j] != NULL && quadNear
                (objectGetQuad(table->list[i]),
                 objectGetQuad(table->list[j]))
                && table->list[i]->toBeRemoved == 0
                && table->list[j]->toBeRemoved == 0)
                if (objectIsColliding(table->list[i], table->list[j])) {
                    if(table->list[i]!=NULL && table->list[j]!=NULL)
                        OBJECT_COLLIDE(table->list[i], table->list[j],
                                timedif);
                    if(table->list[i]!=NULL && table->list[j]!=NULL)
                        OBJECT_COLLIDE(table->list[j], table->list[i],
                                timedif);
                }

    objectTableRemovePending();

    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL) {
            /* Atualiza e... */
            OBJECT_UPDATE(table->list[i], configurationGet()->keepSpeed
                          || !newIteraction, timedif);
            /* Verifica se saiu do mapa. */
            pos = objectGetPos(table->list[i]);
            if (pos.x > MAX_X || pos.y > MAX_Y || pos.x < 0 || pos.y < 0) {
                OBJECT_BOUNDS(table->list[i]);
            }
        }

    objectTableRemovePending();

    objectTableSort();
    for (i = table->curMax - 1; i >= 0 && table->list[i] == NULL; i--)
        table->curMax--;
}

void objectTableExecute(void (*func) (object p))
{
    int i;
	objectTable table = objectTableGet();
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            func(table->list[i]);
}

int objectTableIsObjectColliding(object o)
{
    int i;
	objectTable table = objectTableGet();
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL && table->list[i] != o)
            if (quadNear(objectGetQuad(o), objectGetQuad(table->list[i])))
                if (objectIsColliding(table->list[i], o))
                    return 1;
    return 0;
}

int objectTableFilled()
{
	objectTable table = objectTableGet();
    if (table->curMax == table->size) {
        objectTableSort();
        if (table->curMax == table->size)
            return 1;
    }
    return 0;
}

void objectTableDump()
{
    int i;
	objectTable table = objectTableGet();
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            OBJECT_DUMP(table->list[i]);
}

void objectTableFinish()
{
    int i;
	objectTable table = objectTableGet();
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            OBJECT_REMOVE(table->list[i]);
	free(table->list);
    free(table);
}

void objectTableLeave(unsigned int id)
{
    //unsigned int i;
    int pos;
	objectTable table = objectTableGet();
    if((pos = objectTableSearchPosition(id)) == -1)
        genError("Erro: Pessoa nao encontrada!\n");
    /*for(i = 0; i < table->curMax; i++)
        if(table->list[i] == o)
            break;
    if(table->list[i] != o)
        genError("Busca deu merda!\n");*/
    table->list[pos] = NULL;
   // objectTableSort();
}

void objectTableRandColor()
{
    int i;
	objectTable table = objectTableGet();
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            table->list[i]->tex.color = randInt(0x000000, 0xFFFFFF);
}

