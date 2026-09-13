#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes.h"
#include <string.h>
#include <windows.h>

int main() 
{
    SetConsoleOutputCP(65001);
    int equacoes = 0;

    printf("Quantas equações serão digitadas? ");
    if (scanf("%d", &equacoes) == 1 && equacoes > 0) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 

        // Alocação para Matriz Aumentada: 'equacoes' linhas por 'equacoes + 1' colunas
        double **matriz = (double **) malloc(equacoes * sizeof(double *));
        for (int i = 0; i < equacoes; i++) {
            matriz[i] = (double *) malloc((equacoes + 1) * sizeof(double));
        }

        scan_equacao(equacoes, matriz);
        escalonar_matriz(equacoes, matriz);
        imprime_matriz(equacoes, matriz, "Matriz Escalonada");

        // Liberação de memória
        for (int i = 0; i < equacoes; i++) {
            free(matriz[i]);
        }
        free(matriz);
    }

    return 0;
}