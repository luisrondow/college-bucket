#include "planta.h"
#include "rega.h"
#include "tarefa.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLANTAS 100
#define MAX_REGAS 500
#define MAX_TAREFAS 200

int main()
{
    PlantaPtr plantas[MAX_PLANTAS];
    RegaPtr regas[MAX_REGAS];
    TarefaPtr tarefas[MAX_TAREFAS];
    int total_plantas = 0, total_regas = 0, total_tarefas = 0;

    carregar_dados(plantas, regas, tarefas,
                   &total_plantas, &total_regas, &total_tarefas);

    int opcao;
    do
    {
        printf("\n1.Listar  2.Adicionar planta  3.Registar rega  "
               "4.Verificar  5.Listar tarefas  6.Criar tarefa  "
               "7.Concluir tarefa  8.Sair\n> ");
        scanf("%d", &opcao);
        while (getchar() != '\n')
            ;

        switch (opcao)
        {
        case 1:
        {
            listar_plantas(plantas, total_plantas);
            break;
        }
        case 2:
        {
            int id, intervalo;
            char nome[50], especie[50], data[11];
            printf("ID: ");
            scanf("%d", &id);
            while (getchar() != '\n')
                ;
            printf("Nome: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = '\0';
            printf("Especie: ");
            fgets(especie, sizeof(especie), stdin);
            especie[strcspn(especie, "\n")] = '\0';
            printf("Data de plantio (YYYY-MM-DD): ");
            fgets(data, sizeof(data), stdin);
            data[strcspn(data, "\n")] = '\0';
            printf("Intervalo de rega (dias): ");
            scanf("%d", &intervalo);
            while (getchar() != '\n')
                ;
            adicionar_planta(plantas, &total_plantas, MAX_PLANTAS,
                             id, nome, especie, data, intervalo);
            break;
        }
        case 3:
        {
            int id_planta, data, quantidade;
            printf("ID da planta: ");
            scanf("%d", &id_planta);
            while (getchar() != '\n')
                ;
            printf("Data da rega (timestamp): ");
            scanf("%d", &data);
            while (getchar() != '\n')
                ;
            printf("Quantidade de agua (ml): ");
            scanf("%d", &quantidade);
            while (getchar() != '\n')
                ;
            registar_rega(plantas, total_plantas,
                          regas, &total_regas, MAX_REGAS,
                          id_planta, data, quantidade);
            break;
        }
        case 4:
        {
            int data_atual = (int)time(NULL);
            imprimir_plantas_a_regar(plantas, total_plantas, data_atual, MAX_PLANTAS);
            break;
        }
        case 5:
        {
            listar_tarefas_pendentes(tarefas, total_tarefas);
            break;
        }
        case 6:
        {
            char descricao[100];
            int data_prevista;
            printf("Descricao: ");
            fgets(descricao, sizeof(descricao), stdin);
            descricao[strcspn(descricao, "\n")] = '\0';
            printf("Data prevista: ");
            scanf("%d", &data_prevista);
            while (getchar() != '\n')
                ;
            criar_tarefa(tarefas, &total_tarefas, MAX_TAREFAS,
                         descricao, data_prevista);
            break;
        }
        case 7:
        {
            int id;
            printf("ID da tarefa: ");
            scanf("%d", &id);
            while (getchar() != '\n')
                ;
            concluir_tarefa(tarefas, total_tarefas, id);
            break;
        }
        case 8:
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    } while (opcao != 8);

    guardar_dados(plantas, regas, tarefas,
                  total_plantas, total_regas, total_tarefas);

    for (int i = 0; i < total_plantas; i++)
        planta_destruir(plantas[i]);
    for (int i = 0; i < total_regas; i++)
        rega_destruir(regas[i]);
    for (int i = 0; i < total_tarefas; i++)
        tarefa_destruir(tarefas[i]);

    return 0;
}