#include <stdio.h>
#include <string.h>

// Definindo a estrutura Territorio
typedef struct {
    char nome[30];       // Nome do território
    char cor[10];        // Cor do exército
    int tropas;          // Número de tropas
} Territorio;

int main() {
    Territorio mapa[5];  // Vetor estático com 5 territórios

    printf("=== Cadastro de Territórios ===\n");

    // Entrada de dados
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // Remove o '\n'

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // Limpa o buffer do teclado
    }

    // Exibição dos dados
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do exército: %s\n", mapa[i].cor);
        printf("Tropas: %d\n\n", mapa[i].tropas);
    }

    return 0;
}
