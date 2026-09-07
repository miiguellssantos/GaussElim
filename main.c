#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcoes.h"
#include <locale.h>

int main() 
{
    setlocale(LC_ALL, ""); // incluir acentos no terminal (ARRUMAR)
    int equacoes = 0;

    printf("Quantas equações serão digitadas? ");
    if (scanf("%d", &equacoes) == 1 && equacoes > 0){
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 

        scan_equacao(equacoes);
    }

    return 0;
}