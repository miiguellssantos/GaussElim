#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes.h"
#include <locale.h>
#include <string.h>

int main()
{
    setlocale(LC_ALL, ""); // incluir acentos no terminal (ARRUMAR)
    int equacoes = 0;

    printf("Quantas equações serão digitadas? ");
    if (scanf("%d", &equacoes) == 1 && equacoes > 0)
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        // 1. ALOCAÇÃO DINÂMICA
        // Aloca o array de ponteiros para as linhas
        double **matriz = (double **)malloc(equacoes * sizeof(double *));
        if (matriz == NULL)
        {
            printf("Erro ao alocar memória!\n");
            return 1;
        }

        // Aloca cada linha com a quantidade de colunas (ex: equacoes + 1 se tiver termo independente)
        int colunas = equacoes; // ou equacoes + 1
        for (int i = 0; i < equacoes; i++)
        {
            matriz[i] = (double *)malloc(colunas * sizeof(double));
            if (matriz[i] == NULL)
            {
                printf("Erro ao alocar memória para a linha %d!\n", i);
                return 1;
            }
        }

        scan_equacao(equacoes, matriz);

        // 3. LIBERAÇÃO DE MEMÓRIA (Obrigatório)
        for (int i = 0; i < equacoes; i++)
        {
            free(matriz[i]); // Libera cada linha
        }
        free(matriz); // Libera o array principal de ponteiros
    }

    return 0;
}