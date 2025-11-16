#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definição da Estrutura da Sala (Nó da Árvore) ---
typedef struct Sala {
    char nome[50];         // Nome do cômodo
    struct Sala *esquerda; // Ponteiro para o cômodo à esquerda
    struct Sala *direita;  // Ponteiro para o cômodo à direita
} Sala;

// --- Protótipos das Funções ---
Sala* criarSala(const char *nome);
void montarMapa(Sala **raiz);
void explorarSalas(Sala *atual);
void liberarMapa(Sala *raiz);

// -------------------------------------------------------------------
// ---------------------- FUNÇÕES DE LÓGICA --------------------------
// -------------------------------------------------------------------

/**
 * @brief Cria e aloca dinamicamente uma nova Sala (nó da árvore).
 * * @param nome O nome do cômodo.
 * @return Sala*: Ponteiro para a nova sala criada.
 */
Sala* criarSala(const char *nome) {
    // Aloca memória para a nova sala
    Sala *novaSala = (Sala*)malloc(sizeof(Sala));
    
    if (novaSala == NULL) {
        printf("[ERRO]: Falha na alocação de memória para a sala '%s'.\n", nome);
        exit(1); // Encerra o programa em caso de falha crítica
    }
    
    // Copia o nome para o campo 'nome' da estrutura
    strncpy(novaSala->nome, nome, 49);
    novaSala->nome[49] = '\0'; // Garante o terminador de string
    
    // Inicializa os ponteiros dos filhos como NULL (sem caminhos)
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Monta a estrutura da árvore binária (mapa) da mansão.
 * * @param raiz Ponteiro para o ponteiro da raiz da árvore.
 */
void montarMapa(Sala **raiz) {
    // Nível 0 (Raiz)
    *raiz = criarSala("Hall de Entrada");

    // Nível 1
    Sala *cozinha = criarSala("Cozinha");
    Sala *salaEstar = criarSala("Sala de Estar");
    (*raiz)->esquerda = cozinha;
    (*raiz)->direita = salaEstar;

    // Nível 2
    cozinha->esquerda = criarSala("Despensa"); // Nó Folha
    
    Sala *biblioteca = criarSala("Biblioteca");
    cozinha->direita = biblioteca;
    
    Sala *jardim = criarSala("Jardim");
    salaEstar->esquerda = jardim; // Nó Folha
    
    Sala *escritorio = criarSala("Escritório");
    salaEstar->direita = escritorio;

    // Nível 3 (Nós Folha)
    biblioteca->esquerda = criarSala("Sala Secreta");
    biblioteca->direita = NULL; // Caminho Inexistente
    
    escritorio->esquerda = criarSala("Porão");
    escritorio->direita = criarSala("Quarto Principal");
}

/**
 * @brief Libera a memória alocada dinamicamente para a árvore.
 * * @param raiz O nó raiz da árvore (ou subárvore).
 */
void liberarMapa(Sala *raiz) {
    if (raiz != NULL) {
        // Post-order traversal para liberar primeiro os filhos
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        free(raiz);
    }
}


// -------------------------------------------------------------------
// -------------------- FUNÇÃO DE EXPLORAÇÃO -------------------------
// -------------------------------------------------------------------

/**
 * @brief Permite a navegação interativa do jogador pela árvore.
 * * @param atual A sala atual onde o jogador se encontra.
 */
void explorarSalas(Sala *atual) {
    char escolha;
    
    printf("\n--- INÍCIO DA EXPLORAÇÃO ---\n");
    
    // O loop continua enquanto o jogador não sair ou não atingir um nó-folha
    while (atual != NULL) {
        printf("\nVocê está em: **%s**\n", atual->nome);
        
        // Verifica se é um nó-folha (não tem caminhos à esquerda nem à direita)
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("\n[FIM DA LINHA] 🛑 Esta sala não possui mais caminhos.\n");
            break; 
        }

        // --- Opções de Navegação ---
        printf("Caminhos disponíveis:\n");
        if (atual->esquerda != NULL) {
            printf("  (E)squerda: %s\n", atual->esquerda->nome);
        }
        if (atual->direita != NULL) {
            printf("  (D)ireita: %s\n", atual->direita->nome);
        }
        printf("  (S)air da Mansão\n");
        
        printf("Escolha o caminho (e/d/s): ");
        
        // Lendo a escolha do jogador
        if (scanf(" %c", &escolha) != 1) {
            printf("\n[AVISO]: Entrada inválida. Tente novamente.\n");
            // Limpa o buffer de entrada
            while (getchar() != '\n'); 
            continue;
        }
        
        // Converte para minúsculo para facilitar a validação
        if (escolha >= 'A' && escolha <= 'Z') {
            escolha = escolha + ('a' - 'A');
        }

        // --- Processa a Escolha ---
        if (escolha == 'e') {
            if (atual->esquerda != NULL) {
                printf(">> Você seguiu para a Esquerda.\n");
                atual = atual->esquerda; // Move para a esquerda
            } else {
                printf("[AVISO]: Não há caminho para a Esquerda nesta sala.\n");
            }
        } else if (escolha == 'd') {
            if (atual->direita != NULL) {
                printf(">> Você seguiu para a Direita.\n");
                atual = atual->direita; // Move para a direita
            } else {
                printf("[AVISO]: Não há caminho para a Direita nesta sala.\n");
            }
        } else if (escolha == 's') {
            printf("\n>> 🚪 Você decidiu sair da mansão. Exploração encerrada.\n");
            break;
        } else {
            printf("[AVISO]: Opção inválida. Use 'e' (esquerda), 'd' (direita) ou 's' (sair).\n");
        }
    }
}

// -------------------------------------------------------------------
// ------------------------- FUNÇÃO PRINCIPAL ------------------------
// -------------------------------------------------------------------

int main() {
    Sala *mapaRaiz = NULL; // Ponteiro inicial para o mapa (Hall de Entrada)

    // 1. Monta o Mapa (Árvore Binária)
    printf(">> 🗺️ Montando o mapa da Mansão Enigma Studios...\n");
    montarMapa(&mapaRaiz);
    printf(">> ✅ Mapa montado com sucesso. O Hall de Entrada está pronto.\n");

    // 2. Inicia a Exploração
    if (mapaRaiz != NULL) {
        explorarSalas(mapaRaiz);
    } else {
        printf("[ERRO CRÍTICO]: A raiz do mapa não foi criada. Exploracão impossível.\n");
    }

    // 3. Libera a memória alocada
    liberarMapa(mapaRaiz);
    printf("\n>> 🧹 Memória da mansão liberada.\n");

    return 0;
}