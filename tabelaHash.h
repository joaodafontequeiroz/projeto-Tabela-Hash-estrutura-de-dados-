#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. ESTRUTURA DO USUÁRIO
typedef struct Usuario {
    char username[51];
    unsigned long hash_senha;
} Usuario;

// 2. ESTRUTURA DA TABELA HASH
typedef struct Hash {
    int M;              // Tamanho da tabela
    int qtd;            // Quantidade de itens (para saber se encheu)
    Usuario** Tabela;   // Array de ponteiros para Usuario
} Hash;

// Protótipos
Hash* criaHash(int M);
void liberaHash(Hash* H);
int insereHash(Hash* H, char* username, char* senha);
Usuario* buscaHash(Hash* H, char* username);
int removeHash(Hash* H, char* username);
void imprimeHash(Hash* H);

// Funções auxiliares
unsigned long funcaoValorString(char* str);
int funcaoChaveDivisao(unsigned long chave, int M);
