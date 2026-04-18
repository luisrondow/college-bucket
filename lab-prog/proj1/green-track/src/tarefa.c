#include "tarefa.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Tarefa
{
    int id_tarefa;
    char descricao[100];
    int data_prevista;
    int concluida;
};

TarefaPtr tarefa_criar(int id_tarefa, const char *descricao,
                       int data_prevista, int concluida)
{
    TarefaPtr t = malloc(sizeof(struct Tarefa));
    if (!t)
        return NULL;

    t->id_tarefa = id_tarefa;
    strcpy(t->descricao, descricao);
    t->data_prevista = data_prevista;
    t->concluida = concluida;
    return t;
}

void tarefa_destruir(TarefaPtr t)
{
    free(t);
}

int tarefa_get_id_tarefa(TarefaPtr t) { return t->id_tarefa; }
const char *tarefa_get_descricao(TarefaPtr t) { return t->descricao; }
int tarefa_get_data_prevista(TarefaPtr t) { return t->data_prevista; }
int tarefa_get_concluida(TarefaPtr t) { return t->concluida; }
void tarefa_set_concluida(TarefaPtr t, int concluida) { t->concluida = concluida; }

int criar_tarefa(TarefaPtr *tarefas, int *total_tarefas, int max_tarefas,
                 const char *descricao, int data_prevista)
{
    if (*total_tarefas >= max_tarefas)
    {
        printf("Erro: limite maximo de tarefas atingido.\n");
        return -1;
    }

    tarefas[*total_tarefas] = tarefa_criar(*total_tarefas + 1, descricao,
                                           data_prevista, 0);
    (*total_tarefas)++;
    return 1;
}

void listar_tarefas_pendentes(TarefaPtr *tarefas, int total_tarefas)
{
    printf("=== TAREFAS PENDENTES ===\n");
    for (int i = 0; i < total_tarefas; i++)
    {
        TarefaPtr t = tarefas[i];
        if (tarefa_get_concluida(t) == 0)
        {
            printf("Tarefa %d: %s (prevista: %d)\n",
                   tarefa_get_id_tarefa(t),
                   tarefa_get_descricao(t),
                   tarefa_get_data_prevista(t));
        }
    }
}

void concluir_tarefa(TarefaPtr *tarefas, int total_tarefas, int id)
{
    for (int i = 0; i < total_tarefas; i++)
    {
        if (tarefa_get_id_tarefa(tarefas[i]) == id)
        {
            tarefa_set_concluida(tarefas[i], 1);
            return;
        }
    }
    printf("Tarefa %d nao encontrada.\n", id);
}
