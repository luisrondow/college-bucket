#ifndef GEOMETRIA_H
#define GEOMETRIA_H

/**
 * @file geometria.h
 * @brief Funções para cálculo de áreas de figuras geométricas.
 */

/** @brief Valor da constante π (pi). */
extern const double pi;

/**
 * @brief Calcula a área de um círculo.
 * @param raio Raio do círculo (deve ser >= 0).
 * @return Área do círculo (π × raio²).
 */
double areaCirculo(double raio);

/**
 * @brief Calcula a área de um retângulo.
 * @param base Comprimento da base (deve ser >= 0).
 * @param altura Comprimento da altura (deve ser >= 0).
 * @return Área do retângulo (base × altura).
 */
double areaRetangulo(double base, double altura);

#endif /* GEOMETRIA_H */