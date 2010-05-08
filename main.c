/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/**                                                               **/
/** Nomes:                                                        **/
/** Andre Mesquita Pereira              nUSP: 6879530             **/
/** Henrique Gemignani Passos Lima      nUSP: 6879634             **/
/** Renan Teruo Carneiro                nUSP: 6514157             **/
/*******************************************************************/

/* #include <stdio.h> -- ta no common.h agora */
#include "lib/common.h"
#include "lib/graphics.h"
#include "lib/persontable.h"
#include "lib/configuration.h"

int main(int argc, char **argv)
{
    configuration defaults = configurationInit();
    int i;
    personTable table;

    argRead(argc, argv, defaults);

    /* Inicializa tabela de passageiros */
    table = personTableInit(defaults->defaultSpeed, defaults->createRate);
    srand(defaults->randomSeed);
    for (i = 0; i < PERSON_NUM_INIT; i++)
        if (personTableAddNew(table) == ERROR_PERSON_LIMIT_EXCEEDED)
            genError("Erro: limite de naufragos atingido!\n");
    /* AVISO: genError sai do programa */

    /* Inicializa parte grafica */
    graphicInitialize();

    for (i = 0; i < defaults->repetitions; i++) {
        printf("\n\nIteracao: %d\n\n", i + 1);
        personTableUpdate(table, 0);
        graphicUpdate(table);
        if (defaults->graphic)
            graphicDraw();
        if (defaults->debugMode)
            personTableDump(table);
        if (defaults->pause) {
            printf("Aperte Enter para continuar...\n");
            while (getchar() != '\n');
        }
    }
    graphicFinish();
    personTableRemove(table);
    configurationRemove(defaults);
    return 0;
}
