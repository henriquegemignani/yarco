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
#include "lib/graphics.h"
#include "lib/persontable.h"
#include "lib/configuration.h"
#include "lib/class.h"
#include <time.h>
#include <sys/time.h>

/* Devolve o tempo atual em microsegundos.*/
long timeInMicrosecond()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (long)tv.tv_sec * 1000000 + (long)tv.tv_usec;
}

int main(int argc, char **argv)
{
    configuration defaults = configurationInit();
    int i, iterationFrame;
    personTable table;
    struct timespec sleepTime, sleepErrorRemaining;
    long frameTimeStart, frameDuration = 0, lastFrameDuration = 0;
    sleepTime.tv_sec = 0; /* Tempo entre frames eh sempre menor que 1s */

    argRead(argc, argv, defaults);

    /* Inicializa tabela de passageiros */
    table =
        personTableInit(defaults->defaultSpeed, defaults->createRate,
                        defaults->uniqueGraphic, defaults->fps);
    srand(defaults->randomSeed);
    for (i = 0; i < PERSON_NUM_INIT; i++)
        if (personTableAddNew(table) == ERROR_PERSON_LIMIT_EXCEEDED)
            genError("Erro: limite de naufragos atingido!\n");
    /* AVISO: genError sai do programa */

    /* Incializa as classes. */
    classInitialize();
    personInitializeClass();

    /* Inicializa parte grafica */
    if (defaults->graphic)
        graphicInitialize(WINDOWED_MODE);   /*pode ser FULLSCREEN_MODE */
    
    iterationFrame = 0; /* se iterationFrame == 0 entao eh uma nova iteracao. Caso contrario,
        armazena quantos frames se passaram desde a ultima iteracao. */
    for (i = 0; i < defaults->repetitions;){
    	if(!iterationFrame)
    		printf("\n\nIteracao: %d\n\n", i + 1);
        
        frameTimeStart = timeInMicrosecond();
        
		iterationFrame = (iterationFrame+1) % defaults->fps;
        personTableUpdate(table, (iterationFrame || defaults->keepSpeed), !iterationFrame );
        
        if (defaults->graphic) {
            graphicUpdate(table);
            graphicDraw();
        }
        
        if (defaults->debugMode)
            personTableDump(table);
        if (defaults->pause && !iterationFrame) {
            printf("Aperte Enter para continuar...\n");
            while (getchar() != '\n');
        } else if (!defaults->noSleep) {
            sleepTime.tv_nsec = 1.0e9 / defaults->fps;
            if( nanosleep(&sleepTime, &sleepErrorRemaining) ) {
                /* Ocorreu algum erro no nanoSleep. */
                /* TODO: tratar erros no nanosleep */
                genError("Erro: nanosleep devolveu nao-zero.\n");
            }
            lastFrameDuration = frameDuration;
            frameDuration = timeInMicrosecond() - frameTimeStart;
        }
        if(!iterationFrame)
        	i++;
    }
    if (defaults->graphic)
        graphicFinish();
    personTableRemove(table);
    configurationRemove(defaults);
    classFinish();
    return 0;
}
