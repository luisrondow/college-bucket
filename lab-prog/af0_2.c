/*
 * Escreva um programa para encontrar palíndromos num ficheiro de texto. Um palíndromo é uma sequência de caracteres que se lê da mesma forma,
 * tanto da esquerda para a direita como da direita para a esquerda. Exemplos de palíndromos: sacas, rapar, rodador, anilina.
 * Considere apenas palíndromos de comprimentos entre 3 e 10 caracteres.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXWORD 10
#define MINWORD 3

int string_length(char *s)
{
    int n;
    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}

int main()
{
    char word[MAXWORD];

    int count;
    FILE *fptr;

    fptr = fopen("word.txt", "rt");

    if (fptr == NULL)
    {
        printf("Error opening the file");
        return 1;
    }

    fgets(word, MAXWORD, fptr);

    int word_length = string_length(word);

    if (word_length < 3)
    {
        printf("Input word is to small");
        return 1;
    }

    for (int i = 1; i <= (word_length / 2); i++)
    {
        if (word[i - 1] != word[word_length - i])
        {
            printf("It's not a palindrome");
            return 0;
        }
    }

    printf("It's a palindrome");

    return 0;
}