#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

struct Stack
{
    int *dados;     // Array dinâmico de inteiros
    int topo;       // Índice do topo (-1 se vazia)
    int capacidade; // Capacidade máxima
};

StackPtr stack_criar(int capacidade)
{
    StackPtr stack = malloc(sizeof(struct Stack));
    stack->capacidade = capacidade;
    stack->topo = -1;
    stack->dados = (int *)malloc(capacidade * sizeof(int));

    if (stack->dados == NULL)
    {
        printf("Erro: Memória insuficiente.\n");
        return NULL;
    }

    return stack;
}

void stack_push(StackPtr s, int valor)
{
    if (s->topo + 1 == s->capacidade)
    {
        printf("Pilha cheia\n");
        return;
    }

    s->topo = s->topo + 1;
    s->dados[s->topo] = valor;
    printf("stack topo: %d -- %d \n\n", s->topo, s->dados[s->topo]);
}

int stack_pop(StackPtr s)
{
    if (s->topo == -1)
    {
        printf("Pilha vazia\n");
        return -1;
    }

    int removed = s->dados[s->topo];
    s->topo = s->topo - 1;

    return removed;
}

int stack_vazia(StackPtr s)
{
    if (s->topo != -1)
        return 1;

    return 0;
}

void stack_destruir(StackPtr *s)
{
    free(*s);
    *s = NULL;
}
