/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

struct Configuration {
    double defaultSpeed;
    double createRate;
    int debugMode;
    double duration;
    int pause;
    int graphic;
    int randomSeed;
    int uniqueGraphic;
    int keepSpeed;
    int fps;
    int noSleep;
};
typedef struct Configuration *configuration;

configuration configurationInit();
void configurationRemove(configuration config);

/* Le argumentos e seta variaveis de acordo com os mesmos */
void argRead(int argc, char **argv, configuration defaults);
/*Se o argumento existe, retorna o indice do mesmo. Caso contrario, retorna 0*/
int argFind(int argc, char **argv, char *argLong, char *argShort);
/*Se o argumento existe, retorna o valor dele em forma de string. Caso contrario, retorna NULL*/
char *argVal(int argc, char **argv, char *argLong, char *argShort);
/*Retorna um vetor, onde cada indice representa se a letra daquele indice existe como argumento*/
char *argShortFlags(int argc, char **argv, char *args);

#endif                          /* _CONFIGURATION_H_ */
