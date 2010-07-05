/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "report.h"

static status* players_status;

void initReport(int players) {
	AUTOMALLOCV(players_status, players);
}
void statusReport(int player, char *name, int lives, int score, int peopleHeld)
{
    players_status[player].name = name;
    players_status[player].life = lives;
    players_status[player].score = score;
    players_status[player].people = peopleHeld;
}
status getStatus(int player) {
	return players_status[player];
}
void finishReport() {
	free(players_status);
}
