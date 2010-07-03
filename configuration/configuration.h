/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

typedef struct{int num; float real;} configValue;

void configInitializeDefaults(); /* Chamada automaticamente por configurationInit */
void configurationInit(FILE* source);
void configurationWrite(FILE* target);
void configurationFinish();


configValue configGetValue(char* group, char* config);
configValue configGetValueFromID(int groupid, int configid);
int getGroupID(char* group);
int getConfigID(int groupid, char* config);

void setCurrentGroup(char* group);
int configSet( char* name, configValue);

#endif                          /* _CONFIGURATION_H_ */
