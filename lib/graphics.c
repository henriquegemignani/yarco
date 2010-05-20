/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "object.h"
#include "graphics.h"
#include "person.h"
#include "persontable.h"
#include "physics.h"
#include <allegro.h>

BITMAP *buffer;

void graphicUpdatePerson( person per );

void graphicInitialize( int mode )
{
	allegro_init();
	set_color_depth(32);
	if( mode == WINDOWED_MODE )
		set_gfx_mode( GFX_AUTODETECT_WINDOWED, 	SCREEN_SIZE_X, SCREEN_SIZE_Y, 0, 0 );
	else if( mode == FULLSCREEN_MODE )
		set_gfx_mode( GFX_AUTODETECT_FULLSCREEN, SCREEN_SIZE_X, SCREEN_SIZE_Y, 0, 0 );

	buffer = create_bitmap( SCREEN_SIZE_X, SCREEN_SIZE_Y	);
}

void graphicUpdate( personTable table )
{
	clear( buffer );
	personTableExecute( table, graphicUpdatePerson );
}

void graphicUpdatePerson( person per )
{
	BITMAP *tmp = create_bitmap( 15, 15 );
	point p = objectGetPos( per );
	rectfill( tmp, 0, 0, 15, 15, 3000 ); /* essa linha ainda vai perecer */
	draw_sprite( buffer, tmp, p.x, p.y );
}

void graphicDraw()
{
	draw_sprite( screen, buffer, 0, 0 );
}

void graphicFinish()
{
	destroy_bitmap( buffer );
	allegro_exit();
}
