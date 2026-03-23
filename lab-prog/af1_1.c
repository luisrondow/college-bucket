/*
 * Tendo em conta que a noção de palíndromo não se restringe apenas a palavras isoladas, modifique o programa anteriormente desenvolvido na Atividade
 * Formativa 1 de modo a detetar palíndromos em sentido mais lato.
 * Considere que os palíndromos podem extravasar os limites das palavras e não têm em conta espaços, sinais de pontuação ou acentos.
 * Exemplos deste tipo de palíndromos incluem: “Roma me tem amor”, “após a sopa”, “Irene ri”, “Socorram-me, subi no ônibus em Marrocos” e “A inter etnia”.
 * Repare que podem existir palíndromos contidos noutros palíndromos (por exemplo, “me tem”), mas apenas devem ser identificados os palíndromos mais
 * abrangentes.
 * No output do programa, a expressão identificada como palíndromo deverá ser apresentada exatamente como surge no texto original,
 * preservando espaços, pontuação e acentuação (por exemplo, “Socorram-me, subi no ônibus em Marrocos” e não “socorrammesubinoonibusemmarrocos”).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000
#define MIN 3

typedef struct
{
    int *pos;
    size_t count;
    size_t capacity;
} SpecialChars;

int string_length(char *s)
{
    int n;
    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}

void *normalize_sentence(char *s, int sentencelen, SpecialChars *sc)
{
    int j = 0;
    for (int i = 0; i < sentencelen; i++)
    {
        if (isalnum(s[i]))
        {
            if (s[i] >= 'A' && s[i] <= 'Z')
            {
                s[j] = tolower(s[i]);

                if (sc->count >= sc->capacity)
                {
                    if (sc->capacity == 0)
                    {
                        sc->capacity = 256;
                    }
                    else
                    {
                        sc->capacity *= 2;
                    }
                    sc->pos = realloc(sc->pos, sc->capacity * sizeof(*sc->pos));
                }
                sc->pos[sc->count++] = i;
            }
            else
            {
                s[j] = s[i];
            }
            j++;
        }
        else if (s[i] != '\0')
        {
            if (sc->count >= sc->capacity)
            {
                if (sc->capacity == 0)
                {
                    sc->capacity = 256;
                }
                else
                {
                    sc->capacity *= 2;
                }
                sc->pos = realloc(sc->pos, sc->capacity * sizeof(*sc->pos));
            }
            sc->pos[sc->count++] = i;
        }
    }

    s[j] = '\0';
}

void *rebuild_sentence(char *s, char *original, int new_sentence_len, SpecialChars *sc, int *init_p, int *end_p)
{
    int j = 0;

    for (int i = 0; i < new_sentence_len; i++)
    {
        if (i == sc->pos[j])
        {
            if (original[i] < 'A' || original[i] > 'Z')
            {
                if (i <= *init_p)
                    *init_p = *init_p + 1;
                if (i <= *end_p)
                    *end_p = *end_p + 1;
                memmove(s + (i + 1), s + i, new_sentence_len - i);
            }

            s[i] = original[i];
            j++;
        }
    }
}

int main()
{
    char original[MAX];
    char sentence[MAX];

    int count;
    FILE *fptr;

    fptr = fopen("sentence.txt", "rt");

    if (fptr == NULL)
    {
        printf("Error opening the file");
        return 1;
    }

    fgets(sentence, MAX, fptr);

    int sentence_length = string_length(sentence);

    memcpy(original, sentence, sentence_length);
    original[sentence_length] = '\0';

    if (sentence_length < 3)
    {
        printf("Input sentence is to small");
        return 1;
    }

    printf("Before: \n %s\n\n", original);

    SpecialChars sc = {0};

    normalize_sentence(sentence, sentence_length, &sc);

    printf("After: \n %s\n\n", sentence);

    int new_sentence_length = string_length(sentence);

    int init_p = -1;
    int end_p = -1;
    int lft = 0;
    int rgt = new_sentence_length - 1;

    while (lft < new_sentence_length - 2)
    {
        // posicoes espelhadas diff -> mover pointeiro da direita
        if (sentence[lft] != sentence[rgt])
        {
            rgt--;
        }
        else
        {
            int has_inc = 0;
            // roda palindromo no range verificado
            for (int i = 0; i <= ((rgt - lft) / 2); i++)
            {
                if (sentence[i + lft] != sentence[rgt - i])
                {
                    has_inc = 1;
                    break;
                }
            }

            // Verifica se o palindromo encontrada eh maior que algum previamente encontrado
            if (has_inc == 0 && ((rgt - lft) > (end_p - init_p)))
            {
                init_p = lft;
                end_p = rgt;
            }

            rgt--;
        }

        if (lft == rgt)
        {
            lft++;
            rgt = new_sentence_length - 1;
        }
    }

    printf("===== %d - %d\n\n", init_p, end_p);
    rebuild_sentence(sentence, original, (string_length(sentence) + sc.count), &sc, &init_p, &end_p);
    printf("===== %d - %d\n\n", init_p, end_p);

    if (init_p != -1 && end_p != -1)
    {
        char ans[end_p - init_p + 1];

        for (int i = 0; i <= end_p - init_p; i++)
        {
            ans[i] = sentence[i + init_p];
        }

        printf("It's a palindrome, palindrome: \n\n");
        printf("%s", ans);
    }
    else
    {
        printf("It's not a palindrome, full sentence: \n\n");
        printf("%s", sentence);
    }

    return 0;
}