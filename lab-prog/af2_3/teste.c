#include <stdio.h>
#include "geometria.h"

const double pi = 3.14159;

typedef struct
{
    double raio;
} Circulo;

typedef struct
{
    double base;
    double altura;
} Retangulo;

int main()
{
    Circulo c;
    Retangulo r;

    printf("=== Circulo ===\n\n");
    printf("Insira o raio:");
    scanf("%lf", &c.raio);

    printf("\n=== Retangulo ===\n\n");
    printf("Insira a base:");
    scanf("%lf", &r.base);

    printf("\nInsira a altura:");
    scanf("%lf", &r.altura);

    printf("\nÁrea círculo (r=%d): %.2f", (int)c.raio, areaCirculo(c.raio));
    printf("\nÁrea retângulo (%dx%d): %.2f", (int)r.base, (int)r.altura, areaRetangulo(r.base, r.altura));

    return 0;
}