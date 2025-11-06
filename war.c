#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define NUM_TERRITORIOS 5
#define TAM_NOME 30
#define TAM_COR 10

typedef struct {
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
} Territorio;

// Protótipos
Territorio* inicializarMapa();
void exibirMapa(const Territorio* mapa);
void exibirMenu();
void simularAtaque(Territorio* mapa, int atacante, int defensor);
int sortearMissao();
void exibirMissao(int idMissao);
int verificarMissao(const Territorio* mapa, const char* corJogador, int idMissao);
void limparBufferEntrada();

int main() {
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    Territorio* mapa = inicializarMapa();
    char corJogador[TAM_COR] = "Verde"; // jogador fixo
    int idMissao = sortearMissao();
    int opcao, venceu = 0;

    do {
        exibirMapa(mapa);
        exibirMissao(idMissao);
        exibirMenu();

        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1: {
                int atacante, defensor;
                printf("Território atacante (1-5): ");
                scanf("%d", &atacante);
                printf("Território defensor (1-5): ");
                scanf("%d", &defensor);
                simularAtaque(mapa, atacante - 1, defensor - 1);
                break;
            }
            case 2:
                venceu = verificarMissao(mapa, corJogador, idMissao);
                if (venceu)
                    printf("🎉 Missão cumprida! Você venceu!\n");
                else
                    printf("🚧 Missão ainda não cumprida.\n");
                break;
            case 0:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0 && !venceu);

    free(mapa);
    return 0;
}

// Funções
Territorio* inicializarMapa() {
    Territorio* mapa = calloc(NUM_TERRITORIOS, sizeof(Territorio));
    strcpy(mapa[0].nome, "America"); strcpy(mapa[0].cor, "Azul"); mapa[0].tropas = 3;
    strcpy(mapa[1].nome, "Europa"); strcpy(mapa[1].cor, "Vermelho"); mapa[1].tropas = 5;
    strcpy(mapa[2].nome, "África"); strcpy(mapa[2].cor, "Marrom"); mapa[2].tropas = 4;
    strcpy(mapa[3].nome, "Ásia"); strcpy(mapa[3].cor, "Amarelo"); mapa[3].tropas = 2;
    strcpy(mapa[4].nome, "Oceania"); strcpy(mapa[4].cor, "Verde"); mapa[4].tropas = 6;
    return mapa;
}

void exibirMapa(const Territorio* mapa) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d - %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

void exibirMenu() {
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
}

void simularAtaque(Territorio* mapa, int atacante, int defensor) {
    if (mapa[atacante].tropas <= 0 || mapa[defensor].tropas <= 0) {
        printf("Ataque inválido!\n");
        return;
    }
    int dadoAtq = rand() % 6 + 1;
    int dadoDef = rand() % 6 + 1;

    printf("\nAtaque de %s contra %s\n", mapa[atacante].nome, mapa[defensor].nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoAtq, dadoDef);

    if (dadoAtq >= dadoDef) {
        mapa[defensor].tropas--;
        printf("Defensor perdeu 1 tropa!\n");
        if (mapa[defensor].tropas <= 0) {
            strcpy(mapa[defensor].cor, mapa[atacante].cor);
            printf("🎉 Território %s foi conquistado!\n", mapa[defensor].nome);
        }
    } else {
        mapa[atacante].tropas--;
        printf("Atacante perdeu 1 tropa!\n");
    }
}

int sortearMissao() {
    return rand() % 2; // 0 ou 1
}

void exibirMissao(int idMissao) {
    printf("=== Missão Atual ===\n");
    if (idMissao == 0)
        printf("Conquistar 3 territórios.\n");
    else
        printf("Destruir o exército Verde.\n");
}

int verificarMissao(const Territorio* mapa, const char* corJogador, int idMissao) {
    if (idMissao == 0) {
        int conquistados = 0;
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0)
                conquistados++;
        }
        return conquistados >= 3;
    } else {
        for (int i = 0; i < NUM_TERRITORIOS; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
