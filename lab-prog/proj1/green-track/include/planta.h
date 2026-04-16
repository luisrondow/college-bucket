/* planta.h */
#ifndef PLANTA_H
#define PLANTA_H

typedef struct Planta *PlantaPtr;

PlantaPtr planta_criar(int id, const char *nome, const char *especie,
                       const char *data_plantio, int intervalo_rega,
                       int ultima_rega);

void planta_destruir(PlantaPtr p);

int planta_get_id(const PlantaPtr p);

const char *planta_get_nome(const PlantaPtr p);

const char *planta_get_especie(const PlantaPtr p);

const char *planta_get_data_plantio(const PlantaPtr p);

int planta_get_intervalo_rega(const PlantaPtr p);

int planta_get_ultima_rega(const PlantaPtr p);

void adicionar_planta(PlantaPtr *plantas, int *total_plantas, int max_plantas,
                      int id, const char *nome, const char *especie,
                      const char *data_plantio, int intervalo);

void listar_plantas(PlantaPtr *plantas, int total_plantas);

void imprimir_plantas_a_regar(PlantaPtr *plantas, int total_plantas, int data_atual, int max_plantas);

#endif