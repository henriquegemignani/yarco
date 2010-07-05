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
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define TRANSPARENT 0xFF00FF
#define GAME_SCREEN_PROPORTION 0.925
#define SCREEN_RATIO_X ((double)(screenSizeX+1)/MAX_X)
#define SCREEN_RATIO_Y ((double)(screenGameArea+1)/MAX_Y)
#define PLAYER_ONE_DISPLAY_X 10
#define PLAYER_TWO_DISPLAY_X 800
#define PLAYER_DISPLAY_Y 50
#define LIFE_DISPLAY_Y 40
#define SCORE_DISPLAY_Y 30
#define PEOPLE_DISPLAY_Y 20

static BITMAP *buffer;///*, *blueBoat, *redBoat*/;
static int screenSizeX, screenSizeY, screenGameArea, screenDisplayArea;

static struct{
	int life;
	int score;
	int people;
}players[2];

void graphicUpdateObject(object per);
void graphicInitialize(int mode)
{   
	screenSizeX = configGetValue("General", "ResolutionX").num;
	screenSizeY = configGetValue("General", "ResolutionY").num;
	
	screenGameArea = floor(GAME_SCREEN_PROPORTION*screenSizeY);
	screenDisplayArea = screenSizeY - screenGameArea;

	set_color_depth(32);
    if (mode == WINDOWED_MODE)
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenSizeX, screenSizeY,
                     0, 0);
    else if (mode == FULLSCREEN_MODE)
        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screenSizeX,
                     screenSizeY, 0, 0);

    buffer = create_bitmap(screenSizeX, screenSizeY);
   //blueBoat =
    rectfill(buffer, 0, 0, screenSizeX, screenGameArea, SEA_COLOR);
    rectfill(buffer, 0, screenGameArea, screenSizeX, screenSizeY, WHITE);
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
    rectfill(tmp, 0, 0, per->radius * 3 * xRatio, per->radius * 3 * yRatio, TRANSPARENT);
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

void graphicStatusReport(int player, int lives, int score, int peopleHeld)
{
	players[player].life = lives;
	players[player].score = score;
	players[player].people = peopleHeld;
}

void graphicDisplayUpdate()
{
	char buf[50];
	double screenRatioX = SCREEN_RATIO_X, screenRatioY = SCREEN_RATIO_Y;
	rectfill(buffer, 0, screenGameArea, screenSizeX, screenSizeY, WHITE);
	textout_ex(buffer, font, "PLAYER 1", PLAYER_ONE_DISPLAY_X*screenRatioX, screenSizeY - (PLAYER_DISPLAY_Y*screenRatioY), BLACK, WHITE);
	snprintf(buf, 50, "VIDAS: %d", players[0].life);
	textout_ex(buffer, font, buf, PLAYER_ONE_DISPLAY_X*screenRatioX, screenSizeY - (LIFE_DISPLAY_Y*screenRatioY), BLACK, WHITE);
	snprintf(buf, 50, "PONTOS: %d", players[0].score);
	textout_ex(buffer, font, buf, PLAYER_ONE_DISPLAY_X*screenRatioX, screenSizeY - (SCORE_DISPLAY_Y*screenRatioY), BLACK, WHITE);
	snprintf(buf, 50, "PASSAGEIROS: %d", players[0].people);
	textout_ex(buffer, font, buf, PLAYER_ONE_DISPLAY_X*screenRatioX, screenSizeY - (PEOPLE_DISPLAY_Y*screenRatioY), BLACK, WHITE);

	textout_ex(buffer, font, "PLAYER 2", PLAYER_TWO_DISPLAY_X*screenRatioX, screenSizeY - (PLAYER_DISPLAY_Y*screenRatioY), BLACK, WHITE);
	snprintf(buf, 50, "VIDAS: %d", players[1].life);
	textout_ex(buffer, font, buf, PLAYER_TWO_DISPLAY_X*screenRatioX, screenSizeY - (LIFE_DISPLAY_Y*screenRatioY), BLACK, WHITE);
	snprintf(buf, 50, "PONTOS: %d", players[1].score);
	textout_ex(buffer, font, buf, PLAYER_TWO_DISPLAY_X*screenRatioX, screenSizeY - (SCORE_DISPLAY_Y*screenRatioY), BLACK, WHITE);
	snprintf(buf, 50, "PASSAGEIROS: %d", players[1].people);
	textout_ex(buffer, font, buf, PLAYER_TWO_DISPLAY_X*screenRatioX, screenSizeY - (PEOPLE_DISPLAY_Y*screenRatioY), BLACK, WHITE);
}

void graphicUpdate()
{
    //clear(buffer);
    rectfill(buffer, 0, 0, screenSizeX, screenGameArea, SEA_COLOR);
    objectTableExecute(graphicUpdateObject);
    graphicDisplayUpdate();
}


void graphicDraw()
{
    blit(buffer, screen, 0, 0, 0, 0, screenSizeX, screenSizeY);
}

void graphicFinish()
{
    destroy_bitmap(buffer);
}
