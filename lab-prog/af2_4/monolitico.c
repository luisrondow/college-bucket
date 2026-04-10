/* monolitico.c */
#include <stdio.h>

int contador = 0;
float soma = 0;

void adicionar_valor(float v)
{
    contador++;
    soma += v;
}

float calcular_media()
{
    return soma / contador;
}

int main()
{
    adicionar_valor(10.5);
    adicionar_valor(20.0);
    printf("Média: %.2f\n", calcular_media());
    return 0;
}