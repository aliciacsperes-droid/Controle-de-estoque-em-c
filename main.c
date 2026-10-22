#include <stdio.h>
#include <string.h>

int main() {
    FILE *f = fopen("inventory.txt", "r");
    if (f == NULL) {
        printf("O estoque está vazio.\n");
        return 0;
    }
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0) {
        printf("O estoque está vazio.\n");
        fclose(f);
        return 0;
    }
    fseek(f, 0, SEEK_SET);
    char nome[100];
    int qtd;
    char nomes[100][100];
    int qtds[100];
    int total = 0;
    while (fscanf(f, " %99[^\n]\n%d\n", nome, &qtd) == 2) {
        strcpy(nomes[total], nome);
        qtds[total] = qtd;
        total++;
    }
    fclose(f);
    if (total == 0) {
        printf("O estoque está vazio.\n");
    } else {
        printf("===============================\n");
        printf("Estoque Atual\n");
        printf("===============================\n");
        for (int i = 0; i < total; i++) {
            printf("Nome: %s\n", nomes[i]);
            printf("Quantidade: %d\n", qtds[i]);
            if (i < total - 1) printf("\n");
        }
    }
    printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
    return 0;
}
