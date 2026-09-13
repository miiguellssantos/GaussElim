#pragma once 

double *identifica_numeros(const char *equacao, int n);
void scan_equacao(int n, double **matriz);
void escalonar_matriz(int n, double **matriz);
void imprime_matriz(int n, double **matriz, const char *titulo);
void resolver_substituicao_regressiva(int n, double **matriz);