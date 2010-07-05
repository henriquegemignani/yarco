/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "lib/common.h"
#include "config/configuration.h"
#include "lib/graphics.h"
#include "lib/objecttable.h"
#include "lib/class.h"
#include "class/person.h"
#include "class/ship.h"
#include "class/coral.h"
#include "class/boat.h"
#include <time.h>
#include <sys/time.h>
#include <allegro.h>
#include <allegro/keyboard.h>

/* Devolve o tempo atual em microsegundos.*/
long timeInMicrosecond()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long) tv.tv_sec * 1000000 + (long) tv.tv_usec;
}

volatile int close_button_pressed = 0;
void loginAllegroCloseButtonHandler(void)
{
	close_button_pressed = 1;
}
END_OF_FUNCTION(loginAllegroCloseButtonHandler)

static long timeToOffset = 0;
void logicSleep() {
#ifndef WIN32
	struct timespec sleepTime, sleepErrorRemaining;
	sleepTime.tv_sec = 0;       /* Tempo entre frames eh sempre menor que 1s */
    sleepTime.tv_nsec = 1.0e9 / configurationGet()->fps;
	/* Se o frame anterior demorou menos do que deveria, espera mais.
	E se demorou mais do que devia, espera menos no atual. Somente se
	nao for o primeiro frame. */

	if (sleepTime.tv_nsec < -timeToOffset) {
		timeToOffset += sleepTime.tv_nsec;
		sleepTime.tv_nsec = 0;
	} else {
		sleepTime.tv_nsec += timeToOffset;
	}
	if (sleepTime.tv_nsec > 0) {
		if (nanosleep(&sleepTime, &sleepErrorRemaining)) {
			/* Ocorreu algum erro no nanoSleep. */
			fprintf(stderr, "sleepTime:\n\tsec: %ld\nnsec: %ld\n",
					sleepTime.tv_sec, sleepTime.tv_nsec);
			genError("Erro: nanosleep devolveu nao-zero.\n");
		}
	}
#endif
}


void logicInitialize(int argc, char* argv[]) {
	configuration defaults;
	int i, max;
	
	configurationInit("config.ini");
	defaults = configurationGet();
    argRead(argc, argv, defaults);
	
    srand(defaults->randomSeed);
	
    /* Inicializa as classes. */
    classInitialize();
    personInitializeClass();
    shipInitializeClass();
    coralInitializeClass();
    boatInitializeClass();
	
	/* Garante que a tabela de objetos foi inicializada. */
	objectTableGet();
	
	max = configGetValue("General", "NumPlayers").num;
	for(i = 0; i < max; ++i)
		boatAddNewToTable(i);
	
    /* Asimov */
    objectTableAddObject(shipNew(createTexture(80, 80, 80, TEX_HORIZONTAL_RETANGLE)));
	
	/* Pessoas */
    for (i = 0; i < defaults->numPeople; i++)
        if (personAddNewToTable(defaults->defaultSpeed, defaults->verbose) == NULL)
            genError("Erro: limite de objetos atingido!\n");
			
	/* Corais */
    for (i = 0; i < defaults->numCorals; i++)
        if (coralAddNewToTable(defaults->verbose) == NULL)
            genError("Erro: limite de objetos atingido!\n");
			
	if (allegro_init())
        genError("Erro em inicializar o allegro. Se voce esta utilizando modo texto, tente --nographic\n");
	graphicInitialize(configGetValue("General", "Fullscreen").num);
    if (install_keyboard())
        genError("Falha ao incializar teclado!\n");
		
    LOCK_FUNCTION(loginAllegroCloseButtonHandler);
    set_close_button_callback(loginAllegroCloseButtonHandler);
}

double logicLoop(double timeDifference) {
	static double 
		timeSinceLastIteration = 0,
		newPersonInterval = 0, 
		discoInterval = 0,
		timeLeftToClose = 0;
	static int closeButton = -1, closePressed = 0;
	configuration defaults = configurationGet();
	long frameTimeStart = timeInMicrosecond();
	
	if ((newPersonInterval -= timeDifference) < 0 && defaults->createPeriod > 0) {
		newPersonInterval += randomizeAround(defaults->createPeriod, STD_DIST);
		personAddNewToTable(defaults->defaultSpeed, defaults->verbose);
    }
	
	objectTableUpdate(timeDifference, timeSinceLastIteration > 1);
	
	if(closeButton == -1) closeButton = configGetValue("General", "ButtonExit").num;
	if(key[closeButton]) {
		if(!closePressed) {
			closePressed = 1;
			if(timeLeftToClose > 0)
				close_button_pressed = 1;
			timeLeftToClose = 1.0f;
		}
	} else {
		closePressed = 0;
		timeLeftToClose -= timeDifference;
	}
	
	if (defaults->disco > 0) {
        discoInterval -= timeDifference;
        if (discoInterval <= 0) {
            discoInterval = defaults->disco;
            objectTableRandColor();
        }
    }
    graphicUpdate();
    graphicDraw();
	
	
	
	if (defaults->debugMode && timeSinceLastIteration > 1)
        objectTableDump();
	
	if (!defaults->noSleep)
		logicSleep();
	
	if(timeSinceLastIteration > 1 && defaults->pause) {
        printf("Aperte Enter para continuar...\n");
        while (getchar() != '\n');
	} else {
        timeDifference = (timeInMicrosecond() - frameTimeStart);
        timeToOffset += 1.0e9 / defaults->fps - timeDifference * 1.0e3;
		/* E agora em segundos. */
        timeDifference = (timeInMicrosecond() - frameTimeStart) / 1.0e6;
	}
	
    if (timeSinceLastIteration > 1)
        timeSinceLastIteration -= 1;
	timeSinceLastIteration += timeDifference;
	return timeDifference;
}

void logicFinish() {
    graphicFinish();
	allegro_exit();
    objectTableFinish();
    configurationFinish("config.ini");
    classFinish();
}

int logicGameOver() {
	/* TODO: inserir logica de fim de jogo. */
	return close_button_pressed;
}
