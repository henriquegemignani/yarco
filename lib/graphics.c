/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "graphics.h"
#include "common.h"
#include "object.h"
#include "objecttable.h"

#include <math.h>
#include <allegro.h>

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
    /* floodfill(buffer, 0, 0, SEA_COLOR); */
}

void graphicUpdateObject(object per)
{
    BITMAP *tmp = create_bitmap(per->radius * 3, per->radius * 3);
    point aux1, aux2, aux3, p = objectGetPos(per);
    rectfill(tmp, 0, 0, per->radius * 3, per->radius * 3, 0xff00ff);
    /* TODO (graphicUpdateObject): algo que verifique qual o modo grafico para determinar qual a 
       cor transparente */
    switch (per->tex.type) {
    case TEX_CIRCLE:
        circlefill(tmp, per->radius, per->radius, per->radius,
                   per->tex.color);
        break;
    case TEX_SQUARE:
        rectfill(tmp, 0, 0, per->radius * SQRT_2, per->radius * SQRT_2,
                 per->tex.color);
        break;
        /* a parte dos barcos vai ser punk */
    case /*TEX_ISOSC_TRIANGLE */ TEX_TRIANGLE:
        aux1.x =
            per->radius -
            (per->radius * cos( /*vectorAngle */ (per->dir)));
        aux1.y =
            per->radius -
            (per->radius * sin( /*vectorAngle */ (per->dir)));
        aux2.x =
            per->radius -
            (per->radius *
             cos( /*vectorAngle */ (per->dir) + (4 * PI / 5)));
        aux2.y =
            per->radius -
            (per->radius *
             sin( /*vectorAngle */ (per->dir) + (4 * PI / 5)));
        aux3.x =
            per->radius -
            (per->radius *
             cos( /*vectorAngle */ (per->dir) - (4 * PI / 5)));
        aux3.y =
            per->radius -
            (per->radius *
             sin( /*vectorAngle */ (per->dir) - (4 * PI / 5)));
        triangle(tmp, aux1.x, aux1.y, aux2.x, aux2.y, aux3.x, aux3.y,
                 per->tex.color);
        /*Codigo abaixo mantido para a posteridade - DO NOT EXCLUAM */
        /*triangle(
           tmp, 
           per->radius-(per->radius*cos(vectorAngle(per->acc))), 
           per->radius-(per->radius*sin(vectorAngle(per->acc))), 
           per->radius-(per->radius*cos(vectorAngle(per->acc)+(4*PI/5))), 
           per->radius-(per->radius*sin(vectorAngle(per->acc)+(4*PI/5))), 
           per->radius-(per->radius*cos(vectorAngle(per->acc)-(4*PI/5))), 
           per->radius-(per->radius*sin(vectorAngle(per->acc)-(4*PI/5))), 
           per->tex.color);
         */
        /* rotate_sprite(buffer, tmp, p.x, p.y, per->acc.y / (2 * PI) * 256); */
        /*OH CEUS  TODO: implementar o giramento de barquinhos */
        /*TODO: Ver se funfa. >_> */
        break;
    case TEX_HORIZONTAL_RETANGLE:
        aux1.x = per->radius - (2 * (per->radius / SQRT_5));
        aux1.y = per->radius - (per->radius / SQRT_5);
        aux2.x = per->radius + (2 * (per->radius / SQRT_5));
        aux2.y = per->radius + (per->radius / SQRT_5);
        rectfill(tmp, aux1.x, aux1.y, aux2.x, aux2.y, per->tex.color);
        break;
    default:
        /* foto dos desenvolvedores */
        break;
    }
    draw_sprite(buffer, tmp, p.x - per->radius, p.y - per->radius);
    destroy_bitmap(tmp);
}

void graphicUpdate()
{
    clear(buffer);
    rectfill(buffer, 0, 0, MAX_X, MAX_Y, SEA_COLOR);
    objectTableExecute(graphicUpdateObject);
}


void graphicDraw()
{
    blit(buffer, screen, 0, 0, 0, 0, MAX_X, MAX_Y);
}

void graphicFinish()
{
    destroy_bitmap(buffer);
    allegro_exit();
}
