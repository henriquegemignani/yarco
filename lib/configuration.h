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
    int repetitions;
    int pause;
    int graphic;
    int randomSeed;
    int uniqueGraphic;
};
typedef struct Configuration *configuration;

configuration configurationInit();
void configurationRemove(configuration config);

/* Le argumentos e seta variaveis de acordo com os mesmos */
void argRead(int argc, char **argv, configuration defaults);

int argFind(int argc, char **argv, char *argLong, char *argShort);
char *argVal(int argc, char **argv, char *argLong, char *argShort);
char *argShortFlags(int argc, char **argv, char *args);

#endif                          /* _CONFIGURATION_H_ */
