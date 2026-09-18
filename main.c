#include <stdio.h>
#include <stdlib.h>
#include "libs/funcoes.h"
#include <windows.h>

int main() 
{
    SetConsoleOutputCP(65001);
    int equacoes = 0;

    printf("Quantas equações serão digitadas? ");
    if (scanf("%d", &equacoes) == 1 && equacoes > 0) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 

        // Alocação da matriz do tipo Fracao
        Fracao **matriz = (Fracao **) malloc(equacoes * sizeof(Fracao *));
        for (int i = 0; i < equacoes; i++) {
            matriz[i] = (Fracao *) malloc((equacoes + 1) * sizeof(Fracao));
        }

        scan_equacao(equacoes, matriz);
        escalonar_matriz(equacoes, matriz);
        imprime_matriz(equacoes, matriz, "Matriz Escalonada");
        resolver_substituicao_regressiva(equacoes, matriz);

        // Liberação de memória
        for (int i = 0; i < equacoes; i++) {
            free(matriz[i]);
        }
        free(matriz);
    }

    return 0;
}