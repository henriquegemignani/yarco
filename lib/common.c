/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#include "common.h"
/* #include <stdio.h> -- ta no common.h agora */
#include <math.h>

vector vectorCreate(double x, double y) {
  vector v;
  v.x = x;
  v.y = y;
  return v;
}

vector vectorSum( vector a, vector b ){
	vector v;
	v.x = a.x + b.x;
	v.y = a.y + b.y;
	return v;
}

vector vectorSub( vector a, vector b ){
	vector v;
	v.x = a.x - b.x;
	v.y = a.y - b.y;
	return v;
}

vector vectorMulVet( vector a, vector b ){
	vector v;

	return v;
}

double vectorMulEsc( vector a, vector b ){
	return (( a.x * b.x ) + ( a.y * b.y ));
}

vector vectorPolarToCartesian(vector v) {
    double  vAng = v.y, 
            vLength = v.x;
    v.x = vLength * cos( vAng );
    v.y = vLength * sin( vAng );
    return v;
}
vector vectorCartesianToPolar(vector v) {
    double  vAng = vectorAngle(v), 
            vLength = vectorLength(v);
    v.x = vLength;
    v.y = vAng;
    return v;
}

vector vectorRotate ( vector v, double ang ){
  double vAng;
  vAng = vectorAngle( v );
  return vectorAngleSet( v, ang+vAng );
}

double vectorAngle ( vector v ){
  return atan2( v.x, v.y );
}

vector vectorAngleSet ( vector v, double ang ){
  double vLength;
  vLength = vectorLength ( v );
  v.x = cos( ang ) * vLength;
  v.y = sin( ang ) * vLength;
  return v;
}

vector vectorLengthSet ( vector v, double length ){
  double vAng;
  vAng = vectorAngle ( v );
  v.x = length * cos( vAng );
  v.y = length * sin( vAng );
  return v;
}

double distanceBetweenPoints(point a, point b) {
    double x = a.x - b.x, y = a.y - b.y;
    return sqrt( x*x + y*y );
}

double vectorLength(vector v) {
  return sqrt( v.x * v.x + v.y * v.y );
}

int vectorPrint(vector v) {
  return printf("(%6.3lf,%6.3lf)", v.x, v.y );
}

int randInt(int min, int max) {
  return ( ( (max - min + 1) * ( (double) (1.0*rand()) / (double) (1.0*RAND_MAX + 1.0) ) ) + min );
}

double randDouble(double min, double max) {
  return ( ( (max - min + 1) * ( (double) (1.0*rand()) / (double) (1.0*RAND_MAX + 1.0) ) ) + min );
}

void genError(char *msg){
  fprintf( stderr, "%s", msg );
  exit(EXIT_FAILURE);
}

void MALLOC_DIE() {
    exit(ERROR_MALLOC_FAILURE);
}
