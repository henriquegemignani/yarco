/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/
#include "common.h"
#include "object.h"
#include "graphics.h"
#include "physics.h"
//#include <allegro.h>

BITMAP *buffer;

void graphicUpdateObject(object per);

void graphicInitialize(int mode)
{
    if( allegro_init() )
        genError("Erro em inicializar o allegro. Se voce esta utilizando modo texto, tente --nographic\n");
    set_color_depth(32);
    if (mode == WINDOWED_MODE)
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_SIZE_X, SCREEN_SIZE_Y,
                     0, 0);
    else if (mode == FULLSCREEN_MODE)
        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, SCREEN_SIZE_X,
                     SCREEN_SIZE_Y, 0, 0);

    buffer = create_bitmap(SCREEN_SIZE_X, SCREEN_SIZE_Y);
	floodfill( buffer, 0, 0, 6000 );
}

void graphicUpdateObject(object per)
{
    BITMAP *tmp = create_bitmap(per->radius * 2, per->radius * 2);
    point p = objectGetPos(per);
	floodfill( tmp, 0, 0, 6000 );
	switch( per->tex.type ){
		case TEX_CIRCLE:
			circlefill( tmp, per->radius, per->radius, per->radius, 0  );
			break;
		case TEX_SQUARE:
			rectfill( tmp, 0, 0, per->radius*2, per->radius*2, 0 );
			break;
		/* a parte dos barcos vai ser punk */
		case TEX_ISOSC_TRIANGLE:
			/*OH CEUS  TODO: implementar o giramento de barquinhos*/
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
	floodfill( buffer, 0, 0, 6000 );
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
