#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int* identifica_numeros(const char *equacao, int *qtd) {
    int *numeros = malloc(50 * sizeof(int));
    int num_count = 0;

    for (int i = 0; equacao[i] != '\0'; ) {
        if (isdigit(equacao[i])) {
            int valor_atual = 0;
            while (isdigit(equacao[i])) {
                valor_atual = valor_atual * 10 + (equacao[i] - '0');
                i++;
            }
            numeros[num_count++] = valor_atual;
        } else {
            i++;
        }
    }
    
    *qtd = num_count;
    return numeros;
}

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