/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.h"

struct ConfigItem {
	int 	group;
	char*	name;
	configValue val;
};
static void setCurrentGroup(char*);
static int configSetNum(char*, int);
static int configSetReal(char*, float);

%}

/* bison declarations */
%union {
  int num;
  float real;
  char str[256]; /* == MAXIMUM_CONFIG_NAME_SIZE. Define nao foi... */
}
%token <str> STRING
%token <str> GROUP
%token <num> NUM
%token <real> REAL

/* Grammar follows */
%%
input 
	: GROUP			{ setCurrentGroup($1); }
	| input line
	;

line
	: '\n'
	| GROUP '\n'	{ setCurrentGroup($1); }
	| exp '\n'
	;

exp	: STRING '=' NUM {  configSetNum($1, $3); }
	| STRING '=' REAL { configSetReal($1, $3); }
;

%%

static int config_currentGroup = -1;
static char* config_GroupList[] = {
	"General", "Gameplay", NULL
};
static struct ConfigItem config_ValList[] = {
/*GROUP,    NAME,			INT_VAL, FLOAT_VAL */
	0, "FPS",					 30, -1,
	0, "PersonLimit",			100, -1,
	0, "PersonInitialAmmount",	 30, -1,
	0, "PersonCreateRate",		  5, -1,
	0, "PersonAverageSpeed",	 10, -1,
	
	1, "TurnRate", 				 -1, 1.57079632, /* PI/2 */
	
   -1, NULL      	,  0
};
int configSetNum(char* str, int val) {
	int i;
	for(i = 0; config_ValList[i].name != NULL; ++i) {
		if(config_ValList[i].group == config_currentGroup && strcasecmp(config_ValList[i].name, str) == 0 ) {
			config_ValList[i].val.num = val;
			config_ValList[i].val.real = -1;
			return 0;
		}
	}
	return 1;
}
int configSetReal(char* str, float val) {
	int i;
	for(i = 0; config_ValList[i].name != NULL; ++i) {
		if(config_ValList[i].group == config_currentGroup && strcasecmp(config_ValList[i].name, str) == 0 ) {
			config_ValList[i].val.num = -1;
			config_ValList[i].val.real = val;
			return 0;
		}
	}
	return 1;
}
configValue configGetValue(char* str) {
	int i;
	configValue ret;
	for(i = 0; config_ValList[i].name != NULL; ++i)
		if(strcasecmp(config_ValList[i].name, str) == 0 )
			return config_ValList[i].val;
	ret.num = -1;
	ret.real = -1;
	return ret;
}
configValue configGetValueFromID(int id) {
	return config_ValList[id].val;
}
void setCurrentGroup(char* new) {
	int i;
	for(i = 0; config_GroupList[i] != NULL; ++i) {
		if(strcasecmp(new, config_GroupList[i]) == 0) {
			config_currentGroup = i;
			return;
		}
	}
	config_currentGroup = -1;
}

int yyerror (char *err) {
	/* Insira uma mensagem de erro mais sutil aqui. */
	if(strcasecmp(err, "syntax error") == 0)
		printf("Erro de sintaxe ao ler o arquivo de configuracao!\n");
	else
		printf("%s\n", err);
}

int main (void) { int i; configurationInit(stdin); 
	for(i = 0; config_ValList[i].name != NULL; ++i)
		printf("[%8s] %24s: %3d -- % 4f\n", 
			config_GroupList[config_ValList[i].group],
			config_ValList[i].name, 
			config_ValList[i].val.num, 
			config_ValList[i].val.real);
}
