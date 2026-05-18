#include <stdio.h>
#define TAM 31

struct payload{
    char *nome;
    char *password_hashed;
};

int main(){
    int opc;
    printf("===============================================\n");
    printf("==== (1) novo usuario                      ====\n");
    printf("==== (2) login                             ====\n");
    printf("===============================================\n");
    fgets(opc, sizeof(opc), stdin);
} 