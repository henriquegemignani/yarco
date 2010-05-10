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
#include "lib/person.h"
#include "lib/persontable.h"
#include "lib/configuration.h"
#include <time.h>
#include <string.h>

int main(int argc, char **argv)
{
    char opt = 0;
    double genMax = 0, genMin = 999, genAvg = 0, sumPeople = 0,
        curMax, curMin, curAvg, curPeople;
    configuration defaults = configurationInit();
    personTable table;
    int i, customTable = 0, reportOpt = 0, invalidOpt = 1,
        numPeople = PERSON_NUM_INIT;

    argRead(argc, argv, defaults);
    do {
        if (opt != '\n') {
            printf
                ("Executavel de Testes - digite sua opcao\n"
                 "1) rodar normalmente\n"
                 "2) poucas pessoas\n"
                 "3) muitas pessoas\n"
                 "4) baixa velocidade\n"
                 "5) muita velocidade\n"
                 "6) teste de colisoes simples\n"
                 "7) rodar normalmente com relatorio de velocidades\n"
                 "...\n" "0) sair\n");
        }
        opt = getchar();
        if (opt != '\n') {
            invalidOpt = 0;
            switch (opt) {
            case '0':
                exit(0);
                break;
            case '7':
                reportOpt = 1;  /* aproveitando que eh um switch */
            case '1':
                table =
                    personTableInit(defaults->defaultSpeed,
                                    defaults->createRate,
                                    defaults->uniqueGraphic);
                /* nothing to do, it's up to you */
                break;
            case '2':
                table =
                    personTableInit(defaults->defaultSpeed, 0,
                                    defaults->uniqueGraphic);
                numPeople = 3;
                break;
            case '3':
                table =
                    personTableInit(defaults->defaultSpeed, 0,
                                    defaults->uniqueGraphic);
                numPeople = 99;
                break;
            case '4':
                table =
                    personTableInit(1, defaults->createRate,
                                    defaults->uniqueGraphic);
                break;
            case '5':
                table =
                    personTableInit(100, defaults->createRate,
                                    defaults->uniqueGraphic);
                break;
            case '6':
                table = personTableInit(defaults->defaultSpeed, 0, 1);
                numPeople = 4;
                customTable = 1;
                defaults->keepSpeed = 1;
                break;
            default:
                printf("Opcao nao reconhecida: %c. Try again.\n", opt);
                invalidOpt = 1;
                break;
                /*AVISO: Sai do programa. Espero que esse teco seja temporario */
            }
        }
    } while (invalidOpt);

    srand(defaults->randomSeed);
    if (customTable) {
        /*Valores convenientes */
        personTableCreate(table,
                          vectorCreate(1.0 * MAX_X / 4.0,
                                       1.0 * MAX_Y / 4.0), vectorCreate(10,
                                                                        0));
        personTableCreate(table,
                          vectorCreate(1.0 * MAX_X / 4.0,
                                       2.0 * MAX_Y / 4.0), vectorCreate(10,
                                                                        0));
        personTableCreate(table,
                          vectorCreate(3.0 * MAX_X / 4.0,
                                       2.0 * MAX_Y / 4.0),
                          vectorCreate(-10, 0));
        personTableCreate(table,
                          vectorCreate(3.0 * MAX_X / 4.0,
                                       3.0 * MAX_Y / 4.0),
                          vectorCreate(-10, 0));
    } else
        for (i = 0; i < numPeople; i++)
            if (personTableAddNew(table) == ERROR_PERSON_LIMIT_EXCEEDED)
                genError("Erro: limite de naufragos atingido!\n");
    /* AVISO: genError sai do programa */

    /* Inicializa parte grafica */
    graphicInitialize(table);

    for (i = 0; i < defaults->repetitions; i++) {
        printf("\n\nIteracao: %d\n\n", i + 1);
        personTableUpdate(table, defaults->keepSpeed);
        graphicUpdate();
        if (defaults->graphic)
            graphicDraw();
        if (defaults->debugMode)
            personTableDump(table);
        if (reportOpt) {
            curMax = personTableMaxSpeed(table);
            curMin = personTableMinSpeed(table);
            curAvg = personTableAvgSpeed(table);
            printf("\n"
                   "Velocidade minima: %3.2f\n"
                   "Velocidade maxima: %3.2f\n"
                   "Velocidade media: %3.2f\n", curMin, curMax, curAvg);
            if (curMax > genMax)
                genMax = curMax;
            if (curMin < genMin)
                genMin = curMin;
            curPeople = personTableCount(table);
            sumPeople += curPeople;     /*Valor que sera usado para a media ponderada no final */
            genAvg += curAvg * curPeople;       /*Somando termos da media ponderada */
        }
        if (defaults->pause) {
            printf("Aperte Enter para continuar...\n");
            while (getchar() != '\n');
        }
    }
    if (reportOpt) {
        printf("\n" "Velocidade maxima geral: %3.2f\n" "Velocidade minima geral: %3.2f\n" "Velocidade media geral: %3.2f\n", genMax, genMin, genAvg / sumPeople);       /*Passo final da media ponderada */
    }
    graphicFinish();
    personTableRemove(table);
    configurationRemove(defaults);
    return 0;
}
