#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "funcoes.h"

// --- OPERAÇÕES COM FRAÇÕES ---

// Algoritmo de Euclides para o MDC
long long mdc(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fracao criar_fracao(long long num, long long den) {
    if (den == 0) {
        printf("\nErro: Divisão por zero em fração!\n");
        exit(1);
    }
    if (den < 0) { // Garante o sinal sempre no numerador
        num = -num;
        den = -den;
    }
    long long div = mdc(num, den);
    Fracao f = { num / div, den / div };
    return f;
}

Fracao somar(Fracao a, Fracao b) {
    return criar_fracao(a.num * b.den + b.num * a.den, a.den * b.den);
}

Fracao subtrair(Fracao a, Fracao b) {
    return criar_fracao(a.num * b.den - b.num * a.den, a.den * b.den);
}

Fracao multiplicar(Fracao a, Fracao b) {
    return criar_fracao(a.num * b.num, a.den * b.den);
}

Fracao dividir(Fracao a, Fracao b) {
    return criar_fracao(a.num * b.den, a.den * b.num);
}

void imprimir_fracao(Fracao f) {
    if (f.den == 1) {
        printf("%lld", f.num);
    } else {
        printf("%lld/%lld", f.num, f.den);
    }
}

// --- MAPEAMENTO DE VARIÁVEIS ---

int obtém_indice_var(char c, int n) {
    char var = tolower((unsigned char)c);
    if (n == 3) {
        switch (var) {
            case 'x': return 0;
            case 'y': return 1;
            case 'z': return 2;
            default:  return -1;
        }
    } else if (n == 4) {
        switch (var) {
            case 'w': return 0;
            case 'x': return 1;
            case 'y': return 2;
            case 'z': return 3;
            default:  return -1;
        }
    } else if (n == 5) {
        switch (var) {
            case 'v': return 0;
            case 'w': return 1;
            case 'x': return 2;
            case 'y': return 3;
            case 'z': return 4;
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

// --- PARSER E LEITURA ---

Fracao *identifica_numeros(const char *equacao, int n)
{
    Fracao *linha_matriz = (Fracao *) malloc((n + 1) * sizeof(Fracao));
    if (linha_matriz == NULL) return NULL;

    for (int i = 0; i <= n; i++) {
        linha_matriz[i] = criar_fracao(0, 1);
    }

    int depois_do_igual = 0;

    for (int i = 0; equacao[i] != '\0'; )
    {
        if (isspace((unsigned char)equacao[i])) { i++; continue; }

        if (equacao[i] == '=') {
            depois_do_igual = 1;
            i++;
            continue;
        }

        int sinal = 1;
        if (equacao[i] == '-') { sinal = -1; i++; }
        else if (equacao[i] == '+') { i++; }

        while (isspace((unsigned char)equacao[i])) i++;

        long long val_num = 1;
        int leu_numero = 0;

        if (isdigit((unsigned char)equacao[i])) {
            val_num = 0;
            while (isdigit((unsigned char)equacao[i])) {
                val_num = val_num * 10 + (equacao[i] - '0');
                i++;
            }
            leu_numero = 1;
        }

        while (isspace((unsigned char)equacao[i])) i++;

        if (depois_do_igual) {
            if (leu_numero) {
                linha_matriz[n] = criar_fracao(sinal * val_num, 1);
            }
        } 
        else if (isalpha((unsigned char)equacao[i])) {
            int col = obtém_indice_var(equacao[i], n);
            if (col >= 0 && col < n) {
                linha_matriz[col] = criar_fracao(sinal * val_num, 1);
            }
            i++;
        }
    }

    return linha_matriz;
}

void scan_equacao(int n, Fracao **matriz)
{
    char equacao[100];

    for (int i = 0; i < n; i++)
    {
        printf("\nDigite a equação %d: ", i + 1);
        
        do {
            if (fgets(equacao, sizeof(equacao), stdin) == NULL) break;
            equacao[strcspn(equacao, "\n")] = '\0';
        } while (strlen(equacao) == 0);

        Fracao *linha = identifica_numeros(equacao, n);

        if (linha != NULL) {
            for (int j = 0; j <= n; j++) {
                matriz[i][j] = linha[j];
            }
            free(linha);
        }
    }

    imprime_matriz(n, matriz, "Matriz Aumentada Resultante");
}

// --- ESCALONAMENTO E RESOLUÇÃO ---

void escalonar_matriz(int n, Fracao **matriz)
{
    for (int k = 0; k < n - 1; k++) {
        
        // Se o pivô for 0, troca por uma linha abaixo
        if (matriz[k][k].num == 0) {
            for (int i = k + 1; i < n; i++) {
                if (matriz[i][k].num != 0) {
                    Fracao *temp = matriz[k];
                    matriz[k] = matriz[i];
                    matriz[i] = temp;
                    break;
                }
            }
        }

        if (matriz[k][k].num == 0) continue;

        for (int i = k + 1; i < n; i++) {
            Fracao fator = dividir(matriz[i][k], matriz[k][k]);
            
            for (int j = k; j <= n; j++) {
                Fracao termo_sub = multiplicar(fator, matriz[k][j]);
                matriz[i][j] = subtrair(matriz[i][j], termo_sub);
            }
        }
    }
}

void imprime_matriz(int n, Fracao **matriz, const char *titulo)
{
    printf("\n--- %s ---\n", titulo);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            imprimir_fracao(matriz[i][j]);
            printf("\t");
        }
        printf("|  ");
        imprimir_fracao(matriz[i][n]);
        printf("\n");
    }
}

void resolver_substituicao_regressiva(int n, Fracao **matriz)
{
    Fracao *solucao = (Fracao *) malloc(n * sizeof(Fracao));
    if (solucao == NULL) return;

    for (int i = n - 1; i >= 0; i--) {
        
        if (matriz[i][i].num == 0) {
            printf("\nO sistema não possui solução única (SPI ou SI).\n");
            free(solucao);
            return;
        }

        Fracao soma = criar_fracao(0, 1);
        for (int j = i + 1; j < n; j++) {
            Fracao prod = multiplicar(matriz[i][j], solucao[j]);
            soma = somar(soma, prod);
        }

        Fracao num_restante = subtrair(matriz[i][n], soma);
        solucao[i] = dividir(num_restante, matriz[i][i]);
    }

    printf("\n--- Solução do Sistema (Exata) ---\n");
    for (int i = 0; i < n; i++) {
        printf("%c = ", obtém_nome_var(i, n));
        imprimir_fracao(solucao[i]);
        printf("\n");
    }

    free(solucao);
}