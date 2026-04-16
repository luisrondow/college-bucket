#include "rega.h"
#include "planta.h"

#include <stdlib.h>

struct Rega
{
    int id_rega;
    int id_planta;
    int data_rega;
    int quantidade_agua;
};

RegaPtr rega_criar(int id_rega, int id_planta,
                   int data_rega, int quantidade_agua)
{
    RegaPtr r = malloc(sizeof(struct Rega));
    if (!r)
        return NULL;

    r->id_rega = id_rega;
    r->id_planta = id_planta;
    r->data_rega = data_rega;
    r->quantidade_agua = quantidade_agua;
    return r;
}

void rega_destruir(RegaPtr r)
{
    free(r);
}

int rega_get_id_rega(RegaPtr r) { return r->id_rega; }
int rega_get_id_planta(RegaPtr r) { return r->id_planta; }
int rega_get_data_rega(RegaPtr r) { return r->data_rega; }
int rega_get_quantidade_agua(RegaPtr r) { return r->quantidade_agua; }

int registar_rega(PlantaPtr *plantas, int total_plantas,
                  RegaPtr *regas, int *total_regas, int max_regas,
                  int id_planta, int data, int quantidade)
{
    if (*total_regas >= max_regas)
    {
        printf("Erro: limite maximo de regas atingido.\n");
        return -1;
    }

    int planta_existe = 0;
    for (int i = 0; i < total_plantas; i++)
    {
        if (planta_get_id(plantas[i]) == id_planta)
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

    regas[*total_regas] = rega_criar(*total_regas + 1, id_planta, data, quantidade);
    (*total_regas)++;
    return 1;
}

int verificar_rega(PlantaPtr *plantas, int total_plantas,
                   int data_atual, int ids[], int max_ids)
{
    int encontradas = 0;
    for (int i = 0; i < total_plantas; i++)
    {
        if (encontradas >= max_ids)
            break;

        PlantaPtr p = plantas[i];
        int dias = data_atual - planta_get_ultima_rega(p);
        if (dias >= planta_get_intervalo_rega(p))
        {
            ids[encontradas++] = planta_get_id(p);
        }
    }
    return encontradas;
}
