/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.h"
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
	configSet($1, val); 
};

%%

int yyerror (char *err) {
	if(strcasecmp(err, "syntax error") == 0)
		printf("Erro de sintaxe ao ler o arquivo de configuracao!\n");
	else
		printf("%s\n", err);
	return 0;
}

int main (void) { 
	configInitializeDefaults();
	configurationInit(stdin);
	configurationWrite(stdout);
	configurationFinish();
	return 0;
}
