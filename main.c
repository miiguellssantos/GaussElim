#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes.h"

int main() {
    char equacao[] = "12x + 52y - 3 = 0";
    int quantidade = 0;
    
    int *numeros = identifica_numeros(equacao, &quantidade);

    printf("Números encontrados: ");
    for (int i = 0; i < quantidade; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    free(numeros);
    return 0;
}