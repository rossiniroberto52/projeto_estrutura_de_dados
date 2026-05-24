// obrigatorias: criarHash, isereHash, removeHash, liberaHash, imprimeHash

//16(tam_senha)*2 = 32 primo mais proximo = 31

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define TAM_HASH 31
#define TAM_STR 32


typedef struct {
    int status;
    char username[TAM_STR];
    char crypt_password[TAM_STR];
} user;

int funcHash(int chave){
    return chave % TAM_HASH;
}

int hash2(int chave){
    return 17 - (chave % 17);
}

int valorString(char string[TAM_STR]){
    int valor = 0;
    for(int i = 0; string[i] != '\0'; i++){
        valor = (valor * 37) + string[i];
    }
    return valor;
}

user* criarHash(){
    user* hash = (user*)malloc(TAM_HASH * sizeof(user));
    if(hash != NULL){
        for(int i = 0; i < TAM_HASH; i++){
            hash[i].status = 0;
        }

        return hash;
    }
    return NULL;
}

int insereHash(user* tabela, char* username_digitado, char* senha_hash_digitada){
    int chave = valorString(username_digitado);
    int indice = funcHash(chave);
    int salto = hash2(chave);
    int tentativas = 0; 

    
    while(tabela[indice].status != 0){ 
        if(strcmp(tabela[indice].username, username_digitado) == 0){
            return -1;
        }
        indice += salto;
        indice = (indice%TAM_HASH);
        tentativas++;
        
        if(tentativas == TAM_HASH){
            return 0;
        }
    }
    tabela[indice].status = 1;
    strcpy(tabela[indice].username, username_digitado);
    strcpy(tabela[indice].crypt_password, senha_hash_digitada);
    return 1;
}

int buscaHash(user* tabela, char* username_digitado, char* senha_hash_digitada){
    int chave = valorString(username_digitado);
    int indice = funcHash(chave);
    int salto = hash2(chave);
    int tentativas = 0;

    while(tabela[indice].status != 0){ 
        if(tabela[indice].status == 1 && strcmp(tabela[indice].username, username_digitado) == 0){
            if(strcmp(tabela[indice].crypt_password, senha_hash_digitada) == 0){
                return 1;
            }
            return 0;
        }
        indice += salto;
        indice = (indice % TAM_HASH);
        tentativas++;

        if(tentativas == TAM_HASH){
            return 0; 
        }
    }
    return 0;
}

int removeHash(user* tabela, char* username_digitado){
    int chave = valorString(username_digitado);
    int indice = funcHash(chave);
    int salto = hash2(chave);
    int tentativas = 0;

    while(tabela[indice].status == 1){ 
        if(tabela[indice].status == 1 && strcmp(tabela[indice].username, username_digitado) == 0){
            tabela[indice].status = 2;
            return 1;
        }
        indice += salto;
        indice = (indice % TAM_HASH);
        tentativas++;

        if(tentativas == TAM_HASH){
            return 0; 
        }
    }
    return 0;
}

void liberaHash(user* tabela){
    free(tabela);
}

void imprimeHash(user* tabela){
    for(int i=0; i<TAM_HASH;i++){
        if(tabela[i].status == 0){
            printf("[Indice: %d] - vazio\n", i);
        }else if(tabela[i].status == 1){
            printf("[Indice: %d] - Usuario: %s | Hash: %s\n", i, tabela[i].username, tabela[i].crypt_password);
        }else if(tabela[i].status == 2){
            printf("[Indice: %d] - Removido(lapide)\n", i);
        }
    }
}