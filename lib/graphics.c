/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "graphics.h"
#include "common.h"
#include "object.h"
#include "objecttable.h"
#include "../config/configuration.h"

#include <math.h>
#include <allegro.h>

#define SEA_COLOR 0x001770
#define SCREEN_RATIO_X ((double)(screenSizeX+1)/MAX_X)
#define SCREEN_RATIO_Y ((double)(screenSizeY+1)/MAX_Y)

static BITMAP *buffer;
static int screenSizeX, screenSizeY;

void graphicUpdateObject(object per);
void graphicInitialize(int mode)
{
    if (allegro_init())
        genError
            ("Erro em inicializar o allegro. Se voce esta utilizando modo texto, tente --nographic\n");
    
	screenSizeX = configGetValue("General", "ResolutionX").num;
	screenSizeY = configGetValue("General", "ResolutionY").num;
	
	set_color_depth(32);
    if (mode == WINDOWED_MODE)
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenSizeX, screenSizeY,
                     0, 0);
    else if (mode == FULLSCREEN_MODE)
        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screenSizeX,
                     screenSizeY, 0, 0);

    buffer = create_bitmap(screenSizeX, screenSizeY);
    rectfill(buffer, 0, 0, screenSizeX, screenSizeY, SEA_COLOR);
}

void graphicUpdateObject(object per)
{
    double xRatio = SCREEN_RATIO_X, yRatio = SCREEN_RATIO_Y;
    BITMAP *tmp = create_bitmap(per->radius * 3 * xRatio, per->radius * 3 * yRatio);
    point aux1, aux2, aux3, p = objectGetPos(per);
    xRatio = SCREEN_RATIO_X; //Economoizar processamento, ja que vai ser feito muitas vezes
    yRatio = SCREEN_RATIO_Y;
    p.x *= xRatio;
    p.y *= yRatio;
    rectfill(tmp, 0, 0, per->radius * 3 * xRatio, per->radius * 3 * yRatio, 0xff00ff);
    switch (per->tex.type) {
    case TEX_CIRCLE:
        ellipsefill(tmp, per->radius*xRatio, per->radius*yRatio, per->radius * xRatio, per->radius * yRatio,
                   per->tex.color);
        break;
    case TEX_SQUARE:
        rectfill(tmp, 0, 0, per->radius * SQRT_2 * xRatio, per->radius * SQRT_2 * yRatio,
                 per->tex.color);
        break;
    case TEX_TRIANGLE:
        aux1.x = per->radius - (per->radius * cos((per->dir))) * xRatio;
        aux1.y = per->radius - (per->radius * sin((per->dir))) * yRatio;
        aux2.x =
            per->radius - (per->radius * cos((per->dir) + (4 * PI / 5))) * xRatio;
        aux2.y =
            per->radius - (per->radius * sin((per->dir) + (4 * PI / 5))) * yRatio;
        aux3.x =
            per->radius - (per->radius * cos((per->dir) - (4 * PI / 5))) * xRatio;
        aux3.y =
            per->radius - (per->radius * sin((per->dir) - (4 * PI / 5))) * yRatio;
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
        break;
    case TEX_HORIZONTAL_RETANGLE:
        aux1.x = per->radius - (2 * (per->radius / SQRT_5)) * xRatio;
        aux1.y = per->radius - (per->radius / SQRT_5) * yRatio;
        aux2.x = per->radius + (2 * (per->radius / SQRT_5)) * xRatio;
        aux2.y = per->radius + (per->radius / SQRT_5) * yRatio;
        rectfill(tmp, aux1.x, aux1.y, aux2.x, aux2.y, per->tex.color);
        break;
    default:
        /* foto dos desenvolvedores */
         /*NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO*/
            genWarning("Aviso: Formato nao reconhecido!\n");
        break;
    }
    draw_sprite(buffer, tmp, p.x - per->radius, p.y - per->radius);
    destroy_bitmap(tmp);
}


void graphicUpdate()
{
    clear(buffer);
    rectfill(buffer, 0, 0, screenSizeX, screenSizeY, SEA_COLOR);
    objectTableExecute(graphicUpdateObject);
}


void graphicDraw()
{
    blit(buffer, screen, 0, 0, 0, 0, screenSizeX, screenSizeY);
}

void graphicFinish()
{
    destroy_bitmap(buffer);
    allegro_exit();
}
