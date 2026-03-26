#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar dados de um estudante
typedef struct
{
    char nome[50];
    float nota;
} Estudante;

// Protótipos das funções
void adicionarEstudante(char *nome, float nota, int *numEstudantes, Estudante **estudantes, int *maxQuant);
float calcularMedia(int numEstudantes, Estudante *estudantes);
void listarEstudantes(int numEstudantes, Estudante *estudantes);
void libertarMemoria(Estudante *estudantes);

#define QUANTIDADE_ESTUDANTES 2

// Função principal
int main(void)
{
    int opcao;
    char nome_input[50];
    float nota_input;
    int numEstudantes = 0;
    int maxQuant = QUANTIDADE_ESTUDANTES;
    Estudante *estudantes = (Estudante *)malloc(QUANTIDADE_ESTUDANTES * sizeof(Estudante));

    if (estudantes == NULL)
    {
        printf("Erro ao alocar memoria");
        return 0;
    }

    do
    {
        printf("\n=== MENU ===\n");
        printf("1. Adicionar estudante\n");
        printf("2. Calcular média\n");
        printf("3. Listar estudantes\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            break;
        case 1:
            printf("Nome: ");
            scanf("%s", nome_input);

            do
            {
                printf("Nota: ");
                scanf("%f", &nota_input);

                if (nota_input < 0 || nota_input > 20)
                {
                    printf("Nota deve estar entre 0 e 20");
                }

            } while (nota_input < 0 || nota_input > 20);

            adicionarEstudante(nome_input, nota_input, &numEstudantes, &estudantes, &maxQuant);
            break;
        case 2:
            printf("Média: %.2f\n", calcularMedia(numEstudantes, estudantes));
            break;
        case 3:
            listarEstudantes(numEstudantes, estudantes);
            break;
        default:
            printf("Opcao Invalida\n");
        }
    } while (opcao != 0);

    libertarMemoria(estudantes);
    return 0;
}

// Adiciona um estudante à lista
void adicionarEstudante(char *nome, float nota, int *numEstudantes, Estudante **estudantes, int *maxQuant)
{
    if (*numEstudantes < *maxQuant)
    {
        strcpy((*estudantes)[*numEstudantes].nome, nome);
        (*estudantes)[*numEstudantes].nota = nota;
        *numEstudantes = *numEstudantes + 1;
        printf("Estudante adicionado com sucesso!\n");
    }
    else
    {
        Estudante *tempE = realloc(*estudantes, (*maxQuant * 2) * sizeof(Estudante));
        if (tempE != NULL)
        {
            printf("Memoria realocada!\n");
            *estudantes = tempE;
            *maxQuant = *maxQuant * 2;

            strcpy((*estudantes)[*numEstudantes].nome, nome);
            (*estudantes)[*numEstudantes].nota = nota;
            *numEstudantes = *numEstudantes + 1;
            printf("Estudante adicionado com sucesso!\n");
        }
        else
        {
            printf("Erro ao realocar memoria ");
            return;
        }
    }
}

// Calcula a média das notas
float calcularMedia(int numEstudantes, Estudante *estudantes)
{
    if (numEstudantes == 0)
    {
        printf("Nenhum estudante registado.\n");

        return 0.0;
    }

    float soma = 0;
    int i;

    for (i = 0; i < numEstudantes; i++)
    {
        soma = soma + estudantes[i].nota;
    }

    return soma / numEstudantes;
}

// Lista todos os estudantes
void listarEstudantes(int numEstudantes, Estudante *estudantes)
{
    int i;

    if (numEstudantes == 0)
    {
        printf("Nenhum estudante registado.\n");
        return;
    }

    printf("\n=== Lista de Estudantes ===\n");
    for (i = 0; i < numEstudantes; i++)
    {
        printf("%d. %s - %.2f\n", i + 1, estudantes[i].nome, estudantes[i].nota);
    }
}

// Liberta a memória alocada
void libertarMemoria(Estudante *estudantes)
{
    printf("A libertar memória...\n");
    free(estudantes);
}