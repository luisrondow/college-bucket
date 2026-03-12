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

#define MAX 100
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

void *rebuild_sentence(char *s, char *original, int new_sentence_len, SpecialChars *sc)
{
    int j = 0;

    for (int i = 0; i < new_sentence_len; i++)
    {
        if (i == sc->pos[j])
        {
            if (original[i] < 'A' || original[i] > 'Z')
                memmove(s + (i + 1), s + i, new_sentence_len - i);

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

    for (int i = 1; i <= (new_sentence_length / 2); i++)
    {
        if (sentence[i - 1] != sentence[new_sentence_length - i])
        {
            printf("It's not a palindrome");
            return 0;
        }
    }

    rebuild_sentence(sentence, original, (string_length(sentence) + sc.count), &sc);

    printf("It's a palindrome, original sentence: \n\n");
    printf("%s", sentence);

    return 0;
}