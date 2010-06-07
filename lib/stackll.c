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

STACKLL.c - implementação das funções de pilha usando listas ligadas
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

struct Cell {
    void *card_value;
    struct Cell *next;
};

/*
	as cartas são um número de 0 a 51
	sendo o naipe obtido pela divisao inteira por 13
	e o valor obtido pelo resto da divisao por 13
	ex: 16/13=1, 16mod13=3 -> naipe 1 e valor 3
*/

/* inicia uma pilha vazia */
stack stackInit()
{
    stack s = malloc(sizeof(card));
    *s = NULL;
    return s;
}

/* retorna 1 se a pilha estiver vazia, senão retorna 0 */
int stackIsEmpty(stack top)
{
    if ((*top) == NULL)
        return 1;
    return 0;
}

/* recebe um valor inteiro e o coloca no topo da pilha */
void stackPush(void *c, stack top)
{
    card temp = malloc(sizeof(struct Cell));
    temp->card_value = c;
    temp->next = (*top);
    *top = temp;
}

/* obtém o valor do topo da pilha e elimina a sua posição na memória */
void *stackPop(stack top)
{
    void *c = (*top)->card_value;
    card temp = *top;
    *top = (*top)->next;
    free(temp);
    return c;
}

void stackFinish(stack top)
{
    free(top);
}
