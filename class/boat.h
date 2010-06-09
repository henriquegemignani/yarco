/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/
#ifndef _BOAT_H_
#define _BOAT_H_
#include "../lib/common.h"
#include "../lib/class.h"
typedef struct Object *boat;

/*Inicializa a classe*/
void boatInitializeClass();
/*Pega os valores definidos pela linha de comando*/
void boatGetDefaults(double turnRate, double accel, double friction,
                     int lives, double timeStuck);
/*Cria um bote*/
boat boatCreate(texture tex, point pos, velocity vel);
/*Atualiza o bote*/
void boatUpdate(boat b, int keepDir, double timedif);
/*Nuka um bote*/
void boatRemove(boat b);
/*Trata o bote se ele tentar sair da tela*/
void boatOB(boat b);
/*Trata o que acontece com o bote ao colidir com outros objetos*/
void boatCollide(boat b, object o, double timedif);
/*Cria um bote direto na tabela de objetos*/
boat boatAddNewToTable(int color);
/*Dumpa informacoes sobre o bote*/
void boatDump(boat b);
#endif
