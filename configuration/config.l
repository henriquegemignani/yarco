/* Infix notation calculator */
/* Time-stamp: <98/09/15 16:06:18 ronaldo> calc.l */
%{
# include "config_bison.h"
extern YYSTYPE yylval;
%}

%%

"/*"([^\*]|[^\/])*"*/"	;/* Comentarios deste formato sao ignorados. */
(;|"//"|\#)[^\n]*		;/* ";" ou "#" ou "//" podem ser utilizados para comentar o resto da linha. */

^\[[^\]]+\]$			;/* separador de secao do formato "[TEXTO]". Atualmente aje como comentario. */

"true"|"TRUE"	{ yylval.val = 1; return NUM; }
"false"|"FALSE"	{ yylval.val = 0; return NUM; }

[a-zA-Z]+ {//  if (!keepDir) {
    //    b->extra->isTurning = randInt(0, 2) - 1;        /*Feito dessa forma uma vez que randInt buga para valores negativos */
      //  b->extra->isAccel = randInt(0, 2) - 1;
   // }
    //if (b->extra->isAccel)     {
      //  b->acc.x = -cos(b->dir) * b->extra->accel * b->extra->isAccel;
        //b->acc.y = -sin(b->dir) * b->extra->accel * b->extra->isAccel;
 //  } else         
   //     b->acc = vectorCreate(0, 0);
	sscanf(yytext, "%s", yylval.str);
	return STRING;
}

[0-9]+ {
	sscanf(yytext, "%d", &yylval.val);
	return NUM;
}

[ \t]*          ;

.|\n            { return *yytext; }

%%

int main (void) {
  yyparse();
}
