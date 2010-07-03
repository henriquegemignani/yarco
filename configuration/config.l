/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/*******************************************************************/
%{
#include "config_bison.h"
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

[a-zA-Z]+ {
	sscanf(yytext, "%s", yylval.str);
	return STRING;
}

[0-9]*\.?[0-9]+f? {
	sscanf(yytext, "%lf", &yylval.num);
	return NUM;
}

[ \t]*          ;

.|\n            { return yytext[0]; }

%%

void configurationInit(FILE* source) {
	yyin = source;
	yyparse();
}