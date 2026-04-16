#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
    StackPtr pilha = stack_criar(3);

    stack_push(pilha, 10);
    stack_push(pilha, 20);
    stack_push(pilha, 30);

    printf("Topo: %d\n", stack_pop(pilha)); // 30
    printf("Topo: %d\n", stack_pop(pilha)); // 20

    stack_destruir(&pilha);
    return 0;
}