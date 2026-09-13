#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int obtém_indice_var(char c, int n) {
    char var = tolower((unsigned char)c);
    
    // Se o sistema for de 3 variáveis (x, y, z)
    if (n == 3) {
        switch (var) {
            case 'x': return 0;
            case 'y': return 1;
            case 'z': return 2;
            default:  return -1;
        }
    } 
    // Se for de 4 variáveis (w, x, y, z)
    else if (n == 4) {
        switch (var) {
            case 'w': return 0;
            case 'x': return 1;
            case 'y': return 2;
            case 'z': return 3;
            default:  return -1;
        }
    }
    // Se for de 5 variáveis (v, w, x, y, z)
    else if (n == 5) {
        switch (var) {
            case 'w': return 0;
            case 'x': return 1;
            case 'y': return 2;
            case 'z': return 3;
            default:  return -1;
        }
    }
    
    return -1;
}

char obtém_nome_var(int index, int n) {
    if (n == 3) {
        char vars[] = {'x', 'y', 'z'};
        return vars[index];
    } else if (n == 4) {
        char vars[] = {'w', 'x', 'y', 'z'};
        return vars[index];
    } else if (n == 5) {
        char vars[] = {'v', 'w', 'x', 'y', 'z'};
        return vars[index];
    }
    return '?';
}

double *identifica_numeros(const char *equacao, int n)
{
    double *linha_matriz = (double *) calloc(n + 1, sizeof(double));
    if (linha_matriz == NULL) return NULL;

    int depois_do_igual = 0;

    for (int i = 0; equacao[i] != '\0'; )
    {
        if (isspace((unsigned char)equacao[i])) {
            i++;
            continue;
        }

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
            coef = atof(&equacao[i]);
            while (isdigit((unsigned char)equacao[i]) || equacao[i] == '.') i++;
            leu_numero = 1;
        }

        while (isspace((unsigned char)equacao[i])) i++;

        // 3. Atribuição à Matriz
        if (depois_do_igual) {
            if (leu_numero) {
                linha_matriz[n] = sinal * coef;
            }
        } 
        else if (isalpha((unsigned char)equacao[i])) {
            // Passamos 'n' para mapear x->0, y->1, z->2 corretamente em 3x3
            int col = obtém_indice_var(equacao[i], n);
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
        printf("  %.2f\n", matriz[i][n]);
    }
}

void escalonar_matriz(int n, double **matriz)
{
    for (int k = 0; k < n - 1; k++) {
        
        // Verifica se o pivô é zero para evitar divisão por zero simples
        if (fabs(matriz[k][k]) < 1e-9) {
            // Tenta encontrar uma linha abaixo com valor não nulo apenas se o pivô for zero
            for (int i = k + 1; i < n; i++) {
                if (fabs(matriz[i][k]) > 1e-9) {
                    double *temp = matriz[k];
                    matriz[k] = matriz[i];
                    matriz[i] = temp;
                    break;
                }
            }
        }

        if (fabs(matriz[k][k]) < 1e-9) continue;

        // Eliminação dos elementos abaixo do pivô
        for (int i = k + 1; i < n; i++) {
            double fator = matriz[i][k] / matriz[k][k];
            
            for (int j = k; j <= n; j++) {
                matriz[i][j] -= fator * matriz[k][j];
            }
        }
    }
}

void imprime_matriz(int n, double **matriz, const char *titulo)
{
    printf("\n--- %s ---\n", titulo);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Evita exibir -0.00 devido à precisão de ponto flutuante
            double val = fabs(matriz[i][j]) < 1e-9 ? 0.0 : matriz[i][j];
            printf("%.2f\t", val);
        }
        double termo_indep = fabs(matriz[i][n]) < 1e-9 ? 0.0 : matriz[i][n];
        printf("|  %.2f\n", termo_indep);
    }
}

void resolver_substituicao_regressiva(int n, double **matriz)
{
    double *solucao = (double *) malloc(n * sizeof(double));
    if (solucao == NULL) return;

    // Resolve de baixo para cima (i de n-1 até 0)
    for (int i = n - 1; i >= 0; i--) {
        
        // Verifica se o pivô é zero (sistema sem solução única)
        if (fabs(matriz[i][i]) < 1e-9) {
            printf("\nO sistema não possui solução única (possível SPI ou SI).\n");
            free(solucao);
            return;
        }

        double soma = 0.0;
        for (int j = i + 1; j < n; j++) {
            soma += matriz[i][j] * solucao[j];
        }

        // Isola x_i: (termo_independente - soma_dos_conhecidos) / pivo
        solucao[i] = (matriz[i][n] - soma) / matriz[i][i];
    }

    // Exibição dos resultados finais
    printf("\n--- Solução do Sistema ---\n");
    for (int i = 0; i < n; i++) {
        // Limpa potenciais valores -0.00 de ponto flutuante
        double val = fabs(solucao[i]) < 1e-9 ? 0.0 : solucao[i];
        printf("%c = %.2f\n", obtém_nome_var(i, n), val);
    }

    free(solucao);
}