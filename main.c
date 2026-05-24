#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"

int main(){
    user* tabela = criarHash();
    if(tabela == NULL) {
        printf("Erro fatal: Sem memoria.\n");
        return 1;
    }

    int logado = 0;

    int opc = 0;
    
    while(opc != 9) { 
        printf("\n===============================================\n");
        printf("==== (1) Novo Usuario                      ====\n");
        printf("==== (2) Login                             ====\n");
        printf("==== (3) Remover Usuario                   ====\n");
        printf("==== (4) Imprimir Tabela                   ====\n");
        printf("==== (9) Sair                              ====\n");
        printf("===============================================\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        if(opc == 1) {
            char senha_limpa[TAM_STR];
            char username[TAM_STR];
            char senha_convertida[TAM_STR];

            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", senha_limpa);
            int hash_num = valorString(senha_limpa);
            
            sprintf(senha_convertida, "%d", hash_num);
            memset(senha_limpa, 0, TAM_STR);

            int resultado = insereHash(tabela, username, senha_convertida);

            if(resultado == 1){
                printf("Usuario cadastrado com sucesso!\n");
            } else if (resultado == -1){
                printf("Erro: Usuario ja existe.\n");
            } else {
                printf("Erro: Tabela cheia.\n");
            }
        } 
        else if (opc == 2) {
            char senha_limpa[TAM_STR];
            char username[TAM_STR];
            char senha_convertida[TAM_STR];

            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", senha_limpa);
            int hash_num = valorString(senha_limpa);

            sprintf(senha_convertida, "%d", hash_num);
            memset(senha_limpa, 0, TAM_STR);

            int resultado = buscaHash(tabela, username, senha_convertida);

            if(resultado == 1){
                printf("User: %s, logado com sucesso\n", username);
                logado = 1;
            }else{
                printf("credenciais invalidas\n");
            }
        }
        else if(opc == 3){
            
            if(logado == 1){
                char username_alvo[TAM_STR];
                printf("Username a ser deletado: ");
                scanf("%s", username_alvo);
                int resultado = removeHash(tabela, username_alvo);

                if(resultado == 1){
                    printf("Usuario %s deletado com sucesso.\n", username_alvo);
                    logado = 0;
                }else{
                    printf("Erro: Usuario nao encontrado.\n");
                }
            }else{
                printf("Erro: Acesso negado. Faca login primeiro.\n");
            }
        }
        else if (opc == 4) {
            imprimeHash(tabela);
        }
    }

    liberaHash(tabela);
    return 0;
}