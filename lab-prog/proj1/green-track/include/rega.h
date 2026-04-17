/* rega.h */
#ifndef REGA_H
#define REGA_H

#include "planta.h"

typedef struct Rega *RegaPtr;

RegaPtr rega_criar(int id_rega, int id_planta,
                   int data_rega, int quantidade_agua);

void rega_destruir(RegaPtr r);

int rega_get_id_rega(RegaPtr r);

int rega_get_id_planta(RegaPtr r);

int rega_get_data_rega(RegaPtr r);

int rega_get_quantidade_agua(RegaPtr r);

int registar_rega(PlantaPtr *plantas, int total_plantas,
                  RegaPtr *regas, int *total_regas, int max_regas,
                  int id_planta, int data, int quantidade);

int verificar_rega(PlantaPtr *plantas, int total_plantas,
                   int data_atual, int ids[], int max_ids);

#endif