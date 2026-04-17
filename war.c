// ============================================================================
//         PROJETO WAR ESTRUTURADO - NÍVEL MESTRE (MODULARIZADO)
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Estrutura ---
struct Territorio {
    char nome[30];
    char corExercito[10];
    int numTropas;
};

// ================= PROTÓTIPOS =================
struct Territorio* alocarMapa(int total);
void liberarMemoria(struct Territorio *mapa, char *missao);

void inicializarMapa(struct Territorio *mapa);
void exibirMapa(const struct Territorio *mapa, int total);

void atribuirMissao(char *destino, char *missoes[], int total);
void exibirMissao(const char *missao);
int verificarMissao(char *missao, struct Territorio *mapa, int total);

void atacar(struct Territorio *atk, struct Territorio *def);
void faseDeAtaque(struct Territorio *mapa, int total);

// ================= MAIN =================
int main() {

    srand(time(NULL));

    int total = 5;
    int opcao;

    struct Territorio *mapa = alocarMapa(total);
    char *missaoJogador = malloc(100);

    char *missoes[] = {
        "Destruir o exercito Verde",
        "Conquistar 3 territorios"
    };

    inicializarMapa(mapa);
    atribuirMissao(missaoJogador, missoes, 2);

    exibirMissao(missaoJogador);

    do {
        printf("\n--- MENU DE ACOES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Verificar Missao\n");
        printf("0 - Sair\n");
        printf("Escolha sua acao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                faseDeAtaque(mapa, total);

                if (verificarMissao(missaoJogador, mapa, total)) {
                    printf("\n*** VOCE VENCEU! ***\n");
                    opcao = 0;
                }
                break;

            case 2:
                if (verificarMissao(missaoJogador, mapa, total))
                    printf("Missao cumprida!\n");
                else
                    printf("Missao ainda nao cumprida.\n");
                break;

            case 0:
                printf("Encerrando jogo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador);

    return 0;
}

// ================= IMPLEMENTAÇÕES =================

// --- Alocação ---
struct Territorio* alocarMapa(int total) {
    struct Territorio *mapa = calloc(total, sizeof(struct Territorio));
    if (!mapa) {
        printf("Erro de memoria!\n");
        exit(1);
    }
    return mapa;
}

// --- Liberação ---
void liberarMemoria(struct Territorio *mapa, char *missao) {
    free(mapa);
    free(missao);
}

// --- Inicialização fixa ---
void inicializarMapa(struct Territorio *mapa) {

    strcpy(mapa[0].nome, "Africa");
    strcpy(mapa[0].corExercito, "Azul");
    mapa[0].numTropas = 5;

    strcpy(mapa[1].nome, "America");
    strcpy(mapa[1].corExercito, "Verde");
    mapa[1].numTropas = 3;

    strcpy(mapa[2].nome, "Europa");
    strcpy(mapa[2].corExercito, "Vermelho");
    mapa[2].numTropas = 4;

    strcpy(mapa[3].nome, "Asia");
    strcpy(mapa[3].corExercito, "Verde");
    mapa[3].numTropas = 2;

    strcpy(mapa[4].nome, "Oceania");
    strcpy(mapa[4].corExercito, "Azul");
    mapa[4].numTropas = 6;
}

// --- Exibir mapa ---
void exibirMapa(const struct Territorio *mapa, int total) {
    printf("\n--- MAPA ---\n");
    for (int i = 0; i < total; i++) {
        printf("%d - %s (%s) - Tropas: %d\n",
               i + 1,
               mapa[i].nome,
               mapa[i].corExercito,
               mapa[i].numTropas);
    }
}

// --- Missão ---
void atribuirMissao(char *destino, char *missoes[], int total) {
    strcpy(destino, missoes[rand() % total]);
}

void exibirMissao(const char *missao) {
    printf("\n--- SUA MISSAO (Exercito Azul) ---\n");
    printf("%s\n", missao);
}

// --- Verificação ---
int verificarMissao(char *missao, struct Territorio *mapa, int total) {

    // destruir verde
    if (strstr(missao, "Verde")) {
        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].corExercito, "Verde") == 0)
                return 0;
        }
        return 1;
    }

    // conquistar 3 territórios (azul)
    if (strstr(missao, "3 territorios")) {
        int count = 0;

        for (int i = 0; i < total; i++) {
            if (strcmp(mapa[i].corExercito, "Azul") == 0)
                count++;
        }

        return count >= 3;
    }

    return 0;
}

// --- Ataque ---
void atacar(struct Territorio *atk, struct Territorio *def) {

    int d1 = rand() % 6 + 1;
    int d2 = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Ataque (%s): %d | Defesa (%s): %d\n",
           atk->nome, d1, def->nome, d2);

    if (d1 > d2) {
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        def->numTropas--;
    } else {
        printf("DEFESA VENCEU! O atacante perdeu 1 tropa.\n");
        atk->numTropas--;
    }

    if (def->numTropas <= 0) {
        printf("Territorio conquistado!\n");

        strcpy(def->corExercito, atk->corExercito);
        def->numTropas = 1;
        atk->numTropas--;
    }
}

// --- Fase de ataque ---
void faseDeAtaque(struct Territorio *mapa, int total) {
    int atk, def;

    printf("\n--- FASE DE ATAQUE ---\n");

    exibirMapa(mapa, total);

    printf("\nEscolha o territorio atacante (1 a %d): ", total);
    scanf("%d", &atk);

    printf("Escolha o territorio defensor (1 a %d): ", total);
    scanf("%d", &def);

    atk--;
    def--;

    if (atk < 0 || atk >= total || def < 0 || def >= total) {
        printf("Indice invalido!\n");
        return;
    }

    if (atk == def) {
        printf("Nao pode atacar o mesmo territorio!\n");
        return;
    }

    if (strcmp(mapa[atk].corExercito, mapa[def].corExercito) == 0) {
        printf("Nao pode atacar mesma cor!\n");
        return;
    }

    if (mapa[atk].numTropas <= 1) {
        printf("Tropas insuficientes!\n");
        return;
    }

    atacar(&mapa[atk], &mapa[def]);

    printf("\n--- MAPA ATUALIZADO ---\n");
    exibirMapa(mapa, total);
}