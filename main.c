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
#include "lib/configuration.h"
#include "lib/graphics.h"
#include "lib/objecttable.h"
#include "lib/class.h"
#include "class/person.h"
#include "class/ship.h"
#include "class/coral.h"
#include "class/boat.h"
#include <time.h>
#include <sys/time.h>

#define NUM_PLAYERS 1

/* Devolve o tempo atual em microsegundos.*/
long timeInMicrosecond()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (long) tv.tv_sec * 1000000 + (long) tv.tv_usec;
}

int main(int argc, char **argv)
{
    configuration defaults = configurationGet();
    int i, numFrame = 0;
    objectTable table;
    double 
		timeElapsed = 0,
		timeDifference = 0,
		timeSinceLastIteration = 0,
        newPersonInterval;
	ship asimov;
	boat players[NUM_PLAYERS];
		
    struct timespec sleepTime, sleepErrorRemaining;
    long frameTimeStart, timeToOffset = 0;
    sleepTime.tv_sec = 0;       /* Tempo entre frames eh sempre menor que 1s */

    argRead(argc, argv, defaults);

    srand(defaults->randomSeed);

    /* Incializa as classes. */
    classInitialize();
    personInitializeClass();
	shipInitializeClass();
	coralInitializeClass();
	boatInitializeClass();


    /* Inicializa tabela de objetos */
    table = objectTableGet();
	
	players[0] = boatAddNewToTable(0xFF0000);
	/* players[1] = boatAddNewToTable(0x0000FF); */
	
	asimov = shipNew( createTexture(randInt(40,200), randInt(40,200), randInt(40,200),
		TEX_HORIZONTAL_RETANGLE ) );
	objectTableAddObject(asimov);
	
    for (i = 0; i < PERSON_NUM_INIT; i++)
        if (personAddNewToTable(defaults->defaultSpeed) == NULL)
            genError("Erro: limite de objetos atingido!\n");
    /* AVISO: genError sai do programa */
    newPersonInterval = randomizeAround(defaults->createRate, STD_DIST);

    for (i = 0; i < CORAL_NUM_INIT; i++)
        if (coralAddNewToTable() == NULL)
            genError("Erro: limite de objetos atingido!\n");

    /* Inicializa parte grafica */
    if (defaults->graphic)
        graphicInitialize(WINDOWED_MODE);       /*pode ser FULLSCREEN_MODE */

    i = 0;
    while (timeElapsed < defaults->duration) {
        if (timeSinceLastIteration > 1)
            printf("Iteracao: %d\n", ++i);

        frameTimeStart = timeInMicrosecond();

        if ((newPersonInterval -= timeDifference) < 0) {
            newPersonInterval +=
                randomizeAround(defaults->createRate, STD_DIST);
            personAddNewToTable(defaults->defaultSpeed);
			/* TODO(newPersonInterval): verificar se ja tem o numero de pessoas desejadas.
				Atualmente ta tentando criar e ignora se teve erro. */
			/* TODO(newPersonInterval): implementar limite de pessoas. Atualmente tem mais pessoas
				ate atingir o limite de objetos. */
        }

        objectTableUpdate(timeDifference, timeSinceLastIteration > 1);

        if (defaults->graphic) {
            graphicUpdate(table);
            graphicDraw();
        }

        if (defaults->debugMode && timeSinceLastIteration >= 1)
            objectTableDump();

        if( (defaults->pause && timeSinceLastIteration >= 1) ) {
			printf("Aperte Enter para continuar...\n");
            while (getchar() != '\n');
			
		} else if (!defaults->noSleep) {
			sleepTime.tv_nsec = 1.0e9 / defaults->fps;
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
					/* TODO: tratar erros no nanosleep */
					printf("sleepTime:\n\tsec: %ld\nnsec: %ld\n",
						   sleepTime.tv_sec, sleepTime.tv_nsec);
					genError("Erro: nanosleep devolveu nao-zero.\n");
				}
			}
		}
		
		/* Tempo do frame atual (que acabou de terminar), em microsegundos. */
		if( !(defaults->pause && timeSinceLastIteration >= 1) ) {
			timeDifference = (timeInMicrosecond() - frameTimeStart);
			timeToOffset += 1.0e9 / defaults->fps - timeDifference * 1.0e3;

			/* E agora em segundos. */
			timeDifference = (timeInMicrosecond() - frameTimeStart) / 1.0e6;
		}
		timeElapsed += timeDifference;

        if (timeSinceLastIteration > 1) {
            timeSinceLastIteration -= 1;
            printf("\tNum Frames: %d\n", numFrame + 1);
            numFrame = 0;
        } else {
            numFrame++;
        }
        timeSinceLastIteration += timeDifference;
    }
    if (defaults->graphic)
        graphicFinish();
    objectTableFinish();
    configurationFinish();
    classFinish();
    return 0;
}
