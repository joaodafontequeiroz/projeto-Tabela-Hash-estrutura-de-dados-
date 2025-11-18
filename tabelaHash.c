#include "tabelaHash.h"

// Criamos um usuário "falso" para marcar lugares onde alguém foi removido.
// Isso é necessário para não quebrar a busca linear.
Usuario* ITEM_REMOVIDO; 

// --- FUNÇÕES AUXILIARES ---
unsigned long funcaoValorString(char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) hash = (hash * 33) + c;
    return hash;
}

int funcaoChaveDivisao(unsigned long chave, int M) {
    return (int)(chave % M);
}

// --- GERENCIAMENTO DA TABELA ---

Hash* criaHash(int M) {
    Hash* H = (Hash*)malloc(sizeof(Hash));
    H->M = M;
    H->qtd = 0;
    H->Tabela = (Usuario**)malloc(M * sizeof(Usuario*));
    
    for (int i = 0; i < M; i++) {
        H->Tabela[i] = NULL;
    }

    // Inicializa o marcador de removido apenas uma vez
    if (ITEM_REMOVIDO == NULL) {
        ITEM_REMOVIDO = (Usuario*)malloc(sizeof(Usuario));
        // Apenas para debug, se quiser ver
        strcpy(ITEM_REMOVIDO->username, "###REMOVIDO###"); 
    }

    return H;
}

void liberaHash(Hash* H) {
    if (H == NULL) return;
    for (int i = 0; i < H->M; i++) {
        // Libera se não for NULL e nem o marcador global
        if (H->Tabela[i] != NULL && H->Tabela[i] != ITEM_REMOVIDO) {
            free(H->Tabela[i]);
        }
    }
    free(H->Tabela);
    free(H);
    // Nota: O ITEM_REMOVIDO geralmente é liberado só no final do programa, 
    // mas para simplificar, vamos deixar o sistema operacional limpar ele.
}

int insereHash(Hash* H, char* username, char* senha) {
    // Se a tabela estiver cheia, não dá para inserir na Sondagem Linear
    if (H->qtd == H->M) {
        printf("Erro: Tabela cheia!\n");
        return 0;
    }

    // Verifica se já existe antes de inserir
    if (buscaHash(H, username) != NULL) return 0;

    unsigned long hashNome = funcaoValorString(username);
    int indice = funcaoChaveDivisao(hashNome, H->M);
    
    // LÓGICA DE SONDAGEM LINEAR
    // Enquanto a posição estiver ocupada E não for um item removido...
    while (H->Tabela[indice] != NULL && H->Tabela[indice] != ITEM_REMOVIDO) {
        // Vai para o próximo índice (circular)
        indice = (indice + 1) % H->M;
    }

    // Achamos uma vaga (pode ser NULL ou ITEM_REMOVIDO)
    Usuario* novo = (Usuario*)malloc(sizeof(Usuario));
    strcpy(novo->username, username);
    novo->hash_senha = funcaoValorString(senha); // Hash da senha

    H->Tabela[indice] = novo;
    H->qtd++;
    return 1;
}

Usuario* buscaHash(Hash* H, char* username) {
    unsigned long hashNome = funcaoValorString(username);
    int indice = funcaoChaveDivisao(hashNome, H->M);
    
    int indiceOriginal = indice; // Para evitar loop infinito se não achar

    // Enquanto a posição não for vazia (NULL para a busca)
    while (H->Tabela[indice] != NULL) {
        
        // Se for um usuário válido (não REMOVIDO) e o nome bater
        if (H->Tabela[indice] != ITEM_REMOVIDO) {
            if (strcmp(H->Tabela[indice]->username, username) == 0) {
                return H->Tabela[indice]; // Encontrou
            }
        }

        // Tenta o próximo
        indice = (indice + 1) % H->M; //

        // Se demos a volta completa na tabela, o usuário não existe
        if (indice == indiceOriginal) break;
    }

    return NULL; // Não encontrado
}

int removeHash(Hash* H, char* username) {
    unsigned long hashNome = funcaoValorString(username);
    int indice = funcaoChaveDivisao(hashNome, H->M);
    int indiceOriginal = indice;

    while (H->Tabela[indice] != NULL) {
        if (H->Tabela[indice] != ITEM_REMOVIDO) {
            if (strcmp(H->Tabela[indice]->username, username) == 0) {
                // Encontrou para remover!
                free(H->Tabela[indice]);
                
                // MARCA COMO REMOVIDO (não coloque NULL!)
                H->Tabela[indice] = ITEM_REMOVIDO;
                
                H->qtd--;
                return 1;
            }
        }
        indice = (indice + 1) % H->M;
        if (indice == indiceOriginal) break;
    }
    return 0;
}

void imprimeHash(Hash* H) {
    printf("\n--- TABELA HASH (Sondagem Linear) ---\n");
    for (int i = 0; i < H->M; i++) {
        printf("Indice [%02d]: ", i);
        
        if (H->Tabela[i] == NULL) {
            printf("LIVRE\n");
        } 
        else if (H->Tabela[i] == ITEM_REMOVIDO) {
            printf("X (REMOVIDO)\n"); // Mostra visualmente o marcador
        } 
        else {
            printf("User: %s (HashSenha: %lu)\n", 
                   H->Tabela[i]->username, H->Tabela[i]->hash_senha);
        }
    }
    printf("--------------------------------------\n");
}