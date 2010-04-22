/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "graphics.h"
#include "person.h"
#include "persontable.h"

typedef enum {
  NOTHING,
  PASSENGER,  
  BOAT,   
  OBSTACLE
} TOKEN;

char tokenToChar( TOKEN t ) {
    switch( t ) {
        case NOTHING:   return '.';
        case PASSENGER: return '#';
        case BOAT:      return 'O';
        case OBSTACLE:  return '&';
        default:        return '?';
    }
}

#define OUTPUT_WIDTH 120
#define OUTPUT_HEIGHT 30

#define PIXEL_SIZE_X 20
#define PIXEL_SIZE_Y 15

static TOKEN outputScreen[OUTPUT_HEIGHT][OUTPUT_WIDTH];

int graphicInitialize() {
    int i, j;
    for( i = 0; i < OUTPUT_HEIGHT; i++ )
        for( j = 0; j < OUTPUT_WIDTH; j++ )
            outputScreen[i][j] = NOTHING;
    return 0;
}

void grahpicUpdatePerson(person per) {
    point p = personGetPos(per);
    int x = p.x / PIXEL_SIZE_X, y = p.y / PIXEL_SIZE_Y;
    if( x < OUTPUT_WIDTH && y < OUTPUT_HEIGHT )
        outputScreen[y][x] = PASSENGER;
}

int grahpicUpdate() {
    int i, j;
    for( i = 0; i < OUTPUT_HEIGHT; i++ )
        for( j = 0; j < OUTPUT_WIDTH; j++ )
            outputScreen[i][j] = NOTHING;
    personTableExecute(grahpicUpdatePerson);
    return 0;
}

int graphicDraw() {
    int i, j;
    for( i = 0; i < OUTPUT_HEIGHT; i++ ) {
        for( j = 0; j < OUTPUT_WIDTH; j++ )
            printf("%c", tokenToChar(outputScreen[i][j]));
        printf("\n");
    }
    return 0;
}
