/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "object.h"
#include "graphics.h"
#include "person.h"
#include "persontable.h"

#define TERMINAL_NOTHING    '.'
#define TERMINAL_COLLISION  '!'
#define TERMINAL_OBSTACLE   '&'

#define OUTPUT_WIDTH 120
#define OUTPUT_HEIGHT 30

#define PIXEL_SIZE_X ((double)SCREEN_SIZE_X / OUTPUT_WIDTH)
#define PIXEL_SIZE_Y ((double)SCREEN_SIZE_Y / OUTPUT_HEIGHT)

struct GraphicEngine {
    char outputScreen[OUTPUT_HEIGHT][OUTPUT_WIDTH];
    personTable table;
};
static graphicEngine engine;

void graphicInitialize(personTable table)
{
    AUTOMALLOC(engine);
    engine->table = table;
    int i, j;
    for (i = 0; i < OUTPUT_HEIGHT; i++)
        for (j = 0; j < OUTPUT_WIDTH; j++)
            engine->outputScreen[i][j] = TERMINAL_NOTHING;
}

void graphicUpdatePerson(person per)
{
    point p = objectGetPos(per);
    int x = p.x / PIXEL_SIZE_X, y = p.y / PIXEL_SIZE_Y;
    if (x >= 0 && y >= 0 && x < OUTPUT_WIDTH && y < OUTPUT_HEIGHT) {
        if (engine->outputScreen[y][x] == TERMINAL_NOTHING)
            engine->outputScreen[y][x] = objectGetTexture(per);
        else
            engine->outputScreen[y][x] = TERMINAL_COLLISION;
    }
}

void graphicUpdate()
{
    int i, j;
    for (i = 0; i < OUTPUT_HEIGHT; i++)
        for (j = 0; j < OUTPUT_WIDTH; j++)
            engine->outputScreen[i][j] = TERMINAL_NOTHING;
    personTableExecute(engine->table, graphicUpdatePerson);
}

void graphicDraw()
{
    int i, j;
    for (i = 0; i < OUTPUT_HEIGHT; i++) {
        for (j = 0; j < OUTPUT_WIDTH; j++) {
            printf("%c", engine->outputScreen[i][j]);
        }
        printf("\n");
    }
}

void graphicFinish()
{
    free(engine);
    engine = NULL;
}
