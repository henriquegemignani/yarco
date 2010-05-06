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

void argRead(int argc, char **argv, double *defaultSpeed, double *createRate, int *debugMode, int *repetitions);
/*Le argumentos e seta variaveis de acordo com os mesmos*/

int main(int argc, char ** argv){
  int i, debugMode = 0, repetitions = 100;
  double defaultSpeed = PERSON_SPEED_DEFAULT, createRate = PERSON_CREATE_RATE_DEFAULT;

  argRead(argc, argv, &defaultSpeed, &createRate, &debugMode, &repetitions); 
  /* Separado por questoes de clareza do codigo. */
  /* Possivelmente: criar uma funcao que verifica se um argumento especifico existe, para mais elegancia, embora seja menos eficiente */
  /* Alias, o numero maximo de pasageiros tambem deveria ser customizavel ou non? */

  /*Inicializa tabela de passageiros*/
  personTableInit( defaultSpeed, createRate );
  srand( time( NULL ) );
  for( i = 0; i < PERSON_NUM_INIT; i++ )
    if( personTableAddNew() == ERROR_PERSON_LIMIT_EXCEEDED ) {
      //printf("Erro: limite de naufragos atingido!\n");
      //exit(1);
      genError("Erro: limite de naufragos atingido!\n");
      /*AVISO: genError sai do programa*/
    }
  /*Inicializa parte grafica*/
  graphicInitialize();
  // i = 1;
  //printf("HELL, IT'S LOOPING TIME\n");
  //while(i) {
  for( i = 0; i < repetitions; i++){
    printf("\n\nIteracao: %d\n\n", i+1);
    personTableUpdate();
    graphicUpdate();
	if( debugMode )
		personTableDump();
	else
		graphicDraw();
	//scanf(" %d", &i);
  }
  return 0;
}

void argRead(int argc, char **argv, double *defaultSpeed, double *createRate, int *debugMode, int *repetitions){
  int i;
  for( i = 1; i < argc; i++ ) {
    if( strcmp( argv[i], "-h" ) == 0 || strcmp( argv[i], "--help" ) == 0 ) {
      printf("Usage: %s [OPTIONS]\n\n"
	     "Opcoes: --speed, --rate, --help, -h, --debug, --repetitions\n"
	     "--help, -h: Imprime isso e sai\n"
	     "--speed: Determina a velocidade media dos passageiros. Padrao: %3.2f\n"
	     "--rate: Determina o periodo entre 2 novos passageiros. Padrao: %3.2f\n"
	     "--debug: Mostra posicao, velocidade e aceleracao de cada passageiro, ignorando parte grafica\n"
	     "--repetitions: Define quantas iteracoes o programa mostrara. Padrao: %d\n",
	     argv[0], *defaultSpeed, *createRate, *repetitions );
      exit(0);/*Ohnoes exit no meio do programa! <_< */
    }
    if( strncmp( argv[i], "--speed", 7 ) == 0 ) { /* supoe que usuario colocou um numero */
      if( strlen(argv[i]) > 7 ) /* parametro da forma '--speedX' */ /*Jura que vai suportar parametro da forma speedX? Isso vai complicar na hora de dar suporte a argumento da forma -s X, que, IMO, é mais importante. E vai ter que dar suporte a -sX se a gente fizer isso... Especialmente agravante dado que ha suporte a -h.~Miojo*/
        *defaultSpeed = atof(argv[i] + 7);
      else   /* parametro da forma '--speed X' */
        *defaultSpeed = atof(argv[++i]);
      continue;
    }
    if( strncmp( argv[i], "--rate", 6 ) == 0 ) {
      if( strlen(argv[i]) > 6 )
        *createRate = atof(argv[i] + 6);
      else
        *createRate = atof(argv[++i]);
      continue;
    }
    if( strncmp( argv[i], "--debug", 7 ) == 0 ) {
      *debugMode = 1;
      continue;
    }
    if( strncmp( argv[i], "--repetitions", 13 ) == 0 ) {
      if( strlen(argv[i]) > 13 )
        *repetitions = atoi(argv[i] + 13);
      else
        *repetitions = atoi(argv[++i]);
      continue;
    }
  }
}
