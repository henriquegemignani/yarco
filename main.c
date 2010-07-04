/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/**                                                               **/
/** Nomes:                                                        **/
/** Andre Mesquita Pereira              nUSP: 6879530             **/
/** Henrique Gemignani Passos Lima      nUSP: 6879634             **/
/** Renan Teruo Carneiro                nUSP: 6514157             **/
/*******************************************************************/

#include "lib/common.h"
#include "logic.h"

int main(int argc, char **argv)
{
    double timeElapsed = 0, timeDifference = 0;
	logicInitialize(argc, argv);
	while(42) {
		timeDifference = logicLoop(timeDifference);
		timeElapsed += timeDifference;
		if(logicGameOver())
			break;
	}
	logicFinish();
    return 0;
}
