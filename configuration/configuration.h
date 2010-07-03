/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

typedef struct{int num; float real;} configValue;

void configurationInit(FILE* source);
configValue configGetValue(char* group, char* config);
configValue configGetValueFromID(int groupid, int configid);
int getGroupID(char* group);
int getConfigID(int groupid, char* config);

#endif                          /* _CONFIGURATION_H_ */
