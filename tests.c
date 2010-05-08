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
#include "lib/person.h"
#include "lib/persontable.h"
#include "lib/configuration.h"
#include <time.h>
#include <string.h>

int main(int argc, char **argv)
{
    char opt = 0;
    double genMax = 0, genMin = 999, genAvg = 0, sumPeople =
        0, curMax, curMin, curAvg, curPeople;
    configuration defaults = configurationInit();
    personTable table;
    int i, reportOpt = 0, keepSpeed = 0, invalidOpt = 1, numPeople =
        PERSON_NUM_INIT;



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
                 "6) teste de colisoes\n"
                 "7) rodar normalmente com relatorio de velocidades\n"
                 "...\n" "0) sair\n");
        }
        opt = getchar();
        if (opt != '\n') {
            switch (opt) {
            case '0':
                exit(0);
                invalidOpt = 0;
                break;
            case '1':
                table =
                    personTableInit(defaults->defaultSpeed,
                                    defaults->createRate);
                invalidOpt = 0;
                /* nothing to do, it's up to you */
                break;
            case '2':
                //printf("era pra ter sÃ 3 pessoas aqui!!!\n");
                table = personTableInit(defaults->defaultSpeed, 0);
                numPeople = 3;
                invalidOpt = 0;
                break;
            case '3':
                table = personTableInit(defaults->defaultSpeed, 0);
                numPeople = 99;
                invalidOpt = 0;
                break;
            case '4':
                table = personTableInit(1, defaults->createRate);
                invalidOpt = 0;
                break;
            case '5':
                table = personTableInit(100, defaults->createRate);
                invalidOpt = 0;
                break;
            case '6':
                /* mais um pedaco de codigo q sera uma icognita rodando
                 * atualmente: Notworking
                 * */
                /* sorry guys, muito sono pra terminar isso
                   person p = personTableAddNew();
                   p->pos = vectorCreate( 10, 10 );
                   p->vel = ( 8, 0 );
                   p = personTableAddNew();
                   p->pos = vectorCreate( 20, 10 );
                   p->vel = ( 0, 0 );
                   p = personTableAdd();
                   p->pos = vectorCreate( 15, 15 );
                   p->vel = vectorCreate( 0, 0 );
                   p = personTableAdd();
                   p->pos = vectorCreate( 15, 25 );
                   p->vel = vectorCreate( 0, -5 );
                 */
                numPeople = 0;
                invalidOpt = 0;
                break;
            case '7':
                table =
                    personTableInit(defaults->defaultSpeed,
                                    defaults->createRate);
                reportOpt = 1;
                invalidOpt = 0;
                break;
            default:
                printf("Opcao nao reconhecida: %c. Try again.\n", opt);
                invalidOpt = 1;
                break;
                /*AVISO: Sai do programa. Espero que esse teco seja temporario */
            }
        }
    } while (invalidOpt);

    /* Inicializa tabela de passageiros */

    /*
       personTableInit(defaults->defaultSpeed, defaults->createRate);
     */
    /*  aqui se muda a persontable na unha */



    srand(defaults->randomSeed);
    for (i = 0; i < numPeople; i++)
        if (personTableAddNew(table) == ERROR_PERSON_LIMIT_EXCEEDED)
            genError("Erro: limite de naufragos atingido!\n");


    /* AVISO: genError sai do programa */

    /* Inicializa parte grafica */
    graphicInitialize();

    for (i = 0; i < defaults->repetitions; i++) {
        printf("\n\nIteracao: %d\n\n", i + 1);
        personTableUpdate(table, keepSpeed);
        graphicUpdate(table);
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
            sumPeople += curPeople;
            genAvg += curAvg * curPeople;
        }
        if (defaults->pause) {
            printf("Aperte Enter para continuar...\n");
            while (getchar() != '\n');
        }
    }
    if (reportOpt) {
        printf("\n"
               "Velocidade maxima geral: %3.2f\n"
               "Velocidade minima geral: %3.2f\n"
               "Velocidade media geral: %3.2f\n",
               genMax, genMin, genAvg / sumPeople);
    }
    graphicFinish();
    personTableRemove(table);
    configurationRemove(defaults);
    return 0;
}
