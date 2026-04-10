#include <stdio.h>
#include "stats.h"

int main()
{
    adicionar_valor(10.5);
    adicionar_valor(20.0);
    printf("Média: %.2f\n", calcular_media());
    return 0;
}