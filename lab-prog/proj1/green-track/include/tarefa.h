/* tarefa.h */
#ifndef TAREFA_H
#define TAREFA_H

typedef struct Tarefa *TarefaPtr;

TarefaPtr tarefa_criar(int id_tarefa, const char *descricao,
                       int data_prevista, int concluida);

void tarefa_destruir(TarefaPtr t);

int tarefa_get_id_tarefa(TarefaPtr t);

const char *tarefa_get_descricao(TarefaPtr t);

int tarefa_get_data_prevista(TarefaPtr t);

int tarefa_get_concluida(TarefaPtr t);

int criar_tarefa(TarefaPtr *tarefas, int *total_tarefas, int max_tarefas, const char *descricao, int data_prevista);

void listar_tarefas_pendentes(TarefaPtr *tarefas, int total_tarefas);

void concluir_tarefa(TarefaPtr *tarefas, int total_tarefas, int id);

#endif