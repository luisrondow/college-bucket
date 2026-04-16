#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLANTAS 100
#define MAX_REGAS 500
#define MAX_TAREFAS 200

typedef struct
{
    int id;
    char nome[50];
    char especie[50];
    char data_plantio[11];
    int intervalo_rega;
    int ultima_rega;
} Planta;

typedef struct
{
    int id_rega;
    int id_planta;
    int data_rega;
    int quantidade_agua;
} Rega;

typedef struct
{
    int id_tarefa;
    char descricao[100];
    int data_prevista;
    int concluida;
} Tarefa;

Planta plantas[MAX_PLANTAS];
Rega regas[MAX_REGAS];
Tarefa tarefas[MAX_TAREFAS];
int total_plantas = 0, total_regas = 0, total_tarefas = 0;

void carregar_dados()
{
    FILE *f_plantas = fopen("plantas.csv", "r");
    if (f_plantas != NULL)
    {
        while (fscanf(f_plantas, "%d,%[^,],%[^,],%[^,],%d,%d\n",
                      &plantas[total_plantas].id,
                      plantas[total_plantas].nome,
                      plantas[total_plantas].especie,
                      plantas[total_plantas].data_plantio,
                      &plantas[total_plantas].intervalo_rega,
                      &plantas[total_plantas].ultima_rega) == 6)
        {
            total_plantas++;
        }
        fclose(f_plantas);
    }

    FILE *f_regas = fopen("regas.csv", "r");
    if (f_regas != NULL)
    {
        while (fscanf(f_regas, "%d,%d,%d,%d\n",
                      &regas[total_regas].id_rega,
                      &regas[total_regas].id_planta,
                      &regas[total_regas].data_rega,
                      &regas[total_regas].quantidade_agua) == 4)
        {
            total_regas++;
        }
        fclose(f_regas);
    }

    FILE *f_tarefas = fopen("tarefas.csv", "r");
    if (f_tarefas != NULL)
    {
        while (fscanf(f_tarefas, "%d,%[^,],%d,%d\n",
                      &tarefas[total_tarefas].id_tarefa,
                      tarefas[total_tarefas].descricao,
                      &tarefas[total_tarefas].data_prevista,
                      &tarefas[total_tarefas].concluida) == 4)
        {
            total_tarefas++;
        }
        fclose(f_tarefas);
    }
}

void guardar_dados()
{
    FILE *f_plantas = fopen("plantas.csv", "w");
    if (f_plantas == NULL)
    {
        printf("Erro ao abrir plantas.csv\n");
        return;
    }
    for (int i = 0; i < total_plantas; i++)
    {
        fprintf(f_plantas, "%d,%s,%s,%s,%d,%d\n",
                plantas[i].id, plantas[i].nome, plantas[i].especie,
                plantas[i].data_plantio, plantas[i].intervalo_rega,
                plantas[i].ultima_rega);
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
        fprintf(f_regas, "%d,%d,%d,%d\n",
                regas[i].id_rega, regas[i].id_planta,
                regas[i].data_rega, regas[i].quantidade_agua);
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
        fprintf(f_tarefas, "%d,%s,%d,%d\n",
                tarefas[i].id_tarefa, tarefas[i].descricao,
                tarefas[i].data_prevista, tarefas[i].concluida);
    }
    fclose(f_tarefas);
}

void adicionar_planta(int id, char *nome, char *especie,
                      char *data_plantio, int intervalo)
{
    if (total_plantas >= MAX_PLANTAS)
    {
        printf("Erro: limite maximo de plantas atingido.\n");
        return;
    }
    plantas[total_plantas].id = id;
    strcpy(plantas[total_plantas].nome, nome);
    strcpy(plantas[total_plantas].especie, especie);
    strcpy(plantas[total_plantas].data_plantio, data_plantio);
    plantas[total_plantas].intervalo_rega = intervalo;
    plantas[total_plantas].ultima_rega = (int)time(NULL);
    total_plantas++;
}

void listar_plantas()
{
    printf("=== PLANTAS ===\n");
    for (int i = 0; i < total_plantas; i++)
    {
        printf("ID: %d | Nome: %s | Especie: %s | Intervalo: %d\n",
               plantas[i].id, plantas[i].nome,
               plantas[i].especie, plantas[i].intervalo_rega);
    }
}

int registar_rega(int id_planta, int data, int quantidade)
{
    if (total_regas >= MAX_REGAS)
    {
        printf("Erro: limite maximo de regas atingido.\n");
        return -1;
    }
    int planta_existe = 0;
    for (int i = 0; i < total_plantas; i++)
    {
        if (plantas[i].id == id_planta)
        {
            planta_existe = 1;
            break;
        }
    }
    if (!planta_existe)
    {
        printf("Erro: planta com id %d nao existe.\n", id_planta);
        return -1;
    }
    if (data > (int)time(NULL))
    {
        printf("Erro: data da rega nao pode estar no futuro.\n");
        return -1;
    }
    if (quantidade <= 0)
    {
        printf("Erro: quantidade de agua deve ser positiva.\n");
        return -1;
    }
    regas[total_regas].id_rega = total_regas + 1;
    regas[total_regas].id_planta = id_planta;
    regas[total_regas].data_rega = data;
    regas[total_regas].quantidade_agua = quantidade;
    total_regas++;
    return 1;
}

int verificar_rega(int data_atual, int ids[])
{
    int encontradas = 0;
    for (int i = 0; i < total_plantas; i++)
    {
        if (encontradas >= MAX_PLANTAS)
            break;
        int dias = data_atual - plantas[i].ultima_rega;
        if (dias >= plantas[i].intervalo_rega)
        {
            ids[encontradas++] = plantas[i].id;
        }
    }
    return encontradas;
}

void imprimir_plantas_a_regar(int data_atual)
{
    int ids[MAX_PLANTAS];
    int n = verificar_rega(data_atual, ids);
    printf("=== %d PLANTAS PRECISAM DE REGA ===\n", n);
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < total_plantas; i++)
        {
            if (plantas[i].id == ids[k])
            {
                int dias = data_atual - plantas[i].ultima_rega;
                printf("Planta %s (ID: %d) precisa de rega! (ultima: %d dias atras)\n",
                       plantas[i].nome, plantas[i].id, dias);
                break;
            }
        }
    }
}

int criar_tarefa(char *descricao, int data_prevista)
{
    if (total_tarefas >= MAX_TAREFAS)
    {
        printf("Erro: limite maximo de tarefas atingido.\n");
        return -1;
    }
    tarefas[total_tarefas].id_tarefa = total_tarefas + 1;
    strcpy(tarefas[total_tarefas].descricao, descricao);
    tarefas[total_tarefas].data_prevista = data_prevista;
    tarefas[total_tarefas].concluida = 0;
    total_tarefas++;
    return 1;
}

void listar_tarefas_pendentes()
{
    printf("=== TAREFAS PENDENTES ===\n");
    for (int i = 0; i < total_tarefas; i++)
    {
        if (tarefas[i].concluida == 0)
        {
            printf("Tarefa %d: %s (prevista: %d)\n",
                   tarefas[i].id_tarefa, tarefas[i].descricao,
                   tarefas[i].data_prevista);
        }
    }
}

void concluir_tarefa(int id)
{
    for (int i = 0; i < total_tarefas; i++)
    {
        if (tarefas[i].id_tarefa == id)
        {
            tarefas[i].concluida = 1;
            return;
        }
    }
    printf("Tarefa %d nao encontrada.\n", id);
}

int main()
{
    carregar_dados();

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
            while (getchar() != '\n')
                ;
            printf("Intervalo de rega (dias): ");
            scanf("%d", &intervalo);
            while (getchar() != '\n')
                ;
            adicionar_planta(id, nome, especie, data, intervalo);
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
            criar_tarefa(descricao, data_prevista);
            break;
        }
        }
    } while (opcao != 8);

    guardar_dados();

    return 0;
}
