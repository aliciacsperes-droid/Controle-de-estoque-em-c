#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARQUIVO "inventory.txt"

void listar() {
    FILE *f = fopen(ARQUIVO, "r");
    if (f == NULL) {
        printf("O estoque esta vazio.\n");
        return;
    }
    fseek(f, 0, SEEK_END);
    if (ftell(f) == 0) {
        printf("O estoque esta vazio.\n");
        fclose(f);
        return;
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
        printf("O estoque esta vazio.\n");
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
}

int main() {
    int opcao;
    char nome[100];
    int qtd;
    
    while (1) {
        printf("\n=== Controle de Estoque ===\n");
        printf("1. Cadastrar item\n");
        printf("2. Retirar item\n");
        printf("3. Listar estoque\n");
        printf("4. Sair\n");
        printf("Escolha uma opcao: ");
        if (scanf("%d", &opcao) != 1) {
            printf("Opcao invalida!\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        if (opcao == 1) {
            printf("Nome do item: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("Quantidade: ");
            scanf("%d", &qtd);
            getchar();
            FILE *f = fopen(ARQUIVO, "a");
            fprintf(f, "%s\n%d\n", nome, qtd);
            fclose(f);
            printf("Item cadastrado com sucesso!\n");
        }
        else if (opcao == 2) {
            printf("Nome do item para retirar: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = 0;
            printf("Quantidade para retirar: ");
            scanf("%d", &qtd);
            getchar();
            
            FILE *f = fopen(ARQUIVO, "r");
            if (f == NULL) {
                printf("O estoque esta vazio.\n");
                continue;
            }
            char nomes[100][100];
            int qtds[100];
            int total = 0;
            char tempNome[100];
            int tempQtd;
            while (fscanf(f, " %99[^\n]\n%d\n", tempNome, &tempQtd) == 2) {
                strcpy(nomes[total], tempNome);
                qtds[total] = tempQtd;
                total++;
            }
            fclose(f);
            
            int achou = 0;
            for (int i = 0; i < total; i++) {
                if (strcmp(nomes[i], nome) == 0) {
                    qtds[i] -= qtd;
                    if (qtds[i] < 0) qtds[i] = 0;
                    achou = 1;
                    break;
                }
            }
            if (!achou) {
                printf("Item nao encontrado!\n");
                continue;
            }
            f = fopen(ARQUIVO, "w");
            for (int i = 0; i < total; i++) {
                fprintf(f, "%s\n%d\n", nomes[i], qtds[i]);
            }
            fclose(f);
            printf("Retirada realizada!\n");
        }
        else if (opcao == 3) {
            listar();
        }
        else if (opcao == 4) {
            printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
            break;
        }
        else {
            printf("Opcao invalida!\n");
        }
    }
    return 0;
}
