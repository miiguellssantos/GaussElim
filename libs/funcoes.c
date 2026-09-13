#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include<string.h>

// Retorna o índice da coluna com base no caractere da variável
int obtém_indice_var(char c) {
    switch (tolower((unsigned char)c)) {
        case 'w': return 0;
        case 'x': return 1;
        case 'y': return 2;
        case 'z': return 3;
        default:  return -1; // Caractere inválido
    }
}

double *identifica_numeros(const char *equacao, int n)
{
    // Aloca n + 1 colunas (n para variáveis + 1 para o termo independente)
    double *linha_matriz = (double *) calloc(n + 1, sizeof(double));
    if (linha_matriz == NULL) return NULL;

    int depois_do_igual = 0;

    for (int i = 0; equacao[i] != '\0'; )
    {
        // Ignora espaços
        if (isspace((unsigned char)equacao[i])) {
            i++;
            continue;
        }

        // Detecta a transição para o termo independente
        if (equacao[i] == '=') {
            depois_do_igual = 1;
            i++;
            continue;
        }

        // 1. Sinal (+ ou -)
        int sinal = 1;
        if (equacao[i] == '-') {
            sinal = -1;
            i++;
        } else if (equacao[i] == '+') {
            i++;
        }

        while (isspace((unsigned char)equacao[i])) i++;

        // 2. Leitura do Coeficiente
        double coef = 1.0;
        int leu_numero = 0;

        if (isdigit((unsigned char)equacao[i]) || equacao[i] == '.') {
            coef = atof(&equacao[i]); // Leitura tratada (aceita decimais)
            while (isdigit((unsigned char)equacao[i]) || equacao[i] == '.') i++;
            leu_numero = 1;
        }

        while (isspace((unsigned char)equacao[i])) i++;

        // 3. Atribuição à Matriz
        if (depois_do_igual) {
            // Se já passou do '=', guarda o valor na última coluna (posição n)
            if (leu_numero) {
                linha_matriz[n] = sinal * coef;
            }
        } 
        else if (isalpha((unsigned char)equacao[i])) {
            int col = obtém_indice_var(equacao[i]);
            if (col >= 0 && col < n) {
                linha_matriz[col] = sinal * coef;
            }
            i++;
        }
    }

    return linha_matriz;
}

void scan_equacao(int n, double **matriz)
{
    char equacao[100];

    for (int i = 0; i < n; i++)
    {
        printf("\nDigite a equação %d: ", i + 1);
        
        do {
            if (fgets(equacao, sizeof(equacao), stdin) == NULL) break;
            equacao[strcspn(equacao, "\n")] = '\0';
        } while (strlen(equacao) == 0);

        double *linha = identifica_numeros(equacao, n);

        if (linha != NULL) {
            // Copia n + 1 colunas (coeficientes + termo independente)
            for (int j = 0; j <= n; j++) {
                matriz[i][j] = linha[j];
            }
            free(linha);
        }
    }

    // Exibição da Matriz Aumentada
    printf("\nMatriz Aumentada Resultante:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f\t", matriz[i][j]);
        }
        // Exibe o termo independente separado por barra
        printf("|  %.2f\n", matriz[i][n]);
    }
}