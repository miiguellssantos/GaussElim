# 🧮 Solucionador de Sistemas de Equações Lineares em C

Projetado para a disciplina de **Álgebra Linear** do curso de **Ciência da Computação** — **UFF Rio das Ostras** (Período 2026.2).

Este programa em C lê equações lineares diretamente em formato de texto (string), faz o parsing dos coeficientes e das variáveis de forma dinâmica, monta a matriz aumentada, executa o escalonamento (Eliminação de Gauss) e resolve o sistema via substituição regressiva.

---

## 📁 Estrutura do Projeto

.
├── main.c
├── Makefile
└── libs/
    ├── funcoes.c
    └── funcoes.h

| Arquivo | Descrição |
| :--- | :--- |
| **main.c** | Ponto de entrada, alocação de memória dinâmica e fluxo principal do programa. |
| **libs/funcoes.c** | Implementação do parser de strings, manipulação de matrizes e algoritmos numéricos. |
| **libs/funcoes.h** | Protótipos das funções e definições de cabeçalho. |
| **Makefile** | Automação da compilação e limpeza do projeto. |

---

## 🚀 Funcionalidades

* **Parsing de Equações:** Aceita equações formatadas como `3x - 2y + 3z = 10` ou `3y = 8` sem necessidade de passar coeficientes isolados.
* **Mapeamento de Variáveis Omitidas:** Preenche automaticamente com `0.0` as colunas de variáveis ausentes.
* **Alocação Dinâmica:** Gerenciamento seguro de memória via `malloc` e `free`.
* **Suporte Multi-Variáveis:** Mapeamento dinâmico ajustado à dimensão do sistema ($x, y, z$ para $3\times3$, $w, x, y, z$ para $4\times4$, etc.).
* **Eliminação de Gauss:** Algoritmo numérico para transformar a matriz na Forma Escalonada por Linhas.
* **Substituição Regressiva:** Resolução do sistema triangular superior com exibição dos valores finais de cada variável.

---

## 💻 Como Compilar e Executar

### Utilizando o Makefile (Recomendado)

Para compilar o projeto:
`make`

Para executar o programa:
* **Windows:** `.\main.exe`
* **Linux / MacOS:** `./main`

Para limpar os arquivos objetos e executáveis gerados:
`make clean`

### Compilação Manual via GCC

`gcc main.c libs/funcoes.c -Ilibs -o main -lm`

---

## 📝 Exemplo de Execução

**Entrada:**
Quantas equações serão digitadas? 3

Digite a equação 1: 3x - 2y + 3z = 10
Digite a equação 2: 3y = 8
Digite a equação 3: 4x + 5y - z = 5

**Saída Gerada:**
Matriz Aumentada Resultante:
3.00    -2.00   3.00      10.00
0.00    3.00    0.00      8.00
4.00    5.00    -1.00     5.00

--- Matriz Escalonada ---
3.00    -2.00   3.00    |  10.00
0.00    3.00    0.00    |  8.00
0.00    0.00    -5.00   |  -28.78

--- Solução do Sistema ---
x = -0.64
y = 2.67
z = 5.76

---

## 🎓 Autor e Instituição

* **Instituição:** Universidade Federal Fluminense (UFF) — Campus Rio das Ostras (CCT)
* **Curso:** Bacharelado em Ciência da Computação
* **Disciplina:** Álgebra Linear (2026.2)
* **Autor:** Miguel Lordello dos Santos
