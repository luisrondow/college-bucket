#include "dados.h"

#include <stdio.h>

void carregar_dados(PlantaPtr *plantas, RegaPtr *regas, TarefaPtr *tarefas,
                    int *total_plantas, int *total_regas, int *total_tarefas)
{
    FILE *f_plantas = fopen("plantas.csv", "r");
    if (f_plantas != NULL)
    {
        int id, intervalo_rega, ultima_rega;
        char nome[50], especie[50], data_plantio[11];

        while (fscanf(f_plantas, "%d,%[^,],%[^,],%[^,],%d,%d\n",
                      &id, nome, especie, data_plantio,
                      &intervalo_rega, &ultima_rega) == 6)
        {
            plantas[*total_plantas] = planta_criar(id, nome, especie,
                                                   data_plantio,
                                                   intervalo_rega,
                                                   ultima_rega);
            (*total_plantas)++;
        }
        fclose(f_plantas);
    }

    FILE *f_regas = fopen("regas.csv", "r");
    if (f_regas != NULL)
    {
        int id_rega, id_planta, data_rega, quantidade_agua;

        while (fscanf(f_regas, "%d,%d,%d,%d\n",
                      &id_rega, &id_planta,
                      &data_rega, &quantidade_agua) == 4)
        {
            regas[*total_regas] = rega_criar(id_rega, id_planta,
                                             data_rega, quantidade_agua);
            (*total_regas)++;
        }
        fclose(f_regas);
    }

    FILE *f_tarefas = fopen("tarefas.csv", "r");
    if (f_tarefas != NULL)
    {
        int id_tarefa, data_prevista, concluida;
        char descricao[100];

        while (fscanf(f_tarefas, "%d,%[^,],%d,%d\n",
                      &id_tarefa, descricao,
                      &data_prevista, &concluida) == 4)
        {
            tarefas[*total_tarefas] = tarefa_criar(id_tarefa, descricao,
                                                   data_prevista, concluida);
            (*total_tarefas)++;
        }
        fclose(f_tarefas);
    }
}

void guardar_dados(PlantaPtr *plantas, RegaPtr *regas, TarefaPtr *tarefas,
                   int total_plantas, int total_regas, int total_tarefas)
{
    FILE *f_plantas = fopen("plantas.csv", "w");
    if (f_plantas == NULL)
    {
        printf("Erro ao abrir plantas.csv\n");
        return;
    }
    for (int i = 0; i < total_plantas; i++)
    {
        PlantaPtr p = plantas[i];
        fprintf(f_plantas, "%d,%s,%s,%s,%d,%d\n",
                planta_get_id(p),
                planta_get_nome(p),
                planta_get_especie(p),
                planta_get_data_plantio(p),
                planta_get_intervalo_rega(p),
                planta_get_ultima_rega(p));
    }
    fclose(f_plantas);

    FILE *f_regas = fopen("regas.csv", "w");
    if (f_regas == NULL)
    {
        printf("Erro ao abrir regas.csv\n");
        return;
    }
    for (int i = 0; i < total_regas; i++)
    {
        RegaPtr r = regas[i];
        fprintf(f_regas, "%d,%d,%d,%d\n",
                rega_get_id_rega(r),
                rega_get_id_planta(r),
                rega_get_data_rega(r),
                rega_get_quantidade_agua(r));
    }
    fclose(f_regas);

    FILE *f_tarefas = fopen("tarefas.csv", "w");
    if (f_tarefas == NULL)
    {
        printf("Erro ao abrir tarefas.csv\n");
        return;
    }
    for (int i = 0; i < total_tarefas; i++)
    {
        TarefaPtr t = tarefas[i];
        fprintf(f_tarefas, "%d,%s,%d,%d\n",
                tarefa_get_id_tarefa(t),
                tarefa_get_descricao(t),
                tarefa_get_data_prevista(t),
                tarefa_get_concluida(t));
    }
    fclose(f_tarefas);
}