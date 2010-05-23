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

int main(int argc, char **argv)
{
    configuration defaults = configurationInit();
    int i, frameNum;
    personTable table;

    argRead(argc, argv, defaults);

    /* Inicializa tabela de passageiros */
    table =
        personTableInit(defaults->defaultSpeed, defaults->createRate,
                        defaults->uniqueGraphic);
    srand(defaults->randomSeed);
    for (i = 0; i < PERSON_NUM_INIT; i++)
        if (personTableAddNew(table) == ERROR_PERSON_LIMIT_EXCEEDED)
            genError("Erro: limite de naufragos atingido!\n");
    /* AVISO: genError sai do programa */

    /* Incializa as classes. */
    classInitialize();
    personInitializeClass(defaults->keepSpeed);

    /* Inicializa parte grafica */
    graphicInitialize(WINDOWED_MODE);   /*pode ser FULLSCREEN_MODE */
    frameNum = 0;
    for (i = 0; i < defaults->repetitions;){
    	if(!frameNum)
    		printf("\n\nIteracao: %d\n\n", i + 1);
		frameNum = (frameNum+1)%_FPS;
        personTableUpdate(table, (frameNum || defaults->keepSpeed));
        graphicUpdate(table);
        if (defaults->graphic)
            graphicDraw();
        if (defaults->debugMode)
            personTableDump(table);
        if (defaults->pause && !frameNum) {
            printf("Aperte Enter para continuar...\n");
            while (getchar() != '\n');
        }
        if(!frameNum)
        	i++;
    }
    graphicFinish();
    personTableRemove(table);
    configurationRemove(defaults);
    classFinish();
    return 0;
}
