/* stack.h */
#ifndef STACK_H
#define STACK_H

/* Tipo opaco - ponteiro para estrutura incompleta */
typedef struct Stack *StackPtr;

/* Cria uma pilha vazia com capacidade N */
StackPtr stack_criar(int capacidade);

/* Adiciona um valor no topo da pilha */
void stack_push(StackPtr s, int valor);

/* Remove e retorna o valor do topo */
int stack_pop(StackPtr s);

/* Retorna 1 se vazia, 0 caso contrário */
int stack_vazia(StackPtr s);

/* Liberta toda a memória alocada */
void stack_destruir(StackPtr *s);

#endif /* STACK_H */