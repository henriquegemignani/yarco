/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/
%{
#include "config_bison.h"
#include "configuration.h"
extern YYSTYPE yylval;
%}

%%

"/*"([^\*]|[^\/])*"*/"	;/* Comentarios deste formato sao ignorados. */
(;|"//"|\#)[^\n]*		;/* ";" ou "#" ou "//" podem ser utilizados para comentar o resto da linha. */

^\[[^\]]+\]$	{
	sscanf(yytext, "[%s", yylval.str);
	yylval.str[strlen(yylval.str)-1] = '\0';
	return GROUP;
}/* separador de secao do formato "[TEXTO]". */

"true"|"TRUE"	{ yylval.num = 1.0f; return NUM; }
"false"|"FALSE"	{ yylval.num = 0.0f; return NUM; }

"0x"[0-9a-fA-F]+ {
	sscanf(yytext, "%x", &yylval.temp_int);
	yylval.num = (double) yylval.temp_int; 
	return NUM;
}

[a-zA-Z][a-zA-Z 0-9]* {
	sscanf(yytext, "%s", yylval.str);
	return STRING;
}

-?[0-9]*,[0-9]+f? {
	for(yylval.temp_int = 0; yytext[yylval.temp_int] != ','; ++yylval.temp_int);
	yytext[yylval.temp_int] = '.';
	sscanf(yytext, "%lf", &yylval.num);
	return NUM;
}

-?[0-9]*\.?[0-9]+f? {
	sscanf(yytext, "%lf", &yylval.num);
	return NUM;
}

[ \t]*          ;

.|\n            { return yytext[0]; }

%%

void configurationRead(FILE* source) {
	configInitializeDefaults();
	yyin = source;
	yyparse();
	yylex_destroy();
}