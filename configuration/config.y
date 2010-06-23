%{
#include <stdio.h>
%}

/* bison declarations */
%union {
  int val;
  char str[255]; /* == MAXIMUM_CONFIG_NAME_SIZE. Define nao foi... */
}
%token <str> STRING
%token <val> NUM

/* Grammar follows */
%%
input 
	: /* empty */
	| input line
	;

line
	: '\n'
	| exp '\n'
	;

exp	: STRING '=' NUM { 
	printf("Configuracao %s vale %d\n", $1, $3);
	/* Insira codigo aqui para tratar configs! */
};

%%

int yyerror (char *s) {
	/* Insira uma mensagem de erro mais sutil aqui. */
	printf ("%s\n", s);
}
