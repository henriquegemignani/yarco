/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "configuration.h"
#include <time.h>
#include <string.h>

configuration configurationInit()
{
    configuration config;
    AUTOMALLOC(config);

    /* Valores padroes. */
    config->defaultSpeed = PERSON_SPEED_DEFAULT;
    config->createRate = PERSON_CREATE_RATE_DEFAULT;
    config->debugMode = 0;
    config->repetitions = REPETITONS_DEFAULT;
    config->pause = 0;
    config->graphic = 1;
    config->randomSeed = time(NULL);

    return config;
}

void configurationRemove(configuration config)
{
    free(config);
}

void argRead(int argc, char **argv, configuration defaults)
{
    char *argValue;
    if (argFind(argc, argv, "--help", "-h")) {
        printf("Usage: %s [OPTIONS]\n\n"
               "Opcoes:\n"
               "  -h\t--help\t\tImprime isso e sai\n"
               "  -s\t--speed\t\tDetermina a velocidade media dos passageiros. Padrao: %3.2f\n"
               "  -r\t--rate\t\tDetermina o periodo entre 2 novos passageiros. Padrao: %3.2f\n"
               "  -d\t--debug\t\tMostra posicao, velocidade e aceleracao de cada passageiro\n"
               "  -g\t--nographic\tIgnora parte grafica\n"
               "  -R\t--repetitions\tDefine quantas iteracoes o programa mostrara. Padrao: %d\n"
               "  -p\t--pause\t\tDetermina que o programa pausara a cada iteracao.\n"
               "  -S\t--randomseed\tDefine qual vai ser a semente usada para o RNG. Padrao: hora atual\n",
               argv[0], defaults->defaultSpeed, defaults->createRate,
               defaults->repetitions);
        exit(0);
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
    if ((argValue = argVal(argc, argv, "--randomseed", "-S")))
        defaults->randomSeed = atoi(argValue);
}

int argFind(int argc, char **argv, char *argLong, char *argShort)
{
    int i;
    for (i = 1; i < argc; i++)
        if (!strncmp(argv[i], argLong, strlen(argLong)) ||
            (argShort != NULL
             && !strncmp(argv[i], argShort, strlen(argShort))))
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
        if (argShort != NULL) {
            if (!strncmp(argv[i], argShort, len = strlen(argShort))) {
                if (strlen(argv[i]) > len)
                    return argv[i] + len;
                else
                    return argv[i + 1];
            }
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
