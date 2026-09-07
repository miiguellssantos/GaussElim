#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>

double *identifica_numeros(const char *equacao, int *qtd)
{
    // Aloca espaço razoável para os números extraídos
    double *numeros = malloc(50 * sizeof(double));
    if (numeros == NULL) return NULL;

    int num_count = 0;

    for (int i = 0; equacao[i] != '\0';)
    {
        if (isdigit((unsigned char)equacao[i]))
        {
            double valor_atual = 0;
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

void scan_equacao(int n, double matriz[3][3])
{
    char equacao[50];

    // inicia a matriz zerada
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matriz[i][j] = 0.0;
        }
    }

    for (int i = 0; i < n && i < 3; i++)
    {
        printf("\nDigite a equação %d: ", i + 1);
        
        // Loop para ignorar linhas vazias deixadas por scanfs anteriores
        do {
            if (fgets(equacao, sizeof(equacao), stdin) == NULL) break;
            
            // Remove o '\n' do final da string lida
            equacao[strcspn(equacao, "\n")] = '\0';
            
        } while (strlen(equacao) == 0); // Se for linha vazia, tenta ler novamente

        int qtd_equacao = 0; // Quantidade específica DESTA equação
        double *numeros = identifica_numeros(equacao, &qtd_equacao);

        if (numeros != NULL){
            for (int j = 0; j < qtd_equacao && j < 3; j++)
            {
                matriz[i][j] = numeros[j];
            }
            free(numeros);
        }
    }

    // Exibição do resultado
    printf("\nMatriz Resultante:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.2f\t", matriz[i][j]);
        }
        printf("\n");
    }
    
}