/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "../lib/common.h"
#include "configuration.h"
#include <time.h>
#include <string.h>

static configuration config = NULL;

configuration LEGACY_configurationInit()
{
    configuration config;
    AUTOMALLOC(config);

    /* Valores padrao. */
    config->defaultSpeed = PERSON_SPEED_DEFAULT;
    config->createRate = PERSON_CREATE_RATE_DEFAULT;
    config->debugMode = 0;
    config->duration = DURATION_DEFAULT;
    config->pause = 0;
    config->graphic = 1;
    config->randomSeed = time(NULL);
    config->keepSpeed = 0;
    config->fps = DEFAULT_FPS;
    config->accel = DEFAULT_ACCEL;
    config->friction = DEFAULT_FRICTION;
    config->turnRate = DEFAULT_TURNRATE;
    config->lives = DEFAULT_LIVES;
    config->timeStuck = DEFAULT_TIME_STUCK;
    config->verbose = 0;
    config->numPeople = PERSON_NUM_INIT;
    config->numCorals = CORAL_NUM_INIT;
    config->disco = 0;

    return config;
}

configuration configurationGet()
{
    if (config == NULL)
        config = LEGACY_configurationInit();
    return config;
}

void LEGACY_configurationFinish()
{
    free(config);
    config = NULL;
}

void argRead(int argc, char **argv, configuration defaults)
{
    char *argValue;
    if (argFind(argc, argv, "--help", "-h")) {
        printf("Usage: %s [OPTIONS]\n\n", argv[0]);
        printf("Opcoes:\n" "  -h\t--help\t\tImprime isso e sai\n");
        printf
            ("  -s\t--speed\t\tDetermina a velocidade media dos passageiros. Padrao: %3.2f\n"
             "  -r\t--rate\t\tDetermina o periodo entre 2 novos passageiros. Padrao: %3.2f\n"
             "  -c\t--corals\t\tDetermina o numero de corais. Padrao: %d\n"
             "  -p\t--people\t\tDeermina o numero inicial de pessoas. Padrao: %d\n",
             defaults->defaultSpeed, defaults->createRate,
             defaults->numCorals, defaults->numPeople);
        printf
            ("  -d\t--debug\t\tMostra posicao, velocidade e aceleracao de cada passageiro\n"
             "  -v\t--verbose\t\tFala mais coisas\n"
             "  -g\t--nographic\tIgnora parte grafica\n"
             "  -T\t--duration\t\tDefine por quanto tempo o programa rodara'. Padrao: %f\n",
             defaults->duration);
        printf
            ("  -F\t--fps\t\tControla quantos frames sao exibidos por segundo.\n"
             "  -P\t--pause\t\tDetermina que o programa pausara a cada iteracao. Implica --nosleep.\n"
             "  -S\t--randomseed\tDefine qual vai ser a semente usada para o RNG. Padrao: hora atual\n"
             "  -k\t--keepspeed\t\tPassageiros nao mudam de direcao sem colisoes\n"
             "  -n\t--nosleep\t\tIgnora o sleep, rodando o maximo de frames por segundo possivel.\n");
        printf
            ("  -a\t--acceleration\t\tDetermina a aceleracao dos botes. Padrao: %3.2f\n"
             "  -t\t--turnrate\t\tDetermina, em radianos, quantos graus o bote pode virar por segundo\n"
             "  -f\t--friction\t\tDetermina a desaleracao dos botes pelo atrito. Padrao: %3.2f\n"
             "  -l\t--lives\t\tDetermina quantas vezes o bote pode bater num coral antes de encalhar. Padrao: %d\n"
             "  -b\t--timestuck\t\tDetermina quanto tempo o bote fica encalhado antes de reaparecer. Padrao: %3.2f\n",
             defaults->accel, defaults->friction, defaults->lives,
             defaults->timeStuck);
        /* Separado em diversos printf pq -pedantic reclamou do tamanho da string:
           ./lib/configuration.c:62: warning: string length �791� is greater than the length �509� ISO C90 compilers are required to support */
        exit(0);
    }
    argValue = argShortFlags(argc, argv, "dPgknv");
    if (argFind(argc, argv, "--debug", "-d") || argValue[0])
        defaults->debugMode = 1;
    if (argFind(argc, argv, "--pause", "-P") || argValue[1])
        defaults->pause = 1;
    if (argFind(argc, argv, "--nographic", "-g") || argValue[2])
        defaults->graphic = 0;
    if (argFind(argc, argv, "--keepspeed", "-k") || argValue[3])
        defaults->keepSpeed = 1;
    if (argFind(argc, argv, "--nosleep", "-n") || argValue[4])
        defaults->noSleep = 1;
    if (argFind(argc, argv, "--verbose", "-v") || argValue[5])
        defaults->verbose = 1;
    if (argFind(argc, argv, "--christmas", NULL))
        defaults->disco = 0.1;
    free(argValue);
    if ((argValue = argVal(argc, argv, "--rate", "-r")))
        defaults->createRate = atof(argValue);
    if ((argValue = argVal(argc, argv, "--speed", "-s")))
        defaults->defaultSpeed = atof(argValue);
    if ((argValue = argVal(argc, argv, "--duration", "-T")))
        defaults->duration = atof(argValue);
    if ((argValue = argVal(argc, argv, "--randomseed", "-S")))
        defaults->randomSeed = atoi(argValue);
    if ((argValue = argVal(argc, argv, "--fps", "-F")))
        defaults->fps = atoi(argValue);
    if ((argValue = argVal(argc, argv, "--acceleration", "-a")))
        defaults->accel = atof(argValue);
    if ((argValue = argVal(argc, argv, "--turnrate", "-t")))
        defaults->turnRate = atof(argValue);
    if ((argValue = argVal(argc, argv, "--friction", "-f")))
        defaults->friction = atof(argValue);
    if ((argValue = argVal(argc, argv, "--lives", "-l")))
        defaults->lives = atoi(argValue);
    if ((argValue = argVal(argc, argv, "--timestuck", "-b")))
        defaults->timeStuck = atof(argValue);
    if ((argValue = argVal(argc, argv, "--people", "-p")))
        defaults->numPeople = atoi(argValue);
    if ((argValue = argVal(argc, argv, "--corals", "-c")))
        defaults->numCorals = atoi(argValue);
    if ((argValue = argVal(argc, argv, "--disco", NULL)))
        defaults->disco = atof(argValue);
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
                return argv[i] + len;   /*Argumentos da forma -aX ou --argumentX */
            else
                return argv[i + 1];     /*Argumentos da forma -a X ou --argument X */
        }
        if (argShort != NULL) {
            if (!strncmp(argv[i], argShort, len = strlen(argShort))) {
                if (strlen(argv[i]) > len)
                    return argv[i] + len;       /*Argumentos da forma -aX ou --argumentX */
                else
                    return argv[i + 1]; /*Argumentos da forma -a X ou --argument X */
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
        if (argv[i][0] == '-' && argv[i][1] != '-')     /*Sumariamente: Para cada agumento de main que comeca com '-' mas nao com "--"... */
            for (j = 1; j < strlen(argv[i]); j++)
                for (k = 0; k < argsLen; k++)
                    if (argv[i][j] == args[k])  /*...verifica, char a char, se cada letra da string args esta presente */
                        res[k] = 1;
    return res;
}