/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "common.h"
/* Nota: A estrutura Vector eh definida em "lib/common.h". Esse arquivo eh necessario
	apenas para fazer operacoes com vetores. 
vectorCreate eh declarado e definido em "lib/common". */

/*Soma dois vetores*/
vector vectorSum(vector a, vector b);
/*Subtrai vetores, primeiro vetor menos o segundo*/
vector vectorSub(vector a, vector b);
/*Multiplicacao escalar entre dois vetores*/
double vectorMulEsc(vector a, vector b);
/*Multiplicacao de um vetor por um numero real*/
vector vectorMulDouble(vector v, double alfa);
/*Divide um vetor pelo dividendo dado*/
vector vectorDiv(vector v, double div);
/*Converte de coordenadas polares para coordenadas cartesianas*/
vector vectorPolarToCartesian(vector v);
/*Converte de coordenadas cartesianas para coordenadas polares*/
vector vectorCartesianToPolar(vector v);

/*Retorna o angulo do vetor*/
double vectorAngle(vector v);
/*Retorna o comprimento do vetor*/
double vectorLength(vector);
/*Seta o angulo do vetor*/
vector vectorAngleSet(vector v, double ang);
/*Seta o comprimento do vetor*/
vector vectorLengthSet(vector v, double length);
/*Rotaciona o vetor de acordo com o angulo dado, no sentido anti-horario*/
vector vectorRotate(vector v, double ang);
/*Imprime o vetor, retorna quantos caracteres foram impressos*/
int vectorPrint(vector);

#endif                          /* _VECTOR_H_ */
