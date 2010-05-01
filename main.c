/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/**                                                               **/
/** Nomes: (TODO: galera preencher)				  **/	
/** Andre Mesquita Pereira		nUSP: 6879530		  **/
/** Henrique Gemignani Passos Lima      nUSP: 6879634             **/
/** Renan Teruo Carneiro                nUSP: 6514157             **/
/*******************************************************************/

#include <stdio.h>
#include "lib/common.h"
#include "lib/graphics.h"
#include "lib/persontable.h"

int main(int argc, char ** argv){
  /*Var*/
  personTableInit();
  graphicInitialize();
  graphicUpdate();
  graphicDraw();
  return 0;
}
