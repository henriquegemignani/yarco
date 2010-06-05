/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include "configuration.h"
#include <time.h>
#include <string.h>

static configuration config = NULL;

configuration configurationInit()
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
    config->uniqueGraphic = 0;
    config->keepSpeed = 0;
    config->fps = DEFAULT_FPS;

    return config;
}

configuration configurationGet() {
	if( config == NULL )
		config = configurationInit();
	return config;
}

void configurationFinish()
{
    free(config);
	config = NULL;
}

void argRead(int argc, char **argv, configuration defaults)
{
    char *argValue;
    if (argFind(argc, argv, "--help", "-h")) {
        printf("Usage: %s [OPTIONS]\n\n", argv[0]);
        printf("Opcoes:\n"
               "  -h\t--help\t\tImprime isso e sai\n");
        printf("  -s\t--speed\t\tDetermina a velocidade media dos passageiros. Padrao: %3.2f\n"
               "  -r\t--rate\t\tDetermina o periodo entre 2 novos passageiros. Padrao: %3.2f\n",
				defaults->defaultSpeed, defaults->createRate);
        printf("  -d\t--debug\t\tMostra posicao, velocidade e aceleracao de cada passageiro\n"
               "  -g\t--nographic\tIgnora parte grafica\n"
               "  -T\t--duration\t\tDefine por quanto tempo o programa rodara'. Padrao: %f\n",
			   defaults->duration);
        printf("  -f\t--fps\t\tControla quantos frames sao exibidos por segundo.\n"
               "  -p\t--pause\t\tDetermina que o programa pausara a cada iteracao. Implica --nosleep.\n"
               "  -S\t--randomseed\tDefine qual vai ser a semente usada para o RNG. Padrao: hora atual\n"
               "  -u\t--unique\t\tUsa todos os caracteres entre 'A' e 'z' para passageiros.\n"
               "  -k\t--keepspeed\t\tPassageiros nao mudam de direcao sem colisoes\n"
               "  -n\t--nosleep\t\tIgnora o sleep.\n");
        /* Separado em diversos printf pq -pedantic reclamou do tamanho da string:
./lib/configuration.c:62: warning: string length �791� is greater than the length �509� ISO C90 compilers are required to support */
        exit(0);
    }
    argValue = argShortFlags(argc, argv, "dpgukn");
    if (argFind(argc, argv, "--debug", "-d") || argValue[0])
        defaults->debugMode = 1;
    if (argFind(argc, argv, "--pause", "-p") || argValue[1])
        defaults->pause = 1;
    if (argFind(argc, argv, "--nographic", "-g") || argValue[2])
        defaults->graphic = 0;
    if (argFind(argc, argv, "--unique", "-u") || argValue[3])
        defaults->uniqueGraphic = 1;
    if (argFind(argc, argv, "--keepspeed", "-k") || argValue[4])
        defaults->keepSpeed = 1;
    if (argFind(argc, argv, "--nosleep", "-n") || argValue[5])
        defaults->noSleep = 1;
    free(argValue);
    if ((argValue = argVal(argc, argv, "--rate", "-r")))
        defaults->createRate = atof(argValue);
    if ((argValue = argVal(argc, argv, "--speed", "-s")))
        defaults->defaultSpeed = atof(argValue);
    if ((argValue = argVal(argc, argv, "--duration", "-T")))
        defaults->duration = atof(argValue);
    if ((argValue = argVal(argc, argv, "--randomseed", "-S")))
        defaults->randomSeed = atoi(argValue);
    if ((argValue = argVal(argc, argv, "--fps", "-f")))
        defaults->fps = atoi(argValue);
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
