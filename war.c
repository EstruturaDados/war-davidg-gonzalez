// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//
// OBJETIVOS:
// - Utilizar alocação dinâmica com calloc/free.
// - Implementar sistema de ataque entre territórios.
// - Utilizar ponteiros para manipulação de dados.
// - Aplicar modularização com funções bem definidas.
// - Garantir legibilidade e organização do código.
//
// ============================================================================

// Inclusão das bibliotecas necessárias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Estrutura de Dados ---
struct Territorio {
    char nome[30];
    char corExercito[10];
    int numTropas;
};

// --- Função utilitária ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- Alocação dinâmica ---
struct Territorio* alocarMapa(int total) {
    struct Territorio *mapa = (struct Territorio*) calloc(total, sizeof(struct Territorio));

    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    return mapa;
}

// --- Liberação de memória ---
void liberarMemoria(struct Territorio *mapa) {
    free(mapa);
}

// --- Exibição ---
void exibirMapa(const struct Territorio *mapa, int total) {
    printf("\n======= MAPA ATUAL =======\n");

    for (int i = 0; i < total; i++) {
        printf("[%d] %s", i, mapa[i].nome);
        printf("Cor: %s", mapa[i].corExercito);
        printf("Tropas: %d\n", mapa[i].numTropas);
        printf("--------------------------\n");
    }
}

// --- Função de Ataque (ATUALIZADA) ---
// Agora: quem vence remove 1 tropa do perdedor
void atacar(struct Territorio *atacante, struct Territorio *defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n======= BATALHA =======\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    // Atacante vence
    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: ATACANTE VENCEU!\n");

        defensor->numTropas--;

        if (defensor->numTropas < 0)
            defensor->numTropas = 0;

    }
    // Defensor vence ou empate
    else {
        printf("Resultado: DEFENSOR VENCEU!\n");

        atacante->numTropas--;

        if (atacante->numTropas < 0)
            atacante->numTropas = 0;
    }

    // Verifica conquista (se defensor zerou tropas)
    if (defensor->numTropas == 0) {
        printf("Território conquistado!\n");

        strcpy(defensor->corExercito, atacante->corExercito);

        // Coloca 1 tropa no território conquistado
        defensor->numTropas = 1;
        atacante->numTropas--;
    }
}

// --- Fase de ataque ---
void faseDeAtaque(struct Territorio *mapa, int total) {
    int atk, def;

    exibirMapa(mapa, total);

    printf("Escolha o território atacante (índice): ");
    scanf("%d", &atk);

    printf("Escolha o território defensor (índice): ");
    scanf("%d", &def);

    limparBufferEntrada();

    // Validações
    if (atk < 0 || atk >= total || def < 0 || def >= total) {
        printf("Índices inválidos!\n");
        return;
    }

    if (atk == def) {
        printf("Não pode atacar o mesmo território!\n");
        return;
    }

    if (strcmp(mapa[atk].corExercito, mapa[def].corExercito) == 0) {
        printf("Não pode atacar territórios da mesma cor!\n");
        return;
    }

    if (mapa[atk].numTropas <= 1) {
        printf("Tropas insuficientes para atacar!\n");
        return;
    }

    atacar(&mapa[atk], &mapa[def]);
}

// --- MAIN ---
int main() {

    srand(time(NULL));

    struct Territorio *mapa;
    int totalTerritorios;
    int opcao;

    printf("==============================\n");
    printf("WAR ESTRUTURADO\n");
    printf("==============================\n");

    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &totalTerritorios);
    limparBufferEntrada();

    mapa = alocarMapa(totalTerritorios);

    // Cadastro
    for (int i = 0; i < totalTerritorios; i++) {
        printf("\nTerritório %d\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);

        printf("Cor do exército: ");
        fgets(mapa[i].corExercito, 10, stdin);

        printf("Número de tropas: ");
        scanf("%d", &mapa[i].numTropas);
        limparBufferEntrada();
    }

    // Loop principal
    do {
        printf("\n======= MENU =======\n");
        printf("1 - Atacar\n");
        printf("2 - Exibir mapa\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                faseDeAtaque(mapa, totalTerritorios);
                break;

            case 2:
                exibirMapa(mapa, totalTerritorios);
                break;

            case 0:
                printf("Encerrando jogo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);

    return 0;
}