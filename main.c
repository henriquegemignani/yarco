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
#include <time.h>
#include <string.h>

struct Configuration {
    double defaultSpeed;
    double createRate;
    int debugMode;
    int repetitions;
    int pause;
    int graphic;
};

void argRead(int argc, char **argv, struct Configuration *defaults);
/* Le argumentos e seta variaveis de acordo com os mesmos */
int argFind(int argc, char **argv, char *argLong, char *argShort);
char *argVal(int argc, char **argv, char *argLong, char *argShort);
char *argShortFlags(int argc, char **argv, char *args);

int main(int argc, char **argv)
{
    struct Configuration defaults;
    int i;
    personTable table;

    defaults.defaultSpeed = PERSON_SPEED_DEFAULT;
    defaults.createRate = PERSON_CREATE_RATE_DEFAULT;
    defaults.debugMode = 0;
    defaults.repetitions = 50;
    defaults.pause = 0;
    defaults.graphic = 1;

    argRead(argc, argv, &defaults);

    /* Inicializa tabela de passageiros */
    table = personTableInit(defaults.defaultSpeed, defaults.createRate);
    srand(time(NULL));
    for (i = 0; i < PERSON_NUM_INIT; i++)
        if (personTableAddNew(table) == ERROR_PERSON_LIMIT_EXCEEDED)
            genError("Erro: limite de naufragos atingido!\n");
    /* AVISO: genError sai do programa */

    /* Inicializa parte grafica */
    graphicInitialize();

    for (i = 0; i < defaults.repetitions; i++) {
        printf("\n\nIteracao: %d\n\n", i + 1);
        personTableUpdate(table);
        graphicUpdate(table);
        if (defaults.graphic)
            graphicDraw();
        if (defaults.debugMode)
            personTableDump(table);
        if (defaults.pause) {
            printf("Aperte Enter para continuar...\n");
            while (getchar() != '\n');
        }
    }
    return 0;
}

void argRead(int argc, char **argv, struct Configuration *defaults)
{
    char *argValue;
    if (argFind(argc, argv, "--help", "-h")) {
        printf("Usage: %s [OPTIONS]\n\n"
               "Opcoes: --speed, --rate, --help, -h, --debug, --repetitions\n"
               "--help, -h: Imprime isso e sai\n"
               "--speed, -h: Determina a velocidade media dos passageiros. Padrao: %3.2f\n"
               "--rate, -r: Determina o periodo entre 2 novos passageiros. Padrao: %3.2f\n"
               "--debug, -d: Mostra posicao, velocidade e aceleracao de cada passageiro\n"
               "--nographic, -g: Ignora parte grafica\n"
               "--repetitions, -R: Define quantas iteracoes o programa mostrara. Padrao: %d\n"
               "--pause, -p: Determina que o programa pausara a cada iteracao.\n",
               argv[0], defaults->defaultSpeed, defaults->createRate,
               defaults->repetitions);
        exit(0);                /*Ohnoes exit no meio do programa! <_< */
    }
    argValue = argShortFlags(argc, argv, "dpg");
    if (argFind(argc, argv, "--debug", "-d") || argValue[0])
        defaults->debugMode = 1;
    if (argFind(argc, argv, "--pause", "-p") || argValue[1])
        defaults->pause = 1;
    if (argFind(argc, argv, "--nographic", "-g") || argValue[2])
        defaults->graphic = 0;
    free(argValue);
    if ((argValue = argVal(argc, argv, "--rate", "-r")))
        defaults->createRate = atof(argValue);
    if ((argValue = argVal(argc, argv, "--speed", "-s")))
        defaults->defaultSpeed = atof(argValue);
    if ((argValue = argVal(argc, argv, "--repetitions", "-R")))
        defaults->repetitions = atoi(argValue);
}

int argFind(int argc, char **argv, char *argLong, char *argShort)
{
    int i;
    for (i = 1; i < argc; i++)
        if (!strncmp(argv[i], argLong, strlen(argLong))
            || !strncmp(argv[i], argShort, strlen(argShort)))
            return i;
    return 0;
}

char *argVal(int argc, char **argv, char *argLong, char *argShort)
{
    int i, len;
    for (i = 0; i < argc; i++) {
        if (!strncmp(argv[i], argLong, len = strlen(argLong))) {
            if (strlen(argv[i]) > len)
                return argv[i] + len;
            else
                return argv[i + 1];
        }
        if (!strncmp(argv[i], argShort, len = strlen(argShort))) {
            if (strlen(argv[i]) > len)
                return argv[i] + len;
            else
                return argv[i + 1];
        }
    }
    return NULL;
}

char *argShortFlags(int argc, char **argv, char *args)
{
    int i, j, k, argsLen;
    char *res;
    argsLen = strlen(args);
    AUTOMALLOCV(res, argsLen);
    for (i = 0; i < argsLen; i++)
        res[i] = 0;
    for (i = 1; i < argc; i++)
        if (argv[i][0] == '-' && argv[i][1] != '-')
            for (j = 1; j < strlen(argv[i]); j++)
                for (k = 0; k < argsLen; k++)
                    if (argv[i][j] == args[k])
                        res[k] = 1;
    return res;
}
