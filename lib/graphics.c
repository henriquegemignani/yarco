/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "graphics.h"
#include "common.h"
#include "object.h"
#include "objecttable.h"
#include "../config/configuration.h"
#include "report.h"

#include <math.h>
#include <allegro.h>

#define SEA_COLOR 0x001770
#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define TRANSPARENT 0xFF00FF
#define GAME_SCREEN_PROPORTION 0.925
#define SCREEN_RATIO_X ((double)(screenSizeX+1)/MAX_X)
#define SCREEN_RATIO_Y ((double)(screenGameArea+1)/MAX_Y)
#define PLAYER_MULTIPLAYER_DISPLAY_X 200
#define PLAYER_OFFSET_DISPLAY_X 10
#define PLAYER_DISPLAY_Y 50
#define LIFE_DISPLAY_Y 40
#define SCORE_DISPLAY_Y 30
#define PEOPLE_DISPLAY_Y 20
#define HIGHSCORE_OFFSET_Y (screenSizeY/2 - 30)
#define HIGHSCORE_DIST_Y 10

static BITMAP *buffer;
static int screenSizeX, screenSizeY, screenGameArea, screenDisplayArea;

int logicGetScore(int player);
char *logicGetPlayerName(int player);

void graphicUpdateObject(object per);
void graphicInitialize(int mode)
{
    screenSizeX = configGetValue("General", "ResolutionX").num;
    screenSizeY = configGetValue("General", "ResolutionY").num;

    screenGameArea = floor(GAME_SCREEN_PROPORTION * screenSizeY);
    screenDisplayArea = screenSizeY - screenGameArea;

    set_color_depth(32);
    if (mode == WINDOWED_MODE)
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, screenSizeX, screenSizeY,
                     0, 0);
    else if (mode == FULLSCREEN_MODE)
        set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, screenSizeX,
                     screenSizeY, 0, 0);

    buffer = create_bitmap(screenSizeX, screenSizeY);
    rectfill(buffer, 0, 0, screenSizeX, screenGameArea, SEA_COLOR);
    rectfill(buffer, 0, screenGameArea, screenSizeX, screenSizeY, WHITE);
}

void graphicUpdateObject(object per)
{
    double xRatio = SCREEN_RATIO_X, yRatio = SCREEN_RATIO_Y;
    BITMAP *tmp =
        create_bitmap(per->radius * 3 * xRatio, per->radius * 3 * yRatio);
    point aux1, aux2, aux3, p = objectGetPos(per);
    xRatio = SCREEN_RATIO_X;    /*Economizar processamento, ja que vai ser feito muitas vezes*/
    yRatio = SCREEN_RATIO_Y;
    p.x *= xRatio;
    p.y *= yRatio;
    rectfill(tmp, 0, 0, per->radius * 3 * xRatio, per->radius * 3 * yRatio,
             TRANSPARENT);
    switch (per->tex.type) {
    case TEX_CIRCLE:
        ellipsefill(tmp, per->radius * xRatio, per->radius * yRatio,
                    per->radius * xRatio, per->radius * yRatio,
                    per->tex.color);
        break;
    case TEX_SQUARE:
        rectfill(tmp, 0, 0, per->radius * SQRT_2 * xRatio,
                 per->radius * SQRT_2 * yRatio, per->tex.color);
        break;
    case TEX_TRIANGLE:
        aux1.x = per->radius - (per->radius * cos((per->dir))) * xRatio;
        aux1.y = per->radius - (per->radius * sin((per->dir))) * yRatio;
        aux2.x =
            per->radius -
            (per->radius * cos((per->dir) + (4 * PI / 5))) * xRatio;
        aux2.y =
            per->radius -
            (per->radius * sin((per->dir) + (4 * PI / 5))) * yRatio;
        aux3.x =
            per->radius -
            (per->radius * cos((per->dir) - (4 * PI / 5))) * xRatio;
        aux3.y =
            per->radius -
            (per->radius * sin((per->dir) - (4 * PI / 5))) * yRatio;
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

void graphicDisplayUpdate()
{
    static int numplayers = -1;
    char buf[50];
    double screenRatioX = SCREEN_RATIO_X, screenRatioY = SCREEN_RATIO_Y;
    int i, offsetX;
	status players_status;
    if (numplayers == -1)
        numplayers = configGetValue("General", "NumPlayers").num;
    rectfill(buffer, 0, screenGameArea, screenSizeX, screenSizeY, WHITE);

    for (i = 0; i < numplayers; ++i) {
		players_status = getStatus(i);
        offsetX =
            (PLAYER_MULTIPLAYER_DISPLAY_X * i +
             PLAYER_OFFSET_DISPLAY_X) * screenRatioX;
        textout_ex(buffer, font,
                   players_status.name ==
                   NULL ? "" : players_status.name, offsetX,
                   screenSizeY - (PLAYER_DISPLAY_Y * screenRatioY), BLACK,
                   WHITE);
        snprintf(buf, 50, "VIDAS: %d", players_status.life);
        textout_ex(buffer, font, buf, offsetX,
                   screenSizeY - (LIFE_DISPLAY_Y * screenRatioY), BLACK,
                   WHITE);
        snprintf(buf, 50, "PONTOS: %d", players_status.score);
        textout_ex(buffer, font, buf, offsetX,
                   screenSizeY - (SCORE_DISPLAY_Y * screenRatioY), BLACK,
                   WHITE);
        snprintf(buf, 50, "PASSAGEIROS: %d", players_status.people);
        textout_ex(buffer, font, buf, offsetX,
                   screenSizeY - (PEOPLE_DISPLAY_Y * screenRatioY), BLACK,
                   WHITE);
    }
}

void graphicDrawHighScore(/*struct HighScore* scoretable,*/ int ammount) {
    int i;
    double yRatio = SCREEN_RATIO_Y;
    rectfill(buffer, 0, 0, screenSizeX, screenSizeY, BLACK);
    textprintf_centre_ex(buffer, font, screenSizeX/2, HIGHSCORE_OFFSET_Y*yRatio, WHITE, BLACK, "HIGHSCORES!");
    for (i=0; i<ammount; i++)
        textprintf_centre_ex(buffer, font, screenSizeX/2, (HIGHSCORE_OFFSET_Y + HIGHSCORE_DIST_Y * (i+1))*yRatio, WHITE, BLACK, 
			"%-32s %12d", logicGetPlayerName(i), logicGetScore(i));
    graphicDraw();
}

void graphicUpdate()
{
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
