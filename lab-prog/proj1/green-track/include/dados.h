#include "planta.h"
#include "rega.h"
#include "tarefa.h"

/* dados.h */
#ifndef DADOS_H
#define DADOS_H

void carregar_dados(PlantaPtr *plantas, RegaPtr *regas, TarefaPtr *tarefas, int *total_plantas, int *total_regas, int *total_tarefas);

void guardar_dados(PlantaPtr *plantas, RegaPtr *regas, TarefaPtr *tarefas, int total_plantas, int total_regas, int total_tarefas);

#endif