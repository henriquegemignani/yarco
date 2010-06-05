/*******************************************************************/
/** MAC0211 - Laboratorio de Programacao I                        **/
/** Projeto de Jogo                                               **/
/** --- codigo extraido do EP1 de Estrutura de Dados, modificado  **/
/**   parcialmente para atender as necessidades.                  **/
/*******************************************************************/
/* TODO: mexer nos cabecalhos desse arquivo. */
/*
André Mesquita Pereira
Número USP: 6879530

MAC0323-2010 - Professor Ronaldo Hashimoto

EP 1

STACK.h - header contendo a interface de pilha
*/

typedef struct Cell *card;
typedef struct Cell **stack;
/*
	o tipo 'card' praticamente só é usado no arquivo 'STACKLL.c'
*/

stack	stackInit(); /* retorna uma pilha vazia */
int		stackIsEmpty( stack top ); /* retorna 1 se a pilha estiver vazio, 0 se não estiver */
void	stackPush( void *c, stack top ); /* insere 'c' na pilha */
void*	stackPop( stack top ); /* retorna o o topo da pilha */
void    stackFinish( stack top );
