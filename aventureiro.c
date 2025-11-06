#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_TERRITORIOS 5

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funções
Territorio* cadastrarTerritorios();
void exibirMapa(Territorio* mapa);
void simularAtaque(Territorio* mapa, int atacante, int defensor);

int main() {
    srand(time(NULL)); // inicializa aleatoriedade

    // Alocação dinâmica
    Territorio* mapa = calloc(NUM_TERRITORIOS, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro inicial
    mapa = cadastrarTerritorios();

    int opcao, atacante, defensor;
    do {
        exibirMapa(mapa);

        printf("1 - Atacar\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("Escolha o território atacante (1-5): ");
            scanf("%d", &atacante);
            printf("Escolha o território defensor (1-5): ");
            scanf("%d", &defensor);

            simularAtaque(mapa, atacante - 1, defensor - 1);
        }

    } while (opcao != 0);

    free(mapa); // libera memória
    return 0;
}

// Cadastro dos territórios
Territorio* cadastrarTerritorios() {
    Territorio* mapa = calloc(NUM_TERRITORIOS, sizeof(Territorio));
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("\nTerritório %d:\n", i + 1);

        printf("Nome: ");
        getchar(); // limpa buffer
        fgets(mapa[i].nome, sizeof(mapa[i].nome), stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do exército: ");
        fgets(mapa[i].cor, sizeof(mapa[i].cor), stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
    return mapa;
}

// Exibição do mapa
void exibirMapa(Territorio* mapa) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);
        printf("Nome: %s | Cor: %s | Tropas: %d\n\n",
               mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simulação de ataque
void simularAtaque(Territorio* mapa, int atacante, int defensor) {
    if (mapa[atacante].tropas <= 0) {
        printf("O território atacante não possui tropas!\n");
        return;
    }
    if (mapa[defensor].tropas <= 0) {
        printf("O território defensor já foi conquistado!\n");
        return;
    }

    int dadoAtq = rand() % 6 + 1; // dado de 1 a 6
    int dadoDef = rand() % 6 + 1;

    printf("\nAtaque de %s (%d tropas) contra %s (%d tropas)\n",
           mapa[atacante].nome, mapa[atacante].tropas,
           mapa[defensor].nome, mapa[defensor].tropas);

    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);

    if (dadoAtq >= dadoDef) {
        mapa[defensor].tropas--;
        printf("Defensor perdeu 1 tropa!\n");
        if (mapa[defensor].tropas <= 0) {
            printf("🎉 %s conquistou o território %s!\n",
                   mapa[atacante].cor, mapa[defensor].nome);
        }
    } else {
        mapa[atacante].tropas--;
        printf("Atacante perdeu 1 tropa!\n");
    }
}

