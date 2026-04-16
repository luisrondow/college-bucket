#include "planta.h"

#include <stdlib.h>
#include <string.h>

struct Planta
{
    int id;
    char nome[50];
    char especie[50];
    char data_plantio[11];
    int intervalo_rega;
    int ultima_rega;
};

PlantaPtr planta_criar(int id, const char *nome, const char *especie,
                       const char *data_plantio, int intervalo_rega,
                       int ultima_rega)
{
    PlantaPtr p = malloc(sizeof(struct Planta));
    if (!p)
        return NULL;

    p->id = id;
    strcpy(p->nome, nome);
    strcpy(p->especie, especie);
    strcpy(p->data_plantio, data_plantio);
    p->intervalo_rega = intervalo_rega;
    p->ultima_rega = ultima_rega;
    return p;
}

void planta_destruir(PlantaPtr p)
{
    free(p);
}

int planta_get_id(PlantaPtr p) { return p->id; }
const char *planta_get_nome(PlantaPtr p) { return p->nome; }
const char *planta_get_especie(PlantaPtr p) { return p->especie; }
const char *planta_get_data_plantio(PlantaPtr p) { return p->data_plantio; }
int planta_get_intervalo_rega(PlantaPtr p) { return p->intervalo_rega; }
int planta_get_ultima_rega(PlantaPtr p) { return p->ultima_rega; }

void adicionar_planta(PlantaPtr *plantas, int *total_plantas, int max_plantas,
                      int id, const char *nome, const char *especie,
                      const char *data_plantio, int intervalo)
{
    if (*total_plantas >= max_plantas)
    {
        printf("Erro: limite maximo de plantas atingido.\n");
        return;
    }

    plantas[*total_plantas] = planta_criar(id, nome, especie, data_plantio,
                                           intervalo, (int)time(NULL));
    (*total_plantas)++;
}

void listar_plantas(PlantaPtr *plantas, int total_plantas)
{
    printf("=== PLANTAS ===\n");
    for (int i = 0; i < total_plantas; i++)
    {
        PlantaPtr p = plantas[i];
        printf("ID: %d | Nome: %s | Especie: %s | Intervalo: %d\n",
               planta_get_id(p),
               planta_get_nome(p),
               planta_get_especie(p),
               planta_get_intervalo_rega(p));
    }
}

void imprimir_plantas_a_regar(PlantaPtr *plantas, int total_plantas, int data_atual, int max_plantas)
{
    int ids[max_plantas];
    int n = verificar_rega(plantas, total_plantas, data_atual, ids, max_plantas);
    printf("=== %d PLANTAS PRECISAM DE REGA ===\n", n);
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < total_plantas; i++)
        {
            PlantaPtr p = plantas[i];
            if (planta_get_id(p) == ids[k])
            {
                int dias = data_atual - planta_get_ultima_rega(p);
                printf("Planta %s (ID: %d) precisa de rega! (ultima: %d dias atras)\n",
                       planta_get_nome(p),
                       planta_get_id(p),
                       dias);
                break;
            }
        }
    }
}
