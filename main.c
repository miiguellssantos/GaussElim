#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes.h"
#include <locale.h>

int main() 
{
    setlocale(LC_ALL, "");
    int equacoes = 0;

    printf("Quantas equações serão digitadas? ");
    if (scanf("%d", &equacoes) == 1 && equacoes > 0)
    {
        // Limpa o '\n' restante do buffer do scanf antes de usar fgets
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        scan_equacao(equacoes);
    }

    return 0;
}

/*
int main() {
    setlocale(LC_ALL, "");
    int quantidade = 0;
    int equacoes = 0;

    printf("Quantas equações serão digitadas? ");
    scanf("%d", &equacoes);

    scan_equacao(equacoes, &quantidade);
    
    return 0;
} */

/*
char equacao[] = "12x + 52y - 3 = 0";

int *numeros = identifica_numeros(equacao, &quantidade);


printf("Números encontrados: ");
for (int i = 0; i < quantidade; i++) {
    printf("%d ", numeros[i]);
}
printf("\n");
free(numeros);
*/