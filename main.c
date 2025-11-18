#include <stdio.h>
#include "tabelaHash.h"

#define TAMANHO_TAB 17

int main() {
    
    Hash* tabela = criaHash(TAMANHO_TAB);
    int op = 0;
    char user[51], pass[51];

    printf("=== HashGuard System (Sondagem Linear) ===\n");

    while (op != 5) {
        printf("\n1. Cadastrar | 2. Login | 3. Remover | 4. Ver Tabela | 5. Sair\nOpcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                printf("User: "); scanf("%s", user);
                printf("Pass: "); scanf("%s", pass);
                if (insereHash(tabela, user, pass)) printf("Sucesso!\n");
                else printf("Erro: Tabela cheia ou usuario duplicado.\n");
                break;
            case 2:
                printf("User: "); scanf("%s", user);
                printf("Pass: "); scanf("%s", pass);
                Usuario* u = buscaHash(tabela, user);
                if (u && u->hash_senha == funcaoValorString(pass))
                    printf("LOGIN OK!\n");
                else printf("Login Falhou.\n");
                break;
            case 3:
                printf("User para remover: "); scanf("%s", user);
                if (removeHash(tabela, user)) printf("Removido!\n");
                else printf("Nao encontrado.\n");
                break;
            case 4:
                imprimeHash(tabela);
                break;
            case 5: printf("Sistema encerrado.\n"); break;
        }
    }
    liberaHash(tabela);
    return 0;
}