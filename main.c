/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/**                                                               **/
/** Nomes:                                                        **/
/** Andre Mesquita Pereira              nUSP: 6879530             **/
/** Henrique Gemignani Passos Lima      nUSP: 6879634             **/
/** Renan Teruo Carneiro                nUSP: 6514157             **/
/*******************************************************************/

#include <stdio.h>
#include "lib/common.h"
#include "lib/graphics.h"
#include "lib/person.h"
#include "lib/persontable.h"
#include <time.h>
#include <string.h>

void argRead(int argc, char **argv, double *defaultSpeed, double *createRate);

int main(int argc, char ** argv){
  int i, aux;
  unsigned int id;
  double defaultSpeed = PERSON_SPEED_DEFAULT, createRate = PERSON_CREATE_RATE_DEFAULT;
  person per;
  point pt;

  argRead(argc, argv, &defaultSpeed, &createRate); 
  /* Separado por questoes de clareza do codigo. */
  /* Possivelmente: criar uma funcao que verifica se um argumento especifico existe, para mais elegancia, embora seja menos eficiente */
  /* Alias, o numero maximo de pasageiros tambem deveria ser customizavel ou non? */

  personTableInit();
  srand(time(NULL));
  for( i = 0; i < PERSON_NUM_INIT; i++ ) {
    aux = randInt(0, 4);
    pt = vectorCreate( 
        aux < 2 ? randDouble( 0, SCREEN_SIZE_X ) : (aux - 2) * SCREEN_SIZE_X,
        aux > 1 ? randDouble( 0, SCREEN_SIZE_Y ) : (aux - 1) * SCREEN_SIZE_Y );
    per = personCreate( pt, defaultSpeed );
    id = personTableAdd(per);
    if( id == ERROR_PERSON_LIMIT_EXCEEDED ) {
      printf("Erro: limite de naufragos atingido!\n");
      exit(1);
    }
    personSetID( per, id );
  }
  graphicInitialize();
  i = 1;
  printf("HELL, IT'S LOOPING TIME\n");
  while(i) {
    personTableUpdate();
    graphicUpdate();
    graphicDraw();
    scanf(" %d", &i);
  }
  return 0;
}

void argRead(int argc, char **argv, double *defaultSpeed, double *createRate){
  int i;
  for( i = 1; i < argc; i++ ) {
    if( strcmp( argv[i], "-h" ) == 0 || strcmp( argv[i], "--help" ) == 0 ) {
      printf("Usage: %s [--speed S] [--rate R]\n\n"
	     "-speed determina a velocidade media dos passageiros (padrao: %3.2f)\n"
	     "-rate determina o periodo entre 2 novos passageiros (padrao: %3.2f)\n",
	     argv[0], *defaultSpeed, *createRate );
      exit(0);
    }
    if( strncmp( argv[i], "--speed", 7 ) == 0 ) { /* supoe que usuario colocou um numero */
      if( strlen(argv[i]) > 7 ) /* parametro da forma '--speedX' */
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
  }
}
