/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

typedef struct{int num; float real; char* str;} configValue;

void configInitializeDefaults();
void configurationInit(char* config_file);
void configurationRead(FILE* source);
void configurationWrite(FILE* target);
void configurationFinish(char* config_file);

configValue configGetValue(char* group, char* config);
configValue configGetValueFromID(int groupid, int configid);
int getGroupID(char* group);
int getConfigID(int groupid, char* config);

configValue createConfigValue(double real, char* str);

void setCurrentGroup(char* group);
int configSet( char* name, configValue);


/* LEGACY! */
struct Configuration {
    double defaultSpeed;
    double createPeriod;
    int debugMode;
    double duration;
    int pause;
    int randomSeed;
    int keepSpeed;
    int fps;
    int noSleep;
    double accel;
    double friction;
    double turnRate;
    int lives;
    double timeStuck;
    int verbose;
    int numPeople;
    int numCorals;
    double disco;
};
typedef struct Configuration *configuration;

configuration configurationGet();
void LEGACY_configurationFinish();

/* Le argumentos e seta variaveis de acordo com os mesmos */
void argRead(int argc, char **argv, configuration defaults);
/*Se o argumento existe, retorna o indice do mesmo. Caso contrario, retorna 0*/
int argFind(int argc, char **argv, char *argLong, char *argShort);
/*Se o argumento existe, retorna o valor dele em forma de string. Caso contrario, retorna NULL*/
char *argVal(int argc, char **argv, char *argLong, char *argShort);
/*Retorna um vetor, onde cada indice representa se a letra daquele indice existe como argumento*/
char *argShortFlags(int argc, char **argv, char *args);

#endif                          /* _CONFIGURATION_H_ */

