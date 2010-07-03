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
	char*	name;
	configValue val;
};
struct ConfigGroup {
	char* groupName;
	struct ConfigItem list[];
};

static void setCurrentGroup(char* group);
static int configSet( char* name, configValue);

%}

/* bison declarations */
%union {
  double num;
  char str[256]; /* == MAXIMUM_CONFIG_NAME_SIZE. Define nao foi... */
}
%token <str> STRING
%token <str> GROUP
%token <num> NUM

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

exp
: STRING '=' NUM { 
	configValue val;
	val.num = (int) $3;
	val.real = (float) $3;
	valconfigSet($1, val); 
};

%%

static int config_currentGroup = -1;
static struct ConfigGroup config_list[] = {
/* GROUP, config_list */
/*    CONFIG_NAME,         INTVAL, FLOATVAL */
"General", {
	"MaximumFPS",			  30, 30,
	"ResolutionX",			1024,1024,
	"ResolutionY",			 768,768,
	
	"LimitObject",			 150,150,
	"LimitCoral",			  12, 12,
	"LimitPerson",			 100,100,
	
	"PersonInitialAmmount",	  30, 30,
	"PersonCreateRate",		   5,  5,
	"PersonAverageSpeed",	  10, 10,
	
	"RadiusPerson",			   5,  5,
	"RadiusShip",			  50, 50,
	"RadiusCoral",			  10, 10,
	"RadiusBoat",			  10, 10,
	NULL,					  -1, -1
},
	
"Gameplay", {
	"TurnRate", 			   1, 1.57079632, // PI/2
	"Acceleration",			  50, 50,
	"Friction",				   0,0.5,
	"TimesStuck",			   5,  5,
	"InitialLives",			   3,  3,
	NULL,					  -1, -1
},

NULL, NULL
};

#define CUR_CONFIGLIST config_list[config_currentGroup]

/* Setters */
void setCurrentGroup(char* new) {
	config_currentGroup = getGroupID(group);
}
int configSet(char* str, int val) {
	int i;
	for(i = 0; CUR_CONFIGLIST[i].name != NULL; ++i) {
		if(strcasecmp(CUR_CONFIGLIST[i].name, str) == 0 ) {
			CUR_CONFIGLIST[i].val = val;
			return 0;
		}
	}
	return 1;
}

/* ConfigValue getters */
configValue configGetValue(char* group, char* config) {
	int groupid = getGroupID(group);
	return configGetValueFromID(groupid, getConfigID(groupid, config));
}
configValue configGetValueFromID(int groupid, int configid) {
	return config_list[groupid][configid].val;
}

/* ID getters */
int getGroupID(char* group) {
	int i;
	for(i = 0; config_list[i] != NULL; ++i)
		if(strcasecmp(new, config_list[i].groupName) == 0)
			return i;
	return -1;
}
int getConfigID(int groupid, char* config) {
	int i;
	for(i = 0; config_list[groupid][i].name != NULL; ++i)
		if(strcasecmp(config, config_list[groupid][i].name) == 0 )
			return i;
	return -1;
}

int yyerror (char *err) {
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
