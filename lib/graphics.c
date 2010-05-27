/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/
#include "common.h"
#include "object.h"
#include "graphics.h"
#include "physics.h"
#include <math.h>

#define SEA_COLOR 0x001770

BITMAP *buffer;

void graphicUpdateObject(object per);

void graphicInitialize(int mode)
{
    if (allegro_init())
        genError
            ("Erro em inicializar o allegro. Se voce esta utilizando modo texto, tente --nographic\n");
    set_color_depth(32);
    if (mode == WINDOWED_MODE)
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_SIZE_X, SCREEN_SIZE_Y,
                     0, 0);
    else if (mode == FULLSCREEN_MODE)
        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCREEN_SIZE_X,
                     SCREEN_SIZE_Y, 0, 0);

    buffer = create_bitmap(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    floodfill(buffer, 0, 0, SEA_COLOR);
}

void graphicUpdateObject(object per)
{
    BITMAP *tmp = create_bitmap(per->radius * 2, per->radius * 2);
    point /*aux1, aux2, aux3, */ p = objectGetPos(per);
    rectfill(tmp, 0, 0, per->radius * 2, per->radius * 2, 0xff00ff);    /*TODO (graphicUpdateObject): algo que verifique qual o modo grafico para determinar qual a cor transparente */
    switch (per->tex.type) {
    case TEX_CIRCLE:
        circlefill(tmp, per->radius, per->radius, per->radius, 0);
        break;
    case TEX_SQUARE:
        rectfill(tmp, 0, 0, per->radius * 2, per->radius * 2, 0);
        break;
        /* a parte dos barcos vai ser punk */
    case TEX_ISOSC_TRIANGLE:
        triangle(
            tmp, 
            per->radius-(per->radius*cos(vectorAngle(per->acc))), 
            per->radius-(per->radius*sin(vectorAngle(per->acc))), 
            per->radius-(per->radius*cos(vectorAngle(per->acc)+(4*PI/5))), 
            per->radius-(per->radius*sin(vectorAngle(per->acc)+(4*PI/5))), 
            per->radius-(per->radius*cos(vectorAngle(per->acc)-(4*PI/5))), 
            per->radius-(per->radius*sin(vectorAngle(per->acc)-(4*PI/5))), 
            0x000000);
       /* rotate_sprite(buffer, tmp, p.x, p.y, per->acc.y / (2 * PI) * 256);*/
        /*OH CEUS  TODO: implementar o giramento de barquinhos */
        /*TODO: Ver se funfa. >_> */
        break;
    default:
        /* foto dos desenvolvedores */
        break;
    }
    draw_sprite(buffer, tmp, p.x, p.y);
    destroy_bitmap(tmp);
}

void graphicUpdate(objectTable table)
{
    clear(buffer);
    floodfill(buffer, 0, 0, SEA_COLOR);
    objectTableExecute(table, graphicUpdateObject);
}


void graphicDraw()
{
    draw_sprite(screen, buffer, 0, 0);
}

void graphicFinish()
{
    destroy_bitmap(buffer);
    allegro_exit();
}
