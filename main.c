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
    int pedantic; /* morre em qualquer erro? */
};

void argRead(int argc, char **argv, struct Configuration *defaults );
/* Le argumentos e seta variaveis de acordo com os mesmos */
int argFind(int argc, char **argv, char *argLong, char *argShort);
char *argVal(int argc, char **argv, char *argLong, char *argShort);

int main(int argc, char ** argv){
  struct Configuration defaults;
  int i;
  
  defaults.defaultSpeed = PERSON_SPEED_DEFAULT;
  defaults.createRate = PERSON_CREATE_RATE_DEFAULT;
  defaults.debugMode = 0;
  defaults.repetitions = 50;
  defaults.pedantic = 1;

  argRead(argc, argv, &defaults); 
  /* Separado por questoes de clareza do codigo. 
  Possivelmente: criar uma funcao que verifica se um argumento especifico existe, 
    para mais elegancia, embora seja menos eficiente.
  Alias, o numero maximo de pasageiros tambem deveria ser customizavel ou non? */

  /* Inicializa tabela de passageiros */
  personTableInit( defaults.defaultSpeed, defaults.createRate );
  srand( time( NULL ) );
  for( i = 0; i < PERSON_NUM_INIT; i++ )
    if( personTableAddNew() == ERROR_PERSON_LIMIT_EXCEEDED )
      genError("Erro: limite de naufragos atingido!\n");
      /* AVISO: genError sai do programa */
  
  /* Inicializa parte grafica */
  graphicInitialize();

  for( i = 0; i < defaults.repetitions; i++){
    printf("\n\nIteracao: %d\n\n", i+1);
    personTableUpdate();
    graphicUpdate();
	if( defaults.debugMode )
		personTableDump();
	else
		graphicDraw();
  }
  return 0;
}

/*void argRead(int argc, char **argv, struct Configuration *defaults ) {
  int i;
  for( i = 1; i < argc; i++ ) {
    if( strcmp( argv[i], "-h" ) == 0 || strcmp( argv[i], "--help" ) == 0 ) {
      printf("Usage: %s [OPTIONS]\n\n"
	     "Opcoes: --speed, --rate, --help, -h, --debug, --repetitions\n"
	     "--help, -h: Imprime isso e sai\n"
	     "--speed: Determina a velocidade media dos passageiros. Padrao: %3.2f\n"
	     "--rate: Determina o periodo entre 2 novos passageiros. Padrao: %3.2f\n"
	     "--debug: Mostra posicao, velocidade e aceleracao de cada passageiro, ignorando parte grafica\n"
	     "--repetitions: Define quantas iteracoes o programa mostrara. Padrao: %d\n"
             "--pedantic: Define se o programa para a execucao em erros. Padrao: %s\n",
	     argv[0], defaults->defaultSpeed, defaults->createRate, defaults->repetitions,
            defaults->pedantic ? "True" : "False"
         );
	 exit(0);*//*Ohnoes exit no meio do programa! <_< *//*
    }
    if( strncmp( argv[i], "--speed", 7 ) == 0 ) { *//* supoe que usuario colocou um numero *//*
       if( strlen(argv[i]) > 7 )*/ /* parametro da forma '--speedX' */ 
    /* Jura que vai suportar parametro da forma speedX? Isso vai complicar na hora de dar 
    suporte a argumento da forma -s X, que, IMO, é mais importante. E vai ter que dar 
    suporte a -sX se a gente fizer isso... Especialmente agravante dado que ha suporte a -h.
    ~Miojo*//*
        defaults->defaultSpeed = atof(argv[i] + 7);
	else  */ /* parametro da forma '--speed X' *//*
        defaults->defaultSpeed = atof(argv[++i]);
      continue;
    }
    if( strncmp( argv[i], "--rate", 6 ) == 0 ) {
      if( strlen(argv[i]) > 6 )
        defaults->createRate = atof(argv[i] + 6);
      else
        defaults->createRate = atof(argv[++i]);
      continue;
    }
    if( strncmp( argv[i], "--debug", 7 ) == 0 ) {
      defaults->debugMode = 1;
      continue;
    }
    if( strncmp( argv[i], "--repetitions", 13 ) == 0 ) {
      if( strlen(argv[i]) > 13 )
        defaults->repetitions = atoi(argv[i] + 13);
      else
        defaults->repetitions = atoi(argv[++i]);
      continue;
    }
    if( strncmp( argv[i], "--pedantic", 10 ) == 0 ) {
      if( strlen(argv[i]) > 10 )
        defaults->pedantic = atoi(argv[i] + 13);
      else
        defaults->pedantic = atoi(argv[++i]);
      continue;
    }
  }
}*/

void argRead (int argc, char **argv, struct Configuration *defaults ){
  char *argValue;
  if( argFind( argc, argv, "--help", "-h") ){
    printf("Usage: %s [OPTIONS]\n\n"
	   "Opcoes: --speed, --rate, --help, -h, --debug, --repetitions\n"
	   "--help, -h: Imprime isso e sai\n"
	   "--speed, -h: Determina a velocidade media dos passageiros. Padrao: %3.2f\n"
	   "--rate, -r: Determina o periodo entre 2 novos passageiros. Padrao: %3.2f\n"
	   "--debug, -d: Mostra posicao, velocidade e aceleracao de cada passageiro, ignorando parte grafica\n"
	   "--repetitions, -R: Define quantas iteracoes o programa mostrara. Padrao: %d\n"
	   "--pedantic, -p: Define se o programa para a execucao em erros. Padrao: %s\n",
	   argv[0], defaults->defaultSpeed, defaults->createRate, defaults->repetitions,
	   defaults->pedantic ? "True" : "False"
	   );
    exit(0);/*Ohnoes exit no meio do programa! <_< */
  }
  if( argFind( argc, argv, "--debug", "-d") )
    defaults -> debugMode = 1;    
  if( ( argValue = argVal( argc, argv, "--rate", "-r") ) )
    defaults -> createRate = atof( argValue );
  if( ( argValue = argVal( argc, argv, "--speed", "-s") ) )
    defaults -> defaultSpeed = atof( argValue );
  if( ( argValue = argVal( argc, argv, "--repetitions", "-R" ) ) )
    defaults -> repetitions = atoi( argValue );
  if( ( argValue = argVal( argc, argv, "--pedantic", "-p") ) )
    defaults -> pedantic = atoi( argValue );
}

int argFind(int argc, char **argv, char *argLong, char *argShort){
  int i;
  for( i = 1; i < argc; i++)
    if( !strncmp( argv[i], argLong, strlen( argLong ) ) || !strncmp( argv[i], argShort, strlen( argShort ) ) )
      return i;
  return 0;
}

char *argVal(int argc, char **argv, char *argLong, char *argShort){
  int i, len;
  for(i = 0; i < argc; i++){
    if( !strncmp ( argv[i], argLong, len = strlen( argLong ) ) ){
      if( strlen( argv[i] ) > len )
	return argv[i]+len;
      else
	return argv[i+1];
    }
    if( !strncmp ( argv[i], argShort, len = strlen( argShort ) ) ){
      if( strlen( argv[i] ) > len )
	return argv[i]+len;
      else
	return argv[i+1];
    }
  }
  return NULL;
}
