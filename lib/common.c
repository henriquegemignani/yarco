/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
#include <stdio.h>
#include <math.h>

vector VECTORcreate(double x, double y) {
  vector v;
  v.x = x;
  v.y = y;
  return v;
}

double VECTORlength(vector v) {
  return sqrt( v.x * v.x + v.y * v.y );
}

int VECTORprint(vector v) {
  return printf("(%6.3lf,%6.3lf)", v.x, v.y );
}

int randNumber(int min, int max) {
  return (4657 - min) % max; /* numero aleatoriamente escolhido */
}
