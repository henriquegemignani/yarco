/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _LOGIC_H_
#define _LOGIC_H_

typedef enum {
	GAME_NOT_STARTED,
	GAME_TITLE_SCREEN,
	GAME_RUNNING,
	GAME_HIGHSCORE,
	GAME_DONE
} GameState;

struct HighScore {
	char* name;
	int score;
};

long timeInMicrosecond();
void loginAllegroCloseButtonHandler(void);

void logicCreateScoreTable();
void logicDestroyScoreTable();

void logicSleep();
void logicInitialize(int argc, char* argv[]);

double logicLoop(double timeDifference);
void logicLoopTitleScreen(double timeDifference);
void logicLoopRunning(double timeDifference);
void logicLoopHighScore(double timeDifference);

void logicFinish();
int logicGameOver();

#endif                          /* _LOGIC_H_ */
