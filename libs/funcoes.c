#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int *identifica_numeros(const char *equacao, int *qtd)
{
    // Aloca espaço razoável para os números extraídos
    int *numeros = malloc(50 * sizeof(int));
    if (numeros == NULL) return NULL;

    int num_count = 0;

    for (int i = 0; equacao[i] != '\0';)
    {
        if (isdigit((unsigned char)equacao[i]))
        {
            int valor_atual = 0;
            while (isdigit((unsigned char)equacao[i]))
            {
                valor_atual = valor_atual * 10 + (equacao[i] - '0');
                i++;
            }
            numeros[num_count++] = valor_atual;
        }
        else
        {
            i++;
        }
    }

    *qtd = num_count;
    return numeros;
}

/*
int *identifica_numeros(const char *equacao, int *qtd)
{
    int *numeros = malloc(50 * sizeof(int));
    int num_count = 0;

    for (int i = 0; equacao[i] != '\0';)
    {
        if (isdigit(equacao[i]))
        {
            int valor_atual = 0;
            while (isdigit(equacao[i]))
            {
                valor_atual = valor_atual * 10 + (equacao[i] - '0');
                i++;
            }
            numeros[num_count++] = valor_atual;
        }
        else
        {
            i++;
        }
    }

    *qtd = num_count;
    return numeros;
} 
*/

void scan_equacao(int n)
{
    char equacao[50];

    for (int i = 0; i < n; i++)
    {
        printf("\nDigite a equação %d: ", i + 1);
        
        // Lê a linha inteira incluindo espaços (máx 49 chars)
        if (fgets(equacao, sizeof(equacao), stdin) == NULL) continue;

        int qtd_equacao = 0; // Quantidade específica DESTA equação
        int *numeros = identifica_numeros(equacao, &qtd_equacao);

        if (numeros != NULL)
        {
            printf("Números encontrados (%d): ", qtd_equacao);
            for (int j = 0; j < qtd_equacao; j++)
            {
                printf("%d ", numeros[j]);
            }
            printf("\n");

            free(numeros); // Evita vazamento de memória
        }
    }
}

/*
void scan_equacao(int n, int *qtd)
{
    char equacao[50];
    for (int i = 0; i < n; i++)
    {
        printf("Digite a equação %d:", i + 1);
        scanf("%49s", equacao);
        int *numeros = identifica_numeros(equacao, qtd);

        printf("Números encontrados: ");
        for (int j = 0; j < *qtd; j++){
            printf("%d ", numeros[j]);
        }
        printf("\n");

        free(numeros);
    }
}
    */