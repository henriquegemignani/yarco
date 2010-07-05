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
	int temp_int;
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
: STRING '=' NUM	{ configSet($1, createConfigValue($3, NULL)); }
| STRING '=' STRING	{ configSet($1, createConfigValue(-1, $3)); }
;

%%

int yyerror (char *err) {
	if(strcasecmp(err, "syntax error") == 0)
		fprintf(stderr, "Erro de sintaxe ao ler o arquivo de configuracao!\n");
	else
		fprintf(stderr, "%s\n", err);
	return 0;
}
