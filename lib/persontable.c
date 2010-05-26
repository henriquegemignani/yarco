/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "object.h"
#include "class.h"
#include "person.h"
#include "persontable.h"
#include "physics.h"

struct PersonTable {
    object list[PERSON_NUM_LIMIT];
    unsigned int curMax, lastID;
    double defaultSpeed, createRate, createCounter;
    int uniqueGraphics;
    int fps;
};

#define PERSON_DEFAULTTEX '#'

/* Funcoes privadas. */
object personTableAdd(personTable table, object p)
{
    if (table->curMax == PERSON_NUM_LIMIT) {
        personTableSort(table);
        if (table->curMax == PERSON_NUM_LIMIT)
            return ERROR_PERSON_LIMIT_EXCEEDED;
    }
    table->list[table->curMax++] = p;
    objectSetID(p, ++table->lastID);
    return p;
}

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


char createPersonGraphic(personTable table)
{
    return table->uniqueGraphics ? (char) ('@' +
                                           (table->lastID %
                                            ('z' -
                                             'A'))) : PERSON_DEFAULTTEX;
}

/* Funcoes publicas. */

personTable personTableInit(double defaultSpeed, double createRate,
                            int uniqueGraphics, int fps)
{
    personTable table;
    AUTOMALLOC(table);

    table->curMax = table->lastID = 0;
    table->defaultSpeed = defaultSpeed;
    table->createRate = createRate;
    table->createCounter = randomizeAround(createRate, STD_DIST);
    table->uniqueGraphics = uniqueGraphics;
    table->fps = fps;

    return table;
}


person personTableAddNew(personTable table)
{
    person aux =
        personNew(createPersonGraphic(table), table->defaultSpeed), p =
        personTableAdd(table, aux);
    if (p == ERROR_PERSON_LIMIT_EXCEEDED)
        personRemove(aux);
    return p;
}


person personTableCreate(personTable table, point pos, velocity vel)
{
    person aux = personCreate(createPersonGraphic(table), pos, vel),
        p = personTableAdd(table, aux);
    if (p == ERROR_PERSON_LIMIT_EXCEEDED)
        personRemove(aux);
    return p;
}

object personTableSearch(personTable table, unsigned int id)
{
    int i;
    for (i = 0; i < table->curMax; i++)
        if (objectGetID(table->list[i]) == id)
            return table->list[i];
    return NULL;
}


int personTableRemoveByID(personTable table, unsigned int id)
{
    int i;
    object pAux;
    for (i = 0; i < table->curMax; i++)
        if (objectGetID(table->list[i]) == id) {
            pAux = table->list[i];
            table->list[i] = NULL;
            OBJECT_REMOVE(pAux);
            return 0;
        }
    return WARNING_PERSON_NOT_FOUND;
}


int personTableRemoveByPerson(personTable table, object p)
{
    return personTableRemoveByID(table, objectGetID(p));
}


void personTableSort(personTable table)
{
    quicksort(table->list, 0, table->curMax - 1);
}


/* Management functions */
void personTableUpdate(personTable table, int keepDir, int newSec)
{
    int i, j;
    point pos;
    /* Verificando colisoes. */
    for (i = 0; i < table->curMax; i++)
        for (j = i + 1; j < table->curMax; j++)
            if (quadNear
                (objectGetQuad(table->list[i]),
                 objectGetQuad(table->list[j])))
                if (objectIsColiding(table->list[i], table->list[j]))
                    OBJECT_COLLIDE(table->list[i], table->list[j]);

    /* Para cada pessoa... */
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL) {
            /* Atualiza e... */
            OBJECT_UPDATE(table->list[i], keepDir, table->fps);

            /* Verifica se saiu do mapa. */
            pos = objectGetPos(table->list[i]);
            if (pos.x > MAX_X || pos.y > MAX_Y || pos.x < 0 || pos.y < 0) {
                OBJECT_BOUNDS(table->list[i]);
            }
        }

    if (table->createRate > 0 && table->curMax < PERSON_NUM_LIMIT
        && newSec) {
        /* Verifica se ja esta na hora de criar mais uma pessoa. */
        table->createCounter -= 1;
        if (table->createCounter < 0) {
            personTableAddNew(table);
            table->createCounter +=
                randomizeAround(table->createRate, STD_DIST);
        }
    }
    personTableSort(table);
    for (i = table->curMax - 1; i >= 0 && table->list[i] == NULL; i--)
        table->curMax--;
}



void personTableExecute(personTable table, void (*func) (person p))
{
    int i;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            func(table->list[i]);
}




void personTableDump(personTable table)
{
    int i;
    for (i = 0; i < table->curMax; i++) {
        printf("Object[%2d]: ", i);
        if (table->list[i] != NULL)
            OBJECT_DUMP(table->list[i]);
        else
            printf("NULL");
        printf("\n");
    }
    printf("\n");
}



void personTableRemove(personTable table)
{
    int i;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            OBJECT_REMOVE(table->list[i]);
    free(table);
}


double personTableMaxSpeed(personTable table)
{
    int i;
    double max, curspeed;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL) {
            max = objectGetSpeed(table->list[i++]);
            break;
        }
    for (; i < table->curMax; i++)
        if (table->list[i] != NULL)
            if ((curspeed = objectGetSpeed(table->list[i])) > max)
                max = curspeed;
    return max;
}


double personTableMinSpeed(personTable table)
{
    int i;
    double min, curspeed;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL) {
            min = objectGetSpeed(table->list[i++]);
            break;
        }
    for (; i < table->curMax; i++)
        if (table->list[i] != NULL)
            if ((curspeed = objectGetSpeed(table->list[i])) < min)
                min = curspeed;
    return min;
}


double personTableAvgSpeed(personTable table)
{
    int i, numPeople = 0;
    double sum = 0;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL) {
            sum += objectGetSpeed(table->list[i]);
            numPeople++;
        }
    return sum / numPeople;
}


int personTableCount(personTable table)
{
    int i, numPeople = 0;
    for (i = 0; i < table->curMax; i++)
        if (table->list[i] != NULL)
            numPeople++;
    return numPeople;
}
