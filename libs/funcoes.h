#ifndef FUNCOES_H
#define FUNCOES_H

typedef struct {
    long long num;
    long long den;
} Fracao;

Fracao criar_fracao(long long num, long long den);
Fracao somar(Fracao a, Fracao b);
Fracao subtrair(Fracao a, Fracao b);
Fracao multiplicar(Fracao a, Fracao b);
Fracao dividir(Fracao a, Fracao b);
void imprimir_fracao(Fracao f);

int obtém_indice_var(char c, int n);
char obtém_nome_var(int index, int n);
Fracao *identifica_numeros(const char *equacao, int n);
void scan_equacao(int n, Fracao **matriz);
void escalonar_matriz(int n, Fracao **matriz);
void imprime_matriz(int n, Fracao **matriz, const char *titulo);
void resolver_substituicao_regressiva(int n, Fracao **matriz);

#endif