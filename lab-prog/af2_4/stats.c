#include "stats.h"

static int contador = 0;
static float soma = 0;

void adicionar_valor(float v)
{
    contador++;
    soma += v;
}

float calcular_media()
{
    return soma / contador;
}
