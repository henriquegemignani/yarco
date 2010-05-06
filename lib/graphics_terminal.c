/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "graphics.h"
#include "person.h"
#include "persontable.h"
/* #include <stdio.h> -- ta no common.h agora */

typedef enum {
    NOTHING,
    PASSENGER,
    COLLISION,
    BOAT,
    OBSTACLE
} TOKEN;

char tokenToChar(TOKEN t)
{
    switch (t) {
    case NOTHING:
        return '.';
    case PASSENGER:
        return '#';
    case COLLISION:
        return '!';
    case BOAT:
        return 'O';
    case OBSTACLE:
        return '&';
    default:
        return '?';
    }
}

#define OUTPUT_WIDTH 120
#define OUTPUT_HEIGHT 30

#define PIXEL_SIZE_X (SCREEN_SIZE_X / OUTPUT_WIDTH)
#define PIXEL_SIZE_Y (SCREEN_SIZE_Y / OUTPUT_HEIGHT)

static TOKEN outputScreen[OUTPUT_HEIGHT][OUTPUT_WIDTH];

int graphicInitialize()
{
    int i, j;
    for (i = 0; i < OUTPUT_HEIGHT; i++)
        for (j = 0; j < OUTPUT_WIDTH; j++)
            outputScreen[i][j] = NOTHING;
    return 0;
}

void graphicUpdatePerson(person per)
{
    point p = personGetPos(per);
    int x = p.x / PIXEL_SIZE_X, y = p.y / PIXEL_SIZE_Y;
    if (x >= 0 && y >= 0 && x < OUTPUT_WIDTH && y < OUTPUT_HEIGHT){
      if(outputScreen[y][x] == NOTHING)
        outputScreen[y][x] = PASSENGER; /* TODO: detectar colisao 
                                           e marcar corretamente */
      else
	outputScreen[y][x] = COLLISION;
    }
    
}

int graphicUpdate()
{
    int i, j;
    for (i = 0; i < OUTPUT_HEIGHT; i++)
        for (j = 0; j < OUTPUT_WIDTH; j++)
            outputScreen[i][j] = NOTHING;
    personTableExecute(graphicUpdatePerson);
    return 0;
}

int graphicDraw()
{
    int i, j;
    for (i = 0; i < OUTPUT_HEIGHT; i++) {
        for (j = 0; j < OUTPUT_WIDTH; j++)
            printf("%c", tokenToChar(outputScreen[i][j]));
        printf("\n");
    }
    return 0;
}
