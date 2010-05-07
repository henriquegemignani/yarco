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
};

void argRead(int argc, char **argv, struct Configuration *defaults);
/* Le argumentos e seta variaveis de acordo com os mesmos */
int argFind(int argc, char **argv, char *argLong, char *argShort);
char *argVal(int argc, char **argv, char *argLong, char *argShort);

int main(int argc, char **argv)
{

	printf( "Executavel de Testes - digite sua opcao\n
			1) rodar normalmente\n
				...
			0) sair\n
			");
	char opt = getc();

    struct Configuration defaults;
    int i;

	switch( opt )
	{
		case "0":
			exit(0);
			break;
		case "1":
			defaults.defaultSpeed = PERSON_SPEED_DEFAULT;
			defaults.createRate = PERSON_CREATE_RATE_DEFAULT;
			defaults.debugMode = 0;
			defaults.repetitions = 50;
			defaults.pause = 0;
			break;
	}

	/*
    defaults.defaultSpeed = PERSON_SPEED_DEFAULT;
    defaults.createRate = PERSON_CREATE_RATE_DEFAULT;
    defaults.debugMode = 0;
    defaults.repetitions = 50;
    defaults.pause = 0;

    argRead(argc, argv, &defaults);

	*/

    /* Separado por questoes de clareza do codigo. 
       Possivelmente: criar uma funcao que verifica se um argumento especifico existe, 
       para mais elegancia, embora seja menos eficiente.
       Alias, o numero maximo de pasageiros tambem deveria ser customizavel ou non? */

    /* Inicializa tabela de passageiros */

    personTableInit(defaults.defaultSpeed, defaults.createRate);

	/*
	 *	aqui se muda a persontable na unha
	 * */

    srand(time(NULL));
    for (i = 0; i < PERSON_NUM_INIT; i++)
        if (personTableAddNew() == ERROR_PERSON_LIMIT_EXCEEDED)
            genError("Erro: limite de naufragos atingido!\n");
    /* AVISO: genError sai do programa */

    /* Inicializa parte grafica */
    graphicInitialize();

    for (i = 0; i < defaults.repetitions; i++) {
        printf("\n\nIteracao: %d\n\n", i + 1);
        personTableUpdate();
        graphicUpdate();
        if (defaults.debugMode)
            personTableDump();
        else
            graphicDraw();
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
               "--debug, -d: Mostra posicao, velocidade e aceleracao de cada passageiro, ignorando parte grafica\n"
               "--repetitions, -R: Define quantas iteracoes o programa mostrara. Padrao: %d\n"
               "--pause, -p: Determina que o programa pausara a cada iteracao.\n",
               argv[0], defaults->defaultSpeed, defaults->createRate,
               defaults->repetitions);
        exit(0);                /*Ohnoes exit no meio do programa! <_< */
    }
    if (argFind(argc, argv, "--debug", "-d"))
        defaults->debugMode = 1;
    if (argFind(argc, argv, "--pause", "-p"))
        defaults->pause = 1;
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
